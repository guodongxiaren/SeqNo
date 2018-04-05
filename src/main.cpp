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
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>


#include <properties.hpp>

using namespace std;
using namespace sql;

int get_seq_no(Connection *con, int appid)
{
    con->setAutoCommit(false);
    PreparedStatement *stmt = con->prepareStatement("select no from test.seq where appid = ? for update");
    if (!stmt)
    {
         cout<<"stmt error"<<endl;
         return -1;
            
    }
    stmt->setInt(1, appid);
     // 执行各种SQL语句
    con->setSchema("test");
    ResultSet* res = stmt->executeQuery();   

    int value;
    while (res->next())
    {
        cout<<"xxx"<<res->getInt("no")<<endl;
        value = res->getInt("no");
    }

    con->commit();
    return value;

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
    int no;
    no = get_seq_no(con, 123);
    cout<<"seq no:"<<no<<endl;

    delete con;
	// driver不需要显式delete，Connection对象会小心释放它
}
