#ifndef SARR_H
#define SARR_H

/* SARR stands for Static Array */
/* SARRS stands for Static Array in Struct */

#include <errno.h>
#include <stddef.h>

/*
 * Declare a global/static array with get, set, size, and length functions.
 * length() now tracks the last valid index (number of valid elements - 1).
 */
#define SARR_DECL(name, type, capacity)                                        \
  type name[capacity];                                                         \
  size_t name##_length_ = 0;                                                   \
  const size_t name##_capacity = capacity;                                     \
  static inline int name##_set(size_t i, type val) {                           \
    if (i >= name##_capacity) {                                                \
      return ENOBUFS; /* Error: index out of bounds */                         \
    }                                                                          \
    name[i] = val;                                                             \
    if (i >= name##_length_) {                                                 \
      name##_length_ = i + 1;                                                  \
    }                                                                          \
    return 0; /* Success */                                                    \
  }                                                                            \
  static inline int name##_get(size_t i, type *value) {                        \
    if (i >= name##_length_) {                                                 \
      return ENOBUFS; /* Error: index out of bounds */                         \
    }                                                                          \
    if (value)                                                                 \
      *value = name[i];                                                        \
    return 0;                                                                  \
  }                                                                            \
  static inline size_t name##_size() { return name##_capacity; }               \
  static inline size_t name##_length() { return name##_length_; }

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
