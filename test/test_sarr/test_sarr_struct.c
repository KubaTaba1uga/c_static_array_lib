#include <unity.h>

#include "static_array_lib.h"

/* Define a custom struct to use with SARR */
typedef struct {
  int id;
  char name[20];
} CustomStruct;

/* Declare a SARR for CustomStruct */
SARR_DECL(custom_array, CustomStruct, 10);

void setUp(void) {
  // Reset valid length before each test
  custom_array_offset = 0;
}

void tearDown(void) {
  // Optional: Cleanup code after each test
}

void test_sarr_append_get_struct(void) {
  CustomStruct value;

  // Test appending and getting elements
  CustomStruct item1 = {1, "Item1"};
  TEST_ASSERT_EQUAL_INT(0, custom_array_append(item1));
  TEST_ASSERT_EQUAL_INT(0, custom_array_get(0, &value));
  TEST_ASSERT_EQUAL_INT(1, value.id);
  TEST_ASSERT_EQUAL_STRING("Item1", value.name);

  CustomStruct item2 = {2, "Item2"};
  TEST_ASSERT_EQUAL_INT(0, custom_array_append(item2));
  TEST_ASSERT_EQUAL_INT(0, custom_array_get(1, &value));
  TEST_ASSERT_EQUAL_INT(2, value.id);
  TEST_ASSERT_EQUAL_STRING("Item2", value.name);
}

void test_sarr_size_struct(void) {
  // Test array size function
  TEST_ASSERT_EQUAL_INT(10, custom_array_size());
}

void test_sarr_length_struct(void) {
  // Test initial length
  TEST_ASSERT_EQUAL_INT(0, custom_array_length());

  // Test length after appending elements
  CustomStruct item = {3, "Item3"};
  TEST_ASSERT_EQUAL_INT(0, custom_array_append(item));
  TEST_ASSERT_EQUAL_INT(1, custom_array_length());

  CustomStruct item2 = {4, "Item4"};
  TEST_ASSERT_EQUAL_INT(0, custom_array_append(item2));
  TEST_ASSERT_EQUAL_INT(2, custom_array_length());
}

void test_sarr_out_of_bounds_struct(void) {
  // Ensure appending beyond capacity is handled properly
  CustomStruct item = {5, "OverflowItem"};

  for (size_t i = 0; i < 10; ++i) {
    CustomStruct temp = {i, "Item"};
    TEST_ASSERT_EQUAL_INT(0, custom_array_append(temp));
  }

  // This append should fail
  TEST_ASSERT_EQUAL_INT(ENOBUFS, custom_array_append(item));

  CustomStruct value;
  TEST_ASSERT_EQUAL_INT(ENOENT, custom_array_get(15, &value));

  // Check that the length remains consistent
  TEST_ASSERT_EQUAL_INT(10, custom_array_length());
}
