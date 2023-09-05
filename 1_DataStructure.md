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

### Rapporteur Timer Structure

```c
typedef struct Timer_ {
    timer_t posix_timer;  // POSIX Timer core
    void* user_arguments; // User-defined data
    long expiration_time; // Expiration time in milliseconds
    long secondary_time;  // Secondary expiration time for periodic timers
    int threshold;        // Max invocation limit for periodic timers
    void (*callback)(struct Rapporteur_Timer*, void*); // Callback function
    bool is_exponential;  // Is the timer of exponential backoff nature?
    // Dynamic attributes
    long time_remaining;  // Remaining time when paused
    int invocation_count; // Number of times the timer has fired
    // ... other attributes
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

### Q2: How does the `Rapporteur_Timer` structure encapsulate the POSIX timer?

**A2**: The `Rapporteur_Timer` structure contains a `timer_t posix_timer` member that holds the POSIX timer. All operations performed on our wrapper timer are ultimately relayed to this core POSIX timer.

### Q3: Can you explain the role of dynamic attributes in the `Rapporteur_Timer` structure?

**A3**: Dynamic attributes like `time_remaining` and `invocation_count` are attributes that can change during the timer's lifecycle. For example, `time_remaining` holds the remaining time when the timer is paused, and `invocation_count` keeps track of the number of times the timer has fired.

### Q4: What is the purpose of the `threshold` attribute in the `Rapporteur_Timer` structure?

**A4**: The `threshold` attribute defines the maximum number of times a periodic timer should fire. This allows developers to set a limit on the number of invocations for a timer, instead of letting it run indefinitely.

---

I hope this README serves as a detailed introduction and helps you with your interviews. Feel free to ask for further clarifications or additions.
