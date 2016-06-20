//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "LobQueryValue.hpp"

//////////////////////////////////////////////////////////////////
/*
db::oracle::lob::QueryValue::QueryValue
(const oci::Type t, const LocatorPtr l):
     QueryValue(t),
     qb(l)
{
     return;
}
*/
db::oracle::lob::QueryValue::~QueryValue() {

     return;
}

db::oracle::Buffer& db::oracle::lob::QueryValue::getBuffer() {

     return qb;
}

const db::oracle::Buffer& db::oracle::lob::QueryValue::getBuffer() const {

     return qb;
}
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
db::oracle::lob::BlobQueryValue::BlobQueryValue(const LocatorPtr l):
     QueryValue(TypeBlob(), l)
{
     return;
}

db::oracle::lob::BlobQueryValue::~BlobQueryValue() {

     return;
}
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
db::oracle::lob::ClobQueryValue::ClobQueryValue(const LocatorPtr l):
     QueryValue(TypeClob(), l)
{
     return;
}

db::oracle::lob::ClobQueryValue::~ClobQueryValue() {

     return;
}
//////////////////////////////////////////////////////////////////
