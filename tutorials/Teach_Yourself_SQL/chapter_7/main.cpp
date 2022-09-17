#include <iostream>

#include "xhsqlite3/xhsqlite3.hpp"
#include "table_struct.hpp"

using namespace xhsqlite3;

int main(int argc, char **argv)
{
    auto storage = init_storage("../db/teach_yourself_SQL.sql3");
    // storage.sync_schema();

    // 等于选择
    auto order_items_id_quantity_price = storage.select(columns(&OrderItems::prod_id, &OrderItems::quantity, &OrderItems::item_price), from<OrderItems>(),
                                                        where(eq(&OrderItems::order_num, 20008)));
    printf("%-20s%-20s%-20s\n", "prod_id", "quantity", "item_price");
    for (auto &row: order_items_id_quantity_price)
    {
        printf("%-20s%-20d%-20.2f\n", std::get<0>(row).c_str(), std::get<1>(row), std::get<2>(row));
    }
    std::cout << std::endl;

    // 乘法
    auto order_items_id_quantity_price_2 = storage.select(columns(&OrderItems::prod_id, &OrderItems::quantity, &OrderItems::item_price), from<OrderItems>(),
                                                        where(eq(&OrderItems::order_num, 20008)));
    printf("%-20s%-20s%-20s\n", "prod_id", "quantity", "item_price");
    for (auto &row: order_items_id_quantity_price_2)
    {
        printf("%-20s%-20d%-20.2f\n", std::get<0>(row).c_str(), std::get<1>(row), std::get<2>(row));
    }
    std::cout << std::endl;


    return 0;
}