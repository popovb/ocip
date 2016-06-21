//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "LobLocator.hpp"
#include <string>
#include <istream>
#include <ostream>
#include <vector>

#ifndef __db_oracle_lob_Streamer_hpp__
#define __db_oracle_lob_Streamer_hpp__

namespace db {
     namespace oracle {
	  namespace lob {
//////////////////////////////////////////////////////////////////
	       typedef std::string String;
	       typedef std::vector<char> BufferVec;
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	       class Streamer {

	       public:
		    enum class ErrorType { undefined, iostream, oci };

	       public:
		    typedef struct {

			 ErrorType type;
			 String str;

		    } ErrorInfo;

	       public:
		    Streamer(const LocatorPtr);

		    bool operator<<(std::istream&);
		    bool operator>>(std::ostream&);

		    ErrorInfo getErrorInfo() const;

	       private:
		    const LocatorPtr locator;

		    ErrorInfo info;
		    void clear_info();

		    const int sizeb;
		    BufferVec buffer;
	       };
//////////////////////////////////////////////////////////////////
	  }
     }
}
#endif // __db_oracle_lob_Streamer_hpp__
