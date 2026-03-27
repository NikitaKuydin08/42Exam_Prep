/*
Allowed functions: fork, waitpid, exit, alarm, sigaction, kill, printf, strsignal,
errno, sigaddset, sigemptyset, sigfillset, sigdelset, sigismember
*/

#include <stdbool.h>

int sandbox(void (*f)(void), unsigned int timeout, bool verbose)
{
    
}
