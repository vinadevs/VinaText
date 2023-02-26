/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#include "stdafx.h"
#include <bitset>
#include "TextFormatConverter.h"
#include "AppUtil.h"
#include "StringHelper.h"
#include "checksum\md5.h"
#include "checksum\sha-256.h"
#include "boost\crc.hpp"
#include "boost\uuid\sha1.hpp"

//
// Depending on the url parameter in base64_chars, one of
// two sets of base64 characters needs to be chosen.
// They differ in their last two characters.
//
static const char* base64_chars[2] = {
	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789"
	"+/",

	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
	"abcdefghijklmnopqrstuvwxyz"
	"0123456789"
	"-_" };

static unsigned int pos_of_char(const unsigned char chr) {
	//
	// Return the position of chr within base64_encode()
	//

	if (chr >= 'A' && chr <= 'Z') return chr - 'A';
	else if (chr >= 'a' && chr <= 'z') return chr - 'a' + ('Z' - 'A') + 1;
	else if (chr >= '0' && chr <= '9') return chr - '0' + ('Z' - 'A') + ('z' - 'a') + 2;
	else if (chr == '+' || chr == '-') return 62; // Be liberal with input and accept both url ('-') and non-url ('+') base 64 characters (
	else if (chr == '/' || chr == '_') return 63; // Ditto for '/' and '_'
	else
		//
		// 2020-10-23: Throw std::exception rather than const char*
		//(Pablo Martin-Gomez, https://github.com/Bouska)
		//
		LOG_OUTPUT_MESSAGE_COLOR(_T("> [Base64 Converter] Input text is not valid base64-encoded data."), BasicColors::orange); return 0;
}

static std::string insert_linebreaks(std::string str, size_t distance) {
	//
	// Provided by https://github.com/JomaCorpFX, adapted by me.
	//
	if (!str.length()) {
		return "";
	}

	size_t pos = distance;

	while (pos < str.size()) {
		str.insert(pos, "\n");
		pos += distance + 1;
	}

	return str;
}

template <typename String, unsigned int line_length>
static std::string encode_with_line_breaks(String s) {
	return insert_linebreaks(base64_encode(s, false), line_length);
}

template <typename String>
static std::string encode_pem(String s) {
	return encode_with_line_breaks<String, 64>(s);
}

template <typename String>
static std::string encode_mime(String s) {
	return encode_with_line_breaks<String, 76>(s);
}

template <typename String>
static std::string encode(String s, bool url) {
	return base64_encode(reinterpret_cast<const unsigned char*>(s.data()), s.length(), url);
}

std::string base64_encode(unsigned char const* bytes_to_encode, size_t in_len, bool url) {

	size_t len_encoded = (in_len + 2) / 3 * 4;

	unsigned char trailing_char = url ? '.' : '=';

	//
	// Choose set of base64 characters. They differ
	// for the last two positions, depending on the url
	// parameter.
	// A bool (as is the parameter url) is guaranteed
	// to evaluate to either 0 or 1 in C++ therefore,
	// the correct character set is chosen by subscripting
	// base64_chars with url.
	//
	const char* base64_chars_ = base64_chars[url];

	std::string ret;
	ret.reserve(len_encoded);

	unsigned int pos = 0;

	while (pos < in_len) {
		ret.push_back(base64_chars_[(bytes_to_encode[pos + 0] & 0xfc) >> 2]);

		if (pos + 1 < in_len) {
			ret.push_back(base64_chars_[((bytes_to_encode[pos + 0] & 0x03) << 4) + ((bytes_to_encode[pos + 1] & 0xf0) >> 4)]);

			if (pos + 2 < in_len) {
				ret.push_back(base64_chars_[((bytes_to_encode[pos + 1] & 0x0f) << 2) + ((bytes_to_encode[pos + 2] & 0xc0) >> 6)]);
				ret.push_back(base64_chars_[bytes_to_encode[pos + 2] & 0x3f]);
			}
			else {
				ret.push_back(base64_chars_[(bytes_to_encode[pos + 1] & 0x0f) << 2]);
				ret.push_back(trailing_char);
			}
		}
		else {

			ret.push_back(base64_chars_[(bytes_to_encode[pos + 0] & 0x03) << 4]);
			ret.push_back(trailing_char);
			ret.push_back(trailing_char);
		}

		pos += 3;
	}

	return ret;
}

