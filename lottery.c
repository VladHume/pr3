#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

void draw(int count, int max) {
    int used[100] = {0};
    int i = 0, r;
    while (i < count) {
        r = rand() % max + 1;
        if (!used[r]) {
            printf("%d ", r);
            used[r] = 1;
            i++;
        }
    }
    printf("\n");
}

int main() {
    srand(time(NULL));
    printf("7 of 49: ");
    draw(7, 49);
    printf("6 of 36: ");
    draw(6, 36);
    while (1);
    return 0;
}
