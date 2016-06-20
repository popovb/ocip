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
#include "BindValue.hpp"
#include "LobBindValue.hpp"
#include "String.hpp"

#ifndef __db_OracleBinder_hpp__
#define __db_OracleBinder_hpp__

namespace db {
     namespace oracle {
//////////////////////////////////////////////////////////////////
	  typedef size_t PosNo;
	  typedef String PosName;
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	  class Binder {

	  public:
	       Binder(const oci::handle::Error&);
	       ReturnInfo bind(const oci::handle::Stmt&,
			       const PosNo,
			       const BindValue&) const;

	       ReturnInfo bind(const oci::handle::Stmt&,
			       const PosName,
			       const BindValue&) const;

	  private:
	       const oci::handle::Error& e;
	       ReturnInfo bind_name(const oci::handle::Stmt&,
				    const PosName,
				    const BindValue&,
				    const ub2) const;

	       ReturnInfo bind_pos(const oci::handle::Stmt&,
				   const PosNo,
				   const BindValue&,
				   const ub2) const;
	  };
//////////////////////////////////////////////////////////////////
     }
}
#endif // __db_OracleBinder_hpp__
