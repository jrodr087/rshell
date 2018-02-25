#!/bin/sh
../bin/rshell << 'EOF'
echo "outputting to file: this is a test "
echo this is a test > test.txt
echo "contents of the test file"
cat < test.txt
echo "appending to file: this is not going to overwrite the previous text"
echo this is not going to overwrite the previous text >> test.txt
echo contents of the test file:
cat < test.txt
echo append redir test complete
rm test.txt
exit;
EOF
