# Advanced Timer Control APIs Notes 📚🕰️

## Introduction 🌟
In this session, we're focusing on writing custom APIs for better control over timers and their associated data structures. Specifically, we'll be discussing two new APIs: `resetTimer` and `startTimer`.

---

## Custom APIs 💡
### resetTimer API 🔄
#### Definition 📝
- **Prototype**: `resetTimer(TimerDataStructure *arg)`
- **Functionality**: Acts as a wrapper over `timer_settime()` API.
- **Purpose**: Can start or stop a running timer.

#### Arguments 📌
- `TimerDataStructure *arg`: Pointer to the timer's data structure.

#### Implementation Details 🛠️
- If both the interval and IT value of the timer's data structure are set to zero, invoking `resetTimer` will stop the running timer.
- If non-zero values are specified for the interval or IT value, invoking `resetTimer` will start the timer.

---

### startTimer API ⏳
#### Definition 📝
- **Prototype**: `startTimer(TimerDataStructure *arg)`
- **Functionality**: A simple wrapper over `resetTimer` API.
- **Purpose**: To start a timer that is not currently running.

#### Arguments 📌
- `TimerDataStructure *arg`: Pointer to the timer's data structure.

#### Implementation Details 🛠️
- Should only be invoked when interval and IT value of the timer's data structure are non-zero.
- Sets the state of the timer to "Timer Running".

> **Note 📝**: The declarations for both of these APIs should be included in the corresponding header file.

---

## Common Pitfalls and Notes 🚧
- Don't use `startTimer` to stop a running timer; it's designed only for starting timers.
- `resetTimer` plays a dual role; it can either start or stop a timer depending on the interval and IT values.
  
---

# Interview Questions & Answers 🤔💡

1. **What is the purpose of the `resetTimer` API?**
    - *Answer*: The `resetTimer` API is designed to either start or stop a running timer. It acts as a wrapper over the `timer_settime()` API.

2. **How does the `startTimer` API differ from `resetTimer`?**
    - *Answer*: The `startTimer` API is specifically designed to start a timer that is not currently running. It is essentially a wrapper over `resetTimer` but is intended for a more specific use-case.

3. **Can `resetTimer` start and stop a timer? How?**
    - *Answer*: Yes, `resetTimer` can either start or stop a timer. If both the interval and IT value in the timer's data structure are zero, it will stop the timer. If they are non-zero, it will start the timer.

4. **What happens if you call `startTimer` with a timer that has an interval and IT value set to zero?**
    - *Answer*: Since `startTimer` is a wrapper over `resetTimer`, and `resetTimer` stops the timer if both values are zero, calling `startTimer` with zero values would be incorrect. `startTimer` should only be invoked when you're sure the timer attributes are non-zero.

5. **Where should the declarations for these custom APIs go?**
    - *Answer*: The declarations for both `resetTimer` and `startTimer` should be included in the corresponding header file for proper usage and linking.

---

Good luck with your interviews! 🍀👍
