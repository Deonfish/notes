# tmp

> 两种思路：
>
> - 窗口可以缩小或放大
> - 窗口可以平移或放大
> - (固定窗口题直接滑动)

给定一个由若干 0 和 1 组成的数组 A，我们最多可以将 K 个值从 0 变成 1 。

返回仅包含 1 的最长（连续）子数组的长度。

 

示例 1：

输入：A = [1,1,1,0,0,0,1,1,1,1,0], K = 2
输出：6
解释： 
[1,1,1,0,0,1,1,1,1,1,1]
粗体数字从 0 翻转到 1，最长的子数组长度为 6。

```c++
int longestOnes(vector<int>& A, int K) {
        int i = 0, j = 0, res = 0;
        for(; i < A.size(); ++i)
        {
            if(A[i] == 0)
            {
                if(K > 0) --K;
                else
                {
                    // 记录上一次的结果
                    res = max(res, i-j);
                    while(A[j++] == 1); // 把j++到第一个不是1的下一个位置
                }
            }
        }
        return max(res, i-j);
    }
```

#### [424. 替换后的最长重复字符](https://leetcode-cn.com/problems/longest-repeating-character-replacement/)

给你一个仅由大写英文字母组成的字符串，你可以将任意位置上的字符替换成另外的字符，总共可最多替换 *k* 次。在执行上述操作后，找到包含重复字母的最长子串的长度。

**注意:**
字符串长度 和 *k* 不会超过 104。

输入:
s = "AABABBA", k = 1

输出:

4

```c++
int characterReplacement(string s, int k) {
        vector<int> count(26, 0);
        int l = 0, ans = 0, maxCount = 0;
        for(int r = 0; r < s.size(); ++r){
            count[s[r]-'A']++;
            maxCount = max(maxCount, count[s[r]-'A']);
            if(r-l+1 - maxCount <= k)
                ans = max(ans, r-l+1);
            else{
                // 只维护基本信息，平移窗口
                count[s[l]-'A']--;
                l++;
            }
        }
        return ans;
    }
```



#### [面试题48. 最长不含重复字符的子字符串](https://leetcode-cn.com/problems/zui-chang-bu-han-zhong-fu-zi-fu-de-zi-zi-fu-chuan-lcof/)(动态规划)

请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。

**示例 1:**

```
输入: "abcabcbb"
输出: 3 
解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
```

```c++
class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> count;
        set<char> st;
        int l = 0, r = 0, ans = 0;
        for(; r < s.size(); ++r)
        {
            count[s[r]]++;
            if(count[s[r]] > 1) st.insert(s[r]);
            if(!st.size()) ans = max(ans, r-l+1);
            else
            {
                count[s[l]]--;
                if(count[s[l]] == 1) st.erase(st.find(s[l]));
                l++;
            }
        }
        return ans;
    }
};
```

#### [1438. 绝对差不超过限制的最长连续子数组](https://leetcode-cn.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/)

给你一个整数数组 `nums` ，和一个表示限制的整数 `limit`，请你返回最长连续子数组的长度，该子数组中的任意两个元素之间的绝对差必须小于或者等于 `limit` *。*

如果不存在满足条件的子数组，则返回 `0` 。

```c++
int longestSubarray(vector<int>& nums, int limit) {
        multiset<int> st;
        int ans = 0;
        for(int i = 0, j = 0; i < nums.size(); ++i)
        {
            st.insert(nums[i]);
            if(*st.rbegin()-*st.begin() > limit){
                st.erase(st.find(nums[j]));
                ++j;
            }
            ans = max(ans, i-j+1);
        }
        return ans;
    }
```

