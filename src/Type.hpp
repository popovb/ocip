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

#include "OciType.hpp"

#ifndef __db_oracle_Type_hpp__
#define __db_oracle_Type_hpp__

namespace db {
     namespace oracle {
//////////////////////////////////////////////////////////////////
	       class TypeString: public db::oracle::oci::Type {

	       public:
		    TypeString();
		    ~TypeString();
	       };
//////////////////////////////////////////////////////////////////
     }
}
#endif // __db_oracle_Type_hpp__
