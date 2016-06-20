//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "ReturnInfo.hpp"
#include "OciServiceContext.hpp"
#include "OciLobLocator.hpp"

#ifndef __db_oracle_lob_Temper_hpp__
#define __db_oracle_lob_Temper_hpp__

namespace db {
     namespace oracle {
	  namespace lob {
//////////////////////////////////////////////////////////////////
 	       class Temper {

 	       public:
		    Temper(const oci::handle::ServiceContext&,
		     	   const oci::handle::Error&);
		    ~Temper();

		    ReturnInfo make_blob(const oci::LobLocator&) const;
		    ReturnInfo make_clob(const oci::LobLocator&) const;

		    void destroy
		    (const oci::LobLocator&) const;

	       private:
		    const oci::handle::ServiceContext& sc;
		    const oci::handle::Error& e;

		    ReturnInfo make(const ub1,
				    const oci::LobLocator&) const;
 	       };
//////////////////////////////////////////////////////////////////
	  }
     }
}
#endif // __db_oracle_lob_Temper_hpp__
