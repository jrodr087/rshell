#!/bin/sh
../bin/rshell << 'EOF'
test -e test_test.sh #should output true
mkdir test_fld
test -d test_fld # should output true
test -f test_fld # should output false
test -f test_test.sh # should output true
test -d test_test.sh # should output false
[ -e test_fld ] # true
[ -d test_fld ] #true
[ -f test_fld ] #false
rmdir test_fld
exit;
EOF
