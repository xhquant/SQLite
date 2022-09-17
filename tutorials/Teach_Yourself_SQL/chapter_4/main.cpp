#include <iostream>

#include "xhsqlite3/xhsqlite3.hpp"
#include "table_struct.hpp"

using namespace xhsqlite3;

int main(int argc, char **argv)
{
    auto storage = init_storage("../db/teach_yourself_SQL.sql3");
    // storage.sync_schema();

    // 带条件的选择
    auto prod_name_price = storage.select(columns(&Products::prod_name, &Products::prod_price), from<Products>(), where(is_equal(&Products::prod_price, 3.49)));
    printf("%-20s%-20s\n", "prod_name", "prod_price");
    for (auto &row: prod_name_price)
    {
        printf("%-20s%-20.2f\n", std::get<0>(row).c_str(), std::get<1>(row));
    }
    std::cout << std::endl;

    // 带条件的选择，检测单个值。
    auto prod_name_price_2 = storage.select(columns(&Products::prod_name, &Products::prod_price), from<Products>(), where(lesser_than(&Products::prod_price, 10.)));
    printf("%-20s%-20s\n", "prod_name", "prod_price");
    for (auto &row: prod_name_price_2)
    {
        printf("%-20s%-20.2f\n", std::get<0>(row).c_str(), std::get<1>(row));
    }
    std::cout << std::endl;

    // 带条件的选择，检测单个值。
    auto prod_name_price_3 = storage.select(columns(&Products::prod_name, &Products::prod_price), from<Products>(), where(lesser_or_equal(&Products::prod_price, 10.)));
    printf("%-20s%-20s\n", "prod_name", "prod_price");
    for (auto &row: prod_name_price_3)
    {
        printf("%-20s%-20.2f\n", std::get<0>(row).c_str(), std::get<1>(row));
    }
    std::cout << std::endl;

    // 不匹配检查
    auto prod_id_name = storage.select(columns(&Products::vend_id, &Products::prod_name), from<Products>(), where(is_not_equal(&Products::vend_id, "DLL01")));
    printf("%-20s%-20s\n", "prod_id", "prod_name");
    for (auto &row: prod_id_name)
    {
        printf("%-20s%-20s\n", std::get<0>(row).c_str(), std::get<1>(row).c_str());
    }
    std::cout << std::endl;

    // 范围检查
    auto prod_name_price_4 = storage.select(columns(&Products::prod_name, &Products::prod_price), from<Products>(), where(between(&Products::prod_price, 5, 10)));
    printf("%-20s%-20s\n", "prod_name", "prod_price");
    for (auto &row: prod_name_price_4)
    {
        printf("%-20s%-20.2f\n", std::get<0>(row).c_str(), std::get<1>(row));
    }
    std::cout << std::endl;

    // 空值检查
    auto prod_name_null = storage.select(&Products::prod_name, from<Products>(), where(is_null(&Products::prod_name)));
    std::cout << prod_name_null.size() << std::endl;

    // 空值检查
    auto cust_email = storage.select(&Customers::cust_name, from<Customers>(), where(is_null(&Customers::cust_email)));
    printf("%s\n", "cust_email");
    for (auto &row: cust_email)
    {
        printf("%s\n", row.c_str());
    }


    return 0;
}