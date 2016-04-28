#!/bin/bash -u
# We use set -e and bash with -u to bail on first non zero exit code of any
# processes launched or upon any unbound variable
set -e

echo "using toolset: $CC"
echo "using variant: $VARIANT"

$BOOST_ROOT/bjam toolset=$CC variant=$VARIANT

if [[ $VARIANT == "coverage" ]]; then
  bash scripts/coverage.sh
else
  find bin -name "*-tests" -exec {} \;
fi
