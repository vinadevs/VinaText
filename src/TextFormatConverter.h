/*#*******************************************************************************
# COPYRIGHT NOTES
# ---------------
# This is a part of VinaText Project
# Copyright(C) - free open source - vinadevs
# This source code can be used, distributed or modified under MIT license
#*******************************************************************************/

#pragma once

#ifndef BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A
#define BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A

#include <string>

#if __cplusplus >= 201703L
#include <string_view>
#endif  // __cplusplus >= 201703L

std::string base64_encode(std::string const& s, bool url = false);
std::string base64_encode_pem(std::string const& s);
std::string base64_encode_mime(std::string const& s);

// apis
std::string base64_decode(std::string const& s, bool remove_linebreaks = false);
std::string base64_encode(unsigned char const*, size_t len, bool url = false);

enum hexStat { st_init, st_c, st_cc };
std::string hexa_encode(std::string const& s);
std::string hexa_decode(std::string const& s);

std::string decimal_encode(std::string const& s);
std::string decimal_decode(std::string const& s);

std::string binary_encode(std::string const& s);
std::string binary_decode(std::string const& s);

std::string octa_encode(std::string const& s);
std::string octa_decode(std::string const& s);

std::wstring md5_digest(std::string const& s);

std::wstring sha256_hash(std::string const & s);

uint32_t crc32_generate(std::string const & s);

std::string sha1_hash(std::string const & p_arg);

#if __cplusplus >= 201703L
//
// Interface with std::string_view rather than const std::string&
// Requires C++17
// Provided by Yannic Bonenberger (https://github.com/Yannic)
//
std::string base64_encode(std::string_view s, bool url = false);
std::string base64_encode_pem(std::string_view s);
std::string base64_encode_mime(std::string_view s);

std::string base64_decode(std::string_view s, bool remove_linebreaks = false);
#endif  // __cplusplus >= 201703L

#endif /* BASE64_H_C0CE2A47_D10E_42C9_A27C_C883944E704A */