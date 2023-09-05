# TimerLib: A POSIX Timer Library in C

## Overview

TimerLib is a high-level C library for managing POSIX timers in a Linux environment. This library provides a user-friendly API to simplify timer management tasks such as starting, pausing, resuming, and deleting timers. TimerLib offers a clean way to encapsulate complex lower-level timer functionalities.

## Features

### Simple API
A set of easy-to-use functions for managing timers.

### State Management
Keep track of your timer's current state (`INIT`, `RUNNING`, `PAUSED`, etc.).

### Callback Support
Set up callback functions to be triggered when a timer expires.

### User-Defined Arguments
Pass additional custom arguments to your callback function.

### Pause and Resume
Pause your timer and resume it later right from where you left off.

### Time Remaining
Check how much time is left on your timer.

### Exponential Backoff (Optional)
You can configure timers to use an exponential backoff strategy.

---

## Requirements

- Linux Operating System
- GCC Compiler

---

## Installation and Compilation

### Using Makefile

To compile the TimerLib library along with your project, run:

```bash
make
```

This will compile the source files and produce an executable.

---

## Detailed Function Descriptions and Logic

### setup_timer
```c
Timer_t *setup_timer(
    TimerCallback callback, 
    uint32_t initial_time, 
    uint32_t interval_time, 
    int threshold, 
    void *user_data, 
    bool exponential_backoff
);
```

#### Logic

- Initializes a new timer.
- Sets the initial time delay and time interval for the timer.
- Optionally configures the timer for exponential backoff.
- Takes in a user-defined callback function and argument.


Certainly, here's a more detailed explanation of the logic behind the `start_timer`, `pause_timer`, `resume_timer`, `delete_timer`, `cancel_timer`, and `get_time_remaining` functions. The focus will be on what each function is doing internally.

---

## start_timer

```c
void start_timer(Timer_t *timer);
```

### Logic

1. **Check Validity**: Verifies that the timer object is valid and in a state where it can be started, usually `INIT`.
  
2. **Set State**: Changes the timer's internal state to `RUNNING`.

3. **Initialize POSIX Timer**: Internally calls POSIX timer initialization functions to set up the timer with the parameters initially provided during the setup. 

4. **Start the Timer**: Uses the POSIX `timer_settime` function to activate the timer, which will invoke the callback function when the timer expires.

---

## pause_timer

```c
void pause_timer(Timer_t *timer);
```

### Logic

1. **Check Validity**: First, checks that the timer object is valid and that its current state is `RUNNING`.

2. **Set State**: Changes the internal state of the timer to `PAUSED`.

3. **Stop the Timer**: Calls lower-level POSIX functions to halt the timer but retains the timer's state information for later resumption.

---

## resume_timer

```c
void resume_timer(Timer_t *timer);
```

### Logic

1. **Check Validity**: Ensures the timer object is valid and its current state is `PAUSED`.

2. **Set State**: Changes the internal state back to `RUNNING`.

3. **Restart the Timer**: Uses the saved state information to resume the timer exactly where it was paused. Internally, this typically involves calling `timer_settime` with the remaining time.

---

## delete_timer

```c
void delete_timer(Timer_t **timer);
```

### Logic

1. **Check Validity**: Checks that the timer object is valid.

2. **Set State**: Changes the internal state of the timer to `DELETED`.

3. **Deallocate Resources**: Frees up any allocated resources related to the timer, such as dynamic memory and system resources.

4. **NULL the Pointer**: Sets the pointer to `NULL` to avoid any accidental usage after deletion.

---

## cancel_timer

```c
void cancel_timer(Timer_t *timer);
```

### Logic

1. **Check Validity**: Makes sure the timer object is valid and in a `RUNNING` or `PAUSED` state.

2. **Set State**: Changes the internal state to `CANCELLED`.

3. **Stop Timer**: Stops the timer immediately using lower-level functions but does not deallocate the resources.

---

## get_time_remaining

```c
uint32_t get_time_remaining(Timer_t *timer);
```

### Logic

1. **Check Validity**: Checks if the timer object is valid and in a `RUNNING` or `PAUSED` state.

2. **Fetch Remaining Time**: Internally calls POSIX `timer_gettime` to get the remaining time for the timer.

3. **Return Value**: Converts the time structure to milliseconds (or any desired unit) and returns this value to the caller.

---

I hope this adds clarity to what each function in the TimerLib is doing. Feel free to include these explanations in the README.md to help users better understand the inner workings of the library.
## Example Usage

Please refer to the `timerlib_test.c` file for a full example of how to use each TimerLib function.

---

## Contributing

Contributions in the form of issues, pull requests, or any feedback are welcome.

---

## License

This project is licensed under the MIT License. See `LICENSE.md` for details.

---

## Author

TimerLib is developed and maintained by Anamika.

Happy Coding!