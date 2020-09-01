/* Copyright (C) 2020 David Sloan
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __Path_h
#define __Path_h

#include "Base/List.h"
#include "Base/String.h"
#include "Base/Exception.h"

namespace FileSystem
{
  class Path : Base::Stringable {
    public:
      Path();
      Path(Base::String const& path);
      Path(Path const& path);

      Path& operator+= (Path const& value);
      Path& operator+= (Base::String const& value);

      Path operator+ (Path const& value);
      Path operator+ (Base::String const& value);

      Path operator/ (Path const& value);
      Path operator/ (Base::String const& value);
      friend Path operator/(char const* lhs, Path const& rhs)
      {
	      return Path(lhs) / rhs;
      }

      bool isAbsolute() const;
      size_t length() const;

      Path trimExt() const;

      bool dirExists() const;
      bool fileExists() const;
      void createDir() const;
      void remove() const;
      Base::String stem() const;

      Path subpath(off_t index, size_t len) const
      {
	      return Path(*this, index, len);
      }
      Path subpath(off_t index) const
      {
	      return this->subpath(index, this->length() - index);
      }

      Base::String operator[] (const off_t index) const;

      Base::String toString() const override;

      int hash() const { return this->toString().hash(); }
      bool operator==(Path const& other) const { return this->toString() == other.toString(); }
      bool operator==(char const* other) const { return this->toString() == other; }
      bool operator!=(Path const& other) const { return this->toString() != other.toString(); }
      bool operator!=(char const* other) const { return this->toString() != other; }

    private:
      Base::List<Base::String> parts_;
      bool absolute_;

      Path(Path const& path, off_t index, size_t len);

      void verifyPartName(Base::String& part) const;
  };
}

#endif
