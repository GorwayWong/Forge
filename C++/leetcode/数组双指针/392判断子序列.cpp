#include <string>

class _392Solution
{
public:
    bool isSubsequence(std::string s, std::string t)
    {
        int i = 0, j = 0;
        while (i < s.size())
        {
            while (j < t.size() && t[j] != s[i])
            {
                j++;
            }
            if (j >= t.size())
            {
                return false;
            }
            else{
                i++;
                j++;
            }
        }
        return true;
    }
};