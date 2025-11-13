#include<string>

class _434Solution {
public:
    int countSegments(std::string s) {
        int count=0;
        int i=0;
        while(i<s.length()){
            if(s[i]==' '){
                while(i<s.length() && s[i]==' ') i++;
            }else{
                while(i<s.length() && s[i]!=' ') i++;
                count++;
            }
        }
        return count;
    }
};