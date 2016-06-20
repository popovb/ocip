//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "Definer.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::Definer::Definer(const oci::handle::Error& er):
     e(er)
{
     return;
}

db::oracle::ReturnInfo
db::oracle::Definer::define(const oci::handle::Stmt& s,
			    const PosNo p,
			    const QueryValue& qv) const {

     auto h = qv.getDefine();
     const oci::IndicatorValue& iv = qv.getIndicator();
     const Buffer& ob = qv.getBuffer();
     auto t = qv.get_type();
     ReturnInfo ri(
	  e,
	  OCIDefineByPos(
	       *s,
	       (*h).ptrptr,
	       *e,
	       (ub4)p,
	       (dvoid*)ob.buffer(),
	       (sb4)ob.size(),
	       t.get_oci_type(),
	       (dvoid*)iv.ptr(),
	       (ub2*)0,
	       (ub2*)0,
	       OCI_DEFAULT
	       )
	  );
     auto orc = ri.getReturnCode();
     h.setStatus(*orc);
     return ri;
    }
//////////////////////////////////////////////////////////////////
