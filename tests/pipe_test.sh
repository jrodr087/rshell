#!/bin/sh
../bin/rshell << 'EOF'
echo "piping to cat: this is a test "
echo this is a test | cat
echo "piping contents of a test file to be uppercased: this is a test pipe"
echo this is a test pipe > test.txt
cat < test.txt | tr a-z A-Z | cat
echo pipe redir test complete
rm test.txt
exit;
EOF
