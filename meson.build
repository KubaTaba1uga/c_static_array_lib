# C Static Array Lib
# ******************************************************************************
# *    Project
# ******************************************************************************
project('c_static_array_lib', 'c',
         version: '0.0.1',
	 meson_version: '>=1.0.1',
	 default_options: [
            'werror=true',
            'c_std=c99',
         ],
)

# ******************************************************************************
# *    Lib
# ******************************************************************************
inc_dir = include_directories('include')

static_array_lib = declare_dependency(
  include_directories: inc_dir
)

if get_option('install_headers')
   install_headers('include/static_array_lib.h', subdir: 'static_array_lib')
endif

# ******************************************************************************
# *    Tests
# ******************************************************************************
subdir('test')

