// Include standard input-output header file and custom timer library
#include "timerlib.h"
#include <stdio.h>

static volatile int user_has_input = 0; // Add a flag

static void user_defined_app_cb(Timer_t *timer, void *user_data) {
  if (user_has_input) { // Check the flag before printing
    printf("User data = %s\n", (char *)user_data);
    user_has_input = 0; // Reset the flag
  }
}

// Main function
int main(int argc, char **argv) {

  // Get and format the current time
  time_t rawtime;
  struct tm *timeinfo;
  char buffer[80];

  time(&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", timeinfo);

  // Create a timer using the setup_timer API, setting various timer parameters
  Timer_t *timer =
      setup_timer(user_defined_app_cb, 1000, 1000, 0, buffer, false);

  // Start the created timer
  start_timer(timer);

  // Display options to the user for interacting with the timer
  printf("1. Pause Timer\n");
  printf("2. Resume Timer\n");
  printf("3. Delete timer\n");
  printf("4. Cancel Timer\n");
  printf("5. Get Remaining Time\n");
  printf("6. Print Timer State\n");

  // Declare a variable to capture user choice
  int choice;
  choice = 0;

  // Run an infinite loop to capture user choices for interacting with the timer
  while (1) {
    if (timer == NULL) {
      printf("Timer is deleted. Exiting.\n");
      break;
    }

    scanf("%d", &choice);
    user_has_input = 1; // Set the flag when the user gives input

    switch (choice) {
    case 1:
      pause_timer(timer);
      printf("Timer has been paused.\n");
      break;
    case 2:
      resume_timer(timer);
      printf("Timer has been resumed.\n");
      break;
    case 3:
      printf(
          "Are you sure you want to delete the timer? (1 for Yes, 0 for No): ");
      int confirm;
      scanf("%d", &confirm);
      if (confirm) {
        delete_timer(&timer);
        printf("Timer has been deleted.\n");
      }
      break;
    case 4:
      cancel_timer(timer);
      printf("Timer has been cancelled.\n");
      break;
    case 5:
      printf("Remaining Time = %lu milliseconds\n",
             timer_get_time_remaining_in_mill_sec(timer));
      break;
    case 6:
      print_timer_state(timer);
      break;
    default:
      printf("Invalid choice, please try again.\n");
      break;
    }
    printf("\n"); // Add an extra line for readability
  }

  pause();
  return 0;
}
