#include <iostream>

#include "sqlite_orm/sqlite_orm.h"

struct Employee
{
    int id;
    std::string name;
    int age;
    std::string address;
    double salary;
};

struct DetailedEmployee : public Employee
{
    std::string birthData;
};

int main(int argc, char **argv)
{
    auto storage = xhsqlite::make_storage("insert.sql3",
                                            xhsqlite::make_table("Company",
                                                                   xhsqlite::make_column("ID", &Employee::id, xhsqlite::primary_key()),
                                                                   xhsqlite::make_column("NAME", &Employee::name),
                                                                   xhsqlite::make_column("AGE", &Employee::age),
                                                                   xhsqlite::make_column("ADDRESS", &Employee::address),
                                                                   xhsqlite::make_column("SALARY", &Employee::salary)));
    storage.sync_schema();
    storage.remove_all<Employee>();

    // 添加一条记录
    Employee paul{-1, "Paul", 32, "California", 20000.00};
    paul.id = storage.insert(paul);

    // 添加另一条数据
    DetailedEmployee teddy;
    teddy.name = "Teddy";
    teddy.age = 23;
    teddy.address = "Norway";
    teddy.salary = 20000.00;

    // 插入子类时必须指定类型
    teddy.id = storage.insert<Employee>(teddy);

    // 其它三个员工
    std::vector<Employee> otherEmployees;
    otherEmployees.push_back(Employee{-1, "Mark", 25, "Rich-Mond", 65000.00});
    otherEmployees.push_back(Employee{-1, "David", 27, "Texas", 85000.00});
    otherEmployees.push_back(Employee{-1, "Kim", 22, "South-Hall", 45000.00});
    //  transaction is optional. It is used here to optimize sqlite usage - every insert opens
    //  and closes database. So triple insert will open and close the db three times.
    //  Transaction openes and closes the db only once.
    storage.transaction([&] {
        for (auto &employee: otherEmployees)
        {
            storage.insert(employee);
        }
        return true;
    });


    // 导出数据库数据
    for (auto &employee: storage.iterate<Employee>())
    {
        std::cout << storage.dump(employee) << std::endl;
    }

    return 0;
}