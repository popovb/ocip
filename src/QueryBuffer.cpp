//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "QueryBuffer.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::Buffer::Buffer() {

     return;
}

db::oracle::Buffer::~Buffer() {

     return;
}
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
db::oracle::StringBuffer::StringBuffer(const size_t n):
     sz(n),
     bv(BufferVec(n, '\0'))
{
     return;
}

db::oracle::StringBuffer::~StringBuffer() {

     return;
}

char* db::oracle::StringBuffer::buffer() const {

     return (char*)&bv[0];
}

size_t db::oracle::StringBuffer::size() const {

     return (sz - 1);
}

void db::oracle::StringBuffer::clear() {

     for (char& c : bv) {

	  c = '\0';
     }
}

db::oracle::String
db::oracle::StringBuffer::string() const {

     return String(&bv[0]);
}
//////////////////////////////////////////////////////////////////
