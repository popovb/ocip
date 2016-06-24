//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "LobStreamer.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::lob::Streamer::Streamer(const LocatorPtr l):
     locator(l),
     info({ErrorType::undefined, ""}),
     sizeb(8192),
     buffer(BufferVec(sizeb))
{
     return;
}

bool db::oracle::lob::Streamer::operator<<(std::istream& i) {

     clear_info();
     if (!i) {

	  info = {ErrorType::iostream, "input stream error"};
	  return false;
     }

     if (i.eof()) {

	  info = {ErrorType::iostream, "eof already yet"};
	  return false;
     }

     i.seekg(0, std::istream::end);
     auto ssz = i.tellg();
     i.seekg(0, std::istream::beg);
     offset of = 1;
     bool first = true;
     ReturnInfo ri;

     while (i) {

	  i.read(&buffer[0], sizeb);
	  if (i.good()) {
	       if (first) {
		    if (i.gcount() == ssz) {

			 ri = locator->write_once(of, &buffer[0], i.gcount());
			 ssz -= i.gcount();

		    } else {
			 ri = locator->write_first(of, ssz,
						   &buffer[0], i.gcount());
			 ssz -= i.gcount();
		    }
		    first = false;

	       } else {
		    if (i.gcount() == ssz) {

			 ri = locator->write_last(nullptr, i.gcount());
			 ssz -= i.gcount();

		    } else {

			 ri = locator->write_next(&buffer[0], i.gcount());
			 ssz -= i.gcount();
		    }
	       }

	       if (!ri) {

		    info = {ErrorType::oci, ri.string()};
		    return false;

	       } else {
		    if (! ri.needData()) return true;
	       }
	       continue;

	  } else {
	       if (i.eof()) {
		    if (i.gcount() == 0) {
			 if (first) {

			      return true;

			 } else {

			      info = {ErrorType::oci, ri.string()};
			      return false;
			 }
		    }

		    if (first) {

			 ri = locator->write_once(of, &buffer[0], i.gcount());
			 ssz -= i.gcount();
			 first = false;

		    } else {

			 ri = locator->write_last(&buffer[0], i.gcount());
			 ssz -= i.gcount();
		    }

		    if (!ri) {

			 info = {ErrorType::oci, ri.string()};
			 return false;
		    }
		    return true;
	       }
	  }
	  break;
     }
     info = {ErrorType::iostream, "input stream error"};
     return false;
}

bool db::oracle::lob::Streamer::operator>>(std::ostream& o) {

     clear_info();
     if (!o.good()) {

	  info = {ErrorType::iostream, "output stream error"};
	  return false;
     }

     offset of = 1;
     ReturnInfo ri;
     ri = locator->read_first(of, &buffer[0], sizeb);
     if (!ri) {

	  info = {ErrorType::oci, ri.string()};
	  return false;
     }

     o.write(&buffer[0], locator->bytes());
     if (!o.good()) {

	  info = {ErrorType::iostream, "output stream error"};
	  return false;
     }

     while (ri.needData()) {

	  ri = locator->read_next(&buffer[0], sizeb);
	  if (ri) {

	       o.write(&buffer[0], locator->bytes());
	       if (!o.good()) {

		    info = {ErrorType::iostream, "output stream error"};
		    return false;
	       }
	  } else break;
     }

     if(ri) return true;
     info = {ErrorType::oci, ri.string()};
     return false;
}

void db::oracle::lob::Streamer::clear_info() {

     info = {ErrorType::undefined, ""};
}

db::oracle::lob::Streamer::ErrorInfo
db::oracle::lob::Streamer::getErrorInfo() const {

     return info;
}
//////////////////////////////////////////////////////////////////
