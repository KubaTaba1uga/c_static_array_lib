#include <unity.h>

#include "static_array_lib.h"

/* Define a struct with an int array field using SARRS */
typedef struct {
  SARRS_FIELD(my_array, int, 10);
} IntArrayStruct;

/* Declare SARRS functions for IntArrayStruct's array */
SARRS_DECL(IntArrayStruct, my_array, int, 10);

void setUp(void) {
  // No setup needed for now
}

void tearDown(void) {
  // No teardown needed for now
}

void test_saars_append(void) {
  IntArrayStruct s;
  SARRS_INIT(s, my_array);

  // Test appending elements
  TEST_ASSERT_EQUAL_INT(0, IntArrayStruct_my_array_append(&s, 42));
  TEST_ASSERT_EQUAL_INT(0, IntArrayStruct_my_array_append(&s, 99));

  // Verify length after appending
  TEST_ASSERT_EQUAL_INT(2, IntArrayStruct_my_array_length(&s));
}

void test_saars_get(void) {
  IntArrayStruct s;
  SARRS_INIT(s, my_array);

  // Prepopulate the array
  IntArrayStruct_my_array_append(&s, 42);
  IntArrayStruct_my_array_append(&s, 99);

  int value;
  // Test getting elements
  TEST_ASSERT_EQUAL_INT(0, IntArrayStruct_my_array_get(&s, 0, &value));
  TEST_ASSERT_EQUAL_INT(42, value);
  TEST_ASSERT_EQUAL_INT(0, IntArrayStruct_my_array_get(&s, 1, &value));
  TEST_ASSERT_EQUAL_INT(99, value);
}

void test_saars_size(void) {
  // Test array size function
  TEST_ASSERT_EQUAL_INT(10, IntArrayStruct_my_array_size());
}

void test_saars_length(void) {
  IntArrayStruct s;
  SARRS_INIT(s, my_array);

  // Test initial length
  TEST_ASSERT_EQUAL_INT(0, IntArrayStruct_my_array_length(&s));

  // Test length after appending elements
  IntArrayStruct_my_array_append(&s, 10);
  TEST_ASSERT_EQUAL_INT(1, IntArrayStruct_my_array_length(&s));

  IntArrayStruct_my_array_append(&s, 20);
  TEST_ASSERT_EQUAL_INT(2, IntArrayStruct_my_array_length(&s));
}

void test_saars_out_of_bounds_append(void) {
  IntArrayStruct s;
  SARRS_INIT(s, my_array);

  // Ensure appending beyond capacity is handled properly
  for (size_t i = 0; i < 10; ++i) {
    TEST_ASSERT_EQUAL_INT(0, IntArrayStruct_my_array_append(&s, i));
  }

  // This append should fail
  TEST_ASSERT_EQUAL_INT(ENOBUFS, IntArrayStruct_my_array_append(&s, 100));
}

void test_saars_out_of_bounds_get(void) {
  IntArrayStruct s;
  SARRS_INIT(s, my_array);

  // Prepopulate the array
  IntArrayStruct_my_array_append(&s, 42);
  IntArrayStruct_my_array_append(&s, 99);

  int value;
  // Test getting out-of-bounds index
  TEST_ASSERT_EQUAL_INT(ENOENT, IntArrayStruct_my_array_get(&s, 15, &value));

  // Check that the length remains consistent
  TEST_ASSERT_EQUAL_INT(2, IntArrayStruct_my_array_length(&s));
}
