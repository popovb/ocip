//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//
// Copyright (c) 2016, Boris Popov <popov.b@gmail.com>
//

#include <oci.h>

#ifndef __db_oracle_oci_Type_hpp__
#define __db_oracle_oci_Type_hpp__

namespace db {
     namespace oracle {
	  namespace oci {
//////////////////////////////////////////////////////////////////
	       class Type {

	       public:
		    Type(const ub2);
		    ~Type();

		    ub2 get_oci_type() const;

	       private:
		    const ub2 oci_type;
	       };
//////////////////////////////////////////////////////////////////
	  }
     }
}
#endif // __db_oracle_oci_Type_hpp__
