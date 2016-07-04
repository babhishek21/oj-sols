/**
 * Nested List Weight Sum I (Leetcode)
 * Given a nested list of integers, returns the sum of all integers in the list weighted by their depth
 * For example, given the list {{1,1},2,{1,1}} the function should return 10 (four 1's at depth 2, one 2 at depth 1)
 * Given the list {1,{4,{6}}} the function should return 27 (one 1 at depth 1, one 4 at depth 2, one 6 at depth2)
 */

/**
 * This is the interface that represents nested lists.
 * You should not implement it, or speculate about its implementation.
 */
public interface NestedInteger {

  // Returns true if this NestedInteger holds a single integer, rather than a nested list
 public boolean isInteger();

  // Returns the single integer that this NestedInteger holds, if it holds a single integer
  // Returns null if this NestedInteger holds a nested list
 public Integer getInteger();

  // Returns the nested list that this NestedInteger holds, if it holds a nested list
  // Returns null if this NestedInteger holds a single integer
 public List<NestedInteger> getList();
}

public class Solution {
  public int getDepthSum(List<NestedInteger> nestedList) {
    return dfs(nestedList, 1);
  }

  public int dfs(List<NestedInteger> nestedList, int depth) {
    if(nestedList == null || nestedList.size() == 0)
      return 0;

    int sum = 0;
    for(NestedInteger nestedListItem: nestedList) {
      if(nestedListItem.isInteger())
        sum += nestedListItem.getInteger() * depth;
      else
        sum += dfs(nestedListItem.getList(), depth+1);
    }

    return sum;
  }
}

/**
 * Nested List Weight Sum II (Leetcode)
 * Different from the previous question where weight is increasing from root to leaf, now the weight is defined
 * from bottom up. i.e., the leaf level integers have weight 1, and the root level integers have the largest weight.
 */

// Solution 1: One pass DFS Solution. Use an array to store depth wise sum, then post-process.
// O(n) time + O(d) extra space + O(d) vector resizing time
// WARNING: C++ code (Not JAVA)
class Solution1 {
public:
  int getDepthSumInverse(vector<NestedInteger> nestedList) {
    vector<int> levelSum;

    for(auto nestedListItem: nestedList)
      dfs(nestedListItem, 0, levelSum);

    int sum = 0;
    for(int i=0; i<levelSum; i++)
      sum += levelSum[i]*(i+1);

    return sum;
  }

private:
  void dfs(vector<NestedInteger> &nestedListItem, int depth, vector<int> &levelSum) {
    if(levelSum.size() < depth + 1)
      levelSum.resize(depth+1);

    if(nestedListItem.isInteger())
      levelSum[depth] += nestedListItem.getInteger();
    else
      for(auto nestedListItemItem: nestedListItem.getList())
        dfs(nestedListItemItem, depth+1, levelSum);
  }
}

// Solution 2: One pass DFS solution where we pass sum of each level to deeper levels. No post-processing.
// O(n) time + O(d) extra space
public class Solution2 {
  public int getDepthSumInverse(List<NestedInteger> nestedList) {
    return dfs(nestedList, 0);
  }

  public int dfs(List<NestedInteger> nestedList, int prevSum) {
    List<NestedInteger> nextLevel = new ArrayList<>();

    for(NestedInteger nestedListItem: nestedList) {
      if(nestedListItem.isInteger())
        prevSum += nestedListItem.getInteger();
      else
        nextLevel.addAll(nestedListItem.getList());
    }

    return prevSum + (nextLevel.isEmpty() ? 0 : dfs(nextLevel, prevSum));
  }

// Alternative second solution where we do it iteratively
// Unweghted sum is kept untouched. So is added d times
  public int getDepthSumInverse2(List<NestedInteger> nestedList) {
    int weighted = 0, unweighted = 0;

    while(!nestedList.isEmpty()) {
      List<NestedInteger> nextLevel = new ArrayList<>();

      for(NestedInteger nestedListItem: nestedList) {
        if(nestedListItem.isInteger())
          unweighted += nestedListItem.getInteger();
        else
          nextLevel.addAll(nestedListItem.getList());
      }

      weighted += unweighted;
      nestedList = nextLevel;
    }

    return weighted;
  }

// Third solution (like the second one) where we do BFS instead of DFS. Also iteratively.
  public int getDepthSumInverse3(List<NestedInteger> nestedList) {
    int weighted = 0, unweighted = 0;

    Queue<List<NestedInteger>> queue = new LinkedList<>();
    queue.offer(nestedList); // no exceptions thrown

    while(!queue.isEmpty()) {
      int currentLevelWidth = queue.size();

      while(currentLevelWidth-- > 0) {
        nestedList = queue.poll();

        for(NestedInteger nestedListItem: nestedList) {
          if(nestedListItem.isInteger())
            unweighted += nestedListItem.getInteger();
          else
            queue.offer(nestedListItem.getList());
        }
      }

      weighted += untouched;
    }

    return weighted;
  }
}


