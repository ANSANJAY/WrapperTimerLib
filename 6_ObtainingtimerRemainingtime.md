# Timer Test Program & Extended Functionality 📚🔍

## Introduction 🌟
In this session, we learn about a test program for testing our custom wrapper timer. We are using this program to extend the functionalities of our existing timer library.

---

## Test Program Structure 🏗️
### Initial Setup 🛠️
- **File Name**: `timerlib_test.c`
- **Purpose**: To test the custom timer API functionality.
- **Functionality**: 
  - Define random user data.
  - Create a wrapper timer using `setupTimer` API.
  - Pass user-defined callback and other timer attributes like expiration time, secondary expiration time, and threshold.

#### Initialization Steps 🚀
1. Pass user-defined application callback to the timer.
2. Set expiration time to 1000ms.
3. Set secondary expiration time to 1000ms.
4. Set the number of thresholds to 0 (Indefinite expiration).
5. Pass user data.
6. Set up exponential backoff (To be implemented).

#### Starting the Timer 🕐
- Use the `startTimer` API to start the timer. 
- Expectation: Timer fires every 1000ms and invokes the user-defined callback.

-----
```C
// Function to get the remaining time on a timer in milliseconds
unsigned long timer_get_time_remaining_in_mill_sec(Timer_t *timer) {
    struct itimerspec remaining_time;
    memset(&remaining_time, 0, sizeof(struct itimerspec));
    
    timer_gettime(timer->posix_timer, &remaining_time);
    
    return timespec_to_millisec(&remaining_time.it_value);
}
```
The function `timer_get_time_remaining_in_mill_sec` is designed to get the remaining time for a given timer object (`Timer_t *timer`) in milliseconds.

Here's a breakdown of what each line does:

1. **`struct itimerspec remaining_time;`**: Declares a `struct itimerspec` object named `remaining_time`. The `itimerspec` structure is used in POSIX-compliant systems to specify timers. It typically contains two `timespec` structures: one for the initial time and one for the interval.

2. **`memset(&remaining_time, 0, sizeof(struct itimerspec));`**: Initializes all the fields of `remaining_time` to zero. The `memset` function sets the first `sizeof(struct itimerspec)` bytes of the memory area pointed to by `&remaining_time` to zero.

3. **`timer_gettime(timer->posix_timer, &remaining_time);`**: Calls the `timer_gettime()` function, which fills `remaining_time` with the current setting of the timer pointed to by `timer->posix_timer`.

4. **`return timespec_to_millisec(&remaining_time.it_value);`**: Calls a helper function named `timespec_to_millisec` to convert the remaining time stored in `remaining_time.it_value` to milliseconds and returns this value.

The function ultimately returns the remaining time on the timer in milliseconds.
----
Here's an example to illustrate how `timer_gettime()` can be used:

Suppose you have a timer `my_timer` that is set to expire after 10 seconds initially, and then every 5 seconds after that.

The `struct itimerspec` that you might set for this timer would look like:

```c
struct itimerspec timerSpec;
timerSpec.it_value.tv_sec = 10;  // 10 seconds
timerSpec.it_value.tv_nsec = 0;  // 0 nanoseconds
timerSpec.it_interval.tv_sec = 5;  // 5 seconds
timerSpec.it_interval.tv_nsec = 0;  // 0 nanoseconds
```

Now, let's say 4 seconds have passed since the timer was started. If you call `timer_gettime()` at this point to check the remaining time, it should return 6 seconds as the time remaining until the next expiration and 5 seconds as the interval for subsequent expirations.

Here's how you could code this:

```c
#include <stdio.h>
#include <time.h>
#include <string.h>  // for memset
#include <signal.h>  // for timer_create, etc.

// Function to convert timespec to milliseconds
unsigned long timespec_to_millisec(struct timespec *ts) {
    return (ts->tv_sec * 1000) + (ts->tv_nsec / 1000000);
}

int main() {
    timer_t my_timer;
    struct sigevent sevp;
    struct itimerspec timerSpec, remaining_time;

    memset(&sevp, 0, sizeof(struct sigevent));
    sevp.sigev_notify = SIGEV_NONE;  // No signal is sent, for demonstration

    // Create a timer
    if (timer_create(CLOCK_REALTIME, &sevp, &my_timer) == -1) {
        perror("timer_create");
        return 1;
    }

    // Set timer to expire after 10 seconds and then every 5 seconds
    timerSpec.it_value.tv_sec = 10;
    timerSpec.it_value.tv_nsec = 0;
    timerSpec.it_interval.tv_sec = 5;
    timerSpec.it_interval.tv_nsec = 0;

    if (timer_settime(my_timer, 0, &timerSpec, NULL) == -1) {
        perror("timer_settime");
        return 1;
    }

    // Simulate 4 seconds passing
    sleep(4);

    // Get the remaining time and interval on the timer
    if (timer_gettime(my_timer, &remaining_time) == -1) {
        perror("timer_gettime");
        return 1;
    }

    // Output the remaining time and interval
    printf("Time remaining: %ld seconds\n", remaining_time.it_value.tv_sec);
    printf("Interval: %ld seconds\n", remaining_time.it_interval.tv_sec);

    // Convert the remaining time to milliseconds and print it
    unsigned long remaining_millis = timespec_to_millisec(&remaining_time.it_value);
    printf("Time remaining in milliseconds: %lu\n", remaining_millis);

    return 0;
}
```

Output would be something like:

```
Time remaining: 6 seconds
Interval: 5 seconds
Time remaining in milliseconds: 6000
```

This shows that `timer_gettime()` gives you the remaining time until the next expiration (`it_value`) as well as the interval between expirations (`it_interval`).


------------------------

