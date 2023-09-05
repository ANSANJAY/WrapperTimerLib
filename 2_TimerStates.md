
# Detailed Notes on Timer Data Structure and Timer States 📝

## Timer Data Structure: `WrappedTimer` 🕒

### Introduction 🎯
- `WrappedTimer` is a wrapper around the POSIX timer data structure.
- Aimed at implementing timers in a comprehensive manner.

### Member Attributes 🧱

#### Static Attributes 👇
- **POSIX Timer**: The core time-tracking unit in the `WrappedTimer`.
- **Callback Function**: Invoked when the timer fires.
- **User Arguments**: Custom arguments that get passed to the callback function.
- **Expiration Time Interval**: Milliseconds until the timer first expires.
- **Secondary Expiration Time**: Relevant only for periodic timers. Milliseconds for subsequent expirations.
- **Threshold**: Maximum number of times the timer will fire.
- **Is Exponential Backoff**: A boolean flag to track if the timer employs exponential backoff.

#### Dynamic Attributes 🔄
- **Time Remaining**: Time left for the timer to expire when paused.
- **Invocation Counter**: How many times the timer has fired.
- **Current Expiration Time**: Expiration time passed to `setTime`.
- **Exponential Backoff Time**: If the timer is of exponential backoff nature.
- **Timer State**: The current state of the timer (Running, Paused, etc.).

---

## Timer States 🔄

### States Enumerated 📋
1. **Timer Init State**: Timer has been created but not running.
2. **Timer Running State**: Timer is active and counting down.
3. **Timer Cancel State**: Timer has been canceled but not deleted.
4. **Timer Pause State**: Timer is paused.
5. **Timer Resume State**: Timer resumes after a pause.
6. **Timer Delete State**: Timer is deleted and cannot be reused.

### State Transitions 🔄

- **From Timer Init State**
  - Can move to Timer Running State or Timer Delete State.
  
- **From Timer Running State**
  - Can move to Timer Cancel State, Timer Pause State, or Timer Delete State.
  
- **From Timer Cancel State**
  - Can go back to Timer Running State or move to Timer Delete State.
  
- **From Timer Pause State**
  - Can only move to Timer Resume State or Timer Delete State.
  
- **From Timer Resume State**
  - Goes back to Timer Running State but can also move to Timer Delete State.

---

# Interview Questions and Answers ❓💡

## Q1: Explain the purpose of the `WrappedTimer` data structure. 
### A1: 
The `WrappedTimer` is a wrapper around the POSIX timer, designed to provide an interface for creating and managing timers. It includes both static and dynamic attributes, making it a flexible solution for various timer requirements.

## Q2: Describe the difference between static and dynamic attributes in the `WrappedTimer`.
### A2: 
Static attributes, such as the POSIX timer, user arguments, and expiration times, are generally set once and remain unchanged. Dynamic attributes, like the time remaining and invocation counter, change during the timer's lifecycle.

## Q3: What are the possible states a timer can be in?
### A3: 
The possible states include Timer Init, Timer Running, Timer Cancel, Timer Pause, Timer Resume, and Timer Delete. Each state Wrappedesents a specific phase in the timer's lifecycle.

## Q4: How does the Timer state machine work? 
### A4: 
The Timer can transition between various states based on API calls and user interactions. For example, a timer can move from an Init state to a Running state when `setTime` is invoked. It can also transition to a Deleted state from any other state, rendering it unusable thereafter.

## Q5: Explain the significance of the Threshold attribute in `WrappedTimer`.
### A5: 
The Threshold attribute sets the maximum number of times a periodic timer can fire. It provides control over the timer's behavior, ensuring it doesn't run indefinitely. 

---

