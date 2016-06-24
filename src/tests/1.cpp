#include <Driver.hpp>
#include <BindValue.hpp>
#include <LobStreamer.hpp>
#include <LobBindValue.hpp>
#include <LobQueryValue.hpp>
#include <String.hpp>
#include <iostream>
#include <vector>
#include <fstream>

int main() {

     system("rm src/tests/out*");
     // #01
     //////////////////////////////////////////////////////////////////
     using namespace db::oracle;
     Driver OD;
     OD.connect("scott", "tiger", "asp");
     //////////////////////////////////////////////////////////////////

     // #02
     //////////////////////////////////////////////////////////////////
     String s1(R"(
INSERT INTO DEPT (DEPTNO, DNAME, LOC) VALUES (50, 'DEV', 'MOSCOW')
)");
     auto stmt = OD.prepare(s1);
     auto ri1 = stmt->execute();
     std::cerr << "stmt->execute(): " << ri1.string() << std::endl;
     auto ri2 = OD.rollback();
     std::cerr << "rollback: " << ri2.string() << std::endl;
     //////////////////////////////////////////////////////////////////

     // #03
     //////////////////////////////////////////////////////////////////
     String s2(R"(
INSERT INTO DEPT (DEPTNO, DNAME, LOC) VALUES (:1, :2, :3)
)");
     auto stmt2 = OD.prepare(s2);
     InStringBindValue bv1("50");
     InStringBindValue bv2("DEV");
     InStringBindValue bv3("MOSCOW");

     auto ri3 = stmt2->bind(1, bv1);
     std::cerr << "stmt2->bind(1, bv1): " << ri3.string() << std::endl;

     auto ri4 = stmt2->bind(2, bv2);
     std::cerr << "stmt2->bind(2, bv2): " << ri4.string() << std::endl;

     auto ri5 = stmt2->bind(3, bv3);
     std::cerr << "stmt2->bind(3, bv3): " << ri5.string() << std::endl;

     auto ri6 = stmt2->execute();
     std::cerr << "stmt2->execute(): " << ri6.string() << std::endl;

     InStringBindValue bv4("60");
     InStringBindValue bv5("LENINGRAD");

     auto ri7 = stmt2->bind(1, bv4);
     std::cerr << "stmt2->bind(1, bv4): " << ri7.string() << std::endl;

     auto ri8 = stmt2->bind(3, bv5);
     std::cerr << "stmt2->bind(3, bv5): " << ri8.string() << std::endl;

     auto ri9 = stmt2->execute();
     std::cerr << "stmt2->execute(): " << ri9.string() << std::endl;

     InStringBindValue bv6("70");
     InStringBindValue bv7;

     auto ri10 = stmt2->bind("1", bv6);
     std::cerr << "stmt2->bind(\"1\", bv6): " << ri10.string() << std::endl;

     auto ri11 = stmt2->bind("3", bv7);
     std::cerr << "stmt2->bind(\"3\", bv7): " << ri11.string() << std::endl;

     auto ri12 = stmt2->execute();
     std::cerr << "stmt2->execute(): " << ri12.string() << std::endl;

     String s3(R"(
DELETE FROM DEPT WHERE DEPTNO >= 50
 )");
     auto stmt3 = OD.prepare(s3);
     auto ri13 = stmt3->execute();
     std::cerr << "stmt3->execute(): " << ri13.string() << std::endl;
     //////////////////////////////////////////////////////////////////

     // #04
     //////////////////////////////////////////////////////////////////
     StringQueryValue DEPTNO;
     StringQueryValue DNAME;
     StringQueryValue LOC;

     String s4(R"(
select DEPTNO, DNAME, LOC from DEPT
 )");
     auto stmt4 = OD.prepare(s4);
     auto ri14 = stmt4->define(1, DEPTNO);
     std::cerr << "stmt4->define(1, DEPTNO): " << ri14.string() << std::endl;

     auto ri15 = stmt4->define(2, DNAME);
     std::cerr << "stmt4->define(2, DNAME): " << ri15.string() << std::endl;

     auto ri16 = stmt4->define(3, LOC);
     std::cerr << "stmt4->define(3, LOC): " << ri16.string() << std::endl;

     auto ri17 = stmt4->execute(0);
     std::cerr << "stmt4->execute(): " << ri17.string() << std::endl;
     if (ri17.isNoData()) {

	  std::cerr << "NO DATA" << ri17.string() << std::endl;
	  return 0;
     }

     ((StringBuffer&)DEPTNO.getBuffer()).clear();
     ((StringBuffer&)DNAME.getBuffer()).clear();
     ((StringBuffer&)LOC.getBuffer()).clear();
     auto ri18 = stmt4->fetch();
     std::cerr << "stmt4->fetch(): " << ri18.string() << std::endl;
     while (ri18) {

	  if (DEPTNO.getIndicator()) {

	       std::cerr << "DEPTNO no truncated ";
	  }

	  if (! DEPTNO.getIndicator()) {

	       std::cerr << "DEPTNO truncated ";
	       auto iv = DEPTNO.getIndicator();
	       if (iv.size().exist) {

		    std::cerr << iv.size().size;
	       }
	  }

	  if (DEPTNO.getIndicator().is_null()) {

	       std::cerr << "NULL";

	  } else {

	       std::cerr << ((StringBuffer&)(DEPTNO.getBuffer())).string();
	  }

		    std::cerr << " | ";

		    std::cerr << ((StringBuffer&)(DNAME.getBuffer())).string();
			     std::cerr << " | ";
			     std::cerr << ((StringBuffer&)(LOC.getBuffer())).string();
					   std::cerr << std::endl;
					   ((StringBuffer&)(DEPTNO.getBuffer())).clear();
					   ((StringBuffer&)(DNAME.getBuffer())).clear();
					   ((StringBuffer&)(LOC.getBuffer())).clear();
	  ri18 = stmt4->fetch();
	  std::cerr << "stmt4->fetch(): " << ri18.string() << std::endl;
     }
     //////////////////////////////////////////////////////////////////
     /*
    DEPTNO|DNAME         |LOC
----------|--------------|-------------
        10|ACCOUNTING    |NEW YORK
        20|RESEARCH      |DALLAS
        30|SALES         |CHICAGO
        40|OPERATIONS    |BOSTON
     */
     // #05
     //////////////////////////////////////////////////////////////////
     String s5(R"(

insert into DEPT values (60, 'DEV', 'MOSCOW') returning LOC into :v

 )");
     auto stmt5 = OD.prepare(s5);
     OutStringBindValue OBV(150);
     OBV.getBuffer().clear();
     auto ri19 = stmt5->bind("v", OBV);
     std::cerr << "stmt5->bind(\"v\", OBV): " << ri19.string() << std::endl;
     auto ri20 = stmt5->execute();
     std::cerr << "stmt5->execute(1): " << ri20.string() << std::endl;

     if (OBV.getIndicator()) {

	  if (OBV.getIndicator().is_null()) {

	       std::cerr << "*** NULL ***";

	  } else {

	       std::cerr << "*** NOT NULL ***";
	  }
	  std::cerr << std::endl;
     }
     std::cerr << ">" << OBV.getBuffer().string() << "<" << std::endl;
     auto ri21 = stmt3->execute();
     std::cerr << "stmt3->execute(): " << ri21.string() << std::endl;

     // #07
     //////////////////////////////////////////////////////////////////
     {
	  db::oracle::lob::LocatorPtr lp;
	  lp = OD.make_locator();
	  auto ri22 = lp->make_temp_blob();
	  std::cerr <<
	       "lp->make_temp_blob(): " << ri22.string() << std::endl;
	  auto ri23 = lp->make_temp_clob();
	  std::cerr <<
	       "lp->make_temp_clob(): " << ri23.string() << std::endl;
	  auto ri24 = lp->openRO();
	  std::cerr << "lp->openRO(): " << ri24.string() << std::endl;
	  lp->close();
	  auto ri25 = lp->openRW();
	  std::cerr << "lp->openRW(): " << ri25.string() << std::endl;
	  auto ri26 = lp->trim();
	  std::cerr << "lp->trim(): " << ri26.string() << std::endl;

	  //write
	  std::string example("ХуепутыХуепуты");
	  auto ri27 = lp->write_once(1, (char*)example.c_str(), example.size());
	  std::cerr <<
	       "lp->write(1, example.c_str(), example.size()): " <<
	       ri27.string() <<
	       std::endl;
	  std::cerr << "size write: " << lp->bytes() << std::endl;

	  //read
	  std::vector<char> bu(256, '\0');
	  auto ri28 = lp->read_once(1, &bu[0], 255);
	  std::cerr << "lp->read(1, &bu[0], 255): " << ri28.string() << std::endl;
	  std::cerr << "out after read: " <<  std::string(&bu[0]) << std::endl;
	  std::cerr << "size read: " << lp->bytes() << std::endl;
	  lp->close();
     }
     //////////////////////////////////////////////////////////////////

     // #09
     //////////////////////////////////////////////////////////////////
     {
	  db::oracle::lob::LocatorPtr lp;
	  lp = OD.make_locator();
	  auto ri29 = lp->make_temp_blob();
	  std::cerr << "lp->make_temp_blob(): " << ri29.string() << std::endl;
	  auto ri30 = lp->openRW();
	  std::cerr << "lp->openRW(): " << ri30.string() << std::endl;
	  std::ifstream is("src/tests/example.jpg", std::ifstream::binary);
	  if (is) {
	       if (! is.eof()) {

		    db::oracle::lob::Streamer SSS(lp);
		    if (SSS << is) {

			 std::cerr << "SSS << is OK" << std::endl;

		    } else {

			 auto prop = SSS.getErrorInfo();
			 std::cerr << "str:  " << prop.str  << std::endl;
		    }
	       }
	  }
	  lp->close();
	  auto ri31 = lp->openRO();
	  std::cerr << "lp->openRO(): " << ri31.string() << std::endl;
	  std::ofstream os("src/tests/out.jpg", std::ios::binary | std::ios::trunc);
	  if (os) {
	       if (! os.eof()) {

		    std::cerr << "OUT STREAM OK!" << std::endl;
		    db::oracle::lob::Streamer SSS(lp);
		    if (SSS >> os) {

			 std::cerr << "SSS >> os OK" << std::endl;

		    } else {

			 auto prop = SSS.getErrorInfo();
			 std::cerr << "str:  " << prop.str  << std::endl;
		    }
	       }
	  }
	  lp->close();
     }
     //////////////////////////////////////////////////////////////////

     // #10
     //////////////////////////////////////////////////////////////////
     {
	  db::oracle::lob::LocatorPtr lp;
	  lp = OD.make_locator();
	  auto ri29 = lp->make_temp_clob();
	  std::cerr << "lp->make_temp_clob(): " << ri29.string() << std::endl;
	  auto ri30 = lp->openRW();
	  std::cerr << "lp->openRW(): " << ri30.string() << std::endl;
	  std::ifstream is("src/tests/example.txt", std::ifstream::binary);
	  if (is) {
	       if (! is.eof()) {

		    db::oracle::lob::Streamer SSS(lp);
		    if (SSS << is) {

			 std::cerr << "SSS << is OK" << std::endl;

		    } else {

			 auto prop = SSS.getErrorInfo();
			 std::cerr << "str:  " << prop.str  << std::endl;
		    }
	       }
	  }
	  lp->close();
	  auto ri31 = lp->openRO();
	  std::cerr << "lp->openRO(): " << ri31.string() << std::endl;
	  std::ofstream os("src/tests/out.txt", std::ios::binary | std::ios::trunc);
	  if (os) {
	       if (! os.eof()) {

		    std::cerr << "OUT STREAM OK!" << std::endl;
		    db::oracle::lob::Streamer SSS(lp);
		    if (SSS >> os) {

			 std::cerr << "SSS >> os OK" << std::endl;

		    } else {

			 auto prop = SSS.getErrorInfo();
			 std::cerr << "str:  " << prop.str  << std::endl;
		    }
	       }
	  }
	  lp->close();
     }
     //////////////////////////////////////////////////////////////////

     system("src/tests/begin.sh");
     system("src/tests/add_records.sh");

     // #11
     //////////////////////////////////////////////////////////////////
     {
	  db::oracle::lob::LocatorPtr lp;
	  lp = OD.make_locator();
	  auto ri29 = lp->make_temp_blob();
	  std::cerr << "lp->make_temp_blob(): " << ri29.string() << std::endl;
	  auto ri30 = lp->openRW();
	  std::cerr << "lp->openRW(): " << ri30.string() << std::endl;
	  std::ifstream is("src/tests/example.jpg", std::ifstream::binary);
	  if (is) {

	       db::oracle::lob::Streamer SSS(lp);
	       if (SSS << is) {

		    std::cerr << "SSS << is OK" << std::endl;

	       } else {

		    auto prop = SSS.getErrorInfo();
		    std::cerr << "str:  " << prop.str  << std::endl;
	       }
	  }
	  lp->close();

	  String s200(R"(
INSERT INTO BLOBER_TEST (ID, BLOB) VALUES (4, :aa)
)");
	  auto stmt200 = OD.prepare(s200);
	  db::oracle::lob::BlobBindValue ibv200(lp);
	  auto ri200 = stmt200->bind(":aa", ibv200);
	  std::cerr << "stmt200->bind(\":aa\", ibv200): " << ri200.string() << std::endl;
	  auto ri201 = stmt200->execute();
	  std::cerr << "stmt200->execute(): " << ri201.string() << std::endl;
     }
     //////////////////////////////////////////////////////////////////
     // #12
     //////////////////////////////////////////////////////////////////
     OD.disconnect();
     //////////////////////////////////////////////////////////////////
     // #13
     //////////////////////////////////////////////////////////////////
     {
	  OD.connect("scott", "tiger", "asp");
	  String s200(R"(
SELECT BLOB FROM BLOBER_TEST WHERE ID = 4
)");
	  auto stmt200 = OD.prepare(s200);
	  db::oracle::lob::LocatorPtr lp;
	  lp = OD.make_locator();
	  db::oracle::lob::BlobQueryValue BLOB(lp);
	  db::oracle::lob::ClobQueryValue CLOB(lp);
	  auto ri14 = stmt200->define(1, BLOB);
	  std::cerr << "stmt200->define(1): " <<
	       ri14.string() << std::endl;
	  auto ri17 = stmt200->execute();
	  std::cerr << "stmt200->execute(): " << ri17.string() << std::endl;
	  //
	  if (! BLOB.getIndicator().is_null()) {

	       std::cerr << "BLOB.getIndicator() NOT NULL" << std::endl;
	       auto ri31 = lp->openRO();
	       std::cerr << "lp->openRO(): " << ri31.string() << std::endl;
	       std::ofstream os("src/tests/out2.jpg", std::ios::binary | std::ios::trunc);
	       if (os) {
		    if (! os.eof()) {

			 std::cerr << "OUT STREAM OK!" << std::endl;
			 db::oracle::lob::Streamer SSS(lp);
			 if (SSS >> os) {

			      std::cerr << "SSS >> os OK" << std::endl;

			 } else {

			      auto prop = SSS.getErrorInfo();
			      std::cerr << "str:  " << prop.str  << std::endl;
			 }
		    }
	       }
	  } else {

	       std::cerr << "BLOB.getIndicator() NULL --> ERROR!" << std::endl;
	  }
	  lp->close();
	  OD.disconnect();
     }
     //////////////////////////////////////////////////////////////////

     // #14
     //////////////////////////////////////////////////////////////////
     {
	  OD.connect("scott", "tiger", "asp");
	  db::oracle::lob::LocatorPtr lp;
	  lp = OD.make_locator();
	  auto ri29 = lp->make_temp_clob();
	  std::cerr << "lp->make_temp_clob(): " << ri29.string() << std::endl;
	  auto ri30 = lp->openRW();
	  std::cerr << "lp->openRW(): " << ri30.string() << std::endl;
	  std::ifstream is("src/tests/example.txt", std::ifstream::binary);
	  //std::ifstream is("src/tests/history2.txt", std::ifstream::binary);
	  if (is) {

	       db::oracle::lob::Streamer SSS(lp);
	       if (SSS << is) {

		    std::cerr << "SSS << is OK" << std::endl;

	       } else {

		    auto prop = SSS.getErrorInfo();
		    std::cerr << "str:  " << prop.str  << std::endl;
	       }
	  }
	  lp->close();

	  String s200(R"(
INSERT INTO CLOBER_TEST (ID, CLOB) VALUES (5, :aa)
)");
	  auto stmt200 = OD.prepare(s200);
	  db::oracle::lob::ClobBindValue ibv200(lp);
	  auto ri200 = stmt200->bind("aa", ibv200);
	  std::cerr << "stmt200->bind(\"aa\", ibv200): " << ri200.string() << std::endl;
	  auto ri201 = stmt200->execute();
	  std::cerr << "stmt200->execute(): " << ri201.string() << std::endl;
	  OD.commit();
	  OD.disconnect();
     }
     //////////////////////////////////////////////////////////////////

     // #15
     //////////////////////////////////////////////////////////////////
     {
	  OD.connect("scott", "tiger", "asp");
	  String s200(R"(
SELECT CLOB FROM CLOBER_TEST WHERE ID = 5
)");
	  auto stmt200 = OD.prepare(s200);
	  db::oracle::lob::LocatorPtr lp;
	  lp = OD.make_locator();
	  db::oracle::lob::ClobQueryValue CLOB(lp);
	  auto ri14 = stmt200->define(1, CLOB);
	  std::cerr << "stmt200->define(1): " <<
	       ri14.string() << std::endl;
	  auto ri17 = stmt200->execute();
	  std::cerr << "stmt200->execute(): " << ri17.string() << std::endl;
	  //
	  if (CLOB.getIndicator()) {

	       std::cerr << "CLOB.getIndicator() NOT NULL" << std::endl;
	       auto ri31 = lp->openRO();
	       std::cerr << "lp->openRO(): " << ri31.string() << std::endl;
	       std::ofstream os("src/tests/out2.txt", std::ios::binary | std::ios::trunc);
	       if (os) {
		    if (! os.eof()) {

			 std::cerr << "OUT STREAM OK!" << std::endl;
			 db::oracle::lob::Streamer SSS(lp);
			 if (SSS >> os) {

			      std::cerr << "SSS >> os OK" << std::endl;

			 } else {

			      auto prop = SSS.getErrorInfo();
			      std::cerr << "str:  " << prop.str  << std::endl;
			 }
		    }
	       }
	  } else {

	       std::cerr << "CLOB.getIndicator() BAD --> ERROR!" << std::endl;
	  }
	  lp->close();
	  OD.disconnect();
     }
     //////////////////////////////////////////////////////////////////

     // #16
     //////////////////////////////////////////////////////////////////
     {
	  OD.connect("scott", "tiger", "asp");
	  String s200(R"(
SELECT CLOB FROM CLOBER_TEST WHERE ID = 3
)");
	  auto stmt200 = OD.prepare(s200);
	  db::oracle::lob::LocatorPtr lp;
	  lp = OD.make_locator();
	  db::oracle::lob::ClobQueryValue CLOB(lp);
	  auto ri14 = stmt200->define(1, CLOB);
	  std::cerr << "stmt200->define(1): " <<
	       ri14.string() << std::endl;
	  auto ri17 = stmt200->execute();
	  std::cerr << "stmt200->execute(): " << ri17.string() << std::endl;
	  //
	  if (CLOB.getIndicator()) {
	       if (CLOB.getIndicator().is_null()) {

		    std::cerr << "CLOB.getIndicator() NULL IS GOOD!" << std::endl;

	       } else {

		    std::cerr << "CLOB.getIndicator() BAD --> ERROR!" << std::endl;
	       }
	  }
	  lp->close();
	  OD.disconnect();
     }
     //////////////////////////////////////////////////////////////////

     // #17
     //////////////////////////////////////////////////////////////////
     {
	  OD.connect("scott", "tiger", "asp");
	  db::oracle::lob::LocatorPtr lp;
	  lp = OD.make_locator();
	  auto ri29 = lp->make_temp_clob();
	  std::cerr << "lp->make_temp_clob(): " << ri29.string() << std::endl;
	  auto ri30 = lp->openRW();
	  std::cerr << "lp->openRW(): " << ri30.string() << std::endl;
	  std::ifstream is("src/tests/Text.txt", std::ifstream::binary);
	  if (is) {

	       db::oracle::lob::Streamer SSS(lp);
	       if (SSS << is) {

		    std::cerr << "SSS << is OK" << std::endl;

	       } else {

		    auto prop = SSS.getErrorInfo();
		    std::cerr << "str:  " << prop.str  << std::endl;
	       }
	  }
	  lp->close();

	  String s200(R"(
INSERT INTO CLOBER_TEST (ID, CLOB) VALUES (6, :aa)
)");
	  auto stmt200 = OD.prepare(s200);
	  db::oracle::lob::ClobBindValue ibv200(lp);
	  auto ri200 = stmt200->bind("aa", ibv200);
	  std::cerr << "stmt200->bind(\"aa\", ibv200): " << ri200.string() << std::endl;
	  auto ri201 = stmt200->execute();
	  std::cerr << "stmt200->execute(): " << ri201.string() << std::endl;
	  OD.commit();
	  OD.disconnect();
     }
     //////////////////////////////////////////////////////////////////

     // #18
     //////////////////////////////////////////////////////////////////
     {
	  OD.connect("scott", "tiger", "asp");
	  String s200(R"(
SELECT CLOB FROM CLOBER_TEST WHERE ID = 6
)");
	  auto stmt200 = OD.prepare(s200);
	  db::oracle::lob::LocatorPtr lp;
	  lp = OD.make_locator();
	  db::oracle::lob::ClobQueryValue CLOB(lp);
	  auto ri14 = stmt200->define(1, CLOB);
	  std::cerr << "stmt200->define(1): " <<
	       ri14.string() << std::endl;
	  auto ri17 = stmt200->execute();
	  std::cerr << "stmt200->execute(): " << ri17.string() << std::endl;
	  //
	  if (CLOB.getIndicator()) {

	       std::cerr << "CLOB.getIndicator() NOT NULL" << std::endl;
	       auto ri31 = lp->openRO();
	       std::cerr << "lp->openRO(): " << ri31.string() << std::endl;
	       std::ofstream os("src/tests/Text_out.txt", std::ios::binary | std::ios::trunc);
	       if (os) {
		    if (! os.eof()) {

			 std::cerr << "OUT STREAM OK!" << std::endl;
			 db::oracle::lob::Streamer SSS(lp);
			 if (SSS >> os) {

			      std::cerr << "SSS >> os OK" << std::endl;

			 } else {

			      auto prop = SSS.getErrorInfo();
			      std::cerr << "str:  " << prop.str  << std::endl;
			 }
		    }
	       }
	  } else {

	       std::cerr << "CLOB.getIndicator() BAD --> ERROR!" << std::endl;
	  }
	  lp->close();
	  OD.disconnect();
     }
     //////////////////////////////////////////////////////////////////

     // #18
     //////////////////////////////////////////////////////////////////
     {
	  OD.connect("scott", "tiger", "asp");
	  db::oracle::lob::LocatorPtr lp;
	  lp = OD.make_locator();
	  auto ri29 = lp->make_temp_clob();
	  std::cerr << "lp->make_temp_clob(): " << ri29.string() << std::endl;
	  auto ri30 = lp->openRW();
	  std::cerr << "lp->openRW(): " << ri30.string() << std::endl;
	  std::ifstream is("src/tests/history.txt", std::ifstream::binary);
	  if (is) {

	       db::oracle::lob::Streamer SSS(lp);
	       if (SSS << is) {

		    std::cerr << "SSS << is OK" << std::endl;

	       } else {

		    auto prop = SSS.getErrorInfo();
		    std::cerr << "str:  " << prop.str  << std::endl;
	       }
	  }
	  lp->close();

	  String s200(R"(
INSERT INTO CLOBER_TEST (ID, CLOB) VALUES (7, :aa)
)");
	  auto stmt200 = OD.prepare(s200);
	  db::oracle::lob::ClobBindValue ibv200(lp);
	  auto ri200 = stmt200->bind("aa", ibv200);
	  std::cerr << "stmt200->bind(\"aa\", ibv200): " << ri200.string() << std::endl;
	  auto ri201 = stmt200->execute();
	  std::cerr << "stmt200->execute(): " << ri201.string() << std::endl;
	  OD.commit();
	  OD.disconnect();
     }
     //////////////////////////////////////////////////////////////////

     // #19
     //////////////////////////////////////////////////////////////////
     {
	  OD.connect("scott", "tiger", "asp");
	  String s200(R"(
SELECT CLOB FROM CLOBER_TEST WHERE ID = 7
)");
	  auto stmt200 = OD.prepare(s200);
	  db::oracle::lob::LocatorPtr lp;
	  lp = OD.make_locator();
	  db::oracle::lob::ClobQueryValue CLOB(lp);
	  auto ri14 = stmt200->define(1, CLOB);
	  std::cerr << "stmt200->define(1): " <<
	       ri14.string() << std::endl;
	  auto ri17 = stmt200->execute();
	  std::cerr << "stmt200->execute(): " << ri17.string() << std::endl;
	  //
	  if (CLOB.getIndicator()) {

	       std::cerr << "CLOB.getIndicator() NOT NULL" << std::endl;
	       auto ri31 = lp->openRO();
	       std::cerr << "lp->openRO(): " << ri31.string() << std::endl;
	       std::ofstream os("src/tests/history_out.txt", std::ios::binary | std::ios::trunc);
	       if (os) {
		    if (! os.eof()) {

			 std::cerr << "OUT STREAM OK!" << std::endl;
			 db::oracle::lob::Streamer SSS(lp);
			 if (SSS >> os) {

			      std::cerr << "SSS >> os OK" << std::endl;

			 } else {

			      auto prop = SSS.getErrorInfo();
			      std::cerr << "str:  " << prop.str  << std::endl;
			 }
		    }
	       }
	  } else {

	       std::cerr << "CLOB.getIndicator() BAD --> ERROR!" << std::endl;
	  }
	  lp->close();
	  OD.disconnect();
     }
     //////////////////////////////////////////////////////////////////

     system("src/tests/end.sh");
     system("md5sum src/tests/example.jpg");
     system("md5sum src/tests/out.jpg");
     system("md5sum src/tests/out2.jpg");
     system("md5sum src/tests/example.txt");
     system("md5sum src/tests/out.txt");
     system("md5sum src/tests/out2.txt");
     system("md5sum src/tests/Text.txt");
     system("md5sum src/tests/Text_out.txt");
     system("md5sum src/tests/history.txt");
     system("md5sum src/tests/history_out.txt");
     return 0;
}
