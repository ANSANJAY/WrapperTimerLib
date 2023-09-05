// Include standard input-output header file and custom timer library
#include <stdio.h>
#include "timerlib.h"

// Declare a user-defined callback function for the timer
static void user_defined_app_cb(Timer_t *timer, void *user_data){
    // Print the user data provided when the timer fires
    printf("User data = %s\n", (char *)user_data);
}

// Main function
int main(int argc, char **argv){

    // Initialize the user-defined name
    char *name = "Anamika";

    // Create a timer using the setup_timer API, setting various timer parameters
    Timer_t *timer = setup_timer(user_defined_app_cb, 1000 , 1000, 0, name, false);

    // Start the created timer
    start_timer(timer);

    // Display options to the user for interacting with the timer
    printf("1. Pause Timer\n");
    printf("2. Resume Timer\n");
    printf("3. Restart timer\n");
    printf("4. Reschedule timer\n");
    printf("5. Delete timer\n");
    printf("6. Cancel Timer\n");
    printf("7. Get Remaining Time\n");
    printf("8. Print Timer State\n");

    // Declare a variable to capture user choice
    int choice;
    choice = 0;

    // Run an infinite loop to capture user choices for interacting with the timer
    while(1){
        scanf("%d", &choice);

        // Use a switch-case to perform actions based on user input
        switch(choice){

            case 1:
                // Placeholder for pausing the timer
                // pause_timer(timer);
                break;
            case 2:
                // Placeholder for resuming the timer
                // resume_timer(timer);
                break;
            case 3:
                // Placeholder for restarting the timer
                // restart_timer(timer);
                break;
            case 4:
                // Placeholder for rescheduling the timer
                // reschedule_timer(timer, timer->exp_timer, timer->sec_exp_timer);
                break;
            case 5:
                // Placeholder for deleting the timer
                // delete_timer(timer);
                break;
            case 6:
                // Placeholder for canceling the timer
                // cancel_timer(timer);
                break;
            case 7:
                // Placeholder for printing the remaining time
                // printf("Rem Time = %lu\n", timer_get_time_remaining_in_mill_sec(timer));
                break;
            case 8:
                // Placeholder for printing the timer state
                // print_timer(timer);
                break;
            default:
                // Default case, do nothing
                ;
        }
    }
    // Pause to keep the application running until manually terminated
    pause();
    return 0;
}
