#!/bin/sh
../bin/rshell << 'EOF'
echo "contents of this shell script: "
cat < input_redirect_test.sh
echo "contents of RADME.md"
cat < ../README.md
echo contents of main.cpp
cat < ../src/main.cpp
echo input redir test complete
exit;
EOF
