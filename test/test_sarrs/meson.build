# List of test files
test_files = [
  'test_sarrs_int.c',
  'test_sarrs_struct.c'
]

# Iterate over test files
foreach test_file : test_files
  # Extract base name for the target
  test_name = test_file.split('.')[0]

  # Create an executable target for the test
  test_exe = executable(test_name,
    sources: [
      test_file,
      gen_test_runner.process(test_file)
    ],
    dependencies: test_dependencies
  )

  # Register the test
  test(test_name, test_exe)
endforeach
