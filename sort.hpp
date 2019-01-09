
#include <memory>
#include <vector>
#include <iostream>

template<typename T>
class TreeNode {
	TreeNode(T k) : key(k) {}
	T key;
	std::unique_ptr<TreeNode> left, right;
};


template<typename T>
std::unique_ptr<TreeNode<T>> createpostorderhelper(const std::vector<T> &init, int low, int high) {
	std::unique_ptr<TreeNode<T>> n = std::unique_ptr<TreeNode<T>>(new TreeNode<T>(init.at(low)));
	if(low >= high) return n;
	int rightsubtreestart = high;
	for(int i = low+1; i < high; ++i) {
		if(init.at(i) > init.at(low)) {
			rightsubtreestart = i; break;
		}
	}

	n->left = createpostorderhelper<T>(init, low+1, rightsubtreestart-1);
	if(rightsubtreestart < high) {
		n->right = createpostorderhelper<T>(init, rightsubtreestart, high);
	}
	return n;
}

template<typename T>
std::unique_ptr<TreeNode<T>> createpostorder(const std::vector<T> &init) {
	return createpostorderhelper<T>(init, 0, init.size());
}

template<typename T>
void printbranch(const std::unique_ptr<TreeNode<T>> &branch) {
	if(branch != nullptr) {
		std::cout << "-> " << branch->key;
		if(branch->right != nullptr) printbranch(branch->right);
	}
}

template<typename T>
void printtreehelper(const std::unique_ptr<TreeNode<T>>& node, int level=0) {
	if(node != nullptr) {
		std::cout << node->key;
		printbranch(node->right);
		std::cout << std::endl;
		for(int i = 0; i < level; ++i) std::cout << "\t";
		std::cout << "\\";
		if(level >=0) std::cout << "->\t";
		if(node->left != nullptr) printtreehelper(node->left, level+1);
	}
}

template<typename T>
void swap(std::vector<T> &A, int i, int j) {
	T tmp = A.at(i);
	A.at(i) = A.at(j);
	A.at(j) = tmp;
}

inline size_t parent(size_t i) {
	return (i) >> 1;
}

inline size_t left(size_t i) {
	return ((i) << 1) + 1;
}

inline size_t right(size_t i) {
	return ((i) << 1) + 2;
}

template<typename T>
void maxheapify(std::vector<T> &heap, size_t i, size_t maxsize) {
	size_t l = left(i);
	size_t r = right(i);
	size_t largest = l < maxsize and heap.at(l) > heap.at(i) ? l: i;
	if(r < maxsize and heap.at(r) > heap.at(largest)) largest = r;

	if(largest != i) {
		swap(heap, i, largest);
		maxheapify(heap, largest, maxsize);	
	}
}

template<typename T>
void buildmaxheap(std::vector<T> &heap) {
	for(int i = (heap.size()/2)-1; i >=0; --i) {
		maxheapify(heap, i, heap.size());
	}
}

template<typename T>
void heapsort(std::vector<T> &sortme) {
	buildmaxheap(sortme);
	size_t heapsize = sortme.size();
	for(int i = sortme.size()-1; i>0; --i) {
		swap(sortme, 0, i);

		maxheapify(sortme, 0, --heapsize);
	}
}

template<typename T>
T heapmaximum(std::vector<T> &maxheap) {
	return maxheap.at(0);
}

template<typename T>
T extractmax(std::vector<T> &maxheap) {
	T max = maxheap.at(0);
	maxheap.at(0) = maxheap.at(maxheap.size()-1);
	maxheap.erase(maxheap.end()-1);
	maxheapify(maxheap,0, maxheap.size());
	return max;
}

template<typename T>
int partition(std::vector<T> &sortme, int left, int right) {
	//breaks the array in to 4 possibly empty sets
	int i = left-1;
	T x = sortme.at(right);

	for(int j = left; j < right; ++j) {
		if(sortme.at(j) <= x) {
			++i;
			swap(sortme, i, j);	
		}
	}

	swap(sortme, i+1, right);
	return i+1;
}


template<typename T>
void quicksorthelper(std::vector<T> &sortme, int left, int right) {
	if(left >= right) return;
	int pivot = partition(sortme, left, right);
	quicksorthelper(sortme, left, pivot-1);
	quicksorthelper(sortme, pivot+1, right);
}

template<typename T> 
void quicksort(std::vector<T> &sortme) {
	quicksorthelper(sortme, 0, sortme.size()-1);
}


template<typename T>
std::vector<T> countingsort(std::vector<T> A, size_t k) {
	std::vector<T> C(k+1, 0), B(A.size(), -1);
	for(int j = 0; j < A.size(); ++j) {
		C.at(A.at(j)) = C.at(A.at(j)) + 1;
	}

	for(int i = 1; i < C.size(); ++i) {
		C.at(i) = C.at(i) + C.at(i-1);
	}

	for(int j = A.size()-1; j >= 0; --j) {
		B.at(C.at(A.at(j))-1) = A.at(j);
		C.at(A.at(j)) = C.at(A.at(j)) -1;
		std::cout<< std::endl;
	}
	return B;
}


