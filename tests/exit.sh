#!/bin/sh
../bin/rshell << 'EOF'
echo hello world
echo hello world || exit
echo hello world # exit;
echo bob && exit
exit;
EOF
