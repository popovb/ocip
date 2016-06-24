//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "LobLocator.hpp"
#include "Error.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::lob::Locator::Locator(const Environment& e):
     oe(e),
     lob_locator(nullptr),
     temper(e.getServiceContext(), e.getError()),
     io(e.getServiceContext(), e.getError())
{
     init_locator();
}

db::oracle::lob::Locator::~Locator() {

     close();
     temper.destroy(*lob_locator);
     destroy_locator();
}

db::oracle::ReturnInfo
db::oracle::lob::Locator::make_temp_blob() const {

     temper.destroy(*lob_locator);
     return temper.make_blob(*lob_locator);
}

db::oracle::ReturnInfo
db::oracle::lob::Locator::make_temp_clob() const {

     temper.destroy(*lob_locator);
     return temper.make_clob(*lob_locator);
}

void db::oracle::lob::Locator::close() const {

     io.close(*lob_locator);
}

db::oracle::ReturnInfo
db::oracle::lob::Locator::openRO() const {

     return io.openRO(*lob_locator);
}

db::oracle::ReturnInfo
db::oracle::lob::Locator::openRW() const {

     return io.openRW(*lob_locator);
}

db::oracle::ReturnInfo
db::oracle::lob::Locator::trim() const {

     return io.trim(*lob_locator);
}

db::oracle::ReturnInfo
db::oracle::lob::Locator::write_once(const offset o,
				     char* p,
				     const size_t s) {

     return io.write_once(*lob_locator, o, p, s);
}

db::oracle::ReturnInfo
db::oracle::lob::Locator::write_first(const offset o,
				      const size_t ssz,
				      char* p,
				      const size_t s) {

     return io.write_first(*lob_locator, o, ssz, p, s);
}

db::oracle::ReturnInfo
db::oracle::lob::Locator::write_next(char* p,
				     const size_t s) {

     return io.write_next(*lob_locator, p, s);
}

db::oracle::ReturnInfo
db::oracle::lob::Locator::write_last(char* p,
				     const size_t s) {

     return io.write_last(*lob_locator, p, s);
}

db::oracle::ReturnInfo
db::oracle::lob::Locator::read_once(const offset o,
				    char* p,
				    const size_t s) {

     return io.read_once(*lob_locator, o, p, s);
}

db::oracle::ReturnInfo
db::oracle::lob::Locator::read_first(const offset o,
				     char* p,
				     const size_t s) {

     return io.read_first(*lob_locator, o, p, s);
}

db::oracle::ReturnInfo
db::oracle::lob::Locator::read_next(char* p,
				    const size_t s) {

     return io.read_next(*lob_locator, p, s);
}

size_t db::oracle::lob::Locator::bytes() const {

     return io.get_bytes();
}

size_t db::oracle::lob::Locator::chars() const {

     return io.get_chars();
}

void db::oracle::lob::Locator::init_locator() {

     lob_locator = new db::oracle::
	  oci::LobLocator(oe.getEnvironment());
     if (! *lob_locator) {

	  throw Error("Can't init OCILobLocator!");
     }
}

void db::oracle::lob::Locator::destroy_locator() const {

     if (lob_locator != nullptr) delete lob_locator;
}
//////////////////////////////////////////////////////////////////
