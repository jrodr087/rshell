#!/bin/sh
../bin/rshell << 'EOF'
echo hello && echo goodbye
echo hello1 || echo goodbye1
echo hello2; echo goodbye2
touch file
touch file1; touch file2
touch file3 || touch file4 ## won't create file4
rm file
rm file1; rm file2
rm file3 || rm file4 ##wont delete file4
rm file5 && rm file6 ##should fail to remove 5 so it wont try to rm file 6
klmlsdkfm && echo out #won't echo out
skdmfslkme || echo out # will echo out
smdlkemsef; echo out # will echo out
echo ; ls
echo && ls
echo || ls
echo "&&" ls
exit
EOF
