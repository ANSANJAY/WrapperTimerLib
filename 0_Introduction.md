# WrapperTimerLib
This repository provides an easy-to-use, extensible wrapper for implementing timers. It aims to simplify timer operations, offering a more intuitive API over native mechanisms. The project includes documentation, example usages, and a test suite to help you quickly integrate this solution into your own applications

# Timer Library Design in Linux - README.md 📚

## Introduction 📖

In this discourse, we delve into the realm of designing and implementing a timer library in a Linux environment. The primary objective of developing this library is to simplify the timer manipulation process and offer fine-grained control over timer operations such as pause, cancel, resume, delete, restart, and reschedule. 

By constructing this library, we abstract away the underlying complexities related to the Linux kernel, like signal handling or `sigevent` structures, and provide a straightforward API for timer manipulation. This approach also opens the doors for implementing more complex timers in the future, like "Wheel Timers".

## Key Concepts 🗝️

- **Wrapped Timer**: A custom data structure that encapsulates the POSIX timer. This is our interface to the underlying Linux timer mechanism.
  
- **POSIX Timer**: The built-in Linux timer we are wrapping. Whenever "POSIX timer" is mentioned, it refers to the Linux timer we are familiar with.
  
- **Timer Library**: Consists of utility functions like `timer_attach` and `timer_detach` that constitute the complete library.

## Data Structures 🏗️

### Wrapped Timer

The `WrappedTimer` (notice the capital 'T') is our custom data structure which acts as a wrapper over the POSIX timer. One of the main attributes of `WrappedTimer` is the POSIX timer, denoted as `timer_t`.

```c
typedef struct {
    Timer_t posix_timer; // POSIX Timer
    // Additional variables for more control
} Timer_t t;
```

## Functionality 🛠️

- **timer_attach**: This function will attach a `WrappedTimer` instance to the underlying POSIX timer.
  
- **timer_detach**: This function will detach the `WrappedTimer` instance from the underlying POSIX timer.

## Expectations 🎯

Our `WrappedTimer` data structure should allow us to hide the complexity of the underlying POSIX timer and provide us with a simplified interface for timer operations.

---

## Interview Questions and Answers 📝

### Q1: Can you explain the purpose of designing a timer library?

**A1**: The purpose of designing a timer library is to simplify the interface for timer manipulations and operations, abstracting away the complexity associated with native Linux timer systems. It provides a unified API for operations like pause, resume, cancel, and more, making it easier for developers to manage timers.

 The TimerLib library abstracts away the complexities of the underlying POSIX timer mechanisms by providing a high-level, user-friendly API. Here's how it makes it easier:

1. **Unified Interface**: Instead of using multiple POSIX functions and dealing with complex data structures like `itimerspec` or `sigevent`, you can use simple function calls like `start_timer()` or `pause_timer()`.

2. **State Management**: The library internally manages the state of each timer (`INIT`, `RUNNING`, `PAUSED`, etc.), so the developer doesn't have to manually track the state. This reduces the possibility of errors, like attempting to resume a timer that's not paused.

3. **Callback Mechanism**: You can easily set up a callback function to be triggered when a timer expires, allowing for better event-driven programming. This saves you from the hassle of constantly polling to check the timer's status.

4. **User-Defined Arguments**: The library allows you to pass custom arguments to your callback function, providing more context when the timer expires. This feature avoids the need for global variables, making your code cleaner and more modular.

5. **Pause and Resume**: Unlike basic POSIX timers, which would require a complex setup to pause and resume, TimerLib simplifies this with dedicated `pause_timer()` and `resume_timer()` functions. These functions automatically handle the internal state and remaining time, providing an intuitive way to pause and resume timers.

6. **Time Remaining**: The library provides a simple function to check how much time is left on your timer (`get_time_remaining()`), abstracting away the need to directly interact with POSIX functions for this query.

7. **Exponential Backoff**: An optional feature where the library handles the complexity of implementing exponential backoff strategies, useful in retry mechanisms or network calls. 

By wrapping all these functionalities into a simple API, TimerLib allows developers to focus on the application logic rather than the intricacies of timer management.

### Q2: What is the difference between "Wrapped Timer" and "POSIX Timer"?

**A2**: "Wrapped Timer" is a custom data structure that acts as a wrapper over the native "POSIX Timer" in Linux. While the POSIX Timer performs the actual timing operations, the Wrapped Timer abstracts the details and provides a more user-friendly interface for control.

### Q3: How does the `WrappedTimer` data structure hide the complexity of the POSIX timer?

