#!/bin/sh
../bin/rshell << 'EOF'
echo first go
echo second go
touch file
ls
echo ""
echo ;
echo "&& 
rm file
rm file1 file2
echo checking again
mkdir dir1
rmdir dir1
exit
EOF
