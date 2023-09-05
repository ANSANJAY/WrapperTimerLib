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

---

That wraps up the detailed notes. Good luck with your interviews! 🍀👍
