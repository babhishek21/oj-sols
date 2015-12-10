#include<bits/stdc++.h>
using namespace std;

struct SegmentTreeNode {
	int prefixMaxSum, suffixMaxSum, maxSum, sum;

	void assignLeaf(int value) {
		prefixMaxSum = suffixMaxSum = maxSum = sum = value;
	}

	void merge(SegmentTreeNode& left, SegmentTreeNode& right) {
		sum = left.sum + right.sum;
		prefixMaxSum = max(left.prefixMaxSum, left.sum + right.prefixMaxSum);
		suffixMaxSum = max(right.suffixMaxSum, right.sum + left.suffixMaxSum);
		maxSum = max(prefixMaxSum, max(suffixMaxSum, max(left.maxSum, max(right.maxSum, left.suffixMaxSum + right.prefixMaxSum))));
	}

	int getValue() {
		return maxSum;
	}
};

template <typename T, typename V> class SegmentTree {
	SegmentTreeNode *nodes;
	int N;

public:
	SegmentTree(T arr[], int N) {
		this->N = N;
		nodes = new SegmentTreeNode[getSegmentTreeSize(N)];
		buildTree(arr, 1, 0, N-1);
	}

	~SegmentTree() {
		delete[] nodes;
	}

	V getValue(int lo, int hi) {
		SegmentTreeNode result = getValue(1, 0, N-1, lo, hi);
		return result.getValue();
	}

	void update(int index, T value) {
		update(1, 0, N-1, index, value);
	}

private:
	void buildTree(T arr[], int stIndex, int lo, int hi) {
		if(lo == hi) {
			nodes[stIndex].assignLeaf(arr[lo]);
			return;
		}

		int mid = lo + (hi - lo)/2;
		buildTree(arr, 2*stIndex, lo, mid);
		buildTree(arr, 2*stIndex+1, mid+1, hi);
		nodes[stIndex].merge(nodes[2*stIndex], nodes[2*stIndex+1]);
	}

	SegmentTreeNode getValue(int stIndex, int left, int right, int lo, int hi) {
		if(left == lo and right == hi)
			return nodes[stIndex];

		int mid = left + (right - left)/2;
		if(lo > mid)
			return getValue(2*stIndex+1, mid+1, right, lo, hi);
		else if(hi <= mid)
			return getValue(2*stIndex, left, mid, lo, hi);

		SegmentTreeNode leftResult = getValue(2*stIndex, left, mid, lo, mid);
		SegmentTreeNode rightResult = getValue(2*stIndex+1, mid+1, right, mid+1, hi);

		SegmentTreeNode result;
		result.merge(leftResult, rightResult);
		return result;
	}

	void update(int stIndex, int lo, int hi, int index, T value) {
		if(lo == hi) {
			nodes[stIndex].assignLeaf(value);
			return;
		}

		int mid = lo + (hi-lo)/2;
		if(index <= mid)
			update(2*index+1, lo, mid, index, value);
		else if(index > mid)
			update(2*index+2, mid+1, hi, index, value);

		nodes[stIndex].merge(nodes[2*stIndex], nodes[2*stIndex+1]);
	}

	int getSegmentTreeSize(int N) {
		int size = 1;
		for (; size < N; size <<= 1);
		return size << 1;
	}
};

int main() {
	int N, arr[50003], M;

	scanf("%d", &N);

	for (int i=0; i<N; ++i) {
		scanf("%d", &arr[i]);
	}

	SegmentTree<int, int> st(arr, N);

	scanf("%d", &M);

	while(M--) {
		int x, y;

		scanf("%d %d", &x, &y);

		printf("%d\n", st.getValue(x-1, y-1));
	}

	return 0;
}
