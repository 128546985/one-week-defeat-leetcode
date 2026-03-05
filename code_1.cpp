#include <iostream>
#include <vector>
#include <random>
using namespace std;

/*
- 选择排序、冒泡排序、插入排序
- 时间复杂度: O(N^2)
- 空间复杂度: O(1)
*/

// 交换函数
void swapElements(vector<int>& arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}
// 采用位运算的交换函数
void swapElements2(vector<int>& arr, int i, int j){
    // i == j 会使两个位置的值变为0
    if(i != j){
        arr[i] = arr[i] ^ arr[j];
        arr[j] = arr[i] ^ arr[j];
        arr[i] = arr[i] ^ arr[j];
    }
    
}

// 选择排序
void SelectSort(vector<int>& arr){
    if(arr.empty() || arr.size() < 2){
        cout << "[warning : check data arr]" << endl;
        return;
    }
    for(int i = 0; i < arr.size() - 1; i++){
        int min_index = i;
        for(int j = i + 1; j < arr.size(); j++){
            min_index = (arr[j] < arr[min_index]) ? j : min_index;
        }
        swapElements(arr, i, min_index);
    }
}

// 冒泡排序
void BubbleSort(vector<int>& arr){
    if(arr.empty() || arr.size() < 2){
        cout << "[warning : check data arr]" << endl;
        return;
    }
    for(int i = arr.size() - 1; i > 0; i--){
        for(int j = 0; j < i; j++){
            if(arr[j+1] < arr[j]){
                swapElements2(arr, j, j+1);
            }
        }
    }
}

// 插入排序
void InsertSort(vector<int>& arr){
    if(arr.empty() || arr.size() < 2){
        cout << "[warning : check data arr]" << endl;
        return;
    }
    for(int i = 1; i < arr.size(); i++){
        for(int j = i - 1; j >= 0 && arr[j] > arr[j + 1]; j--){
            swapElements(arr, j, j + 1);
        }
    }
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

// 判断只有一个数据出现奇数次的数据
void printOddTimesNum1(vector<int>& arr){
    int result = 0;
    for(int i : arr){
        result ^= i;
    }
    cout<<"odd data : "<< result << endl;
}

// 判断有两个数据出现奇数次的数据
void printOddTimesNum2(vector<int>& arr){
    int eor = 0;
    for(int i : arr){
        eor ^= i;
    }
    // eor = a ^ b ,其中a和b是两个出现奇数次的数据
    int rightOne = eor & (~eor + 1); // 提取出最右边的1的位置

    int onlyOne = 0;
    for(int j : arr){
        if((j & rightOne) == 0){ // 找到数据位置不为1的数据进行异或（相当于分组）
            onlyOne ^= j;
        }
    }
    cout<<"odd data : "<< onlyOne << " and " << (onlyOne ^ eor) << endl;
}

int main() {

    int maxSize = 100;
    int maxValue = 100;
    vector<int> arr = {5, 3, 8, 4, 2}; // 排序容器
    vector<int> arr1 = {5}; // 判断单个数据的排序情况
    vector<int> arr3 = {1, 1, 1, 1 ,2, 2, 3, 3, 3}; // 判断只有一个数据出现奇数次的数据
    vector<int> arr4 = {1, 1, 2, 3}; // 判断有两个数据出现奇数次的数据
    auto arr_random = generateRandomArray(10,100);
    // // 选择排序
    // SelectSort(arr);
    // for(auto& i : arr){
    //     cout << i <<" ";
    // }

    // // 冒泡排序
    // BubbleSort(arr);
    // for(auto& i : arr){
    //     cout << i <<" ";
    // }
    // cout<<endl;

    // 插入排序
    for(auto& i : arr_random){
        cout << i <<" ";
    }
    cout<<endl;
    InsertSort(arr_random);
    for(auto& i : arr_random){
        cout << i <<" ";
    }
    cout<<endl;

    // 判断只有一个数据出现奇数次的数据
    printOddTimesNum1(arr3);

    // 判断有两个数据出现奇数次的数据
    printOddTimesNum2(arr4);

    return 0;

}