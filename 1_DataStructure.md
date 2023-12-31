# Timer Library Design :alarm_clock:

## Introduction :book:

In this section, we discuss the design and implementation of a custom timer library that offers an enhanced level of control over timers. This library wraps around the POSIX timer and provides functionalities such as pause, cancel, resume, delete, restart, and reschedule. It serves as an abstraction layer that hides the complexities of underlying data structures like POSIX timers. 

## Objectives :dart:

- Create a simplified interface for timers
- Implement control functionalities (pause, resume, delete, etc.)
- Open the door for implementing more complex timers like "Will Timer"

## Key Terms :bulb:

- **Wrapper Timer**: Custom data structure that represents our own timer
- **POSIX Timer**: The underlying Linux timer

## Data Structure Definition :page_facing_up:

### Wrapped Timer Structure

```C
	/* Timer config */
     typedef struct Timer_{

    timer_t posix_timer; // as a wrapper on POSIX timer_t structure
    void *user_arg; // for user arg for the call back function
	unsigned long exp_timer;		/* in milli-sec */
	unsigned long sec_exp_timer;	/* in milli-sec */
	uint32_t thresdhold;			/* No of times to invoke the timer callback */
	void (*cb)(struct Timer_ *, void *); /* Timer Callback  */
	bool exponential_backoff; 

	/* place holder value to store
 	 * dynamic attributes of timer */
	unsigned long time_remaining;	/* Time left for paused timer for next expiration */
	uint32_t invocation_counter; 
	struct itimerspec ts;
	unsigned long exp_back_off_time;
	TIMER_STATE_T timer_state;
} Timer_t;
```

## Timer Data Structure: `WrappedTimer` 🕒

### Introduction 🎯
- `WrappedTimer` is a wrapper around the POSIX timer data structure.
- Aimed at implementing timers in a comprehensive manner.

### Member Attributes 🧱

#### Static Attributes 👇
- **POSIX Timer**: The core time-tracking unit in the `WrappedTimer`.
- **Callback Function**: Invoked when the timer fires.
- **User Arguments**: Custom arguments that get passed to the callback function.
- **Expiration Time Interval**: Milliseconds until the timer first expires.
- **Secondary Expiration Time**: Relevant only for periodic timers. Milliseconds for subsequent expirations.
- **Threshold**: Maximum number of times the timer will fire.
- **Is Exponential Backoff**: A boolean flag to track if the timer employs exponential backoff.

#### Dynamic Attributes 🔄
- **Time Remaining**: Time left for the timer to expire when paused.
- **Invocation Counter**: How many times the timer has fired.
- **Current Expiration Time**: Expiration time passed to `setTime`.
- **Exponential Backoff Time**: If the timer is of exponential backoff nature.
- **Timer State**: The current state of the timer (Running, Paused, etc.).

---


---
The Timer_t structure we've designed serves as a wrapper around the basic POSIX `timer_t` structure. It enriches the timer functionality by adding several layers of abstraction and utility. Here's how it differs from a plain POSIX `timer_t`:

### Added Features in Wrapped Timer (`Timer_t`):

1. **User Arguments (`user_arg`)**: Provides the ability to pass custom arguments to the timer's callback function. This is typically not straightforward in POSIX.

2. **Initial and Subsequent Expiration (`exp_timer` and `sec_exp_timer`)**: Offers fine-grained control over the first and subsequent timer expirations, making it easier to create recurring timers with different initial and subsequent delays.

3. **Threshold (`thresdhold`)**: Allows you to set a limit on how many times the timer callback will be invoked. POSIX timers don't inherently support this feature.

4. **Callback (`cb`)**: Provides a clean interface for setting a callback function to be invoked when the timer expires. While POSIX allows this, it usually requires a more complex setup involving signal handling.

5. **Exponential Backoff (`exponential_backoff`)**: Adds support for exponential backoff timers, which is not a built-in feature in POSIX timers.

6. **Time Remaining (`time_remaining`)**: This field keeps track of the remaining time when the timer is paused, simplifying the task of resuming the timer later.

7. **Invocation Counter (`invocation_counter`)**: A counter to keep track of how many times the timer has been invoked, which can be useful for debugging or for actions that should occur only after a certain number of invocations.

8. **Timer State (`timer_state`)**: Manages the state of the timer (`INIT`, `RUNNING`, `PAUSED`, etc.), which you would otherwise need to handle manually when using POSIX timers.

### Common Features:

1. **POSIX Timer (`posix_timer`)**: The underlying POSIX timer object is still part of the structure, allowing for direct interaction with the operating system's timing mechanisms.

