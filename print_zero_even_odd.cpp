#include<functional>
#include<semaphore>
#include<mutex>

using namespace std;

class ZeroEvenOdd {
private:
    int n_;
    binary_semaphore zero_turn_;
    binary_semaphore odd_turn_;
    binary_semaphore even_turn_;
    mutex mtx_;
    bool last_odd_;

public:
    ZeroEvenOdd(int n) :
        n_{n},
        zero_turn_{1},
        odd_turn_{0},
        even_turn_{0},
        last_odd_{false}
        {}

    // printNumber(x) outputs "x", where x is an integer.
    void zero(function<void(int)> printNumber) {
        for(int i = 0; i < n_; ++i){
            zero_turn_.acquire();
            printNumber(0);
            lock_guard lg(mtx_);
            if(last_odd_)
                even_turn_.release();
            else
                odd_turn_.release();
        }

    }

    void even(function<void(int)> printNumber) {
        for(int i = 2; i <= n_; i += 2){
            even_turn_.acquire();
            printNumber(i);
            {
                lock_guard lg(mtx_);
                last_odd_ = false;
            }
            zero_turn_.release();
        }
    }

    void odd(function<void(int)> printNumber) {
        for(int i = 1; i <= n_; i += 2){
            odd_turn_.acquire();
            printNumber(i);
            {
                lock_guard lg(mtx_);
                last_odd_ = true;
            }
            zero_turn_.release();
        }
    }
};