#include<functional>
#include<semaphore>

using namespace std;

class H2O {
    counting_semaphore<1000000> h_slots_;
    counting_semaphore<1000000> o_slots_;

    counting_semaphore<1000000> h_waits_;
    counting_semaphore<1000000> o_waits_;

    int active_atoms_;
    counting_semaphore<100000> barrier_;

    mutex mtx_;

public:
    H2O() :
        h_slots_{2}, o_slots_{1}, h_waits_{0}, o_waits_{0}, barrier_{0}, active_atoms_{0} {}

    void hydrogen(function<void()> releaseHydrogen) {
        h_slots_.acquire();
        {
            lock_guard lg(mtx_);
            ++active_atoms_;
            if(active_atoms_ == 3){
                h_waits_.release(2);
                o_waits_.release();
            }
        }
        h_waits_.acquire();
        releaseHydrogen();
        pass_barrier();
    }

    void oxygen(function<void()> releaseOxygen) {
        o_slots_.acquire();
        {
            lock_guard lg(mtx_);
            ++active_atoms_;
            if(active_atoms_ == 3){
                h_waits_.release(2);
                o_waits_.release();
            }
        }
        o_waits_.acquire();
        releaseOxygen();
        pass_barrier();
    }
    void pass_barrier(){
        bool should_pass = false;
        {
            lock_guard lg(mtx_);
            --active_atoms_;
            if(active_atoms_ == 0){
                should_pass = true;
                h_slots_.release(2);
                o_slots_.release();
            }
        }
        if(should_pass)
            barrier_.release(3);
        barrier_.acquire();
    }
};