template <typename String>
static std::string decode(String encoded_string, bool remove_linebreaks) {
	//
	// decode(…) is templated so that it can be used with String = const std::string&
	// or std::string_view (requires at least C++17)
	//

	if (encoded_string.empty()) return std::string();

	if (remove_linebreaks) {

		std::string copy(encoded_string);

		copy.erase(std::remove(copy.begin(), copy.end(), '\n'), copy.end());

		return base64_decode(copy, false);
	}

	size_t length_of_string = encoded_string.length();
	size_t pos = 0;

	//
	// The approximate length (bytes) of the decoded string might be one or
	// two bytes smaller, depending on the amount of trailing equal signs
	// in the encoded string. This approximation is needed to reserve
	// enough space in the string to be returned.
	//
	size_t approx_length_of_decoded_string = length_of_string / 4 * 3;
	std::string ret;
	ret.reserve(approx_length_of_decoded_string);

	while (pos < length_of_string) {

		unsigned int pos_of_char_1 = pos_of_char(encoded_string[pos + 1]);

		ret.push_back(static_cast<std::string::value_type>(((pos_of_char(encoded_string[pos + 0])) << 2) + ((pos_of_char_1 & 0x30) >> 4)));

		if (encoded_string[pos + 2] != '=' && encoded_string[pos + 2] != '.') { // accept URL-safe base 64 strings, too, so check for '.' also.

			unsigned int pos_of_char_2 = pos_of_char(encoded_string[pos + 2]);
			ret.push_back(static_cast<std::string::value_type>(((pos_of_char_1 & 0x0f) << 4) + ((pos_of_char_2 & 0x3c) >> 2)));

			if (encoded_string[pos + 3] != '=' && encoded_string[pos + 3] != '.') {
				ret.push_back(static_cast<std::string::value_type>(((pos_of_char_2 & 0x03) << 6) + pos_of_char(encoded_string[pos + 3])));
			}
		}

		pos += 4;
	}

	return ret;
}

std::string base64_decode(std::string const& s, bool remove_linebreaks) {
	return decode(s, remove_linebreaks);
}

std::string base64_encode(std::string const& s, bool url) {
	return encode(s, url);
}

std::string base64_encode_pem(std::string const& s) {
	return encode_pem(s);
}

std::string base64_encode_mime(std::string const& s) {
	return encode_mime(s);
}

#if __cplusplus >= 201703L
//
// Interface with std::string_view rather than const std::string&
// Requires C++17
// Provided by Yannic Bonenberger (https://github.com/Yannic)
//

std::string base64_encode(std::string_view s, bool url) {
	return encode(s, url);
}

std::string base64_encode_pem(std::string_view s) {
	return encode_pem(s);
}

std::string base64_encode_mime(std::string_view s) {
	return encode_mime(s);
}

std::string base64_decode(std::string_view s, bool remove_linebreaks) {
	return decode(s, remove_linebreaks);
}

#endif  // __cplusplus >= 201703L

/////////////////////////////////////////////////////////

std::string hexa_encode(std::string const & selText)
{
	std::string hexa = selText;
	size_t textLen = selText.length();
	if (!textLen) return hexa;
	int nbCharPerLine = 32;
	int insertSpace = 0;
	int	uppercase = 1;
	bool isMaj = true;

	size_t eolNbChar = 0;
	if (nbCharPerLine)
	{
		eolNbChar = (textLen / nbCharPerLine) * 2;
	}
	size_t inc = insertSpace ? 3 : 2;
	std::unique_ptr<char[]> pDestText = std::make_unique<char[]>(textLen*(inc + eolNbChar) + 1);

	size_t j = 0;
	for (size_t i = 0, k = 1; i < textLen; i++)
	{
		bool isEOL = false;
		if (nbCharPerLine)
		{
			if (k >= nbCharPerLine)
			{
				isEOL = true;
				k = 1;
			}
			else
			{
				k++;
			}
		}

		const char *format = "";
		int val = selText[i];
		if (val == -1)
		{
			return hexa;
		}

		if (!insertSpace || isEOL)
		{
			format = isMaj ? "%02X" : "%02x";
			sprintf(pDestText.get() + j, format, (unsigned char)val);
			j += 2;
		}
		else
		{
			format = isMaj ? "%02X " : "%02x ";
			sprintf(pDestText.get() + j, format, (unsigned char)val);
			j += 3;
		}

		if (isEOL)
		{
			pDestText[j++] = 0x0D;
			pDestText[j++] = 0x0A;
		}
	}
	pDestText[j] = 0x00;

	hexa = pDestText.get();

	return hexa;
}

