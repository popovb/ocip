//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "RowCounter.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::RowCounter::RowCounter(const oci::handle::Error& er):
     e(er)
{
     return;
}

db::oracle::ReturnInfo db::oracle::RowCounter::
count(const oci::handle::Stmt& s, size_t& ss) const {

     ub4 k = 0;
     ReturnInfo ri(
	  e,
	  OCIAttrGet(
	       *s,
	       OCI_HTYPE_STMT,
	       (void*)&k,
	       (ub4)0,
	       (ub4)OCI_ATTR_ROW_COUNT,
	       *e
	       )
	  );
     ss = k;
     return ri;
}
//////////////////////////////////////////////////////////////////
