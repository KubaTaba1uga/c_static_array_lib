#ifndef SARR_H
#define SARR_H

/* SARR stands for Static Array */
/* SARRS stands for Static Array in Struct */

#include <errno.h>
#include <stddef.h>

/*
 * Declare a global/static array with get, append, size, and length functions.
 * length() now tracks the last valid index (number of valid elements - 1).
 */
#define SARR_DECL(name, type, capacity)                                        \
  type name[capacity];                                                         \
  size_t name##_offset = 0;                                                    \
  static inline int name##_append(type val) {                                  \
    if (name##_offset >= capacity) {                                           \
      return ENOBUFS; /* Error: array full */                                  \
    }                                                                          \
    name[name##_offset++] = val;                                               \
    return 0; /* Success */                                                    \
  }                                                                            \
  static inline int name##_get(size_t i, type *value) {                        \
    if (i >= name##_offset) {                                                  \
      return ENOENT; /* Error: index out of bounds */                          \
    }                                                                          \
    if (value)                                                                 \
      *value = name[i];                                                        \
    return 0;                                                                  \
  }                                                                            \
  static inline size_t name##_size() { return capacity; }                      \
  static inline size_t name##_length() { return name##_offset; }

/*
 * Declare append, get, size, and length for an array field in a struct.
 * length() tracks the last valid index (number of valid elements - 1).
 */
#define SARRS_DECL(struct_type, field, type, capacity)                         \
  static inline int struct_type##_##field##_append(struct_type *s, type val) { \
    if (s->field##_offset >= capacity) {                                       \
      return ENOBUFS; /* Error: array full */                                  \
    }                                                                          \
    s->field[s->field##_offset++] = val;                                       \
    return 0; /* Success */                                                    \
  }                                                                            \
  static inline int struct_type##_##field##_get(const struct_type *s,          \
                                                size_t i, type *value) {       \
    if (i >= s->field##_offset) {                                              \
      return ENOENT; /* Error: index out of bounds */                          \
    }                                                                          \
    if (value)                                                                 \
      *value = s->field[i];                                                    \
    return 0;                                                                  \
  }                                                                            \
  static inline size_t struct_type##_##field##_size(void) { return capacity; } \
  static inline size_t struct_type##_##field##_length(const struct_type *s) {  \
    return s->field##_offset;                                                  \
  }

/* Helper macro to declare a field for valid length tracking in the struct */
#define SARRS_FIELD(field, type, capacity)                                     \
  type field[capacity];                                                        \
  size_t field##_offset;

/* Macro to initialize a struct with a static array field */
#define SARRS_INIT(struct_instance, field)                                     \
  do {                                                                         \
    struct_instance.field##_offset = 0;                                        \
  } while (0)

#endif /* SARR_H */
