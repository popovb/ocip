//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "LobIO.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::lob::IO::IO
(const oci::handle::ServiceContext& s,
 const oci::handle::Error& er):
     sc(s),
     e(er),
     size(0),
     chn(0)
{
     return;
}

void db::oracle::lob::IO::close
(const oci::LobLocator& l) const {

     OCILobClose ((*sc).ptr, *e, (*l).ptr);
}

db::oracle::ReturnInfo
db::oracle::lob::IO::openRO
(const oci::LobLocator& l) const {

     return open(l, OCI_LOB_READONLY);
}

db::oracle::ReturnInfo
db::oracle::lob::IO::openRW
(const oci::LobLocator& l) const {

     return open(l, OCI_LOB_READWRITE);
}

db::oracle::ReturnInfo
db::oracle::lob::IO::trim
(const oci::LobLocator& l) const {

     ReturnInfo ri(
	  e,
	  OCILobTrim(
	       (*sc).ptr,
	       *e,
	       (*l).ptr,
	       (ub4)0
	       )
	  );
     return ri;
}

db::oracle::ReturnInfo
db::oracle::lob::IO::write(const oci::LobLocator& l,
			   const offset o,
			   char* p,
			   const size_t s) {
     size = s;
     chn = 0;
     ReturnInfo ri(
	  e,
	  OCILobWrite2(
	       (*sc).ptr,
	       *e,
	       (*l).ptr,
	       (oraub8*)&size,
	       (oraub8*)&chn,
	       (oraub8)o,
	       (void*)p,
	       (oraub8)s,
	       (ub1)OCI_ONE_PIECE,
	       (void*)NULL,
	       (sb4)NULL,
	       (ub2)0,
	       (ub1)SQLCS_IMPLICIT
	       )
	  );
     return ri;
}

db::oracle::ReturnInfo
db::oracle::lob::IO::read(const oci::LobLocator& l,
			  const offset o,
			  char* p,
			  const size_t s) {
     size = s;
     chn = 0;
     ReturnInfo ri(
	  e,
	  OCILobRead2(
	       (*sc).ptr,
	       *e,
	       (*l).ptr,
	       (oraub8*)&size,
	       (oraub8*)&chn,
	       (oraub8)o,
	       (void*)p,
	       (oraub8)s,
	       (ub1)OCI_ONE_PIECE,
	       (void*)NULL,
	       (sb4)NULL,
	       (ub2)0,
	       (ub1)SQLCS_IMPLICIT
	       )
	  );
     return ri;
}

ub4 db::oracle::lob::IO::get_size() const {

     return size;
}

db::oracle::ReturnInfo
db::oracle::lob::IO::open
(const oci::LobLocator& l,
 const ub1 mode) const {

     ReturnInfo ri(
	  e,
	  OCILobOpen(
	       (*sc).ptr,
	       *e,
	       (*l).ptr,
	       mode
	       )
	  );
     return ri;
}
//////////////////////////////////////////////////////////////////
