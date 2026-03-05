#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <map>
#include <set>

using namespace std;
/*
- 哈希表（unordered_map 和 unordered_set）
    -- 哈希表是一种基于哈希函数实现的键值对存储结构
    -- 哈希函数将键映射到哈希表的索引位置
    -- 哈希表的平均时间复杂度为 O(1)，但最坏情况下可能退化为 O(N)
- 有序表(ordered_map 和 ordered_set)
    -- 有序表是一种基于平衡二叉树实现的键值对存储结构
    -- 有序表支持按键排序和范围查询
    -- 平均时间复杂度为 O(logN)，最坏情况下也为 O(logN)
- 单链表
    -- 单链表是一种线性数据结构，由一系列节点组成，每个节点包含数据和指向下一个节点的指针
    -- 单链表的插入和删除操作时间复杂度为 O(1)，但查找操作时间复杂度为 O(N)
- 双链表
    -- 双链表是一种线性数据结构，每个节点包含数据和指向前后两个节点的指针
    -- 双链表支持双向遍历，插入和删除操作时间复杂度为 O(1)，查找操作时间复杂度为 O(N)

*/

// 示例：使用 unordered_map 和 unordered_set
void unordered_example() {
    unordered_map<string, int> hashMap; // 哈希表
    unordered_set<int> hashSet; // 哈希表
    hashMap["apple"] = 1;
    hashMap["banana"] = 2;
    hashSet.insert(1);
    hashSet.insert(2);
    
    cout << "HashMap contains: ";
    for (const auto& pair : hashMap) {
        cout << pair.first << ": " << pair.second << " ";
    }
    cout << endl;

    cout << "HashSet contains: ";
    for (const auto& value : hashSet) {
        cout << value << " ";
    }
    cout << endl;
}

// 示例：使用 ordered_map 和 ordered_set
void ordered_example() {
    map<string, int> orderedMap; // 有序表
    set<int> orderedSet; // 有序表
    orderedMap["apple_aa"] = 3;
    orderedMap["apple_b"] = 2;
    orderedSet.insert(1);
    orderedSet.insert(2);
    
    cout << "OrderedMap contains: ";
    for (const auto& pair : orderedMap) {
        cout << pair.first << ": " << pair.second << " ";
    }
    cout << endl;

    cout << "OrderedSet contains: ";
    for (const auto& value : orderedSet) {
        cout << value << " ";
    }
    cout << endl;
}
int main() {
    
    // 示例：使用 unordered_map 和 unordered_set
    unordered_example();
    // 示例：使用 ordered_map 和 ordered_set
    ordered_example();


    return 0;
}