//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "ReturnInfo.hpp"
#include "OciServiceContext.hpp"
#include "OciError.hpp"
#include "OciLobLocator.hpp"
#include <oci.h>

#ifndef __db_oracle_lob_IO_hpp__
#define __db_oracle_lob_IO_hpp__

namespace db {
     namespace oracle {
	  namespace lob {
//////////////////////////////////////////////////////////////////
	       typedef size_t offset;
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	       class IO {

	       public:
		    IO(const oci::handle::ServiceContext&,
		       const oci::handle::Error&);

		    void close
		    (const oci::LobLocator&) const;

		    ReturnInfo openRO
		    (const oci::LobLocator&) const;

		    ReturnInfo openRW
		    (const oci::LobLocator&) const;

		    ReturnInfo trim
		    (const oci::LobLocator&) const;

		    ReturnInfo write
		    (const oci::LobLocator&,
		     const offset,
		     char*,
		     const size_t);

		    ReturnInfo read
		    (const oci::LobLocator&,
		     const offset,
		     char*,
		     const size_t);

		    ub4 get_size() const;

	       private:
		    const oci::handle::ServiceContext& sc;
		    const oci::handle::Error& e;
		    oraub8 size;
		    oraub8 chn;

		    ReturnInfo open(const oci::LobLocator&,
				    const ub1) const;
	       };
//////////////////////////////////////////////////////////////////
	  }
     }
}
#endif // __db_oracle_lob_IO_hpp__
