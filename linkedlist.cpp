#include <memory>

template<typename T>
class LinkedList {
public:
	LinkedList(T k) : key(k) {}
	T key;
	std::unique_ptr<LinkedList> prev, next;
}
