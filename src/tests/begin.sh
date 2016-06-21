#!/bin/sh

#export LD_LIBRARY_PATH=pre/lib

sqlplus -S scott/tiger@asp @src/tests/create_test_table.sql

