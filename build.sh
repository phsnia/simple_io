set -e 

CXX="clang"
FLAGS="-Wall -Wextra -O2"
SRC="src/main.c"
OUT="bin/main.exe"

mkdir -p bin
"$CXX" $FLAGS "$SRC" -o "$OUT"
./"$OUT"