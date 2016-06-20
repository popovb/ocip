//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "Fetcher.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::Fetcher::Fetcher(const oci::handle::Error& er):
     e(er)
{
     return;
}

db::oracle::ReturnInfo
db::oracle::Fetcher::fetch(const oci::handle::Stmt& s) const {

     ReturnInfo ri(
	  e,
	  OCIStmtFetch2(
	       *s,
	       *e,
	       (ub4)1,
	       (ub2)OCI_DEFAULT,
	       (sb4)0,
	       (ub4)OCI_DEFAULT
	       )
	  );
     return ri;
}
//////////////////////////////////////////////////////////////////
