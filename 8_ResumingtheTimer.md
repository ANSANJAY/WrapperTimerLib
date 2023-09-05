# Timer Library: Episode on Resume Timer API and State Management 🔄🕒

## Introduction 🌟
In this episode, the spotlight is on the `resumeTimer()` API and how timer state management works, especially transitioning from a paused state to a running state.

---

## API Overview 📝
### 1. API: `resumeTimer()`
- **Purpose**: To resume a paused timer and set its next expiration time.
- **Key Attributes**: `it_value`, `it_interval`, and `time_remaining`

---

## Implementation Details 🛠️

### 1. Resume Timer API (`resumeTimer`) 🔄
1. **Check Timer State**: Verify if the timer is in the paused state.
2. **Repopulate `it_value`**: Populate `it_value` with the `time_remaining` that was stored during the pause.
3. **Populate `it_interval`**: If the timer had a secondary expiration value, it should be filled in `it_interval`.
4. **Reset the Timer**: Make the system call to reset the timer.
5. **Zero-out `time_remaining`**: The attribute `time_remaining` will be set to zero.
6. **Change Timer State**: Set the timer state to `TIMER_RESUMED`.

#### State Transition 🔄
- From `TIMER_RESUMED` to `TIMER_RUNNING`: This will happen when the timer expires for the first time after resuming. 

---

## Updating Header Files 📑
- Declare the prototype of `resumeTimer()` in the corresponding header files.

---

## Additional Notes 📝
- Additional APIs need to be written but are straightforward and have been given as assignments.

---

# Interview Questions & Answers 🤔💡

1. **How does the `resumeTimer()` API work?**
    - *Answer*: The `resumeTimer()` API is designed to resume a timer that is in the paused state. It repopulates `it_value` and `it_interval` attributes based on the time remaining and any secondary expiration value. It then resets the timer, and the timer begins to run again.

2. **What happens to the `time_remaining` attribute when `resumeTimer()` is invoked?**
    - *Answer*: The `time_remaining` attribute is set to zero once the timer is successfully resumed.

3. **What is the initial state of the timer after calling `resumeTimer()`?**
    - *Answer*: The initial state of the timer is set to `TIMER_RESUMED`.

4. **How does the state of the timer transition from `TIMER_RESUMED` to `TIMER_RUNNING`?**
    - *Answer*: The state transitions from `TIMER_RESUMED` to `TIMER_RUNNING` when the timer expires for the first time after it has been resumed.

5. **Why is it important to check the state of the timer before attempting to resume it?**
    - *Answer*: It's crucial to check the state to ensure that the timer is in the paused state. Resuming a timer that is not paused could lead to undefined behavior.

6. **What would happen if the secondary expiration timer value is not zero?**
    - *Answer*: If the secondary expiration timer value is not zero, the timer will continue to expire at intervals defined by this value, and the timer state will transition back to `TIMER_RUNNING`.

7. **What other APIs need to be written following this episode?**
    - *Answer*: The episode suggests that other APIs are straightforward to implement and have been given as assignments.

---

Happy studying! 📘🤓
