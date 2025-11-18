#include<string>

class _495Solution {
public:
    bool repeatedSubstringPattern(std::string s) {
        std::string str = s+s;
        return str.substr(1,str.length()-2).find(s) == -1 ? false : true;
    }
};