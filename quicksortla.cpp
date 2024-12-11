#include <vector>
using namespace std;

class Quick {
public:
    // 使用 static 关键字可以确保无需实例化 Quick 类即可进行排序
    static void sort(vector<int>& nums) {
        // 为了避免出现耗时的极端情况，先随机打乱
        shuffle(nums);
        // 排序整个数组（原地修改）
        sort(nums, 0, nums.size() - 1);
    }

private:
    static void sort(vector<int>& nums, int lo, int hi) {
        if (lo >= hi) {
            return;
        }
        // 对 nums[lo..hi] 进行切分
        // 使得 nums[lo..p-1] <= nums[p] < nums[p+1..hi]
        int p = partition(nums, lo, hi);

        sort(nums, lo, p - 1);
        sort(nums, p + 1, hi);
    }

    // 对 nums[lo..hi] 进行切分
    static int partition(vector<int>& nums, int lo, int hi) {
        int pivot = nums[lo];
        // 关于区间的边界控制需格外小心，稍有不慎就会出错
        // 我这里把 i, j 定义为开区间，同时定义：
        // [lo, i) <= pivot；(j, hi] > pivot
        // 之后都要正确维护这个边界区间的定义
        int i = lo + 1, j = hi;
        // 当 i > j 时结束循环，以保证区间 [lo, hi] 都被覆盖
        while (i <= j) {
            while (i < hi && nums[i] <= pivot) {
                i++;
                // 此 while 结束时恰好 nums[i] > pivot
            }
            while (j > lo && nums[j] > pivot) {
                j--;
                // 此 while 结束时恰好 nums[j] <= pivot
            }

            if (i >= j) {
                break;
            }
            // 此时 [lo, i) <= pivot && (j, hi] > pivot
            // 交换 nums[j] 和 nums[i]
            swap(nums[i], nums[j]);
            // 此时 [lo, i] <= pivot && [j, hi] > pivot
        }
        // 最后将 pivot 放到合适的位置，即 pivot 左边元素较小，右边元素较大
        swap(nums[lo], nums[j]);
        return j;
    }

    // 洗牌算法，将输入的数组随机打乱
    static void shuffle(vector<int>& nums) {
        srand((unsigned) time(NULL));
        int n = nums.size();
        for (int i = 0 ; i < n; i++) {
            // 生成 [i, n - 1] 的随机数
            int r = i + rand()%(n-i);
            swap(nums[i], nums[r]);
        }
    }
    
    // 原地交换数组中的两个元素
    static void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }
};