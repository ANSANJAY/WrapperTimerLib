# Timer Library: Episode on Pause and Resume Timer APIs 🛑▶️

## Introduction 🌟
In this episode, we focus on two crucial APIs: 
- `pauseTimer()`
- `resumeTimer()`

---

## API Overview 📝
### 1. API: `pauseTimer()`
- **Purpose**: To pause the running timer.
- **Key attributes involved**: `time_remaining`, `it_value`, and `it_interval`

### 2. API: `resumeTimer()`
- **Purpose**: To resume the paused timer.
- **Key attributes involved**: `time_remaining`

#### Use Case Scenario 🎬
- Timer starts and is supposed to expire after 10 seconds.
- At `T=6`, `pauseTimer()` is invoked; 4 seconds are left.
- Upon invoking `resumeTimer()`, the timer should resume with the remaining 4 seconds.

---

## Implementation Details 🛠️

### 1. Pause Timer API (`pauseTimer`) 🛑
1. **Store Remaining Time**: Store the remaining time (let's say 4 seconds) in the `time_remaining` attribute.
2. **Set Timer Attributes to Zero**: Set `it_value` and `it_interval` to zero.
3. **Invoke System Call**: Call the `timer_settime()` system call to actually pause the timer.
4. **Update Timer State**: Set the state of the timer to `TIMER_PAUSED`.

### 2. Resume Timer API (`resumeTimer`) ▶️
1. **Set Next Expiration Time**: The next expiration time should be set to the `time_remaining` attribute value (in this case, 4 seconds).

---

## Updating Header Files 📑
- Declare the prototypes of `pauseTimer()` and `resumeTimer()` in the corresponding header files.

---

# Interview Questions & Answers 🤔💡

1. **What is the purpose of the `pauseTimer()` API?**
    - *Answer*: The purpose of the `pauseTimer()` API is to pause a running timer and store the remaining time for it to expire in the `time_remaining` attribute.

2. **How does the `resumeTimer()` API work?**
    - *Answer*: The `resumeTimer()` API resumes a paused timer and sets its next expiration time based on the `time_remaining` attribute, which was stored when the timer was paused.

3. **What system call is used to pause the timer in the implementation?**
    - *Answer*: The `timer_settime()` system call is used to pause the timer.

4. **Why is it important to store the remaining time before pausing the timer?**
    - *Answer*: Storing the remaining time is crucial because, upon resumption, the timer should continue with the same remaining time to expire as it had before being paused.

5. **What happens to the timer state when `pauseTimer()` is invoked?**
    - *Answer*: When `pauseTimer()` is invoked, the state of the timer is set to `TIMER_PAUSED`.

6. **What will be the next expiration time for the timer if it was paused with 4 seconds remaining?**
    - *Answer*: If the timer was paused with 4 seconds remaining, the next expiration time will be set to 4 seconds upon resumption.

7. **How are the `it_value` and `it_interval` attributes used in pausing the timer?**
    - *Answer*: In order to pause the timer, both `it_value` and `it_interval` are set to zero.

---

Happy studying! 📘🤓
