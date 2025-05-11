#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *f = fopen("dice.log", "w");
    if (!f) {
        perror("fopen");
        return 1;
    }

    srand(time(NULL));
    while (1) {
        if (fprintf(f, "%d\n", rand() % 6 + 1) < 0) {
            perror("write");
            break;
        }
    }

    fclose(f);
    return 0;
}
