# Timer Test Program & Extended Functionality 📚🔍

## Introduction 🌟
In this session, we learn about a test program for testing our custom wrapper timer. We are using this program to extend the functionalities of our existing timer library.

---

## Test Program Structure 🏗️
### Initial Setup 🛠️
- **File Name**: `timely_test.c`
- **Purpose**: To test the custom timer API functionality.
- **Functionality**: 
  - Define random user data.
  - Create a wrapper timer using `setupTimer` API.
  - Pass user-defined callback and other timer attributes like expiration time, secondary expiration time, and threshold.

#### Initialization Steps 🚀
1. Pass user-defined application callback to the timer.
2. Set expiration time to 1000ms.
3. Set secondary expiration time to 1000ms.
4. Set the number of thresholds to 0 (Indefinite expiration).
5. Pass user data.
6. Set up exponential backoff (To be implemented).

#### Starting the Timer 🕐
- Use the `startTimer` API to start the timer. 
- Expectation: Timer fires every 1000ms and invokes the user-defined callback.

---

## Extended Functionality 🎯
### Menu-Driven Test Program 📋
- Enhance the test program to provide a user menu for various functionalities like pausing, resuming, restarting, etc.

#### Menu Options 📌
1. Pause Timer
2. Resume Timer
3. Restart Timer
4. Reschedule Timer
5. Delete Timer
6. Cancel Timer
7. Print Time
8. Get Remaining Time in ms

#### Implementation Roadmap 🗺️
- Use a switch statement for user choices.
- Implement each function one-by-one and test it against this test program.

---

## Upcoming Goals 🥅
- Implement and test each menu function in the upcoming lectures.

---

# Interview Questions & Answers 🤔💡

1. **What is the purpose of the `timely_test.c` program?**
   - *Answer*: The `timely_test.c` program is designed to test the functionalities of our custom timer APIs. It is set up to simulate various use-cases and evaluate the performance and reliability of the timer library.

2. **How does the test program initialize and start the timer?**
   - *Answer*: The test program initializes the timer by passing in user-defined data, an application callback, and various timer attributes such as expiration time and secondary expiration time. It then uses the `startTimer` API to kickstart the timer.

3. **Describe the extended functionality being added to the test program.**
   - *Answer*: The extended functionality includes a menu-driven interface that allows the user to interact with the timer by choosing various operations like pausing, resuming, restarting, and so on.

4. **What is the significance of setting the number of thresholds to 0 in the test program?**
   - *Answer*: Setting the number of thresholds to 0 means that the timer will expire indefinitely, allowing us to test long-running scenarios.

5. **How is the test program planning to validate each of the new functionalities?**
   - *Answer*: Each new functionality will be implemented one-by-one, and as they are completed, they will be uncommented in the test program to be tested individually for correctness.

6. **What does the exponential backoff parameter indicate in the test program?**
   - *Answer*: The exponential backoff parameter is a feature to be implemented. It will likely serve to adjust the time intervals between retries dynamically, making the system more resilient to failures.

---

Happy studying! 📘🤓
