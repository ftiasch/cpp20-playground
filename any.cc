#include <catch2/catch_all.hpp>
#include <catch2/generators/catch_generators_all.hpp>

#include <any>
#include <optional>
#include <variant>

TEST_CASE("std::any") {
  std::any some = 233, nothing;
  REQUIRE_THROWS_AS(std::any_cast<double>(some), std::bad_any_cast);
  REQUIRE(std::any_cast<int>(some) == 233);
  REQUIRE(some.type() == typeid(int));
  REQUIRE(some.has_value());
  REQUIRE_FALSE(nothing.has_value());
  some.reset();
  REQUIRE_FALSE(some.has_value());
}

TEST_CASE("std::optional") {
  std::optional<int> some = 233, nothing;
  REQUIRE(some.has_value());
  REQUIRE_FALSE(nothing.has_value());
  REQUIRE(*some == 233);
  REQUIRE(some.value_or(42) == 233);
  REQUIRE(nothing.value_or(42) == 42);
  some.reset();
  REQUIRE_FALSE(some.has_value());
}

TEST_CASE("std::variant") {
  std::variant<int, bool> v = 42;
  REQUIRE(std::variant_size_v<decltype(v)> == 2);
  REQUIRE(std::get<int>(v) == 42);
  REQUIRE(*std::get_if<int>(&v) == 42);
  REQUIRE(std::get_if<bool>(&v) == nullptr);
  REQUIRE_THROWS_AS(std::get<bool>(v), std::bad_variant_access);
  REQUIRE(v.index() == 0);
  REQUIRE(std::holds_alternative<int>(v));
  REQUIRE_FALSE(std::holds_alternative<bool>(v));
  v = true;
  REQUIRE(std::get<bool>(v));
  REQUIRE(v.index() == 1);
  REQUIRE_FALSE(std::holds_alternative<int>(v));
  REQUIRE(std::holds_alternative<bool>(v));
}