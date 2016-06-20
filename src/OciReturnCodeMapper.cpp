//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciReturnCodeMapper.hpp"
#include <vector>

//////////////////////////////////////////////////////////////////
db::oracle::oci::ReturnCodeMapper::ReturnCodeMapper(
     const handle::Error& e,
     const sword s):
     map {
     
     { OCI_SUCCESS,           { "OCI_SUCCESS",           false } },
     { OCI_SUCCESS_WITH_INFO, { "OCI_SUCCESS_WITH_INFO", true  } },
     { OCI_NO_DATA,           { "OCI_NO_DATA",           false } },
     { OCI_ERROR,             { "OCI_ERROR",             true  } },
     { OCI_INVALID_HANDLE,    { "OCI_INVALID_HANDLE",    false } },
     { OCI_NEED_DATA,         { "OCI_NEED_DATA",         false } },
     { OCI_STILL_EXECUTING,   { "OCI_STILL_EXECUTING",   true  } },
     { OCI_CONTINUE,          { "OCI_CONTINUE",          false } },
     { OCI_ROWCBK_DONE,       { "OCI_ROWCBK_DONE",       false } }
},
     errcode(0),
     err(e),
     ret(s),
     success(true),
     code_string(""),
     code_string_extra("")
{
     return;
}

void db::oracle::oci::ReturnCodeMapper::process() {

     is_it_success();
     fill_strings();
}

db::oracle::oci::ReturnCode db::oracle::oci::ReturnCodeMapper::getReturnCode() const {

     return ReturnCode(ret, code_string, code_string_extra);
}

db::oracle::oci::ErrorCode db::oracle::oci::ReturnCodeMapper::getErrorCode() const {

     return ErrorCode(errcode);
}

bool db::oracle::oci::ReturnCodeMapper::getSuccess() const {

     return success;
}

void db::oracle::oci::ReturnCodeMapper::fill_strings() {

     if (map.count(ret) == 0) {

	  String ss("Undefined return code = ");
	  ss += std::to_string(ret);
	  code_string_extra = ss;
     }

     auto data = map.at(ret);
     code_string = data.str;
     if (data.ad) {

	  code_string_extra = error_from_handler();
     }
}

db::oracle::String
db::oracle::oci::ReturnCodeMapper::error_from_handler() {

     String result;
     errcode = 0;
     std::vector<char> buffer(512, '\0');
     auto r = OCIErrorGet (
	  (dvoid*)(*err), 
	  (ub4)1,
	  (text*)NULL,
	  (sb4*)&errcode, 
	  (text*)&buffer[0],
	  (ub4)buffer.size(),
	  (ub4)OCI_HTYPE_ERROR
	  );

     if (r == OCI_SUCCESS) {

	  result = chomp(String(&buffer[0]));
     }
     return result;
}

void db::oracle::oci::ReturnCodeMapper::is_it_success() {

     if (ret == OCI_SUCCESS) {

	  success = true;
	  return;
     }

     if (ret == OCI_SUCCESS_WITH_INFO) {

	  success = true;
	  return;
     }

     success = false;
}
//////////////////////////////////////////////////////////////////
