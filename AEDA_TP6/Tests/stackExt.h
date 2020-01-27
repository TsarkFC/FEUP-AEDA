# include <iostream>
# include <stack>

using namespace std;

template <class T>
class StackExt {
    stack<T> alls;
    stack<T> mins;
public:
	StackExt() {};
	bool empty() const; 
	T &top();
	void pop();
	void push(const T & val);
	T &findMin();
};

// a alterar
template <class T> 
bool StackExt<T>::empty() const{
	return alls.empty();
}

//a alterar
template <class T> 
T& StackExt<T>::top()
{
    T *novo = new T();
    *novo = alls.top();
    return *novo;
}

//a alterar
template <class T> 
void StackExt<T>::pop()
{
    if (alls.empty()) return;
    if (mins.empty()) return;

    if (alls.top() == mins.top()){
        alls.pop();
        mins.pop();
    }
    else alls.pop();
}

//a alterar
template <class T> 
void StackExt<T>::push(const T & val)
{
    if (mins.size() == 0){
        alls.push(val);
        mins.push(val);
    }
    else if (val <= mins.top()){
        alls.push(val);
        mins.push(val);
    }
    else alls.push(val);

}

//a alterar
template <class T> 
T& StackExt<T>::findMin()
{
    T *novo = new T();
    *novo = mins.top();
    return *novo;
}

