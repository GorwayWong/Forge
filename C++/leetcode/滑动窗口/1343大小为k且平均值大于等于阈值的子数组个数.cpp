#include <stdlib.h>
#include <algorithm>
#include <string>
#include <vector>

class _1343Solution
{
public:
    int numOfSubarrays(std::vector<int> &arr, int k, int threshold)
    {
        int count = 0;
        int left, right;
        int sum = 0;
        for (int i = 0; i < arr.size(); i++)
        {
            right = i;
            left = right - k + 1;
            sum += arr[right];
            if (left < 0)
                continue;
            if (sum / k >= threshold)
                count++;
            sum -= arr[left];
        }
        return count;
    }
};