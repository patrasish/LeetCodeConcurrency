#include<functional>
#include<semaphore>

using namespace std;


class FooBar {
private:
    int n_;
    binary_semaphore foo_turn_;
    binary_semaphore bar_turn_;

public:
    FooBar(int n) :
        n_{n}, foo_turn_{1}, bar_turn_{0}{}

    void foo(function<void()> printFoo) {
        
        for (int i = 0; i < n_; i++) {
            foo_turn_.acquire();
        	printFoo();
            bar_turn_.release();
        }
    }

    void bar(function<void()> printBar) {
        
        for (int i = 0; i < n_; i++) {
        	bar_turn_.acquire();
        	printBar();
            foo_turn_.release();
        }
    }
};