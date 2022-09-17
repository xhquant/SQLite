#include <iostream>

#include "xhsqlite3/xhsqlite3.hpp"
#include "table_struct.hpp"


int main(int argc, char **argv)
{
    auto storage = init_storage("../db/teach_yourself_SQL.sql3");
    // storage.sync_schema();

    // 检索单个列
    auto prod_name = storage.select(xhsqlite3::columns(&Products::prod_name));
    for (auto &name: prod_name)
    {
        std::cout << std::get<0>(name) << std::endl;
    }
    std::cout << std::endl;

    // 检索多个列
    auto prod_id_name_price = storage.select(xhsqlite3::columns(&Products::prod_id, &Products::prod_name, &Products::prod_price));
    printf("%-10s %-30s %-10s\n", "prod_id", "prod_name", "prod_price");
    for (auto &row: prod_id_name_price)
    {
        printf("%-10s %-30s %-10.2f\n", std::get<0>(row).c_str(), std::get<1>(row).c_str(), std::get<2>(row));
    }
    std::cout << std::endl;

    // 检索所有列
    auto prods = storage.select(xhsqlite3::asterisk<Products>());
    printf("%-10s %-20s %-30s %-15s %-20s\n", "prod_id", "vend_id", "prod_name", "prod_price", "prod_desc");
    for (auto &row: prods)
    {
        printf("%-10s %-20s %-30s %-15.2f %-20s\n", std::get<0>(row).c_str(), std::get<1>(row).c_str(), std::get<2>(row).c_str(), std::get<3>(row), std::get<4>(row).c_str());
    }
    std::cout << std::endl;

    // 检索产品vend_id
    auto vend_id = storage.select(xhsqlite3::columns(&Products::vend_id));
    printf("%-20s\n", "vend_id");
    for (auto &row: vend_id)
    {
        printf("%-20s\n", std::get<0>(row).c_str());
    }
    std::cout << std::endl;

    // 使用DISTINCT
    // 检索产品vend_id
    vend_id = storage.select(xhsqlite3::columns(xhsqlite3::distinct(&Products::vend_id)));
    printf("%-20s\n", "vend_id");
    for (auto &row: vend_id)
    {
        printf("%-20s\n", std::get<0>(row).c_str());
    }
    std::cout << std::endl;

    // 限制使用的行 limit
    // 检索产品prod_name
    auto prod_name_limit = storage.select(xhsqlite3::columns(&Products::prod_name), xhsqlite3::limit(3));
    for (auto &row: prod_name_limit)
    {
        std::cout << std::get<0>(row) << std::endl;
    }

    return 0;
}