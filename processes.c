#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    for (int i = 0; i < 1000; ++i) {
        pid_t pid = fork();
        if (pid == 0) {
            sleep(60); 
            return 0;
        } else if (pid < 0) {
            perror("fork");
            break;
        }
    }
    sleep(65);
    return 0;
}
