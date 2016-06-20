//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciDefine.hpp"
#include "OciIndicatorValue.hpp"
#include "QueryBuffer.hpp"
#include "Type.hpp"

#ifndef __db_OracleQueryValue_hpp__
#define __db_OracleQueryValue_hpp__

namespace db {
     namespace oracle {
//////////////////////////////////////////////////////////////////
	  class QueryValue {

	  public:
	       QueryValue(const db::oracle::oci::Type);
	       virtual ~QueryValue() = 0;

	       QueryValue(const QueryValue&) = delete;
	       QueryValue& operator=(const QueryValue&) = delete;

	       oci::handle::Define& getDefine() const;

	       oci::IndicatorValue& getIndicator();
	       const oci::IndicatorValue& getIndicator() const;

	       virtual Buffer& getBuffer() = 0;
	       virtual const Buffer& getBuffer() const = 0;

	       const db::oracle::oci::Type& get_type() const;

	  private:
	       oci::handle::Define* define;
	       void make_define();
	       oci::IndicatorValue oiv;

	       const db::oracle::oci::Type type;
	  };
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	  class StringQueryValue: public QueryValue {

	  public:
	       StringQueryValue();
	       StringQueryValue(const size_t);
	       virtual ~StringQueryValue();

	       StringQueryValue(const StringQueryValue&) = delete;
	       StringQueryValue& operator=(const StringQueryValue&) = delete;

	       virtual Buffer& getBuffer() override;
	       virtual const Buffer& getBuffer() const override;

	  private:
	       StringBuffer qb;
	  };
//////////////////////////////////////////////////////////////////
     }
}
#endif // __db_OracleQueryValue_hpp__
