test_sarr_name = 'test_sarr.c'

sarr_test_src = files([
  test_sarr_name
])

test_sarr_exe = executable('test_sarr',
  sources: [
   sarr_test_src,
   gen_test_runner.process(test_sarr_name)
  ],
  dependencies: test_dependencies,
)

test('test_sarr', test_sarr_exe)
