#!/bin/bash -u
# We use set -e and bash with -u to bail on first non zero exit code of any
# processes launched or upon any unbound variable
set -e

echo "using toolset: $CC"
echo "using variant: $VARIANT"

$BOOST_ROOT/bjam toolset=$CC variant=$VARIANT

# Delete any coverage information from prior runs
find . -name "*.gcda" | xargs rm
# Keep these as these are the files created during compilation ;)
# find . -name "*.gcno" | xargs rm

# Run the tests again, so all test output is contiguous

find bin -name "*_tests" -exec {} \;

if [[ $VARIANT == "coverage" ]]; then
  # We pass along -p to keep path segments so as to avoid collisions
  export SERVER=`find . -name "websocket_echo"`
  nohup $SERVER&
  cd scripts && wstest -m fuzzingclient
  cd ..
  cat nohup.out
  jobs
  kill -INT %1
  coveralls --gcov-options '\-lp'
  # codecov --gcov-args=-p --gcov-source-match='^((include/beast)|examples|test)'
fi
