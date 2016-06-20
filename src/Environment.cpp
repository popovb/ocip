//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "Environment.hpp"
#include "Error.hpp"

//////////////////////////////////////////////////////////////////
db::oracle::Environment::Environment():
     env(nullptr),
     error(nullptr),
     scontext(nullptr)
{
     init_env();
     init_error();
     init_service_context();
     return;
}

db::oracle::Environment::~Environment() {

     destroy_service_context();
     destroy_error();
     destroy_env();
     return;
}

void db::oracle::Environment::init_env() {

     env = new oci::handle::Environment;
     if (! *env) {

	  throw Error("Can't init OCIEnv!");
     }
}

void db::oracle::Environment::destroy_env() const {

     if (env != nullptr) delete env;
}

void db::oracle::Environment::init_error() {

     error = new oci::handle::Error(*env);
     if (! *error) {

	  throw Error("Can't init OCIError!");
     }
}

void db::oracle::Environment::destroy_error() const {

     if (error != nullptr) delete error;
}

void db::oracle::Environment::init_service_context() {

     scontext = new oci::handle::ServiceContext;
}

void db::oracle::Environment::destroy_service_context() const {

     if (scontext != nullptr) delete scontext;
}

db::oracle::oci::handle::Environment&
db::oracle::Environment::getEnvironment() const {

     return *env;
}

db::oracle::oci::handle::Error&
db::oracle::Environment::getError() const {

     return *error;
}

db::oracle::oci::handle::ServiceContext&
db::oracle::Environment::getServiceContext() const {

     return *scontext;
}
//////////////////////////////////////////////////////////////////     
