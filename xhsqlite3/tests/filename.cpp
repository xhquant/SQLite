#include <xhsqlite3/xhsqlite3.hpp>
#include <catch2/catch.hpp>

using namespace sqlite_orm;

TEST_CASE("filename") {
    {
        auto storage = make_storage("");
        REQUIRE(storage.filename() == "");
    }
    {
        auto storage = make_storage(":memory:");
        REQUIRE(storage.filename() == ":memory:");
    }
    {
        auto storage = make_storage("myDatabase.sqlite");
        REQUIRE(storage.filename() == "myDatabase.sqlite");
    }
}
