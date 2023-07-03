#include <stdlib.h>
#include <stdint.h>

struct _List {
    int32_t* data;
    int32_t length;
};
typedef struct _List List;

List* resizeArray(List* array) {
    int32_t* dPtr = array->data;
    dPtr = (int32_t *) realloc(dPtr, 15 * sizeof(int32_t)); //doesn't update array->data
    array->data = dPtr;
    return array;
}

int main() {
    List* array = (List *) calloc(1, sizeof(List));
    array->data = (int32_t *) calloc(10, sizeof(int32_t));
    array = resizeArray(array);

    free(array->data);
    free(array);
    return 0;
}