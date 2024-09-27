/*
Connect C++ to the SQL Database:

Use a library like MySQL Connector/C++ or SQLite3 to 
connect your C++ application to the database.
*/

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>
#include <cppconn/resultset.h>

sql::mysql::MySQL_Driver *driver;
sql::Connection *con;
sql::Statement *stmt;
sql::ResultSet *res;

driver = sql::mysql::get_mysql_driver_instance();
con = driver->connect("tcp://127.0.0.1:3306", "user", "password");
con->setSchema("banking_system");
