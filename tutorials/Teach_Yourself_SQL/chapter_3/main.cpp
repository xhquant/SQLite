#include <iostream>

#include "xhsqlite3/xhsqlite3.hpp"
#include "table_struct.hpp"

using namespace xhsqlite3;

int main(int argc, char **argv)
{
    auto storage = init_storage("../db/teach_yourself_SQL.sql3");
    // storage.sync_schema();

    // 检索单个列
    auto prod_name = storage.select(&Products::prod_name);
    printf("%-20s\n", "prod_name");
    for (auto &row: prod_name)
    {
        printf("%-20s\n", row.c_str());
    }
    std::cout << std::endl;

    // 检索排序
    auto prod_name_order_by = storage.select(&Products::prod_name, order_by(&Products::prod_name));
    printf("%-20s\n", "prod_name");
    for (auto &row: prod_name_order_by)
    {
        printf("%-20s\n", row.c_str());
    }
    std::cout << std::endl;

    // 按多个排序
    auto prod_name_order_by_multi = storage.select(columns(&Products::prod_id, &Products::prod_price, &Products::prod_name), multi_order_by(order_by(&Products::prod_price), order_by(&Products::prod_name)));
    printf("%-20s %-20s %-20s\n", "prod_id", "prod_price", "prod_name");
    for (auto &row: prod_name_order_by_multi)
    {
        printf("%-20s %-20.2f %-20s\n", std::get<0>(row).c_str(), std::get<1>(row), std::get<2>(row).c_str());
    }
    std::cout << std::endl;

    // 指定排序方向
    auto prod_price = storage.select(columns(&Products::prod_id, &Products::prod_price, &Products::prod_name), order_by(&Products::prod_price).desc());
    printf("%-20s %-20s %-20s\n", "prod_id", "prod_price", "prod_name");
    for (auto &row: prod_price)
    {
        printf("%-20s %-20.2f %-20s\n", std::get<0>(row).c_str(), std::get<1>(row), std::get<2>(row).c_str());
    }
    std::cout << std::endl;

    // 指定多个排序
    auto prod_price_multi = storage.select(columns(&Products::prod_id, &Products::prod_price, &Products::prod_name), multi_order_by(order_by(&Products::prod_price).desc(), order_by(&Products::prod_name)));
    printf("%-20s %-20s %-20s\n", "prod_id", "prod_price", "prod_name");
    for (auto &row: prod_price_multi)
    {
        printf("%-20s %-20.2f %-20s\n", std::get<0>(row).c_str(), std::get<1>(row), std::get<2>(row).c_str());
    }
    std::cout << std::endl;


    return 0;
}