# codeforces version
clang++ -std=c++20 -O2 -fsanitize=address,undefined -pipe nf.cpp -o main && ./main < input.txt > output.txt

# debug version
clang++ -std=c++20 -O1 -g -fsanitize=address,undefined -fno-omit-frame-pointer -pipe nf.cpp -o nfdebug \
&& ./nfdebug < input.txt > output.txt 2> error.txt