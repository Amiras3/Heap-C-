#include <iostream>
#include <vector>
#include <utility>
#include <memory>

using namespace std;

template<typename T>
class Heap 
{
	vector<T> elements;
	int size = 0;
public:
	Heap(): elements{}, size{0} {}
	
	template<typename U>
	void push(U&& u) {
		elements.push_back(forward<U>(u));
		++size;
		for(int i = size - 1; i; ) {
			if(elements[(i - 1) / 2] < elements[i]) {
				swap(elements[(i - 1) / 2], elements[i]);
				i = (i - 1) / 2;
			} else {
				break;
			}
		}
	}

	void pop() {
		if(!size) {
			return;
		}
		swap(elements[0], elements[size - 1]);
		size--;
		int i = 0;
		while(2 * i + 1 < size) {
			int child = 2 * i + 1;
			if(child + 1 < size && elements[child + 1] > elements[child]) {
				child = child + 1;
			}
			if(elements[child] > elements[i]) {
				swap(elements[child], elements[i]);
				i = child;
			} else {
				break;
			}
		}	
	}
		
		
	T top() const {
		if(size) {
			return elements[0];
		}
		return T();
	}

	bool empty() const {
		return size == 0;
	}
};

int main() {
	Heap<int> h;
	for(int i = 0; i < 100; ++i) {
		int j = i;
		h.push(i);
		h.push(move(j));
	}
	for(int i = 0; i < 200; ++i) {
		cout << h.top() << endl;
		h.pop();	
	}
	return 0;
}

