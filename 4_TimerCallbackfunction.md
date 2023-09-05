# Timer API and Data Structure Notes 📚🕰️

## Introduction 🌟
In this session, we're diving deep into creating a Timer API with a particular focus on the `setupTimer` function and the callback functionality that it employs. This is a part of a larger system to build robust and flexible timer utilities.

---

## `setupTimer` API 💡
### Definition 📝
- Responsible for initializing a Timer data structure called `WrappedTimer`.
- **Prototype**: `setupTimer(arg1, arg2, arg3, arg4, arg5, arg6)`
- **Return Type**: Pointer to the initialized Wrapped Timer.

### Arguments 📌
1. `Function Pointer`: Callback function invoked when the timer fires.
2. `Expiration Time`: User-specified interval in milliseconds for first expiration.
3. `Subsequent Expiration Time`: Interval for second, third, etc., expirations.
4. `Number of Fires`: Number of times the timer should expire.
5. `Application Data`: Data passed as an argument to the timer callback.
6. `Exponential Backoff`: Flag for exponential backoff feature.

### Implementation 🛠️
- Allocate memory for Wrapped Timer.
- Initialize POSIX timer within Wrapped Timer.
- Store all the arguments in the Wrapped Timer's attributes.
- Sanity check to ensure the callback function exists.
- Initialize other timer attributes like `exponentialBackoff`.
  
> **Note 📝**: Also initialize the secondary expiration time in the interval attribute of the timer which was missed in the previous lecture.


```C
// Callback wrapper to handle timer state and user-defined callback
static void timer_callback_wrapper(union sigval arg) {
    Timer_t *timer = (Timer_t *)(arg.sival_ptr);
    if(timer->timer_state == TIMER_RESUMED) {
        if(timer->sec_exp_timer != 0) {
            timer->timer_state = TIMER_RUNNING;
        }
    }

    // Invoke the user-provided callback function
    timer->cb(timer, timer->user_arg);
}

```
---

## Callback Function 🔄
### What does it do? 🤔
- Gets invoked when the timer expires.
- It should invoke the user-defined callback function.

### Implementation 🛠️
1. Typecast the argument to Wrapped Timer type.
2. Invoke the user-defined callback stored in the `cb` attribute.
3. Pass Wrapped Timer and user data as arguments to this function.

---

## Common Pitfalls and Notes 🚧
- Don't forget to initialize the secondary expiration timer, missed in the previous lecture.
- Complete assignments on time APIs like `timespecToMillisecond` and `timerFullTimeAnspach`.

---

# Interview Questions & Answers 🤔💡
1. **What is the primary purpose of the `setupTimer` API?**
    - *Answer*: The primary purpose is to initialize the `WrappedTimer` data structure with attributes like callback functions, expiration times, and other user-specified data.

2. **How does the callback function work in the `WrappedTimer` setup?**
    - *Answer*: When the timer expires, a pre-specified callback function gets invoked. This callback function, in turn, invokes the user-defined callback that was passed during the timer setup.

3. **What is the significance of Exponential Backoff in the timer?**
    - *Answer*: Exponential backoff is a flag that signifies if the timer should employ an exponential increase in the delay intervals between successive timer expirations.

4. **Why is a secondary expiration time needed?**
    - *Answer*: The secondary expiration time is used for the timer's subsequent expirations after the first one. This allows for more complex timing behaviors.

5. **Why is it important to pass the Wrapped Timer object to the callback function?**
    - *Answer*: Passing the Wrapped Timer object to the callback function allows the callback to have full context, giving it the ability to manipulate the timer or access other hidden information.


**Question:**
can you explain how the "setup_timer" API in the given C code works? Specifically, what does it do, and what are its arguments? Could you also touch upon why a wrapper around the POSIX timer is beneficial?

---

### Answer:

The `setup_timer` API serves as a constructor for creating a "wrapper timer" object, essentially wrapping around a POSIX timer to provide added functionality and ease of use. It takes in six arguments:

1. `void (*timer_cb)(Timer_t*, void *)`: This is a function pointer that points to the callback function that will be invoked when the timer expires.
  
2. `unsigned long exp_timer`: This is the expiration time interval for the first timer expiration, specified in milliseconds.

3. `unsigned long sec_exp_timer`: This is the expiration time interval for subsequent timer expirations, also specified in milliseconds.

4. `uint32_t threshold`: This argument specifies the maximum number of times the timer should expire. A value of 0 means the timer will fire indefinitely.

5. `void *user_arg`: This is a pointer to user data that will be passed as an argument to the timer callback function.

6. `bool exponential_backoff`: This boolean value indicates whether the timer will use exponential backoff or not.

The API returns a pointer to a "cooked-up" wrapper timer, fully initialized and ready for use.

#### Benefits of Wrapper Timer:

1. **Ease of Use**: The wrapper timer simplifies timer creation and management by abstracting away many of the lower-level details.

2. **Enhanced Functionality**: The wrapper provides extra features like the ability to pause, resume, and set thresholds on the number of timer expirations.

3. **User Data**: The wrapper allows passing in user data, which makes it easier to use the timer in more complex applications.

4. **Flexibility**: The API makes it easy to change the timer's behavior, such as enabling exponential backoff.

5. **Code Reusability**: Once set up, the wrapper timer can be used across different applications, promoting code reusability.

By using this `setup_timer` API, the programmer gets an easy-to-use, feature-rich timer that encapsulates much of the complexity of using POSIX timers directly.
---

That wraps up the detailed notes. Good luck with your interviews! 🍀👍
