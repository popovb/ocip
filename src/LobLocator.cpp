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
db::oracle::lob::Locator::write(const offset o,
				char* p,
				const size_t s) {

     return io.write(*lob_locator, o, p, s);
}

db::oracle::ReturnInfo
db::oracle::lob::Locator::read(const offset o,
			       char* p,
			       const size_t s) {

     return io.read(*lob_locator, o, p, s);
}

size_t db::oracle::lob::Locator::get_size() const {

     return io.get_size();
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
