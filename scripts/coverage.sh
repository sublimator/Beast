# 0. Clear old counters ;)
# We use -f as that way rm doesnt' return a non 0 error code
find . -name "*.gcda" | xargs rm -f
rm *.info -f

echo $PATH
# 1. create baseline coverage data file
lcov --no-external -c -i -d . -o baseline.info

#2. perform test
find bin -name "*-tests" -exec {} \;
export SERVER=`find . -name "websocket_echo"`
nohup $SERVER&
cd scripts && wstest -m fuzzingclient
cd ..
cat nohup.out
jobs
kill -INT %1 || echo "already dead"
# 3. create test coverage data file
lcov --no-external -c -d . -o tests.info

# 4. combine baseline and test coverage data
# codecov.io
lcov -a baseline.info -a tests.info -o lcov.info
~/.local/bin/codecov -X gcov
