//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "LobTemper.hpp"
#include <oci.h>

//////////////////////////////////////////////////////////////////
db::oracle::lob::Temper::Temper
(const oci::handle::ServiceContext& s,
 const oci::handle::Error& er):
     sc(s),
     e(er)
{
     return;
}

db::oracle::lob::Temper::~Temper() {

     return;
}

db::oracle::ReturnInfo db::oracle::lob::Temper::make_blob
(const ::db::oracle::oci::LobLocator& l) const {

     return make(OCI_TEMP_BLOB, l);
}

db::oracle::ReturnInfo db::oracle::lob::Temper::make_clob
(const ::db::oracle::oci::LobLocator& l) const {

     return make(OCI_TEMP_CLOB, l);
}

void db::oracle::lob::
Temper::destroy(const ::db::oracle::oci::LobLocator& l) const {

     OCILobFreeTemporary ((*sc).ptr, *e, (*l).ptr);
}

db::oracle::ReturnInfo db::oracle::lob::Temper::make
(const ub1 t,
 const ::db::oracle::oci::LobLocator& l) const {

     ReturnInfo ri(
	  e,
	  OCILobCreateTemporary(
	       (*sc).ptr,
	       *e,
	       (*l).ptr,
	       OCI_DEFAULT,
	       OCI_DEFAULT,
	       t,
	       FALSE,
	       OCI_DURATION_SESSION
	       )
	  );
     return ri;
}
//////////////////////////////////////////////////////////////////
