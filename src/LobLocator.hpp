//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "Environment.hpp"
#include "OciLobLocator.hpp"
#include "ReturnInfo.hpp"
#include "LobTemper.hpp"
#include "LobIO.hpp"
#include <memory>

#ifndef __db_oracle_lob_Locator_hpp__
#define __db_oracle_lob_Locator_hpp__

namespace db {
     namespace oracle {
	  namespace lob {
//////////////////////////////////////////////////////////////////
	       class Locator;
	       typedef std::shared_ptr<Locator> LocatorPtr;
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	       class BindValue;
	       class Buffer;
	       class Locator {

		    friend class BindValue;
		    friend class Buffer;

	       public:
		    Locator(const Environment&);
		    ~Locator();

		    ReturnInfo make_temp_blob() const;
		    ReturnInfo make_temp_clob() const;

		    void close() const;
		    ReturnInfo openRO() const;
		    ReturnInfo openRW() const;

		    ReturnInfo trim() const;

		    ReturnInfo write(const offset,
				     char*,
				     const size_t);
		    ReturnInfo read(const offset,
				    char*,
				    const size_t);

		    size_t get_size() const;

	       private:
		    const Environment& oe;
		    ::db::oracle::oci::LobLocator* lob_locator;

		    void init_locator();
		    void destroy_locator() const;

		    Temper temper;
		    IO io;
	       };
//////////////////////////////////////////////////////////////////
	  }
     }
}
#endif // __db_oracle_lob_Locator_hpp__
