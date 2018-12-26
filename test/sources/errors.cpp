#include "common.hpp"

TEST(errors_tests, errors_test)
{
  using namespace primordialmachine;
  try {
  } catch (const test_exception& ex) {
    SUCCEED();
  } catch (const exception& ex) {
    FAIL();
  } catch (...) {
    FAIL();
  }
}
