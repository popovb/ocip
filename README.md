```
########                         OCIP
#      # 
#      # ####### #    ## ####### 
#      # #       #   # # #     #
#      # #       #  #  # #     # 
#      # #       # #   # #     # 
#      # #       ##    # #     # 
######## ####### #     # #     #
```

# ОСИП(OCIP) --- лёгкая обёртка C++ над [Oracle Call Interface](http://www.oracle.com/technetwork/database/features/oci/)

## Соединение с базой

### Инициализация
```cpp
using namespace db::oracle;
Driver* OD;
try {
	OD = new Driver;

} catch(Error& e) {

	std::cerr << e.what() << std::endl;
	exit(1);
}
```

### Соединение
```cpp
//scott - name
//tiger - password
//asp - connect string
try {
	OD->connect("scott", "tiger", "asp");

} catch(Error& e) {

	std::cerr << e.what() << std::endl;
	exit(1);
}
```

### Commit & Rollback
```cpp
//ri1 & ri2 -- return info
auto ri1 = OD->commit();
auto ri2 = OD->rollback();
if (ri1) { std::cerr << "OK!\n"; }
```

### Разъединение
```cpp
OD->disconnect();
delete OD;
```

## Работа со statement

### INSERT
```cpp
String s1("INSERT INTO DEPT (DEPTNO, DNAME, LOC) VALUES (50, \'DEV\', \'MOSCOW\'");
StatementPtr stmt;
try {
	stmt = OD->prepare(s1);

} catch (Error& e) {

	std::cerr << e.what() << std::endl;
	exit(1);
}

auto ri1 = stmt->execute();
//or stmt->execute(1);
//1 - iteraton numbers
if (!ri1) { std::cerr << ri1.string() << std::endl; }
```

### INSERT с биндингом
#### Позизионный биндинг
```cpp
String s2("INSERT INTO DEPT (DEPTNO, DNAME, LOC) VALUES (:1, :2, :3)");
auto stmt2 = OD->prepare(s2);

InStringBindValue bv1("50");
InStringBindValue bv2("DEV");
InStringBindValue bv3("MOSCOW");

auto ri3 = stmt2->bind(1, bv1);
auto ri4 = stmt2->bind(2, bv2);
auto ri5 = stmt2->bind(3, bv3);

auto ri6 = stmt2->execute();
if (!ri6) { std::cerr << ri6.string() << std::endl; }
```
#### Именованный биндинг
```cpp
InStringBindValue bv6("70");
//insert NULL value:
InStringBindValue bv7;

auto ri10 = stmt2->bind("1", bv6);
auto ri11 = stmt2->bind("3", bv7);

auto ri12 = stmt2->execute();
if (!ri12) { std::cerr << ri12.string() << std::endl; }
```

### SELECT
```cpp
StringQueryValue DEPTNO;
StringQueryValue DNAME;
StringQueryValue LOC;

String s4("select DEPTNO, DNAME, LOC from DEPT");
auto stmt4 = OD->prepare(s4);

//defining:
auto ri14 = stmt4->define(1, DEPTNO);
auto ri15 = stmt4->define(2, DNAME);
auto ri16 = stmt4->define(3, LOC);

auto ri17 = stmt4->execute(0);
if (ri17.isNoData()) {

	std::cerr << ri17.string() << std::endl;
	exit(0);
}

//fetching
auto ri18 = stmt4->fetch();

while (ri18) {
	if (DEPTNO.getIndicator().is_null()) {
		std::cerr << "NULL\n";

	} else {
		std::cerr << ((StringBuffer&)(DEPTNO.getBuffer())).string();
	}
	ri18 = stmt4->fetch();
}
```

### INSERT c RETURNING
```cpp
String s5("insert into DEPT values (60, \'DEV\', \'MOSCOW\') returning LOC into :v");

auto stmt5 = OD->prepare(s5);
OutStringBindValue OBV(150);
OBV.getBuffer().clear();
auto ri19 = stmt5->bind("v", OBV);
auto ri20 = stmt5->execute();

if (OBV.getIndicator().is_null()) {

	std::cerr << "NULL\n";

} else {

	std::cerr << OBV.getBuffer().string() << std::endl;
}
```

## Работа с LOBами
### Загрузка в базу из файла
```cpp
#include <LobStreamer.hpp>

lob::LocatorPtr lp;
try {
	lp = OD->make_locator();

} catch(Error& e) {

	std::cerr << e.what() << std::endl;
	exit(1);
}

//создать временный LOB
auto ri29 = lp->make_temp_clob(); //или make_temp_blob()

//открыть
auto ri30 = lp->openRW();

//создать поток
std::ifstream is("src/tests/history.txt", std::ifstream::binary);
if (is) {

	lob::Streamer SSS(lp);
	if (SSS << is) {
		std::cerr << "OK\n" << std::endl;

	} else {
		auto prop = SSS.getErrorInfo();
		std::cerr << prop.str  << std::endl;
	}
}
lp->close();

//вставка LOBa
String s200("INSERT INTO CLOBER_TEST (ID, CLOB) VALUES (7, :aa)");
auto stmt200 = OD->prepare(s200);
lob::ClobBindValue ibv200(lp);
auto ri200 = stmt200->bind("aa", ibv200);
auto ri201 = stmt200->execute();
```

### Выгрузка из базы в файл
```cpp
#include <LobQueryValue.hpp>

String s200("SELECT CLOB FROM CLOBER_TEST WHERE ID = 6");
auto stmt200 = OD->prepare(s200);
lob::LocatorPtr lp;
lp = OD->make_locator();
lob::ClobQueryValue CLOB(lp);
auto ri14 = stmt200->define(1, CLOB);
auto ri17 = stmt200->execute();
std::ofstream os("src/tests/history_out.txt", std::ios::binary | std::ios::trunc);
lob::Streamer SSS(lp);
if (SSS >> os) {

	std::cerr << "OK\n" << std::endl;

} else {
	auto prop = SSS.getErrorInfo();
	std::cerr << prop.str  << std::endl;
}
lp->close();
```

## Ещё примеры
src/tests/1.cpp

## Компиляция
```sh
cmake -D OCI_INC_DIR=/path_to_headers_oci -D OCI_LIB_DIR=/path_to_lib_oci CMakeLists.txt
make
```

## Лицензия
Mozilla Public License Version 2.0
