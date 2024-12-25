#include "static_array_lib.h"
#include <unity.h>

/* Test array declaration and initialization */
SARR_DECL(test_array, int, 10);

void setUp(void) {
  // Reset valid length before each test
  test_array_offset = 0;
}

void tearDown(void) {
  // Optional: Cleanup code after each test
}

void test_sarr_append_get(void) {
  int *value;

  // Test appending and getting elements
  TEST_ASSERT_EQUAL_INT(0, test_array_append(42));
  TEST_ASSERT_EQUAL_INT(0, test_array_get(0, &value));
  TEST_ASSERT_NOT_NULL(value);
  TEST_ASSERT_EQUAL_INT(42, *value);

  TEST_ASSERT_EQUAL_INT(0, test_array_append(99));
  TEST_ASSERT_EQUAL_INT(0, test_array_get(1, &value));
  TEST_ASSERT_NOT_NULL(value);
  TEST_ASSERT_EQUAL_INT(99, *value);
}

void test_sarr_size(void) {
  // Test array size function
  TEST_ASSERT_EQUAL_INT(10, test_array_size());
}

void test_sarr_length(void) {
  // Test initial length
  TEST_ASSERT_EQUAL_INT(0, test_array_length());

  // Test length after appending elements
  TEST_ASSERT_EQUAL_INT(0, test_array_append(10));
  TEST_ASSERT_EQUAL_INT(1, test_array_length());

  TEST_ASSERT_EQUAL_INT(0, test_array_append(20));
  TEST_ASSERT_EQUAL_INT(2, test_array_length());
}

void test_sarr_overwrite(void) {
  int *value;

  // Test appending and overwriting existing values
  TEST_ASSERT_EQUAL_INT(0, test_array_append(11));
  TEST_ASSERT_EQUAL_INT(0, test_array_get(0, &value));
  TEST_ASSERT_NOT_NULL(value);
  TEST_ASSERT_EQUAL_INT(11, *value);

  TEST_ASSERT_EQUAL_INT(0, test_array_append(22));
  TEST_ASSERT_EQUAL_INT(0, test_array_get(1, &value));
  TEST_ASSERT_NOT_NULL(value);
  TEST_ASSERT_EQUAL_INT(22, *value);

  // Length should reflect the number of appended elements
  TEST_ASSERT_EQUAL_INT(2, test_array_length());
}

void test_sarr_out_of_bounds(void) {
  int *value;

  // Ensure appending beyond capacity is handled properly
  for (size_t i = 0; i < 10; ++i) {
    TEST_ASSERT_EQUAL_INT(0, test_array_append((int)i));
  }

  // This append should fail
  TEST_ASSERT_EQUAL_INT(ENOBUFS, test_array_append(100));

  // Attempt to access out-of-bounds index
  TEST_ASSERT_EQUAL_INT(ENOENT, test_array_get(15, &value));

  // Check that the length remains consistent
  TEST_ASSERT_EQUAL_INT(10, test_array_length());
}
