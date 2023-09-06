# Timer State Machine and Implementation Notes 🕐

## Table of Contents 📚
1. [Timer States](#timer-states)
2. [Creating a Timer](#creating-a-timer)
3. [Timer Operations](#timer-operations)
4. [Implementation of `setup_timer` API](#implementation-of-setup_timer-api)

---

## Timer States 🔄

### Overview
The state machine for timers can transition through multiple states based on the API calls. 

### States
1. **Timer Init State**: The initial state of the timer upon creation.
2. **Timer Running State**: Timer transitions to this state when started.
3. **Timer Deleted State**: Timer can be deleted from any state.
4. **Timer Canceled State**: Timer can be canceled, but memory is not freed.
5. **Timer Paused State**: Timer can be paused from the running state.
6. **Timer Resumed State**: Timer can be resumed from the paused state.

### Transitions
- Timer Init State ➡️ Timer Running State: Through API `timer_set_time`.
- Timer Running State ➡️ Timer Deleted State: Can be deleted at any point.
- Timer Running State ➡️ Timer Canceled State: Timer can be canceled.
- Timer Running State ➡️ Timer Paused State: Timer can be paused.
- Timer Paused State ➡️ Timer Resumed State: Timer can be resumed.

---

The `setup_timer` function is designed to simplify the process of creating and initializing a timer in a POSIX-based system. Below is a breakdown of why this function is structured the way it is:

### Parameters:

- **`TimerCallback callback`**: This is a user-defined function that will be called when the timer expires. The function has flexibility, as it doesn't force the user to follow a pre-determined function signature for callbacks.

- **`uint32_t initial_time`**: This is the initial time delay (in milliseconds) after which the timer will expire for the first time. It allows for fine-grained control over when the timer actually kicks off.

- **`uint32_t interval_time`**: This is the time interval (also in milliseconds) at which the timer will expire repeatedly after the initial expiration. It offers the ability to make the timer recurring at a specific interval.

- **`int threshold`**: This sets a limit on the number of times the timer will call the callback function. It's useful for situations where you don't want a timer to run indefinitely.

- **`void *user_data`**: This is a pointer to user-defined data that will be passed as an argument to the callback function. This offers greater flexibility, as you can pass any type of data to your callback.

- **`bool exponential_backoff`**: This is a flag to indicate whether the timer will use an exponential backoff strategy for the intervals. If set to true, the time interval between subsequent timer expirations will double, which is often useful in network-related tasks for reducing congestion or load on a resource.

### Logic:

- **Initializes a new timer**: It sets up a new timer object and allocates resources for it.

- **Sets the initial time delay and time interval**: These parameters (in milliseconds) allow you to control how and when the timer will expire.

- **Optionally adds exponential backoff**: If required, the timer will use an exponential backoff strategy for its intervals.

- **Takes a user-defined callback function and custom arguments**: The function is flexible, allowing you to define your own logic to execute when the timer expires, along with any custom data that this logic may require.

By wrapping all these features and logic into a single `setup_timer` function, it makes it much easier to work with POSIX timers. It abstracts away the underlying complexity involved in setting up, managing, and tearing down timers, providing a user-friendly API.

## Creating a Timer ⏲️

When you create a timer using the `timer_create` API, it is initially in the Timer Init state.

### Steps:
1. Invoke `timer_create` API.
2. Timer is set in Timer Init State. It means timer has been created but not started.

---

## Timer Operations 🛠️

### Setting the Time
Invoke `timer_set_time` to start the timer.

### Deleting the Timer
You can delete the timer from any state using an API call.

### Pausing and Resuming
You can pause a running timer and later resume it.

---

## Implementation of `setup_timer` API 🏗️

### Overview
The API initializes a "wrapper timer" with various attributes based on the user's inputs.

### Arguments
- Function Pointer: Function to invoke when timer fires.
- Expiration Time Interval: In milliseconds.
- Subsequent Expiration Interval: For 2nd, 3rd, and so on.
- Expiry Count: Number of times timer should expire.
- Application Data: Data to be passed to the timer.
- Exponential Backoff Flag: Is it an exponential backoff timer?

### Process
1. Allocate memory for timer data structure.
2. Initialize all member attributes from parsed arguments.
3. Use sanity checks for mandatory attributes like callback functions.
4. Initialize `sigevent` structure.
5. Create POSIX timer.
6. Initialize TSA attribute for first expiration.

```C
// Function to set up and initialize the timer
Timer_t* setup_timer(
    void (*timer_cb)(Timer_t*, void *),     // User-defined callback function
    unsigned long exp_timer,                // Initial expiration time in milliseconds
    unsigned long sec_exp_timer,            // Subsequent expiration time in milliseconds
    uint32_t threshold,                     // Maximum number of expirations (0 for infinite)
    void *user_arg,                         // User argument for callback
    bool exponential_backoff) {             // Flag for exponential backoff

    // Allocate and initialize Timer_t structure
    Timer_t *timer = calloc(1, sizeof(Timer_t));
    timer->user_arg = user_arg;
    timer->exp_timer = exp_timer;
    timer->sec_exp_timer = sec_exp_timer;
    timer->cb = timer_cb;
    timer->thresdhold = threshold;
    timer_set_state(timer, TIMER_INIT);
    timer->exponential_backoff = exponential_backoff;
    
    // Sanity check to ensure that callback function is provided
    assert(timer->cb);
    
    struct sigevent evp;
    memset(&evp, 0, sizeof(struct sigevent));
    
    evp.sigev_value.sival_ptr = (void *)(timer);
    evp.sigev_notify = SIGEV_THREAD;
    evp.sigev_notify_function = timer_callback_wrapper;
    
    // Create the POSIX timer
    int rc = timer_create (CLOCK_REALTIME, &evp, &timer->posix_timer);
    assert(rc >= 0);
    
    // Fill in the timer specs for initial and subsequent intervals
    timer_fill_itimerspec(&timer->ts.it_value, timer->exp_timer);
    timer_fill_itimerspec(&timer->ts.it_interval, timer->sec_exp_timer);
    
    timer->exp_back_off_time = 0;
    return timer;
}

```
---

## Interview Questions ❓

### Q1: What are the different states a timer can be in?
**A1**: The timer can be in several states like Timer Init, Timer Running, Timer Deleted, Timer Canceled, Timer Paused, and Timer Resumed.

### Q2: How do you transition a timer from Timer Init to Timer Running?
**A2**: You invoke the API `timer_set_time` to transition from Timer Init to Timer Running state.

### Q3: What does the `setup_timer` API do?
**A3**: The `setup_timer` API initializes a wrapper timer by accepting various attributes such as function pointer, expiration time intervals, etc., and returns a pointer to the initialized timer.

### Q4: Is it possible to delete a timer while it's running?
**A4**: Yes, a timer can be deleted from any state, including while it's running.

### Q5: What is the significance of exponential backoff in the context of the timer?
**A5**: Exponential backoff is a strategy to control the rate of some operation to avoid overloading the system. In the context of timers, it helps to define the behavior of repeated timer expirations.
