//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "Binder.hpp"
#include "OciText.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::Binder::Binder(const oci::handle::Error& er):
     e(er)
{
     return;
}

db::oracle::ReturnInfo
db::oracle::Binder::bind(const oci::handle::Stmt& s,
			 const PosNo p,
			 const BindValue& bv) const {
     auto h = bv.getBind();
     ReturnInfo ri(
	  e,
	  OCIBindByPos(
	       *s,
	       (*h).ptrptr,
	       *e,
	       (ub4)p,
	       (dvoid*)bv.buffer(),
	       (sb4)bv.size(),
	       bv.get_type().get_oci_type(),
	       (dvoid*)bv.getIndicator().ptr(),
	       (ub2*)0,
	       (ub2*)0,
	       (ub4)0,
	       (ub4*)0,
	       OCI_DEFAULT
	       )
	  );
     auto orc = ri.getReturnCode();
     h.setStatus(*orc);
     return ri;
}

db::oracle::ReturnInfo
db::oracle::Binder::bind(const oci::handle::Stmt& s,
			 const PosName p,
			 const BindValue& bv) const {
     oci::Text posname(p);
     auto h = bv.getBind();
     ReturnInfo ri(
	  e,
	  OCIBindByName(
	       *s,
	       (*h).ptrptr,
	       *e,
	       posname.getText(),
	       (sb4)(posname.length()),
	       (dvoid*)bv.buffer(),
	       (sb4)bv.size(),
	       bv.get_type().get_oci_type(),
	       (dvoid*)bv.getIndicator().ptr(),
	       (ub2*)0,
	       (ub2*)0,
	       (ub4)0,
	       (ub4*)0,
	       OCI_DEFAULT
	       )
	  );
     auto orc = ri.getReturnCode();
     h.setStatus(*orc);
     return ri;
}
//////////////////////////////////////////////////////////////////
