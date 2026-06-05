// Copyright 2021 NNTU-CS
#include <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  <vector>
#include <algorithm>
#include <utility>
#include <string>
#include  "bst.h"

void makeTree(BST<std::string>& tree, const char* filename) {
    std::ifstream file(filename);

    if (!file) {
        std::cout << "File error!" << std::endl;
    }
    while (!file.eof()) {
        std::string word = "";
        bool isReadingWord = true;
        while (isReadingWord) {
            int symbol = file.get();
            if ('A' <= symbol && symbol <= 'Z') {
                symbol += ('a' - 'A');
                word += symbol;
            } else if ('a' <= symbol && symbol <= 'z') {
                word += symbol;
            } else {
                isReadingWord = false;
            }
        }
        if (word != "") {
            tree.add(word);
        }
    }

    file.close();
}
void printFreq(BST<std::string>& tree) {
    std::vector<std::pair<int, std::string>> infos = tree.getData();
    std::sort(infos.begin(), infos.end(),
        [](const std::pair<int, std::string>& a,
            const std::pair<int, std::string>& b) {
                return a.first > b.first;
        });

    std::ofstream file("result/freq.txt");
    for (auto info = infos.begin(); info != infos.end(); ) {
        file << info->second << " - " << info->first << std::endl;
        std::cout << info->second << " - " << info->first << std::endl;
        info++;
    }
    file.close();
}
