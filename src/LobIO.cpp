//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "LobIO.hpp"

//////////////////////////////////////////////////////////////////
ub1 db::oracle::lob::IO::ONCE  = OCI_ONE_PIECE;
ub1 db::oracle::lob::IO::FIRST = OCI_FIRST_PIECE;
ub1 db::oracle::lob::IO::NEXT  = OCI_NEXT_PIECE;
ub1 db::oracle::lob::IO::LAST  = OCI_LAST_PIECE;
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
db::oracle::lob::IO::IO
(const oci::handle::ServiceContext& s,
 const oci::handle::Error& er):
     sc(s),
     e(er),
     amount_bytes(0),
     amount_chars(0),
     off(1)
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
db::oracle::lob::IO::write_once(const oci::LobLocator& l,
				const offset o,
				char* p,
				const size_t s) {
     amount_chars = 0;
     amount_bytes = s;
     off = o;
     return write_(l, p, s, ONCE);
}

db::oracle::ReturnInfo
db::oracle::lob::IO::write_first(const oci::LobLocator& l,
				 const offset o,
				 const size_t as,
				 char* p,
				 const size_t s) {
     amount_chars = 0;
     amount_bytes = as;
     off = o;
     return write_(l, p, s, FIRST);
}

db::oracle::ReturnInfo
db::oracle::lob::IO::read_first(const oci::LobLocator& l,
				const offset o,
				char* p,
				const size_t s) {
     amount_chars = 0;
     amount_bytes = 0;
     off = o;
     return read_(l, p, s, FIRST);
}

db::oracle::ReturnInfo
db::oracle::lob::IO::write_next(const oci::LobLocator& l,
				char* p,
				const size_t s) {
     amount_chars = 0;
     amount_bytes = 0;
     return write_(l, p, s, NEXT);
}

db::oracle::ReturnInfo
db::oracle::lob::IO::read_next(const oci::LobLocator& l,
			       char* p,
			       const size_t s) {
     amount_chars = 0;
     amount_bytes = 0;
     return read_(l, p, s, NEXT);
}

db::oracle::ReturnInfo
db::oracle::lob::IO::write_last(const oci::LobLocator& l,
				char* p,
				const size_t s) {
     amount_chars = 0;
     amount_bytes = 0;
     return write_(l, p, s, LAST);
}

db::oracle::ReturnInfo
db::oracle::lob::IO::read_once(const oci::LobLocator& l,
			       const offset o,
			       char* p,
			       const size_t s) {
     amount_chars = 0;
     amount_bytes = s;
     off = o;
     return read_(l, p, s, ONCE);
}

oraub8 db::oracle::lob::IO::get_bytes() const {

     return amount_bytes;
}

oraub8 db::oracle::lob::IO::get_chars() const {

     return amount_chars;
}

db::oracle::ReturnInfo
db::oracle::lob::IO::open(const oci::LobLocator& l,
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

db::oracle::ReturnInfo
db::oracle::lob::IO::write_(const oci::LobLocator& l,
			    char* p,
			    const size_t s,
			    const ub1 mode) {
     ReturnInfo ri(
	  e,
	  OCILobWrite2(
	       (*sc).ptr,
	       *e,
	       (*l).ptr,
	       (oraub8*)&amount_bytes,
	       (oraub8*)&amount_chars,
	       (oraub8)off,
	       (void*)p,
	       (oraub8)s,
	       (ub1)mode,
	       (void*)NULL,
	       (sb4)NULL,
	       (ub2)0,
	       (ub1)SQLCS_IMPLICIT
	       )
	  );
     return ri;
}

db::oracle::ReturnInfo
db::oracle::lob::IO::read_(const oci::LobLocator& l,
			    char* p,
			    const size_t s,
			    const ub1 mode) {
     ReturnInfo ri(
	  e,
	  OCILobRead2(
	       (*sc).ptr,
	       *e,
	       (*l).ptr,
	       (oraub8*)&amount_bytes,
	       (oraub8*)&amount_chars,
	       (oraub8)off,
	       (void*)p,
	       (oraub8)s,
	       (ub1)mode,
	       (void*)NULL,
	       (sb4)NULL,
	       (ub2)0,
	       (ub1)SQLCS_IMPLICIT
	       )
	  );
     return ri;
}
//////////////////////////////////////////////////////////////////
