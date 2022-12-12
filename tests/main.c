#include "../include/lib.h"

int main(void) {
    smart_ptr *a = create_ptr(8);
    if (a == NULL) {
        printf("object null\n");
        return (1);
    }
    a->set_str(a, "Bonjour");
    printf("value : %s\n", (char *)a->ptr);
    a->set_str(a, "Putassiole");
    a->recreate(a, 15);
    a->set_str(a, "Putassiole");
    printf("value : %s\n", (char *)a->ptr);
    a->destroy(a);
}
