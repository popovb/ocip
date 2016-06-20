//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "BindValue.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::BindValue::BindValue(const oci::IndicatorValue::Null i,
			 const db::oracle::oci::Type t):
     type(t),
     bind(nullptr),
     iv(i)
{
     make_bind();
     return;
}

db::oracle::BindValue::~BindValue() {

     if (bind != nullptr) delete bind;
}

db::oracle::oci::handle::Bind&
db::oracle::BindValue::getBind() const {

     return *bind;
}

const db::oracle::oci::IndicatorValue&
db::oracle::BindValue::getIndicator() const {

     return iv;
}

const db::oracle::oci::Type&
db::oracle::BindValue::get_type() const {

     return type;
}

void db::oracle::BindValue::make_bind() {

     bind = new oci::handle::Bind;
}
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
db::oracle::InStringBindValue::InStringBindValue():
     BindValue(oci::IndicatorValue::Null::Yes,
	       db::oracle::TypeString()),
     str("")
{
     return;
}

db::oracle::InStringBindValue::InStringBindValue(const String s):
     BindValue(oci::IndicatorValue::Null::No,
	       db::oracle::TypeString()),
     str(s)
{
     return;
}

db::oracle::InStringBindValue::~InStringBindValue() {

     return;
}

void* db::oracle::InStringBindValue::buffer() const {

     return (void*)(str.c_str());
}

size_t db::oracle::InStringBindValue::size() const {

     return (str.size() + 1);
}
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
db::oracle::OutStringBindValue::OutStringBindValue(const size_t n):
     BindValue(oci::IndicatorValue::Null::No,
	       db::oracle::TypeString()),
     qb(n)
{
     return;
}

db::oracle::OutStringBindValue::~OutStringBindValue() {

     return;
}

void* db::oracle::OutStringBindValue::buffer() const {

     return (void*)(qb.buffer());
}

size_t db::oracle::OutStringBindValue::size() const {

     return qb.size();
}

db::oracle::StringBuffer&
db::oracle::OutStringBindValue::getBuffer() {

     return qb;
}
//////////////////////////////////////////////////////////////////
