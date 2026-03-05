#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <queue>
using namespace std;
/*
- 堆的操作
    -- heapInsert ： 向上调整，时间复杂度 O(logN)
    -- heapify ： 向下调整，时间复杂度 O(logN)
- 堆排序
    -- 堆排序的核心思想是将数组转化为大根堆或小根堆 
    -- 时间复杂度 O(N*logN)
    -- 空间复杂度 O(1)
- 将数组按顺序转为完全二叉树，对于数组某一个位置转为节点位置 i
    -- 左子节点为 2*i + 1
    -- 右子节点为 2*i + 2
    -- 父节点为 (i - 1) / 2
- 优先级队列（堆的拓展）
    -- 优先级队列是一个特殊的队列，元素按照优先级顺序出队
- C++现成的堆结构：
    -- priority_queue<int> pq; 默认是大根堆
    -- 如果只想让堆作为一个黑盒来执行相关任务，可以使用 priority_queue
    -- 如果想要用堆做更细的操作，需要自己写堆结构
    -- priority_queue<int, vector<int>, greater<int>> minHeap; // 小根堆
    -- priority_queue<int, vector<int>, less<int>> maxHeap; // 大根堆
- 不基于比较的排序算法
    -- 计数排序
    -- 基数排序
    -- 注意：这些排序算法的时间复杂度通常是 O(N) 或 O(N*K)，其中 K 是数据范围
    -- 但它们的空间复杂度通常较高，可能是 O(N) 或 O(K)，因此在实际应用中需要根据数据特点选择合适的排序算法
- 稳定的排序算法（排序时，对于相同的数，其相对位置不变）
    -- 冒泡排序、插入排序、归并排序、基数排序等
- 不稳定的排序算法
    -- 选择排序、快速排序、堆排序等
*/

