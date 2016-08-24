//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "Environment.hpp"
#include "ReturnInfo.hpp"
#include "OciStmt.hpp"
#include "OciText.hpp"
#include "BindValue.hpp"
#include "QueryValue.hpp"
#include "Binder.hpp"
#include "Definer.hpp"
#include "Fetcher.hpp"
#include "Executor.hpp"
#include "RowCounter.hpp"
#include "LobBindValue.hpp"
#include "String.hpp"
#include <memory>

#ifndef __db_OracleStatement_hpp__
#define __db_OracleStatement_hpp__

namespace db {
     namespace oracle {
//////////////////////////////////////////////////////////////////
	  typedef String StatementString;
	  class Statement;
	  typedef std::shared_ptr<Statement> StatementPtr;
//////////////////////////////////////////////////////////////////     

//////////////////////////////////////////////////////////////////
	  class Statement {

	  public:
	       Statement(const Environment&,
			 const StatementString);
	       ~Statement();

	       ReturnInfo execute() const;
	       ReturnInfo execute(const IterationNumbers) const;

	       ReturnInfo bind(const PosNo, const BindValue&) const;
	       ReturnInfo bind(const PosName, const BindValue&) const;

	       ReturnInfo define(const PosNo, const QueryValue&) const;

	       ReturnInfo fetch() const;

	       ReturnInfo row_count(size_t&) const;

	  private:
	       const Environment& oe;
	       oci::handle::Stmt* stmt;

	       Binder binder;
	       Definer definer;
	       Fetcher fetcher;
	       Executor executor;
	       RowCounter counter;

	       void init_stmt();
	       void destroy_stmt() const;
	       void prepare(const StatementString);
	       oci::Text text;
	  };
//////////////////////////////////////////////////////////////////
     }
}
#endif // __db_OracleStatement_hpp__
