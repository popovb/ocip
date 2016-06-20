//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "QueryValue.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::QueryValue::QueryValue(const oci::Type t):
     define(nullptr),
     type(t)
{
     make_define();
}

db::oracle::QueryValue::~QueryValue() {

     if (define != nullptr) delete define;
}

db::oracle::oci::handle::Define&
db::oracle::QueryValue::getDefine() const {

     return *define;
}

db::oracle::oci::IndicatorValue&
db::oracle::QueryValue::getIndicator() {

     return oiv;
}

const db::oracle::oci::IndicatorValue&
db::oracle::QueryValue::getIndicator() const {

     return oiv;
}

const db::oracle::oci::Type&
db::oracle::QueryValue::get_type() const {

     return type;
}

void db::oracle::QueryValue::make_define() {

     define = new oci::handle::Define;
}
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
db::oracle::StringQueryValue::StringQueryValue():
     QueryValue(TypeString()),
     qb(8192)
{
     return;
}

db::oracle::StringQueryValue::StringQueryValue(const size_t n):
     QueryValue(TypeString()),
     qb(n)
{
     return;
}

db::oracle::StringQueryValue::~StringQueryValue() {

     return;
}

::db::oracle::Buffer& db::oracle::StringQueryValue::getBuffer() {

     return qb;
}

const ::db::oracle::Buffer&
db::oracle::StringQueryValue::getBuffer() const {

     return qb;
}
//////////////////////////////////////////////////////////////////
