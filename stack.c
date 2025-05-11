#include <stdio.h>

void recurse(int depth) {
    printf("Depth: %d\n", depth);
    recurse(depth + 1);
}

int main() {
    recurse(1);
    return 0;
}
