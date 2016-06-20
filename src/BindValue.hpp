//
// Copyright (c) 2016, Boris Popov <popov@whitekefir.ru>
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//

#include "OciBind.hpp"
#include "OciIndicatorValue.hpp"
#include "QueryBuffer.hpp"
#include "Type.hpp"
#include "String.hpp"

#ifndef __db_OracleBindValue_hpp__
#define __db_OracleBindValue_hpp__

namespace db {
     namespace oracle {
//////////////////////////////////////////////////////////////////
	  class BindValue {

	  public:
	       BindValue(const oci::IndicatorValue::Null,
			 const db::oracle::oci::Type);
	       virtual ~BindValue() = 0;

	       BindValue(const BindValue&) = delete;
	       BindValue& operator=(const BindValue&) = delete;

	       virtual void* buffer() const = 0;
	       virtual size_t size() const = 0;

	       oci::handle::Bind& getBind() const;
	       const oci::IndicatorValue& getIndicator() const;

	       const db::oracle::oci::Type& get_type() const;

	  private:
	       const db::oracle::oci::Type type;

	       oci::handle::Bind* bind;
	       void make_bind();

	       oci::IndicatorValue iv;
	  };
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	  class InStringBindValue: public BindValue {

	  public:
	       InStringBindValue();
	       InStringBindValue(const String);
	       virtual ~InStringBindValue();

	       InStringBindValue(const InStringBindValue&) = delete;
	       InStringBindValue& operator=(const InStringBindValue&) = delete;

	       void* buffer() const override;
	       size_t size() const override;

	  private:
	       String str;
	  };
//////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////
	  class OutStringBindValue: public BindValue {

	  public:
	       OutStringBindValue(const size_t);
	       virtual ~OutStringBindValue();

	       OutStringBindValue(const OutStringBindValue&) = delete;
	       OutStringBindValue& operator=(const OutStringBindValue&) = delete;

	       void* buffer() const override;
	       size_t size() const override;

	       StringBuffer& getBuffer();

	  private:
	       StringBuffer qb;
	  };
//////////////////////////////////////////////////////////////////
     }
}
#endif // __db_OracleBindValue_hpp__
