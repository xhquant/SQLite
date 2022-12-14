#include <xhsqlite3/xhsqlite3.hpp>
#include <catch2/catch.hpp>

using namespace sqlite_orm;

TEST_CASE("statement_serializator unique") {
    internal::serializator_context_base context;
    auto un = unique();
    auto value = serialize(un, context);
    REQUIRE(value == "UNIQUE");
}
