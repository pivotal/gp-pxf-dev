#include <stdio.h>
#include <stdlib.h>
#include "LibpqCommon.h"

int main(int argc, char *argv[])
{
    PGconn *conn = getDBDefaultConnection();
    ASSERT_TRUE(CONNECTION_OK == PQstatus(conn));
   
    dropTable(conn, "libpqtable");
    createTable(conn, "CREATE TABLE libpqtable (a int)");
    printf("create table success\n");

    PGresult *result = NULL;
    result = PQexec(conn, "START TRANSACTION");
    ASSERT_TRUE(PGRES_COMMAND_OK == PQresultStatus(result));
    printf("start transaction success\n");

    int num = insertData(conn, "INSERT INTO libpqtable VALUES (1)");
    ASSERT_TRUE(num == 1);
    num = insertData(conn, "INSERT INTO libpqtable VALUES (2)");
    ASSERT_TRUE(num == 1);
    printf("insert data into table success\n");
   
    result = PQexec(conn, "ROLLBACK");
    ASSERT_TRUE(PGRES_COMMAND_OK == PQresultStatus(result));
    printf("transaction rollback success\n");
    
    char *sql = "SELECT a FROM libpqtable";
    result = PQexec(conn, sql);
    ASSERT_TRUE(PGRES_TUPLES_OK == PQresultStatus(result));

    num = PQntuples(result);
    ASSERT_TRUE(num == 0);
    printf("select data from table success\n");

    PQclear(result);

    dropTable(conn, "libpqtable");
    printf("drop table success\n");

    PQfinish(conn);

    return 0;
}
