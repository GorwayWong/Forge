#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <string>
#include <vector>

class _2349Solution
{
public:
    int minimumRecolors(std::string blocks, int k)
    {
        int recolor = 0;
        int left, right;
        int n = blocks.length();
        int count = 0;
        int result = 9999;
        for (int i = 0; i < n; i++)
        {
            right = i;
            left = right - k + 1;
            if (blocks[right] == 'W')
                recolor++;
            if (left < 0)
            {
                continue;
            }
            if (recolor < result)
                result = recolor;
            if (blocks[left] == 'W')
                recolor--;
        }
        return result;
    }
};