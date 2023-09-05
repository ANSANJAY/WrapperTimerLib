# Timer State Machine and Implementation Notes 🕐

## Table of Contents 📚
1. [Timer States](#timer-states)
2. [Creating a Timer](#creating-a-timer)
3. [Timer Operations](#timer-operations)
4. [Implementation of `setup_timer` API](#implementation-of-setup_timer-api)

---

## Timer States 🔄

### Overview
The state machine for timers can transition through multiple states based on the API calls. 

### States
1. **Timer Init State**: The initial state of the timer upon creation.
2. **Timer Running State**: Timer transitions to this state when started.
3. **Timer Deleted State**: Timer can be deleted from any state.
4. **Timer Canceled State**: Timer can be canceled, but memory is not freed.
5. **Timer Paused State**: Timer can be paused from the running state.
6. **Timer Resumed State**: Timer can be resumed from the paused state.

### Transitions
- Timer Init State ➡️ Timer Running State: Through API `timer_set_time`.
- Timer Running State ➡️ Timer Deleted State: Can be deleted at any point.
- Timer Running State ➡️ Timer Canceled State: Timer can be canceled.
- Timer Running State ➡️ Timer Paused State: Timer can be paused.
- Timer Paused State ➡️ Timer Resumed State: Timer can be resumed.

---

## Creating a Timer ⏲️

When you create a timer using the `timer_create` API, it is initially in the Timer Init state.

### Steps:
1. Invoke `timer_create` API.
2. Timer is set in Timer Init State. It means timer has been created but not started.

---

## Timer Operations 🛠️

### Setting the Time
Invoke `timer_set_time` to start the timer.

### Deleting the Timer
You can delete the timer from any state using an API call.

### Pausing and Resuming
You can pause a running timer and later resume it.

---

## Implementation of `setup_timer` API 🏗️

### Overview
The API initializes a "wrapper timer" with various attributes based on the user's inputs.

### Arguments
- Function Pointer: Function to invoke when timer fires.
- Expiration Time Interval: In milliseconds.
- Subsequent Expiration Interval: For 2nd, 3rd, and so on.
- Expiry Count: Number of times timer should expire.
- Application Data: Data to be passed to the timer.
- Exponential Backoff Flag: Is it an exponential backoff timer?

### Process
1. Allocate memory for timer data structure.
2. Initialize all member attributes from parsed arguments.
3. Use sanity checks for mandatory attributes like callback functions.
4. Initialize `sigevent` structure.
5. Create POSIX timer.
6. Initialize TSA attribute for first expiration.

---

## Interview Questions ❓

### Q1: What are the different states a timer can be in?
**A1**: The timer can be in several states like Timer Init, Timer Running, Timer Deleted, Timer Canceled, Timer Paused, and Timer Resumed.

### Q2: How do you transition a timer from Timer Init to Timer Running?
**A2**: You invoke the API `timer_set_time` to transition from Timer Init to Timer Running state.

### Q3: What does the `setup_timer` API do?
**A3**: The `setup_timer` API initializes a wrapper timer by accepting various attributes such as function pointer, expiration time intervals, etc., and returns a pointer to the initialized timer.

### Q4: Is it possible to delete a timer while it's running?
**A4**: Yes, a timer can be deleted from any state, including while it's running.

### Q5: What is the significance of exponential backoff in the context of the timer?
**A5**: Exponential backoff is a strategy to control the rate of some operation to avoid overloading the system. In the context of timers, it helps to define the behavior of repeated timer expirations.
