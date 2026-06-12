#include<functional>
#include<semaphore>

using namespace std;

class Foo {
    binary_semaphore first_turn_;
    binary_semaphore second_turn_;
    binary_semaphore third_turn_;
public:
    Foo() :
        first_turn_{1}, second_turn_{0}, third_turn_{0}
        {}

    void first(function<void()> printFirst) {
        first_turn_.acquire();
        printFirst();
        second_turn_.release();
    }

    void second(function<void()> printSecond) {
        second_turn_.acquire();
        printSecond();
        third_turn_.release();
    }

    void third(function<void()> printThird) {
        third_turn_.acquire();
        printThird();
    }
};