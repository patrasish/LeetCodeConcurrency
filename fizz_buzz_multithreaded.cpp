#include<functional>
#include<mutex>
#include<condition_variable>

using namespace std;


class FizzBuzz {
private:
    int n_;
    mutex mtx_;
    condition_variable cv_;
    int cur_;

public:
    FizzBuzz(int n) :
        n_{n}, cur_{1} {}

    // printFizz() outputs "fizz".
    void fizz(function<void()> printFizz) {
        while(true){
            {
                unique_lock ul(mtx_);
                cv_.wait(ul, [this]{
                    return (cur_ > n_) || (((cur_ % 3) == 0) && ((cur_ % 5) > 0));
                });
                if(cur_ > n_){
                    ul.unlock();
                    cv_.notify_all();
                    return;
                }
                printFizz();
                ++cur_;
            }
            cv_.notify_all();
        }
    }

    // printBuzz() outputs "buzz".
    void buzz(function<void()> printBuzz) {
        while(true){
            {
                unique_lock ul(mtx_);
                cv_.wait(ul, [this]{
                    return (cur_ > n_) || (((cur_ % 3) > 0) && ((cur_ % 5) == 0));
                });
                if(cur_ > n_){
                    ul.unlock();
                    cv_.notify_all();
                    return;
                }
                printBuzz();
                ++cur_;
            }
            cv_.notify_all();
        }
    }

    // printFizzBuzz() outputs "fizzbuzz".
	void fizzbuzz(function<void()> printFizzBuzz) {
        while(true){
            {
                unique_lock ul(mtx_);
                cv_.wait(ul, [this]{
                    return (cur_ > n_) || (((cur_ % 3) == 0) && ((cur_ % 5) == 0));
                });
                if(cur_ > n_){
                    ul.unlock();
                    cv_.notify_all();
                    return;
                }
                printFizzBuzz();
                ++cur_;
            }
            cv_.notify_all();
        }
    }

    // printNumber(x) outputs "x", where x is an integer.
    void number(function<void(int)> printNumber) {
        while(true){
            {
                unique_lock ul(mtx_);
                cv_.wait(ul, [this]{
                    return (cur_ > n_) || (((cur_ % 3) > 0) && ((cur_ % 5) > 0));
                });
                if(cur_ > n_){
                    ul.unlock();
                    cv_.notify_all();
                    return;
                }
                printNumber(cur_);
                ++cur_;
            }
            cv_.notify_all();
        }
    }
};