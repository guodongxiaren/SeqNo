/*************************************************************************
	> File Name: main.cpp
	> Author: 
	> Mail: 
	> Created Time: Wed 04 Apr 2018 09:35:27 PM CST
 ************************************************************************/

#include <iostream>

#include <mysql_driver.h>
#include <mysql_connection.h>
using namespace std;
using namespace sql;
int main()
{
    mysql::MySQL_Driver *driver;
    Connection *con;

    driver = mysql::get_mysql_driver_instance();
    if (driver)
    {
        cout<<"dirver ok"<<endl;
    }

    con = driver->connect("tcp://127.0.0.1:3306", "root", "root1234");
    if (con)
    {
        cout<<"conn ok"<<endl;
    }

    delete con;
	// driver不需要显式delete，Connection对象会小心释放它
}
