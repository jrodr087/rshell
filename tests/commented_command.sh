#!/bin/sh
../bin/rshell << 'EOF'
echo hello world #this should not print
echo abc #no print
#hello
; #empty semicolon
echo #echo nothing
exit
EOF
