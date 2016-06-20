//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciEnvironment.hpp"
#include <oci.h>

#ifndef __db_oracle_oci_descriptor_OCILobLocator_hpp__
#define __db_oracle_oci_descriptor_OCILobLocator_hpp__

namespace db {
     namespace oracle {
	  namespace oci {
//////////////////////////////////////////////////////////////////
	       class LobLocator {

	       public:
		    typedef struct {

			 OCILobLocator* ptr;
			 OCILobLocator** ptrptr;

		    } Ptr;

	       public:
		    LobLocator(const handle::Environment&);
		    ~LobLocator();

		    operator bool() const;
		    bool operator!() const;

		    Ptr operator*() const;
		    size_t size() const;

	       private:
		    OCILobLocator* locator;
		    OCILobLocator** ptr_locator;
		    sword code;
	       };
//////////////////////////////////////////////////////////////////
	  }
     }
}
#endif // __db_oracle_oci_descriptor_OCILobLocator_hpp__
