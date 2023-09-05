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

### Q2: What is the difference between "Wrapped Timer" and "POSIX Timer"?

**A2**: "Wrapped Timer" is a custom data structure that acts as a wrapper over the native "POSIX Timer" in Linux. While the POSIX Timer performs the actual timing operations, the Wrapped Timer abstracts the details and provides a more user-friendly interface for control.

### Q3: How does the `WrappedTimer` data structure hide the complexity of the POSIX timer?

**A3**: The `WrappedTimer` data structure encapsulates the POSIX timer (`timer_t`) and possibly additional variables or flags that enable more fine-grained control. All the operations you perform using the `WrappedTimer` are internally translated to operations on the POSIX timer, making it easier to manipulate without dealing with the lower-level details.

### Q4: What additional functionalities could you foresee adding to the `WrappedTimer` data structure for more advanced use-cases?

**A4**: For more advanced use-cases, we could add functionalities like batching multiple timers together, adding event hooks for when timers start or stop, or even chaining timers to execute in a specific sequence.

### Q5: Can you explain the significance of `timer_attach` and `timer_detach` functions?

**A5**: The `timer_attach` function is responsible for linking or initializing the `WrappedTimer` with the underlying POSIX timer. On the other hand, `timer_detach` is used for cleaning up or disassociating the `WrappedTimer` from the POSIX timer. These functions are the core of our timer library, allowing for seamless interaction with the POSIX timers.

---

This README serves as a basic guide to understanding the timer library designed for Linux systems. Happy coding! 🌟
