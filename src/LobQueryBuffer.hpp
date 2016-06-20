//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "QueryBuffer.hpp"
#include "LobLocator.hpp"

#ifndef __db_oracle_lob_QueryBuffer_hpp__
#define __db_oracle_lob_QueryBuffer_hpp__

namespace db {
     namespace oracle {
	  namespace lob {
//////////////////////////////////////////////////////////////////
	       class Buffer: public oracle::Buffer {

	       public:
		    Buffer(const LocatorPtr);
		    virtual ~Buffer();

		    virtual char* buffer() const override;
		    virtual size_t size() const override;

	       private:
		    char* buff;
		    size_t siz;

		    void load_buff(const LocatorPtr);
	       };
//////////////////////////////////////////////////////////////////
	  }
     }
}
#endif // __db_oracle_lob_QueryBuffer_hpp__
