//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciError.hpp"
#include "ReturnInfo.hpp"
#include "OciStmt.hpp"

#ifndef __db_oracle_RowCounter_hpp__
#define __db_oracle_RowCounter_hpp__

namespace db {
     namespace oracle {
//////////////////////////////////////////////////////////////////
	  class RowCounter {

	  public:
	       RowCounter(const oci::handle::Error&);

	       ReturnInfo
	       count(const oci::handle::Stmt&, size_t&) const;

	  private:
	       const oci::handle::Error& e;
	  };
//////////////////////////////////////////////////////////////////
     }
}
#endif // __db_oracle_RowCounter_hpp__
