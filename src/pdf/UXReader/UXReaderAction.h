//
//	UXReaderAction.hpp
//	UXReader v0.1
//
// Copyright 2017-2019 Julius Oklamcak. All rights reserved.
//

#pragma once

namespace UXReader
{
	class UXReaderDestination;

	enum class UXReaderActionType {None, URI, Goto, RemoteGoto, Launch, Link};

	class UXReaderAction final
	{
		private: // Variables
			UXReaderActionType m_Type = UXReaderActionType::None;
			std::unique_ptr<UXReaderDestination> m_Destination;
			std::vector<UXRect> m_Rectangles;
			std::wstring m_URI;

		public: // Methods
			UXReaderAction(const std::string& URI, const UXRect& rectangle);
			UXReaderAction(const UXReaderDestination& destination, const UXRect& rectangle);
			UXReaderAction(const UXReaderDestination& destination, const std::wstring& URI, const UXRect& rectangle);
			UXReaderAction(const std::wstring& URI, const UXRect& rectangle);
			UXReaderAction(const std::wstring& URI, const std::vector<UXRect>& rectangles);
			~UXReaderAction(void);

			UXReaderAction(void) = delete;
			UXReaderAction(const UXReaderAction&) = default;
			UXReaderAction& operator=(const UXReaderAction&) = default;
			UXReaderAction& operator=(UXReaderAction&&) = default;
			UXReaderAction(UXReaderAction&&) = default;

			UXReaderActionType Type(void) const;
			const UXReaderDestination* Destination(void) const;
			const std::vector<UXRect>& Rectangles(void) const;
			const std::wstring& URI(void) const;

			bool Contains(const UXPoint& point) const;

			void Description(void) const;
	};
}
