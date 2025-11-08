#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>

class _290Solution {
public:
    bool wordPattern(std::string pattern, std::string s) {
        int length = pattern.size();
        std::unordered_map<char,std::string> udmap1;
        std::unordered_map<std::string,char> udmap2;
        std::string word;
        std::stringstream ss(s);
        int wordCount = 0;
        std::vector<std::string> words;
        while (ss >> word)
        {
            words.push_back(word);
            wordCount++;
        }
        if(wordCount!=length) return false;
        for(int i = 0;i<length;i++){
            if(!udmap1.count(pattern[i])){
                udmap1.insert({pattern[i],words[i]});
            }else{
                if(udmap1[pattern[i]].compare(words[i])){
                    return false;
                }
            }

            if(!udmap2.count(words[i])){
                udmap2.insert({words[i],pattern[i]});
            }else{
                if(!(udmap2[words[i]]==pattern[i])){
                    return false;
                }
            }
        }
        return true;
    }
};