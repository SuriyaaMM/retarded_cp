# codeforces version
clang++ -std=c++23 -O2 -fsanitize=address,undefined -fno-omit-frame-pointer -pipe nf.cpp -o main && ./main < input.txt > output.txt

# o3 version
clang++ -std=c++23 -O3 -pipe nf.cpp -o main && ./main < input.txt > output.txt

# debug version
clang++ -std=c++23 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -pipe nf.cpp -o nfdebug \
&& ./nfdebug < input.txt > output.txt 2> error.txt