2. **Interval Timer Specification (`ts`)**: This POSIX `itimerspec` structure allows you to set the initial delay and interval for timer expirations, just like you would with a plain POSIX timer.

In summary, your wrapped `Timer_t` structure extends the basic functionality provided by POSIX `timer_t`, making it more flexible, easier to manage, and better suited for a wider variety of tasks.
---
## Interview Questions :question:

### Q1: What is the motivation behind designing a custom timer library?

**A1**: The custom timer library aims to provide a simplified interface for handling timers, abstracting away the complexities of POSIX timers. It also offers extended functionalities like pausing, resuming, and cancelling timers, which are not straightforward with raw POSIX timers.

### Q2: How does the `Wrapped_Timer` structure encapsulate the POSIX timer?

**A2**: The `Wrapped_Timer` structure contains a `timer_t posix_timer` member that holds the POSIX timer. All operations performed on our wrapper timer are ultimately relayed to this core POSIX timer.

### Q3: Can you explain the role of dynamic attributes in the `Wrapped_Timer` structure?

**A3**: Dynamic attributes like `time_remaining` and `invocation_count` are attributes that can change during the timer's lifecycle. For example, `time_remaining` holds the remaining time when the timer is paused, and `invocation_count` keeps track of the number of times the timer has fired.

### Q4: What is the purpose of the `threshold` attribute in the `Wrapped_Timer` structure?

**A4**: The `threshold` attribute defines the maximum number of times a periodic timer should fire. This allows developers to set a limit on the number of invocations for a timer, instead of letting it run indefinitely.

---
### Questions and Answers for Timer Wrapper Program 🤓

---

#### Question 1: What is the purpose of the `TIMER_STATE_T` enumeration in the program?

**Answer:**
The `TIMER_STATE_T` enumeration is used to represent the different states a timer can be in. These states include:

- `TIMER_INIT`: Initial state of the timer.
- `TIMER_DELETED`: State representing that the timer has been deleted.
- `TIMER_PAUSED`: State indicating that the timer is paused.
- `TIMER_CANCELLED`: State showing that the timer has been cancelled.
- `TIMER_RESUMED`: State indicating that the timer has been resumed.
- `TIMER_RUNNING`: State showing that the timer is currently running.

This helps in better management and understanding of the timer's current status.

---

#### Question 2: Can you explain the role of the `setup_timer` function?

**Answer:**
The `setup_timer` function serves as the initializer for the `Timer_t` structure. It takes the following arguments:

- `timer_cb`: The callback function that will be invoked when the timer expires.
- `exp_timer`: The time duration in milliseconds after which the timer will first expire.
- `sec_exp_timer`: The time duration in milliseconds for subsequent expirations.
- `threshold`: The maximum number of times the timer should expire. A value of 0 means infinite expirations.
- `user_arg`: An argument that will be passed to the callback function.
- `exponential_backoff`: A boolean flag to indicate whether the timer should use exponential backoff.

The function returns a pointer to the initialized `Timer_t` structure.

---

#### Question 3: How is the state of a timer accessed or modified?

**Answer:**
The state of the timer is accessed or modified using two inline functions:

- `timer_get_current_state(Timer_t *timer)`: This function returns the current state of the timer. It takes a pointer to the `Timer_t` structure as an argument.
  
- `timer_set_state(Timer_t *timer, TIMER_STATE_T timer_state)`: This function sets the state of the timer. It takes a pointer to the `Timer_t` structure and the new state as arguments.

These functions encapsulate the state management logic, providing an interface to easily get or set the timer's state.

---

#### Question 4: What does the `resurrect_timer` function do?

**Answer:**
The `resurrect_timer` function is designed to resume a paused or cancelled timer. The specific implementation details are not provided in the header file, but based on its name and common usage, it is reasonable to assume that it changes the state of the timer to `TIMER_RUNNING` or `TIMER_RESUMED` and resets any necessary timers or counters to ensure the timer starts running again.

---

#### Question 5: How does the program handle time durations and expirations?

**Answer:**
The program handles time durations and expirations using the following fields in the `Timer_t` structure:

- `exp_timer`: This field holds the time in milliseconds after which the timer will first expire.
  
- `sec_exp_timer`: This field holds the time in milliseconds for subsequent timer expirations.
  
- `time_remaining`: This field holds the time left for the next expiration when the timer is paused.

These fields allow for flexible configuration of how the timer expires, whether it's just once, multiple times, or after specific intervals.

---