std::string hexa_decode(std::string const & _str)
{
	auto fGetTrueHexValue = [](char c) -> int
	{
		switch (c)
		{
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			return (c - '0');

		case 'a':
		case 'A':
			return 10;

		case 'b':
		case 'B':
			return 11;

		case 'c':
		case 'C':
			return 12;

		case 'd':
		case 'D':
			return 13;

		case 'e':
		case 'E':
			return 14;

		case 'f':
		case 'F':
			return 15;

		default:
			return -1;
		}
	};

	std::string ascii;
	size_t l = _str.length();
	bool hasWs = false;
	if (!l || l < 2) return ascii;
	if (l < 5)	//3 :  "00X" or "X00" where X == \n or " "
				//4 :  "0000"
	{

	}
	// Check 5 first characters
	else // 5: "00 00" or "00000"
	{
		hasWs = _str[2] == ' ';
	}
	// Begin conversion
	hexStat stat = st_init;
	size_t i = 0;
	for (; _str[i]; i++)
	{
		if (_str[i] == ' ')
		{
			if (!hasWs) return ascii;
			if (stat != st_cc) return ascii;
			stat = st_init;
		}
		/*
		else if (_str[i] == '\t')
		{

		}
		*/
		else if ((_str[i] == '\n') || (_str[i] == '\r'))
		{
			if ((stat != st_cc) && (stat != st_init)) return false;
			stat = st_init;
		}
		else if ((_str[i] >= 'a' && _str[i] <= 'f') ||
			(_str[i] >= 'A' && _str[i] <= 'F') ||
			(_str[i] >= '0' && _str[i] <= '9'))
		{
			if (stat == st_cc)
			{
				if (hasWs) return ascii;
				stat = st_c;
			}
			else if (stat == st_c)
			{
				// Process

				auto hi = fGetTrueHexValue(_str[i - 1]);
				if (hi == -1)
					return ascii;

				auto lo = fGetTrueHexValue(_str[i]);
				if (lo == -1)
					return ascii;

				ascii.push_back(static_cast<char>(hi * 16 + lo));
				stat = st_cc;
			}
			else if (stat == st_init)
			{
				stat = st_c;
			}
		}
		/*
		else if (_str[i] == ' ')
		{

		}
		*/
		else
		{
			return ascii;
		}

	}
	return ascii;
}

std::string decimal_encode(std::string const & s)
{
	std::string decimal;
	for (int i = 0; i < s.length(); i++)
	{
		if (i == s.length() - 1)
			decimal += explorer_extra_string_format("%zd", (int)s[i]);
		else
			decimal += explorer_extra_string_format("%zd", (int)s[i]) + " ";
	}
	return decimal;
}

std::string decimal_decode(std::string const & s)
{
	std::string text;
	std::vector<std::string> listDecimal = AppUtils::SplitterStdString(s, " ");
	for (int i = 0; i < listDecimal.size(); i++)
	{
		if (listDecimal[i].empty()) continue;
		int value = std::stoi(STDStringHelper::trim(listDecimal[i]));
		if (value <= 255)
		{
			text += (char)value;
		}
	}
	return text;
}

std::string binary_encode(std::string const & s)
{
	std::string binary;
	for (int i = 0; i < s.length(); i++)
	{
		binary += std::bitset<8>(s.c_str()[i]).to_string();
	}
	return binary;
}

std::string binary_decode(std::string const & s)
{
	auto fBinaryStringToText = [](std::string binaryString) -> std::string 
	{
		std::string text = "";
		std::stringstream sstream(binaryString);
		while (sstream.good())
		{
			std::bitset<8> bits;
			sstream >> bits;
			text += char(bits.to_ulong());
		}
		return text;
	};
	std::string text = fBinaryStringToText(s);
	return text;
}

std::string octa_encode(std::string const & s)
{
	std::string octa;
	for (int i = 0; i < s.length(); i++)
	{
		if (i == s.length() - 1)
			octa += explorer_extra_string_format("%zo", (int)s[i]);
		else
			octa += explorer_extra_string_format("%zo", (int)s[i]) + " ";
	}
	return octa;
}

std::string octa_decode(std::string const & s)
{
	std::string text;
	std::vector<std::string> listDecimal = AppUtils::SplitterStdString(s, " ");
	for (int i = 0; i < listDecimal.size(); i++)
	{
		if (listDecimal[i].empty()) continue;
		int value = std::stoi(STDStringHelper::trim(listDecimal[i]), 0, 8);
		if (value <= 255)
		{
			text += (char)value;
		}
	}
	return text;
}

std::wstring md5_digest(std::string const& s)
{
	MD5 md5;
	std::string md5ResultA = md5.digestString(s.c_str());
	std::wstring md5ResultW(md5ResultA.begin(), md5ResultA.end());
	return md5ResultW;
}

std::wstring sha256_hash(std::string const& s)
{
	uint8_t sha2hash[32];
	sha256_generator::create_sha_256(sha2hash, reinterpret_cast<const uint8_t*>(s.c_str()), strlen(s.c_str()));

	wchar_t sha2hashStr[65] = { '\0' };
	for (size_t i = 0; i < 32; i++)
		wsprintf(sha2hashStr + i * 2, TEXT("%02x"), sha2hash[i]);

	return sha2hashStr;
}

uint32_t crc32_generate(std::string const& s) 
{
	boost::crc_32_type result;
	result.process_bytes(s.data(), s.length());
	return result.checksum();
}

std::string sha1_hash(std::string const& p_arg)
{
	boost::uuids::detail::sha1 sha1;
	sha1.process_bytes(p_arg.data(), p_arg.size());
	unsigned hash[5] = { 0 };
	sha1.get_digest(hash);

	// Back to string
	char buf[41] = { 0 };

	for (int i = 0; i < 5; i++)
	{
		std::sprintf(buf + (i << 3), "%08x", hash[i]);
	}

	return std::string(buf);
}

/////////////////////////////////////////////////////////