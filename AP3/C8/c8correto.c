#include <stdlib.h>
#include <stdint.h>

int main() {
    char* destination = (char *) calloc(27, sizeof(char));
    char* source = (char *) malloc(26 * sizeof(char));

    for(uint8_t i = 0; i < 26; i++) {
        *(destination + i) = *(source + i); //Look at the last iteration.
    }

    free(destination);
    free(source);
    return 0;
}