
# Simple example using std::mutex and std::condition_variable

`std::condition_variable` is used for two purposes:
- Notify other threads
- Wait for some condition

`std::condition_variable` allows consumer threads to wait on some condition and suspend themselves until the producer thread triggers a notification using one of the following functions:

a. notify_one() - this resume a single consumer thread to check if its condition was met.
b. notify_all() - this resume all consumer threads, and each one check if its condition was met.

It the condition is true, then the resumed thread continues its execution, otherwise it is suspended again.

# How it works

Two variables are required, a mutex (`std::mutex`) and a condition variable (`std::condition_variable`).

If the producer thread wants to be the notifier then:
1. Acquire the mutex lock using `std::lock_guard<std::mutex> lg(m);` (or `std::unique_lock<std::mutex> ul(m);`, but lock_guard is the most convenient).
2. When done, to notify it calls notify_one() or notify_all() and one, or all, consumer thread is awakened, and the mutex is atomically acquired by the first on reaching it.

If a consumer thread want to wait on some condition then:
1. Acquire the mutex lock using `std::unique_lock<std::mutex> ul(m);`.
2. Execute wait, wait_for, or wait_until. The wait operations atomically release the mutex and suspend the execution of the thread.
3. When the condition variable is notified, the thread is awakened, and the mutex is atomically reacquired. The thread could then check the condition and resume waiting if the wake up was spurious.
