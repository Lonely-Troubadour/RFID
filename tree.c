#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int match(char *pattern, char *dat);
void print_result(int step, char *s, char *response);

/* Data
 * 0010
 * 0011
 * 1100
 * 1101
 * 1110
 */

int main(int argc, char const *argv[])
{
    /**
     * Status variable.
     *  0 - idle
     * -1 - conflict
     *  1 - match
     */
    int status = 0;
    int n = 5;
    int len = 5;
    int step = 0;

    char *dat[] = {"0010", "0011", "1100", "1101", "1110"};
    

    
    char *stack;
    char *ptr;

    stack = (char *) malloc(sizeof(char) * 20);
    ptr = stack;
    *ptr = **dat;

    printf("step-------S----------Tag-----\n");
    
    while (n != 0) {
        step++;
        char * idx_dat = NULL;        
        for (int i = 0; i < len; i++) {
            int result = match(stack, *(dat + i));
            if (result) {
                if (status) {
                    status = -1;
                    break;
                } else {
                    status = result;
                    idx_dat = *(dat + i);
                }
            }
        }

        char *response;
        response = (char *) malloc(sizeof(char) * 20);
        if (status == 1) {
            strcpy(response, idx_dat);
        } else if (status == -1) {
            strcpy(response, "conflict");
        } else {
            strcpy(response, "idle");
        }

        print_result(step, stack, response);
        
        switch (status) {
            case 0:
                while (*ptr == '1') {
                    *ptr = 0;
                    ptr--;
                }
                *ptr = '1';
                break;

            case -1:
                ptr++;
                *ptr = '0';
                break;

            case 1:
                n -= 1;
                while (*ptr == '1') {
                    *ptr = 0;
                    ptr--;
                }
                *ptr = '1';
                break;

            default:
                break;
        }
        status = 0;
        if (step == 15) break;
    }
    
    return 0;
}

int match(char *pattern, char *dat) {
    while (*dat != '\0' && *pattern != '\0') {
        // printf("%c %c\n", *pattern, *dat);
        if (*pattern != *dat)
            return 0;
        pattern++;
        dat++;
    }
    return 1;
}

void print_result(int step, char *s, char *response) {
    printf("%-10d %-10s %-10s \n", step, s, response);
}
