unity_subproject = subproject('unity')

unity_dependency = unity_subproject.get_variable('unity_dep')
gen_test_runner = unity_subproject.get_variable('gen_test_runner')

test_includes = [inc_dir]

test_dependencies = [static_array_lib, unity_dependency]

subdir('test_unity')
subdir('test_sarr')
subdir('test_sarrs')