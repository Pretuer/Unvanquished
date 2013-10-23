/*
===========================================================================

Daemon GPL Source Code
Copyright (C) 2013 Unvanquished Developers

This file is part of the Daemon GPL Source Code (Daemon Source Code).

Daemon Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

Daemon Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with Daemon Source Code.  If not, see <http://www.gnu.org/licenses/>.

===========================================================================
*/

#include <string>
#include "../libs/tinyformat/tinyformat.h"

#ifndef SHARED_STRING_H_
#define SHARED_STRING_H_

namespace Str {

    template<typename T> class BasicStringRef {
    public:
        BasicStringRef(const std::basic_string<T>& other)
        {
            ptr = other.c_str();
            len = other.size();
        }
        BasicStringRef(const T* other)
        {
            ptr = other;
            len = std::char_traits<T>::length(other);
        }

        const T& operator[](size_t pos) const
        {
            return ptr[pos];
        }
        const T* begin() const
        {
            return ptr;
        }
        const T* end() const
        {
            return ptr + len;
        }
        const T* data() const
        {
            return ptr;
        }
        const T* c_str() const
        {
            return ptr;
        }
        const T& front() const
        {
            return ptr[0];
        }
        const T& back() const
        {
            return ptr[len - 1];
        }

        std::basic_string<T> str() const
        {
            return std::basic_string<T>(ptr, len);
        }
        operator std::basic_string<T>() const
        {
            return str();
        }

        bool empty() const
        {
            return len == 0;
        }
        size_t size() const
        {
            return len;
        }

        int compare(BasicStringRef other) const
        {
            int result = std::char_traits<T>::compare(ptr, other.ptr, std::min(len, other.len));
            if (result != 0)
                return result;
            else
                return len - other.len;
        }
        friend bool operator==(BasicStringRef a, BasicStringRef b)
        {
            return a.compare(b) == 0;
        }
        friend bool operator!=(BasicStringRef a, BasicStringRef b)
        {
            return a.compare(b) != 0;
        }
        friend bool operator<(BasicStringRef a, BasicStringRef b)
        {
            return a.compare(b) < 0;
        }
        friend bool operator<=(BasicStringRef a, BasicStringRef b)
        {
            return a.compare(b) <= 0;
        }
        friend bool operator>(BasicStringRef a, BasicStringRef b)
        {
            return a.compare(b) > 0;
        }
        friend bool operator>=(BasicStringRef a, BasicStringRef b)
        {
            return a.compare(b) >= 0;
        }

    private:
        const T* ptr;
        size_t len;
    };
    typedef BasicStringRef<char> StringRef;

    int ToInt(Str::StringRef text);
    bool ToInt(Str::StringRef text, int& result);

    bool IsPrefix(Str::StringRef prefix, Str::StringRef text);
    int LongestPrefixSize(Str::StringRef text1, Str::StringRef text2);

    std::u32string UTF8To32(Str::StringRef str);
    std::string UTF32To8(Str::BasicStringRef<char32_t> str);

#ifdef _WIN32
    std::wstring UTF8To16(Str::StringRef str);
    std::string UTF16To8(Str::BasicStringRef<wchar_t> str);
#endif

    template<typename ... Args>
    std::string Format(const std::string& format, const Args& ... args);

    template<typename ... Args>
    std::string Format(const std::string& format, const Args& ... args) {
        return tinyformat::format(format.c_str(), args ...);
    }
}

#endif //SHARED_STRING_H_
