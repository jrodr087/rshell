#!/bin/sh
../bin/rshell << 'EOF'
(echo "Truee")
((echo "Truee"))
(echo A) || echo B
(test -e test.txt && test -d test.txt)
((echo A) && echo B && echo C || (echo G))
(echo "(Hello World)")
(echo "Truee" && echo "Truee")
(echo "Truee" || echo "Falsee")
(echo "Truee" && (echo "Truee"))
(echo "Truee" || (echo "Falsee"))
(echo "Truee" && (echo "Truee" && (echo "Truee")))
([ -e test.txt ]) && (echo "Truee")
(echo "Truee" || echo "Falsee") && echo "Truee"
(echo "Truee" && echo "Truee") && (echo "Truee" && echo "Truee")
(echo "Truee" && echo "Truee") || (echo "Falsee" && echo "Falsee")
exit
EOF
