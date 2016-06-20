//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciLobLocator.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::oci::
LobLocator::LobLocator(const oci::handle::Environment& e):
     locator(nullptr),
     ptr_locator(&locator),
     code(0)
{
     code = OCIDescriptorAlloc(
	  (dvoid*)(*e),
	  (dvoid**)&locator,
	  (ub4)OCI_DTYPE_LOB,
	  (size_t)0,
	  (dvoid**)0
	  );
}

db::oracle::oci::LobLocator::~LobLocator() {

     if (locator != nullptr) {

	  OCIDescriptorFree(
	       (dvoid*)locator,
	       (ub4)OCI_DTYPE_LOB
	       );
     }
}

db::oracle::oci::LobLocator::operator bool() const {

     if (locator != nullptr) {
	  if (code == OCI_SUCCESS) return true;
     }
     return false;
}

bool db::oracle::oci::LobLocator::operator!() const {

     if (locator == nullptr) return true;
     if (code != OCI_SUCCESS) return true;
     return false;
}

db::oracle::oci::LobLocator::Ptr
db::oracle::oci::LobLocator::operator*() const {

     return {locator, ptr_locator};
}

size_t db::oracle::oci::LobLocator::size() const {

     return sizeof(locator);
}
//////////////////////////////////////////////////////////////////
