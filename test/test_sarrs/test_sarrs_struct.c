#include <unity.h>

#include "static_array_lib.h"

/* Define a custom struct for testing */
typedef struct {
  int id;
  char name[20];
} CustomStruct;

/* Define a struct with a CustomStruct array field using SARRS */
typedef struct {
  SARRS_FIELD(my_array, CustomStruct, 10);
} CustomStructArrayStruct;

/* Declare SARRS functions for CustomStructArrayStruct's array */
SARRS_DECL(CustomStructArrayStruct, my_array, CustomStruct, 10);

void setUp(void) {
  // No setup needed for now
}

void tearDown(void) {
  // No teardown needed for now
}

void test_saars_append_custom_struct(void) {
  CustomStructArrayStruct s;
  SARRS_INIT(s, my_array);

  // Test appending elements
  CustomStruct item1 = {1, "Item1"};
  CustomStruct item2 = {2, "Item2"};
  TEST_ASSERT_EQUAL_INT(0, CustomStructArrayStruct_my_array_append(&s, item1));
  TEST_ASSERT_EQUAL_INT(0, CustomStructArrayStruct_my_array_append(&s, item2));

  // Verify length after appending
  TEST_ASSERT_EQUAL_INT(2, CustomStructArrayStruct_my_array_length(&s));
}

void test_saars_get_custom_struct(void) {
  CustomStructArrayStruct s;
  SARRS_INIT(s, my_array);

  // Prepopulate the array
  CustomStruct item1 = {1, "Item1"};
  CustomStruct item2 = {2, "Item2"};
  CustomStructArrayStruct_my_array_append(&s, item1);
  CustomStructArrayStruct_my_array_append(&s, item2);

  CustomStruct value;
  // Test getting elements
  TEST_ASSERT_EQUAL_INT(0, CustomStructArrayStruct_my_array_get(&s, 0, &value));
  TEST_ASSERT_EQUAL_INT(1, value.id);
  TEST_ASSERT_EQUAL_STRING("Item1", value.name);

  TEST_ASSERT_EQUAL_INT(0, CustomStructArrayStruct_my_array_get(&s, 1, &value));
  TEST_ASSERT_EQUAL_INT(2, value.id);
  TEST_ASSERT_EQUAL_STRING("Item2", value.name);
}

void test_saars_size_custom_struct(void) {
  // Test array size function
  TEST_ASSERT_EQUAL_INT(10, CustomStructArrayStruct_my_array_size());
}

void test_saars_length_custom_struct(void) {
  CustomStructArrayStruct s;
  SARRS_INIT(s, my_array);

  // Test initial length
  TEST_ASSERT_EQUAL_INT(0, CustomStructArrayStruct_my_array_length(&s));

  // Test length after appending elements
  CustomStruct item = {3, "Item3"};
  CustomStructArrayStruct_my_array_append(&s, item);
  TEST_ASSERT_EQUAL_INT(1, CustomStructArrayStruct_my_array_length(&s));

  CustomStruct item2 = {4, "Item4"};
  CustomStructArrayStruct_my_array_append(&s, item2);
  TEST_ASSERT_EQUAL_INT(2, CustomStructArrayStruct_my_array_length(&s));
}

void test_saars_out_of_bounds_append_custom_struct(void) {
  CustomStructArrayStruct s;
  SARRS_INIT(s, my_array);

  // Ensure appending beyond capacity is handled properly
  for (size_t i = 0; i < 10; ++i) {
    CustomStruct temp = {i, "Item"};
    TEST_ASSERT_EQUAL_INT(0, CustomStructArrayStruct_my_array_append(&s, temp));
  }

  CustomStruct item = {11, "OverflowItem"};
  // This append should fail
  TEST_ASSERT_EQUAL_INT(ENOBUFS,
                        CustomStructArrayStruct_my_array_append(&s, item));
}

void test_saars_out_of_bounds_get_custom_struct(void) {
  CustomStructArrayStruct s;
  SARRS_INIT(s, my_array);

  // Prepopulate the array
  CustomStruct item1 = {1, "Item1"};
  CustomStructArrayStruct_my_array_append(&s, item1);

  CustomStruct value;
  // Test getting out-of-bounds index
  TEST_ASSERT_EQUAL_INT(ENOENT,
                        CustomStructArrayStruct_my_array_get(&s, 15, &value));

  // Check that the length remains consistent
  TEST_ASSERT_EQUAL_INT(1, CustomStructArrayStruct_my_array_length(&s));
}
