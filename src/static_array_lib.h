#ifndef SARR_H
#define SARR_H

/* SARR stands for Static Array */
/* SARRS stands for Static Array in Struct */

#include <stddef.h>

/*
 * Declare a global/static array with get, set, size, and length functions.
 * length() now tracks the last valid index (number of valid elements - 1).
 */
#define SARR_DECL(name, type, array_size)                                      \
  static type name[array_size];                                                \
  static size_t name##_valid_length = 0;                                       \
  static inline type name##_get(size_t i) { return name[i]; }                  \
  static inline void name##_set(size_t i, type val) {                          \
    name[i] = val;                                                             \
    if (i >= name##_valid_length) {                                            \
      name##_valid_length = i + 1;                                             \
    }                                                                          \
  }                                                                            \
  static inline size_t name##_size(void) { return array_size; }                \
  static inline size_t name##_length(void) {                                   \
    return name##_valid_length > 0 ? name##_valid_length - 1 : 0;              \
  }

/*
 * Declare get, set, size, and length for an array field in a struct.
 * length() tracks the last valid index (number of valid elements - 1).
 */
#define SARRS_DECL(struct_type, field, type, array_size)                       \
  static inline type struct_type##_##field##_get(const struct_type *s,         \
                                                 size_t i) {                   \
    return s->field[i];                                                        \
  }                                                                            \
  static inline void struct_type##_##field##_set(struct_type *s, size_t i,     \
                                                 type val) {                   \
    s->field[i] = val;                                                         \
    if (i >= s->field##_valid_length) {                                        \
      s->field##_valid_length = i + 1;                                         \
    }                                                                          \
  }                                                                            \
  static inline size_t struct_type##_##field##_size(void) {                    \
    return array_size;                                                         \
  }                                                                            \
  static inline size_t struct_type##_##field##_length(const struct_type *s) {  \
    return s->field##_valid_length > 0 ? s->field##_valid_length - 1 : 0;      \
  }

/* Helper macro to declare a field for valid length tracking in the struct */
#define SARRS_FIELD(field, type, array_size)                                   \
  type field[array_size];                                                      \
  size_t field##_valid_length;

/* Macro to initialize a struct with a static array field */
#define SARRS_INIT(struct_instance, field)                                     \
  do {                                                                         \
    struct_instance.field##_valid_length = 0;                                  \
  } while (0)

#endif /* SARR_H */