// 交换函数
void swapElements(vector<int>& arr, int i, int j){
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// 大根堆创建算法（向上调整）
void heapInsert(vector<int>& arr, int index) {
    while (arr[index] > arr[(index - 1) / 2]){
        swapElements(arr, index, (index - 1) / 2);
        index = (index - 1) / 2; // 更新 index 为父节点位置
    }
}

// 堆化（从index位置向下开始堆化，一般是从0位置开始）
void heapify(vector<int>& arr, int index, int heapSize){
    int left = index * 2 + 1;
    while(left < heapSize){
        int largest = (left + 1) < heapSize && (arr[left + 1] > arr[left]) ? left + 1 : left;
        largest = arr[largest] > arr[index] ? largest : index;
        if(largest == index) break;
        swapElements(arr, index, largest);
        index = largest;
        left = index * 2 + 1;
    }
}

// 堆排序函数
void heapSort(vector<int>& arr){
    if(arr.empty() || arr.size() < 2){
        cout << "[warning : check data arr]" << endl;
        return;
    }
    // // 方法1：O(N*logN) 构建堆（使用heapInsert）
    // for (int i = 0; i < arr.size(); i++) {
    //     heapInsert(arr, i); // 将每个元素插入到大根堆中
    // }
    // 方法2：O(N) 构建堆（使用heapify）
    // 注意：i = arr.size() / 2 - 1 表示最后一个非叶子节点
    for (int i = arr.size() / 2 - 1; i >= 0; i--) { 
        heapify(arr, i, arr.size());
    }
    int heapSize = arr.size();
    swapElements(arr, 0, --heapSize);
    while (heapSize > 0) {
        heapify(arr,0, heapSize);
        swapElements(arr, 0, --heapSize);
    }
}

// 堆拓展：排序问题，对于一个数组，某个位置 i 的节点排序后与该位置的距离不超过 k
// 方法：使用小根堆维护一个大小为 k 的窗口
void sortedArrayDistanceLessK(vector<int>& arr, int k){
    priority_queue<int, vector<int>, greater<int>> heap;
    int index = 0;
    for(; index <= min(k, (int)arr.size()); index++){ // size_t 是无符号类型，可能会导致负数问题
        heap.push(arr[index]); // 将前 k 个元素加入小根堆
    }
    int i = 0;
    for(; index < arr.size(); index++, i++){
        arr[i] = heap.top();
        heap.pop();
        heap.push(arr[index]);
    }
    while(!heap.empty()){
        arr[i++] = heap.top();
        heap.pop();
    }
}

// 基数排序（Radix Sort）
int maxbits(vector<int>& arr){
    int max = numeric_limits<int>::min(); // 初始化为最小整数
    for(int num :arr){
        if(num > max){
            max = num;
        }
    }
    int bits = 0;
    while(max != 0){
        bits++;
        max /= 10;
    }
    return bits; // 返回最大数的位数
}
int getDigit(int data, int d){
    return (data / static_cast<int>(pow(10, d - 1))) % 10;
}
void radixsort(vector<int>& arr, int L, int R, int digit){
    int radix = 10;
    int i = 0, j = 0;
    vector<int> bucket(R - L + 1, 0);
    for(int d = 1; d <= digit; d++){
        vector<int> count(radix, 0);
        for (i = L; i<= R;i++){
            j = getDigit(arr[i], d);
            count[j]++;
        }
        for(i = 1; i < radix; i++){
            count[i] = count[i] + count[i - 1];
        }
        for(i = R; i >= L; i--){
            j = getDigit(arr[i], d);
            bucket[count[j] - 1] = arr[i];
            count[j]--;
        }
        for(i = L, j = 0; i <= R; i++, j++){
            arr[i] = bucket[j];
        }
    }
}
void radixSort(vector<int>& arr){
    if(arr.empty() || arr.size() < 2){
        cout << "[warning : check data arr]" << endl;
        return;
    }
    radixsort(arr, 0, arr.size() - 1, maxbits(arr));
}
int main(){
    // #ifdef _WIN32
    // system("chcp 65001 > nul");
    // #endif
    vector<int> arr = {5, 3, 8, 4, 2}; // 大根堆容器
    vector<int> arr1 = {2, 3, 1, 5, 4}; // 测试堆拓展排序问题
    // 测试创建大根堆
    // for (int i = 0; i < arr.size(); i++) {
    //     heapInsert(arr, i); // 将每个元素插入到大根堆中
    // }
    // cout << "大根堆创建后的数组: ";
    // for (const auto& num : arr) {
    //     cout << num << " ";
    // }
    // cout << endl;
    // 堆排序
    heapSort(arr);
    cout << "堆排序后的数组: ";
    for (const auto& num : arr) {
        cout << num << " ";
    }
    cout << endl;
    // 测试系统自带的优先级队列（堆）
    // 默认
    vector<int> v = {3,1,4};
    priority_queue<int> pq(v.begin(), v.end()); // 初始化后，堆顶为4（大根堆）
    cout << "默认是大根堆顶: " << pq.top() << endl;  // 输出4

    // 大根堆：取最大值
    priority_queue<int, vector<int>, less<int>> maxHeap;
    maxHeap.push(3);
    maxHeap.push(1);
    maxHeap.push(4);
    cout << "大根堆顶: " << maxHeap.top() << endl;  // 输出4
    maxHeap.pop();
    cout << "移除堆顶元素 4 的大根堆顶: " << maxHeap.top() << endl;  // 输出4

    // 小根堆：取最小值
    priority_queue<int, vector<int>, greater<int>> minHeap;
    minHeap.push(3);
    minHeap.push(1);
    minHeap.push(4);
    cout << "小根堆顶: " << minHeap.top() << endl;  // 输出1
    sortedArrayDistanceLessK(arr1, 2); // 测试堆拓展排序问题
    cout << "堆拓展排序后的数组: ";
    for (const auto& num : arr1) {
        cout << num << " ";
    }
    cout << endl;

    // 基数排序
    vector<int> arr2 = {170, 45, 75, 90, 802, 24, 2, 66};
    radixSort(arr2);
    cout << "基数排序后的数组: ";
    for (const auto& num : arr2) {
        cout << num << " ";
    }
    cout << endl;
    return 0;
}