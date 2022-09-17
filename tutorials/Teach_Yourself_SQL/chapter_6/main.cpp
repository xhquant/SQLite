#include <iostream>

#include "xhsqlite3/xhsqlite3.hpp"
#include "table_struct.hpp"

using namespace xhsqlite3;

int main(int argc, char **argv)
{
    auto storage = init_storage("../db/teach_yourself_SQL.sql3");
    // storage.sync_schema();

    // 通配符LIKE, %
    auto prod_id_name = storage.select(columns(&Products::prod_id, &Products::prod_name), from<Products>(), where(like(&Products::prod_name, "Fish%")));
    printf("%-20s%-20s\n", "prod_id", "prod_name");
    for (auto &row: prod_id_name)
    {
        printf("%-20s%-20s\n", std::get<0>(row).c_str(), std::get<1>(row).c_str());
    }
    std::cout << std::endl;

    // 通配符LIKE，%
    auto prod_id_name_2 = storage.select(columns(&Products::prod_id, &Products::prod_name), from<Products>(), where(like(&Products::prod_name, "%bean bag%")));
    printf("%-20s%-20s\n", "prod_id", "prod_name");
    for (auto &row: prod_id_name_2)
    {
        printf("%-20s%-20s\n", std::get<0>(row).c_str(), std::get<1>(row).c_str());
    }
    std::cout << std::endl;

    


    return 0;
}