#include <vector>
#include <algorithm>
#include <iostream>
#include <random>
using namespace std;

class Solution {
public:
    vector<int> sortArray(vector<int>& nums) {
        random_device rd;
        mt19937 g(rd());
        shuffle(nums.begin(), nums.end(), g);
        quicksort(nums, 0, nums.size() - 1);
        return nums;
    }
private:
    void sort(vector<int>& nums, int start, int end) {
        if (start >= end) { /* 保证了nums的长度大于等于2 */
            return;
        }
        int p = quicksort(nums, start, end);
        sort(nums, start, p - 1);
        sort(nums, p + 1, end);
    }

    int quicksort(vector<int>& nums, int start, int end) {

        int i = start + 1;
        int j = end;
        int num = nums[start];
        while (true) {
            while (i < end && nums[i] <= num) { /* 从start + 1开始从左向右寻找比num大的数组下标 */
                i++; /* 当该循环结束时，nums[i] > num 或者 i == end */
            }
            while (j > start && nums[j] > num) { /* 从end开始从右向左寻找比num小的数组下标 */
                j--; /* 当该循环结束时，因为nums[start] == num，所以无论j是否等于start，nums[j] <= num */
            }
            /* 当所有数值都刚好排序好的临界时刻，i + 1 == j，此时nums[i] <= num，nums[j] > num */
            /* 进入下一次循环之后，i++, j--，此时i == j + 1，此时应该退出循环，因为start + 1至end部分已经排序完成 */
            /* 还有一种可能性，那就是i == j，这种情况下，nums[i] <= num，如果nums[i] > num，上面提到，nums[j] <= num必然成立，所以i和j无论如何不可能相等，所以nums[i] <= num */
            /* nums[i] <= num i++的循环结束必然是由于i == end，所以此时i == end，而此时i == j，所以此时i == j == end，说明此时从start + 1到end的所有数值均小于num */
            if (i >= j) { /* 综上所述，在nums[start]是从start到end中的最大值时，此时循环会因为i == j结束，其余情况，均因为i > j结束 */
                break;
            }
            // for_each(nums.begin(), nums.end(), [](int num){ cout << num << " ";});
            // cout << endl;
            /* 情况1：nums[start], nums[start + 1]...nums[j - 1], nums[j], nums[i]...nums[end] */
            /* 情况2：nums[start], nums[start + 1]...nums[j - 1], nums[j] */
            swap(nums[i], nums[j]); /* nums[i]和nums[j]交换之后，从start + 1到i的所有数值都小于等于num，从j到end的所有数值都大于num */
        }
        swap(nums[start], nums[j]);
        return j;
    }
};

int main()
{
    Solution s1;
    vector<int> nums = {5, 2, 3, 1};
    s1.sortArray(nums);
    for_each(nums.begin(), nums.end(), [](int num){ cout << num << " ";});
    cout << endl;
}

