//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "LobBindValue.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::lob::BindValue::BindValue
(const oci::IndicatorValue::Null n,
 const db::oracle::oci::Type t,
 const LocatorPtr l):
     oracle::BindValue(n, t),
     buff(nullptr),
     s(0),
     locator(l)
{
     load_buff(l);
     return;
}

db::oracle::lob::BindValue::BindValue
(const oci::IndicatorValue::Null n,
 const db::oracle::oci::Type t):
     oracle::BindValue(n, t),
     buff(nullptr),
     s(0)
{
     return;
}

db::oracle::lob::BindValue::~BindValue() {

     return;
}

void* db::oracle::lob::BindValue::buffer() const {

     return buff;
}

size_t db::oracle::lob::BindValue::size() const {

     return s;
}

void db::oracle::lob::BindValue::load_buff(const LocatorPtr l) {

     s = l->lob_locator->size();
     buff = (void**)(**(l->lob_locator)).ptrptr;
}
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
db::oracle::lob::BlobBindValue::BlobBindValue(const LocatorPtr l):
     BindValue(oci::IndicatorValue::Null::No,
	       TypeBlob(),
	       l)
{
     return;
}

db::oracle::lob::BlobBindValue::BlobBindValue():
     BindValue(oci::IndicatorValue::Null::Yes,
	       TypeBlob())
{
     return;
}

db::oracle::lob::BlobBindValue::~BlobBindValue() {

     return;
}
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
db::oracle::lob::ClobBindValue::ClobBindValue(const LocatorPtr l):
     BindValue(oci::IndicatorValue::Null::No,
	       TypeClob(),
	       l)
{
     return;
}

db::oracle::lob::ClobBindValue::ClobBindValue():
     BindValue(oci::IndicatorValue::Null::Yes,
	       TypeClob())
{
     return;
}

db::oracle::lob::ClobBindValue::~ClobBindValue() {

     return;
}
//////////////////////////////////////////////////////////////////
