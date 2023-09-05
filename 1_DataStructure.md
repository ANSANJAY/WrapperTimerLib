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

#### Attributes Explanation :clipboard:

- `posix_timer`: POSIX timer at the core
- `user_arguments`: Arguments to pass to the callback function
- `expiration_time` & `secondary_time`: Expiration time in milliseconds
- `threshold`: Maximum number of invocations
- `callback`: Function to call upon timer expiration
- `is_exponential`: Whether the timer is of exponential backoff nature
- `time_remaining`: Time remaining when the timer is paused
- `invocation_count`: Number of times the timer has invoked the callback function

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


