//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciType.hpp"

#ifndef __db_oracle_lob_LobType_hpp__
#define __db_oracle_lob_LobType_hpp__

namespace db {
     namespace oracle {
	  namespace lob {
//////////////////////////////////////////////////////////////////
	       class TypeBlob: public db::oracle::oci::Type {

	       public:
		    TypeBlob();
		    ~TypeBlob();
	       };
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	       class TypeClob: public db::oracle::oci::Type {

	       public:
		    TypeClob();
		    ~TypeClob();
	       };
//////////////////////////////////////////////////////////////////
	  }
     }
}
#endif // __db_oracle_lob_LobType_hpp__
