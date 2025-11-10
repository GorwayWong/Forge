#include<string>
#include<unordered_map>

//需要注意的是这题不是求最长的子串回文串，而是用s的字符能组成的最长回文串
class _409Solution {
public:
    int longestPalindrome(std::string s) {
        std::unordered_map<char,int> udmap;
        int sides=0,center=0;
        for(int i=0;i<s.length();i++){
            if(!udmap.count(s[i])){
                udmap.insert({s[i],1});
            }else{
                udmap[s[i]]++;
            }
        }
        for(auto pair : udmap){
            if(pair.second%2==0){
                sides+=pair.second;
            }else{
                center=1;
                if(pair.second!=1){
                    sides+=pair.second-1;
                }
            }
        }
        return center+sides;
    }
};