**A3**: The `WrappedTimer` data structure encapsulates the POSIX timer (`timer_t`) and possibly additional variables or flags that enable more fine-grained control. All the operations you perform using the `WrappedTimer` are internally translated to operations on the POSIX timer, making it easier to manipulate without dealing with the lower-level details.

### Q4: What additional functionalities could you foresee adding to the `WrappedTimer` data structure for more advanced use-cases?

**A4**: For more advanced use-cases, we could add functionalities like batching multiple timers together, adding event hooks for when timers start or stop, or even chaining timers to execute in a specific sequence.

### Q5: Can you explain the significance of `timer_attach` and `timer_detach` functions?

**A5**: The `timer_attach` function is responsible for linking or initializing the `WrappedTimer` with the underlying POSIX timer. On the other hand, `timer_detach` is used for cleaning up or disassociating the `WrappedTimer` from the POSIX timer. These functions are the core of our timer library, allowing for seamless interaction with the POSIX timers.


1. **Can you briefly explain what the TimerLib library does?**  
   TimerLib is a C library that simplifies the management of POSIX timers on Linux systems. It provides an easy-to-use API for creating, starting, pausing, resuming, and deleting timers. It also supports state management, callback functions, and optional exponential backoff.

### setup_timer.c

1. **Could you explain the purpose of the `setup_timer` function and how it's different from the `start_timer` function?**  
   The `setup_timer` function initializes a new timer, sets its parameters, and optionally configures it for exponential backoff. In contrast, `start_timer` takes an already-initialized timer and starts it.

2. **How does the `setup_timer` function handle optional parameters, such as `exponential_backoff`?**  
   The `exponential_backoff` parameter is a boolean flag. If set to true, the timer will use an exponential backoff strategy for retrying.

3. **What happens if the user passes in an invalid initial time or interval time?**  
   Currently, the library doesn't have built-in validation for these parameters. It assumes the caller will provide valid inputs. If invalid times are provided, the behavior is undefined.

### start_timer.c

1. **What are some scenarios where the `start_timer` function might fail, and how is this handled in the code?**  
   The function could fail if the timer object is invalid or in a state that cannot be started. We handle this by first checking the timer's state.

2. **Could you walk me through the steps taken by the `start_timer` function to initialize and start a POSIX timer?**  
   It first validates the timer object and its state. Then, it changes the internal state to `RUNNING` and calls the POSIX `timer_settime` function to start the timer.

3. **Can you elaborate on the callback function being used? What would happen if the callback function takes a long time to execute?**  
   The callback function is user-defined and passed as a parameter during the setup. If it takes a long time to execute, it could delay the triggering of subsequent timers.

### pause_timer.c

1. **How does the `pause_timer` function update the internal state of a timer?**  
   It changes the timer's internal state to `PAUSED` and stops the underlying POSIX timer.

2. **What POSIX calls are used to actually pause the timer?**  
   We internally use `timer_settime` with a time of zero to stop the timer.

3. **Is it possible to pause a timer that has already been paused? How is this scenario handled?**  
   The function first checks the timer's state. If it is already paused, the function will return without doing anything.

### General Logic and Error Handling

1. **Can you explain how the library handles invalid or `NULL` timer objects?**  
   Each function begins by validating that the timer object is not `NULL` and is in a valid state for the requested operation.

2. **How does your library handle memory allocation and deallocation for timer objects?**  
   Memory is dynamically allocated during the `setup_timer` function and deallocated in the `delete_timer` function.

3. **What would happen if someone tries to delete a timer that has already been deleted?**  
   The `delete_timer` function sets the pointer to `NULL` after deletion. If someone tries to delete it again, the function will first check for `NULL` and will safely return if it is.

### Advanced Questions

1. **How would you extend this library to handle multiple types of timers?**  
   I would add a new parameter or flag to specify the timer type during setup and modify the internal logic to accommodate the different types.

2. **Can you talk about any thread-safety considerations you've made?**  
   Currently, the library is not thread-safe. If it were to be made thread-safe, I would use mutex locks to protect shared data.

3. **If you had to optimize this library for a high-frequency, low-latency environment, what changes would you consider?**  
   I would consider removing any dynamic memory allocations to avoid latency and would look into more efficient data structures for storing timers.

I hope these answers provide a comprehensive understanding of the TimerLib project. Feel free to ask for more details on any point.
---

This README serves as a basic guide to understanding the timer library designed for Linux systems. Happy coding! 🌟
