#include <vector>
#include <unordered_map>
using namespace std;
class RandomizedSet
{
public:
    // 哈希表keu存放值，value存放下标
    unordered_map<int, int> numToLocation;
    // 数组
    vector<int> nums;
    /** Initialize your data structure here. */
    RandomizedSet()
    {
    }

    /** Inserts a value to the set. Returns true if the set did not already contain the specified element. */
    bool insert(int val)
    {
        // 如果在哈希表中存在该元素，返回false
        if (numToLocation.find(val) != numToLocation.end())
        {
            return false;
        }
        // 哈希表中加入值和对应下标，因为数组中插入是在最后一个下标的下一个下标，所以对应的下标为nums.size()
        numToLocation[val] = nums.size();
        // 数组末尾加val
        nums.push_back(val);
        return true;
    }

    /** Removes a value from the set. Returns true if the set contained the specified element. */
    bool remove(int val)
    {
        // 如果哈希表中不存在该元素，则返回false
        if (numToLocation.find(val) == numToLocation.end())
        {
            return false;
        }
        // 在哈希表中根据待删除元素找到待删除元素在数组中的下标
        int location = numToLocation[val];
        // 把数组中最后一个元素的下标改为location
        numToLocation[nums.back()] = location;
        // 在哈希表中删除val
        numToLocation.erase(val);
        // 在数组中待删除元素用数组中最后一个元素替换
        nums[location] = nums.back();
        // 删除最后一个元素
        nums.pop_back();
        return true;
    }

    /** Get a random element from the set. */
    int getRandom()
    {
        return nums[rand() % nums.size()];
    }
};

/**
 * Your RandomizedSet object will be instantiated and called as such:
 * RandomizedSet* obj = new RandomizedSet();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
