//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include <vector>
#include "String.hpp"

#ifndef __db_QueryBuffer_hpp__
#define __db_QueryBuffer_hpp__

namespace db {
     namespace oracle {
//////////////////////////////////////////////////////////////////
	  typedef std::vector<char> BufferVec;
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	  class Buffer {

	  public:
	       Buffer();
	       virtual ~Buffer() = 0;

	       virtual char* buffer() const = 0;
	       virtual size_t size() const = 0;
	  };
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	  class StringBuffer: public Buffer {

	  public:
	       StringBuffer(const size_t);
	       virtual ~StringBuffer();

	       virtual char* buffer() const override;
	       virtual size_t size() const override;

	       void clear();
	       String string() const;

	  private:
	       const size_t sz;
	       BufferVec bv;
	  };
//////////////////////////////////////////////////////////////////
     }
}
#endif // __db_QueryBuffer_hpp__
