#include <unity.h>

#include "static_array_lib.h"

/* Test array declaration and initialization */
SARR_DECL(test_array, int, 10);

void setUp(void) {
  // Reset valid length before each test
  test_array_length_ = 0;
}

void tearDown(void) {
  // Optional: Cleanup code after each test
}

void test_sarr_set_get(void) {
  int value;
  // Test setting and getting elements
  TEST_ASSERT_EQUAL_INT(0, test_array_set(0, 42));
  TEST_ASSERT_EQUAL_INT(0, test_array_get(0, &value));
  TEST_ASSERT_EQUAL_INT(42, value);

  TEST_ASSERT_EQUAL_INT(0, test_array_set(5, 99));
  TEST_ASSERT_EQUAL_INT(0, test_array_get(5, &value));
  TEST_ASSERT_EQUAL_INT(99, value);
}

void test_sarr_size(void) {
  // Test array size function
  TEST_ASSERT_EQUAL_INT(10, test_array_size());
}

void test_sarr_length(void) {
  // Test initial length
  TEST_ASSERT_EQUAL_INT(0, test_array_length());

  // Test length after setting elements
  TEST_ASSERT_EQUAL_INT(0, test_array_set(2, 10));
  TEST_ASSERT_EQUAL_INT(3, test_array_length());

  TEST_ASSERT_EQUAL_INT(0, test_array_set(8, 20));
  TEST_ASSERT_EQUAL_INT(9, test_array_length());
}

void test_sarr_overwrite(void) {
  int value;
  // Test overwriting existing values
  TEST_ASSERT_EQUAL_INT(0, test_array_set(1, 11));
  TEST_ASSERT_EQUAL_INT(0, test_array_get(1, &value));
  TEST_ASSERT_EQUAL_INT(11, value);

  TEST_ASSERT_EQUAL_INT(0, test_array_set(1, 22));
  TEST_ASSERT_EQUAL_INT(0, test_array_get(1, &value));
  TEST_ASSERT_EQUAL_INT(22, value);

  // Length should not change when overwriting
  TEST_ASSERT_EQUAL_INT(2, test_array_length());
}

void test_sarr_out_of_bounds(void) {
  // Ensure out-of-bounds access is handled properly
  TEST_ASSERT_EQUAL_INT(ENOBUFS, test_array_set(15, 100));

  int value;
  TEST_ASSERT_EQUAL_INT(ENOBUFS, test_array_get(15, &value));

  // Check that the length remains consistent
  TEST_ASSERT_EQUAL_INT(0, test_array_length());
}
