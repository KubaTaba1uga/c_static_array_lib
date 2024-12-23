# C Static Array Library

A minimal library providing macros for static arrays in C. This repository includes:
- Macros for creating static arrays (`SARR_DECL`)  
- Macros for creating static arrays as struct fields (`SARRS_DECL`)  
- A Meson-based build system  
- Unit tests using Unity  
- `tasks.py` powered by [Invoke](https://www.pyinvoke.org/) for automation

## Features
1. **Header-Only**: Simply include `static_array_lib.h`, no library compilation needed.  
2. **Static Array Macros**: Simplify creation, access, and length tracking of fixed-size arrays.  
3. **Meson Build**: Configure, build, and test with Meson.  
4. **Automation with Invoke**: Use `tasks.py` to run installs, builds, and tests.

## Getting Started
1. **Include the Header**  
   - Copy `include/static_array_lib.h` into your project or reference it directly.  
   - Example:
     ```c
     #include "static_array_lib.h"
     SARR_DECL(my_array, int, 10);
     
     int main() {
       my_array_append(42);
       // ...
       return 0;
     }
     ```
2. **(Optional) Run Tests**  
   - Install Meson and Unity (or use the provided scripts).  
   - Configure and run tests:
     ```bash
     meson setup build
     meson compile -C build
     meson test -C build
     ```
   - Or use `tasks.py` with Invoke:
     ```bash
     pip install invoke
     invoke install
     invoke setup
     invoke build
     invoke test
     ```

## tasks.py & Invoke
This project includes a `tasks.py` file that defines various tasks for building, testing, and installing dependencies. These tasks use the [Invoke](https://www.pyinvoke.org/) library.  

1. **Install Invoke**  
   ```bash
   pip install invoke
   ```
2. **Use Invoke tasks**  
   ```bash
   invoke install       # Installs Meson, Ruby, and other prerequisites
   invoke setup         # Sets up Meson build directory
   invoke build         # Compiles the project
   invoke test          # Runs the tests
   ```

## Usage
Include `include/static_array_lib.h` in your C code:
```c
#include "static_array_lib.h"
SARR_DECL(my_array, int, 10);

int main() {
    // Append values
    my_array_append(42);
    my_array_append(99);
    // ...
}
```

## Authors
- **Jakub Buczyński** - *C Static Array Lib* -
  [KubaTaba1uga](https://github.com/KubaTaba1uga)

## License
Distributed under the [MIT](LICENSE.md).

