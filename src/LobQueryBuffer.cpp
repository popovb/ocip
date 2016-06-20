//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
//
// Copyright (c) 2016, Boris Popov <popov.b@gmail.com>
//

#include "LobQueryBuffer.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::lob::Buffer::Buffer(const LocatorPtr l):
     buff(nullptr),
     siz(0)
{
     load_buff(l);
     return;
}

db::oracle::lob::Buffer::~Buffer() {

     return;
}

char* db::oracle::lob::Buffer::buffer() const {

     return buff;
}

size_t db::oracle::lob::Buffer::size() const {

     return siz;
}

void db::oracle::lob::Buffer::load_buff(const LocatorPtr l) {

     ::db::oracle::oci::LobLocator* ll = l->lob_locator;
     auto p = **ll;
     siz = sizeof(p.ptr);
     buff = (char*)(p.ptrptr);
     return;
}
//////////////////////////////////////////////////////////////////
