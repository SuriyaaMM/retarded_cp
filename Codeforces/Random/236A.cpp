#include <iostream>
#include <string>
#include <set>

int main(int, char**){

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string name = "";
    std::cin >> name;

    std::set<char> unique_chars(name.begin(), name.end());
    if(unique_chars.size() % 2 == 0)
        std::cout << "CHAT WITH HER!" << std::endl;
    else
        std::cout << "IGNORE HIM!" << std::endl;
}

