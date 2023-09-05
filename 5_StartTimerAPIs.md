# Advanced Timer Control APIs Notes 📚🕰️

## Introduction 🌟
In this session, we're focusing on writing custom APIs for better control over timers and their associated data structures. Specifically, we'll be discussing two new APIs: `resurrect_timer` and `start_timer`.

---

## Custom APIs 💡
### resurrect_timer API 🔄
#### Definition 📝
- **Prototype**: `resurrect_timer(TimerDataStructure *arg)`
- **Functionality**: Acts as a wrapper over `timer_settime()` API.
- **Purpose**: Can start or stop a running timer.

#### Arguments 📌
- `TimerDataStructure *arg`: Pointer to the timer's data structure.

#### Implementation Details 🛠️
- If both the interval and IT value of the timer's data structure are set to zero, invoking `resurrect_timer` will stop the running timer.
- If non-zero values are specified for the interval or IT value, invoking `resurrect_timer` will start the timer.

---

### start_timer API ⏳
#### Definition 📝
- **Prototype**: `start_timer(TimerDataStructure *arg)`
- **Functionality**: A simple wrapper over `resurrect_timer` API.
- **Purpose**: To start a timer that is not currently running.

#### Arguments 📌
- `TimerDataStructure *arg`: Pointer to the timer's data structure.

#### Implementation Details 🛠️
- Should only be invoked when interval and IT value of the timer's data structure are non-zero.
- Sets the state of the timer to "Timer Running".

> **Note 📝**: The declarations for both of these APIs should be included in the corresponding header file.


```C
// Function to restart a paused or stopped timer
void resurrect_timer(Timer_t *timer) {
    int rc = timer_settime(timer->posix_timer, 0, &timer->ts, NULL);
    assert(rc >= 0);
}

// Function to start the timer
void start_timer(Timer_t *timer) {
    // Resurrect (or start) the timer
    resurrect_timer(timer);
    // Set the timer state to running
    timer_set_state(timer, TIMER_RUNNING);
}

```
---

## Common Pitfalls and Notes 🚧
- Don't use `start_timer` to stop a running timer; it's designed only for starting timers.
- `resurrect_timer` plays a dual role; it can either start or stop a timer depending on the interval and IT values.
  
---

# Interview Questions & Answers 🤔💡

1. **What is the purpose of the `resurrect_timer` API?**
    - *Answer*: The `resurrect_timer` API is designed to either start or stop a running timer. It acts as a wrapper over the `timer_settime()` API.

2. **How does the `start_timer` API differ from `resurrect_timer`?**
    - *Answer*: The `start_timer` API is specifically designed to start a timer that is not currently running. It is essentially a wrapper over `resurrect_timer` but is intended for a more specific use-case.

3. **Can `resurrect_timer` start and stop a timer? How?**
    - *Answer*: Yes, `resurrect_timer` can either start or stop a timer. If both the interval and IT value in the timer's data structure are zero, it will stop the timer. If they are non-zero, it will start the timer.

4. **What happens if you call `start_timer` with a timer that has an interval and IT value set to zero?**
    - *Answer*: Since `start_timer` is a wrapper over `resurrect_timer`, and `resurrect_timer` stops the timer if both values are zero, calling `start_timer` with zero values would be incorrect. `start_timer` should only be invoked when you're sure the timer attributes are non-zero.

5. **Where should the declarations for these custom APIs go?**
    - *Answer*: The declarations for both `resurrect_timer` and `start_timer` should be included in the corresponding header file for proper usage and linking.

---

Good luck with your interviews! 🍀👍
