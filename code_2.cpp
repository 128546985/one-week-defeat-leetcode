#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;

/*
- 归并排序
    -- 时间：O(N*logN)
    -- 空间：O(N)
- master 公式
    -- T(N) = a * T(N/b) + O(n^d)
    -- log(b,a) > d -> 复杂度为O(N^log(b,a))
    -- log(b,a) = d -> 复杂度为O(N^d * logN)
    -- log(b,a) < d -> 复杂度为O(N^d)
*/

// 交换函数
void swapElements(vector<int>& arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// 随机数据发生器
vector<int> generateRandomArray(int maxSize, int maxValue) {
    random_device rd; // 获取真随机数种子（通常基于系统熵源，如硬件噪声）
    mt19937 gen(rd()); // 使用 Mersenne Twister 算法（MT19937）的随机数引擎
    
    // 生成长度 [1, maxSize]
    uniform_int_distribution<> sizeDis(1, maxSize);
    int size = sizeDis(gen);
    
    vector<int> arr(size);
    uniform_int_distribution<> valueDis(0, maxValue);
    
    for (int& num : arr) {
        num = valueDis(gen);
    }
    return arr;
}

// arr[L...R]范围上求最大值
int process(vector<int> arr, int L, int R){
    if(L == R){
        return arr[L];
    }
    int mid = L + ((R - L) >> 1); // 求中点
    int leftmax = process(arr, L, mid);
    int rightmax = process(arr, mid + 1, R);
    return max(leftmax, rightmax);
}

// 归并排序
void my_merge(vector<int>& arr, int L, int mid, int R){
    int* help = new int[R - L + 1]; // 或者 vector<int> help(R - L + 1);
    int i = 0;
    int p1 = L;
    int p2 = mid + 1;
    while (p1 <= mid && p2 <= R){
        help[i++] = arr[p1] <= arr[p2] ? arr[p1++] : arr[p2++];
    }
    while (p1 <= mid){
        help[i++] = arr[p1++];
    }
    while (p2 <= R){
        help[i++] = arr[p2++];
    }
    for (int j = 0; j < (R - L + 1); j++){
        arr[L + j] = help[j];
    }
    delete[] help;
}

void MergeSort(vector<int>& arr, int L, int R){
    if(L == R){
        return;
    }
    int mid = L + ((R - L) >> 1); // 求中点
    MergeSort(arr, L, mid);
    MergeSort(arr, mid + 1, R);
    my_merge(arr, L, mid, R);

}

// 小和问题
int my_merge2(vector<int>& arr, int L, int mid, int R){
    int* help = new int[R - L + 1]; // 或者 vector<int> help(R - L + 1);
    int i = 0;
    int p1 = L;
    int p2 = mid + 1;
    int res = 0;
    while (p1 <= mid && p2 <= R){
        res += arr[p1] < arr[p2] ? (R - p2 + 1) * arr[p1] : 0;
        help[i++] = arr[p1] < arr[p2] ? arr[p1++] : arr[p2++];
    }
    while (p1 <= mid){
        help[i++] = arr[p1++];
    }
    while (p2 <= R){
        help[i++] = arr[p2++];
    }
    for (int j = 0; j < (R - L + 1); j++){
        arr[L + j] = help[j];
    }
    delete[] help;
    return res;
}
int process2(vector<int>& arr, int L, int R){
    if(L == R){
        return 0;
    }
    int mid = L + ((R - L) >> 1); // 求中点
    return process2(arr, L, mid) + process2(arr, mid + 1, R) + my_merge2(arr, L, mid, R);
}
int smallSum(vector<int>& arr){
    if(arr.empty() || arr.size() < 2){
        return 0;
    }
    return process2(arr, 0, arr.size() - 1);
}

// 荷兰国旗问题[(arr[i]<num)+(arr[i]=num)+(arr[i]>num)]
void Netherlands_Flag(vector<int>& arr, int num){
    int left = -1;
    int right = arr.size();
    for(int i = 0; i < right; i++){
        if(arr[i] < num){
            swapElements(arr, left + 1, i);
            left++;
        }
        else if(arr[i] > num){
            swapElements(arr, i, right - 1);
            right--;
            i-- ;
        }
    }
}

// 快速排序
vector<int> partition(vector<int>& arr, int L,int R){
    vector<int> p(2);
    int less = L - 1;
    int more = R;
    while(L < more){
        if(arr[L] < arr[R]){
            swapElements(arr, ++less, L++);
        }
        else if(arr[L] > arr[R]){
            swapElements(arr, --more, L);
        }
        else{
            L++;
        }
    }
    swapElements(arr, R, more);
    p[0] = less + 1;
    p[1] = more;
    return p;
}
void quickSort(vector<int>& arr, int L, int R){
    if(L < R){
        int swapinfo = (int)(L + rand() % (R -L + 1));
        swapElements(arr, R, swapinfo);
        vector<int> p = partition(arr, L, R);
        quickSort(arr, L, p[0] - 1);
        quickSort(arr, p[1] + 1, R);
    }
}

int main() {

    int maxSize = 100;
    int maxValue = 100;
    vector<int> arr = {5, 3, 8, 4, 2}; // 排序容器
    vector<int> smallSum_arr = {1, 3, 4, 2, 5}; // 小和问题数组，结果应该为16
    vector<int> arr1 = {5}; // 判断单个数据的排序情况
    vector<int> arr_Netherlands_Flag = {5, 9, 2, 3, 4};
    auto arr_random = generateRandomArray(20,100);

    for (auto &i : arr_random){
        cout << i <<" ";
    }
    cout << endl;

    // // 归并排序
    // MergeSort(arr_random, 0, arr_random.size() - 1);
    // for (auto& i : arr_random){
    //     cout << i <<" ";
    // }
    // cout << endl;
    // 快速排序
    quickSort(arr_random, 0, arr_random.size() - 1);
    for (auto& i : arr_random){
        cout << i <<" ";
    }
    cout << endl;

    // 求范围内最大值
    int process_result = 0;
    process_result = process(arr, 0, arr.size() - 1);
    cout << "max: " << process_result << endl;

    // 小和问题，result = 16
    int smallSum_result = 0;
    smallSum_result = smallSum(smallSum_arr);
    cout << "smallSum: " << smallSum_result << endl;

    // 荷兰国旗问题:{5, 9, 2, 3, 4},num = 4
    int num = 4;
    Netherlands_Flag(arr_Netherlands_Flag, 4);
    for (auto& i : arr_Netherlands_Flag){
        cout << i <<" ";
    }

    return 0;

}