//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "String.hpp"
#include <oci.h>

#ifndef __oci_Text_hpp__
#define __oci_Text_hpp__

namespace db {
     namespace oracle {
	  namespace oci {
//////////////////////////////////////////////////////////////////
	       class Text {

	       public:
		    Text(const String);
		    Text();

		    CONST OraText* getOratext() const;
		    CONST text* getText() const;
		    ub4 length() const;

	       private:
		    String string;
	       };
//////////////////////////////////////////////////////////////////
	  }
     }
}
#endif // __oci_Text_hpp__