The `timer_gettime()` function is used to fetch the amount of time until the next expiration of a POSIX timer, as well as the reload value of the timer. When called, it populates a `struct itimerspec` variable that is passed as its second argument.

The `struct itimerspec` is defined something like:

```c
struct itimerspec {
  struct timespec it_interval;  /* Timer interval */
  struct timespec it_value;     /* Initial expiration */
};
```

Here, `it_interval` specifies the period of the timer, i.e., the time until the timer fires again once it has initially expired. `it_value` specifies the time until the next expiration of the timer from the current time.

Both `it_interval` and `it_value` are of type `struct timespec`, which is defined as:

```c
struct timespec {
  time_t tv_sec;  /* seconds */
  long tv_nsec;   /* nanoseconds */
};
```

The function is usually called as:

```c
int timer_gettime(timer_t timerid, struct itimerspec *value);
```

- `timerid`: The timer identifier.
- `value`: A pointer to a `struct itimerspec` variable that will hold the current setting of the timer.

After the call, the `it_value` field of the `struct itimerspec` variable will contain the amount of time left until the timer will next expire, and the `it_interval` field will contain the period of the timer (or zero if the timer is a one-shot).

The function returns 0 on success, and `-1` on failure, setting `errno` to indicate the error.

So, in the context of your program, `timer_gettime(timer->posix_timer, &remaining_time);` will populate the `remaining_time` `struct` with the remaining time until the next timer expiration (`remaining_time.it_value`) and the period of the timer (`remaining_time.it_interval`).

----

# Detailed Notes  on Time Remaining API in Timer Library 📝

## Introduction 🚀
- The notes focuses on an API that returns the `time remaining for a timer to expire in milliseconds`.
  
## Conceptual Overview 🤔
- If you start a timer with an expiration time of 10 seconds, and check at 6 seconds, it should show 4 seconds remaining.
- Example: `time d = 0, expiration time = 10s`
  - At `time T = 6`, 4000 milliseconds should be returned.
  
## Implementation Details 🛠
  
### File and API 
- Working in the file `timer_lib.c` to complete our library.
  
### Linux Built-In API 🐧
- Linux provides an in-built API to find the time left for a timer to expire.
  
### Variables and Types 📊
- `itimerspec` variable is used to capture the time.
  
### Method Signature 📜
- Linux API: `timer_gettime(timer, &itimerspec_variable);`
  - First Argument: The timer
  - Second Argument: The output parameter (`itimerspec`) where the result will be stored.

### API Logic 👨‍💻
- The API will store the number of seconds and nanoseconds remaining in the `itimerspec` variable.
- A convenience function converts these values to milliseconds.


## Key Takeaways 🎯
- The API is crucial for determining how much time is left for a timer to expire.
- Works with the Linux in-built API and `itimerspec` data type.
- API implementation is straightforward; just calls the built-in Linux function and converts the time to milliseconds.

---

# Interview Questions and Answers about Time Remaining API 🤓

### Q1: What does the Time Remaining API do? 🤔
**A1:** The Time Remaining API returns the time remaining for a timer to expire. It returns this time in milliseconds.

### Q2: How is the time remaining calculated? 🛠
**A2:** The Linux operating system provides an inbuilt API called `timer_gettime` which takes the timer and an `itimerspec` variable as arguments. The remaining time in seconds and nanoseconds is stored in this `itimerspec` variable, which is then converted to milliseconds for output.

### Q3: What is the significance of the `itimerspec` variable in this implementation? 📊
**A3:** The `itimerspec` variable captures the number of seconds and nanoseconds remaining for the timer to expire. It serves as the output parameter where the result from the Linux API is stored.

### Q4: Can you explain the method signature of the Linux in-built API used? 📜
**A4:** Sure, the method signature of the Linux in-built API `timer_gettime` is as follows:
```c
timer_gettime(timer, &itimerspec_variable);
```
- The first argument is the timer you are querying.
- The second argument is the `itimerspec` variable where the remaining time will be stored.


## Extended Functionality 🎯
### Menu-Driven Test Program 📋
- Enhance the test program to provide a user menu for various functionalities like pausing, resuming, restarting, etc.

#### Menu Options 📌
1. Pause Timer
2. Resume Timer
3. Restart Timer
4. Reschedule Timer
5. Delete Timer
6. Cancel Timer
7. Print Time
8. Get Remaining Time in ms

#### Implementation Roadmap 🗺️
- Use a switch statement for user choices.
- Implement each function one-by-one and test it against this test program.

---



# Interview Questions & Answers 🤔💡

1. **What is the purpose of the `timely_test.c` program?**
   - *Answer*: The `timely_test.c` program is designed to test the functionalities of our custom timer APIs. It is set up to simulate various use-cases and evaluate the performance and reliability of the timer library.

2. **How does the test program initialize and start the timer?**
   - *Answer*: The test program initializes the timer by passing in user-defined data, an application callback, and various timer attributes such as expiration time and secondary expiration time. It then uses the `startTimer` API to kickstart the timer.

3. **Describe the extended functionality being added to the test program.**
   - *Answer*: The extended functionality includes a menu-driven interface that allows the user to interact with the timer by choosing various operations like pausing, resuming, restarting, and so on.

4. **What is the significance of setting the number of thresholds to 0 in the test program?**
   - *Answer*: Setting the number of thresholds to 0 means that the timer will expire indefinitely, allowing us to test long-running scenarios.

5. **How is the test program planning to validate each of the new functionalities?**
   - *Answer*: Each new functionality will be implemented one-by-one, and as they are completed, they will be uncommented in the test program to be tested individually for correctness.

6. **What does the exponential backoff parameter indicate in the test program?**
   - *Answer*: The exponential backoff parameter is a feature to be implemented. It will likely serve to adjust the time intervals between retries dynamically, making the system more resilient to failures.

---

Happy studying! 📘🤓
