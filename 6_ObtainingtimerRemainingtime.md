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
