#include <stdio.h>
#include <stdbool.h>
#include <string>

class _1456Solution
{
public:
    int maxVowels(std::string s, int k)
    {
        int maxVowel = 0;
        int left, right;
        int vowel= 0;
        for (int i = 0; i < s.length(); i++)
        {
            right = i;
            left = right - k + 1;
            if(s[right] == 'a' || s[right] == 'e' || s[right] == 'i' || s[right] == 'o' || s[right] == 'u'){
                vowel++;
            }
            if(left<0){
                continue;
            }
            if(vowel>maxVowel){
                maxVowel=vowel;
                if(maxVowel == k){
                    break;
                }
            }
            if (s[left] == 'a' || s[left] == 'e' || s[left] == 'i' || s[left] == 'o' || s[left] == 'u')
            {
                vowel--;
            }
        }
        return maxVowel;
    }
};