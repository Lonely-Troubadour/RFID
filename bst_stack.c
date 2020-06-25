/**
 * BST based anti-collosion algorithm implemented by Stack
 * author: Yongjian Hu
 * class: 2017215120
 * stdNo. 2017213161
 * LICENSE: GPLv3
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Define some global constants
#define MAX_STACK_SIZE 200 // Maximum stack size
#define MAX_ID_SIZE 200 // Maximum ID size
#define MAX_ID_LENGTH 100 // Maximum ID length

// Declaration of functions
int match(char * pattern, char * dat);
void print_result(int step, char * s, char * response);
int read(char ** dat);
void welcome();

int main(int argc, char const * argv[]) {
    /**
     * Status variable.
     *  0 - idle
     * -1 - conflict
     *  1 - match
     */
    int status = 0;
    int n = 0;
    int len = 0;
    int step = 0;

    char ** dat;
    char * stack;
    char * ptr;

    // Initialize data set array.
    dat = (char ** ) malloc(sizeof(char * ) * MAX_ID_SIZE);
    for (int i = 0; i < MAX_ID_SIZE; i++) {
        *(dat + i) = (char * ) malloc(sizeof(char) * MAX_ID_LENGTH);
    }
    
    // Print welcome message
    welcome();

    // Read data
    n = read(dat);
    len = n;
    // Allocate spaces for stack
    stack = (char * ) malloc(sizeof(char) * MAX_STACK_SIZE);
    ptr = stack;
    * ptr = '0';
    
    // Start loop execution
    while (1) {
        printf("-----------------------------------------\n");
        printf("Step No.---Query------Response\n");
        // Start the BST based 
        while (n != 0) {
            char * idx_dat = NULL;
            // Compare string in the stack to IDs in data set.
            // Generate status based on comparison result
            for (int i = 0; i < len; i++) {
                int result = match(stack, *(dat + i));
                if (result) {
                    if (status) {
                        status = -1;
                        break;
                    } else {
                        status = result;
                        idx_dat = * (dat + i);
                    }
                }
            }
            
            // Decite which response to generate based on status
            char * response;
            response = (char * ) malloc(sizeof(char) * 20);
            if (status == 1) {
                strcpy(response, idx_dat);
            } else if (status == -1) {
                strcpy(response, "Collision");
            } else {
                strcpy(response, "Idle");
            }

            // Print the current result
            print_result(step, stack, response);

            // Decide next action.based on status.
            switch (status) {
                // if idle, add 1 to stack value
                case 0:
                    while ( * ptr == '1') {
                        * ptr = 0; // overflow, pop from stack
                        ptr--;
                    }
                    * ptr = '1';
                    break;
                // If conflict, push 0 to stack
                case -1:
                    ptr++;
                    * ptr = '0'; // push
                    break;
                // If matched, add 1 to stack
                case 1:
                    n -= 1; // Counter decreased
                    while ( * ptr == '1') { 
                        * ptr = 0; // overflow, pop from stack
                        ptr--;
                    }
                    * ptr = '1'; 
                    break;

                default:
                    break;
            }

            // Reset status. Step += 1
            status = 0;
            step++;
        }
        printf("-----------------------------------------\n"); 
        // Reset stack and data set
        memset(stack, '\0', MAX_STACK_SIZE);
        // Read next data set
        n = read(dat);
        // If size is -1, quit
        if (n == -1) {
            printf("Good Bye!\n");
            break;
        }
        // Reset size, step, and pointers
        len = n;
        ptr = stack;
        step = 0;
        * ptr = '0';
    }


    return 0;
}

/**
 * Compare data input to pattern, character by character
 */
int match(char * pattern, char * dat) {
    while ( * dat != '\0' && * pattern != '\0') {
        // printf("%c %c\n", *pattern, *dat);
        if ( * pattern != * dat)
            return 0;
        pattern++;
        dat++;
    }
    return 1;
}

/** Print result */
void print_result(int step, char * s, char * response) {
    printf("%-10d %-10s %-10s \n", step, s, response);
}

/** Welcome message */
void welcome() {
    printf("----------------Welcome------------------\n");
    printf("BST based anti-collision algorithm.\n");
    printf("The algorithm is implemented using stack.\n");
    printf("Press Ctrl-C or input -1 to quit program.\n");
    printf("Author: Yongjian Hu, class 2017215120\n");
    printf("-----------------------------------------\n");
}

/** Read data from std in */
int read(char ** dat) {
    char * input;
    char * token;
    int size = 0;
    input = (char * ) malloc (sizeof(char) * MAX_ID_LENGTH * MAX_ID_SIZE);
    printf("Please input ID set: \n");
    scanf("%s", input);
    token = strtok(input, ",");
    while (token != NULL) {
        if (!strcmp(token, "-1")) {
            size = -1;
            break;
        }
        strcpy( * dat, token);
        dat++;
        size++;
        token = strtok(NULL, ",");
    }
    return size;
}