/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 04 Apr 2018 09:35:27 PM CST
 ************************************************************************/

#include <iostream>

#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/statement.h>

#include <properties.hpp>

using namespace std;
using namespace sql;

int get_seq_no(Connection *con, long& value)
{
    con->setAutoCommit(false);
    Statement *stmt = con->createStatement();
    if (!stmt)
    {
         cout<<"stmt error"<<endl;
         return -1;
            
    }
     // 执行各种SQL语句
    stmt->execute("USE test");   

    //con->commit();
    con->rollback();

}
int main()
{
    Properties prop;
    ifstream in("../conf/seqno.ini");
    prop.load(in);
    string dbHost = prop.getProperty("DBHost");
    string dbPort = prop.getProperty("DBPort");
    string dbUser = prop.getProperty("DBUser");
    string dbPswd = prop.getProperty("DBPswd");

    mysql::MySQL_Driver *driver;
    Connection *con;

    driver = mysql::get_mysql_driver_instance();
    if (driver)
    {
        cout<<"dirver ok"<<endl;
    }
    string schema = "tcp://" + dbHost + ":" + dbPort;
    cout<<schema<<endl;
    con = driver->connect(schema, dbUser, dbPswd);
    if (con)
    {
        cout<<"conn ok"<<endl;
    }

    delete con;
	// driver不需要显式delete，Connection对象会小心释放它
}
