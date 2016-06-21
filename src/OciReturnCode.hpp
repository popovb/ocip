//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciError.hpp"
#include "String.hpp"
#include <oci.h>

#ifndef __oci_ReturnCode_hpp__
#define __oci_ReturnCode_hpp__

namespace db {
     namespace oracle {
	  namespace oci {
//////////////////////////////////////////////////////////////////
	       typedef String CodeString;
	       typedef CodeString CodeStringExtra;
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	       class ReturnCode {

	       public:
		    ReturnCode();
		    ReturnCode(const sword);
		    ReturnCode(const sword,
			       const CodeString,
			       const CodeStringExtra);
		    ReturnCode& operator=(const ReturnCode&);

		    sword operator*() const;

		    CodeString string() const;
		    CodeStringExtra string_extra() const;

	       private:
		    sword code;

		    CodeString str;
		    CodeStringExtra str_extra;
	       };
//////////////////////////////////////////////////////////////////
	  }
     }
}
#endif // __oci_ReturnCode_hpp__
