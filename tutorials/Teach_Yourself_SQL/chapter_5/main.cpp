#include <iostream>

#include "xhsqlite3/xhsqlite3.hpp"
#include "table_struct.hpp"

using namespace xhsqlite3;

int main(int argc, char **argv)
{
    auto storage = init_storage("../db/teach_yourself_SQL.sql3");
    // storage.sync_schema();

    // 组合where, and
    auto prod_id_price_name = storage.select(columns(&Products::prod_id, &Products::prod_price, &Products::prod_name), from<Products>(), where(is_equal(&Products::vend_id, "DLL01") and lesser_or_equal(&Products::prod_price, 4)));
    printf("%-20s%-20s%-20s\n", "prod_id", "prod_price", "prod_name");
    for (auto &row: prod_id_price_name)
    {
        printf("%-20s%-20.2f%-20s\n", std::get<0>(row).c_str(), std::get<1>(row), std::get<2>(row).c_str());
    }
    std::cout << std::endl;

    // 组合where, or
    auto prod_name_price = storage.select(columns(&Products::prod_name, &Products::prod_price), from<Products>(), where(is_equal(&Products::vend_id, "DLL01") or is_equal(&Products::vend_id, "BRS01")));
    printf("%-20s%-20s\n", "prod_name", "prod_price");
    for (auto &row: prod_name_price)
    {
        printf("%-20s%-20.2f\n", std::get<0>(row).c_str(), std::get<1>(row));
    }
    std::cout << std::endl;

    // 组合where, and, or
    auto prod_name_price_2 = storage.select(columns(&Products::prod_name, &Products::prod_price), from<Products>(),
                                            where((is_equal(&Products::vend_id, "DLL01") or is_equal(&Products::vend_id, "BRS01"))
                                                  and (greater_or_equal(&Products::prod_price, 10))));
    printf("%-20s%-20s\n", "prod_name", "prod_price");
    for (auto &row: prod_name_price_2)
    {
        printf("%-20s%-20.2f\n", std::get<0>(row).c_str(), std::get<1>(row));
    }
    std::cout << std::endl;

    // 组合where, in
    auto prod_name_price_3 = storage.select(columns(&Products::prod_name, &Products::prod_price), from<Products>(),
                                            where(in(&Products::vend_id, {"DLL01", "BRS01"})),
                                            order_by(&Products::prod_name));
    printf("%-20s%-20s\n", "prod_name", "prod_price");
    for (auto &row: prod_name_price_3)
    {
        printf("%-20s%-20.2f\n", std::get<0>(row).c_str(), std::get<1>(row));
    }
    std::cout << std::endl;

    // 组合where, not
    auto prod_name_2 = storage.select(&Products::prod_name, from<Products>(),
                                      where(not eq(&Products::vend_id, "DLL01")),
                                      order_by(&Products::prod_name));
    printf("%-20s\n", "prod_name");
    for (auto &row: prod_name_2)
    {
        printf("%-20s\n", row.c_str());
    }
    std::cout << std::endl;

    return 0;
}