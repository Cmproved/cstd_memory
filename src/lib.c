#include "../include/lib.h"
#include <string.h>

int memory_set_str(smart_ptr *self, const char *str)
{
    if (strlen(str) > self->size) {
        write(2, "Error: string is too big for destination\n", 42);
        return (1);
    }

    memset(self->ptr, 0, self->size);
    self->ptr = strcpy(self->ptr, str);
    return (0);
}

int free_em_all(size_t objectNumber, ...)
{
    va_list a;
    int failedAttemps = 0;
    smart_ptr *b = NULL;
    va_start(a, objectNumber);

    for (int i = 0; i < objectNumber; ++i) {
        b = va_arg(a, smart_ptr *);
        if (b->destroy(b) == 1) {
            failedAttemps++;
        }
    }

    if (failedAttemps != 0) {
        write(2, "Warning: at least one object was not correctly freed\n", 54);
    }
    return (failedAttemps);
}

int memory_destroy(smart_ptr *self)
{
    free(self->ptr);
    free(self);

    return (0);
}

int memory_recreate(smart_ptr *self, size_t size)
{
    self->ptr = realloc(self->ptr, size);
    if (self->ptr == NULL) {
        write(2, "Error: failed reallocating memory\n", 35);
        return (1);
    }
    self->size = size;
    return (0);
}

smart_ptr *create_ptr(size_t size)
{
    smart_ptr *s = malloc(sizeof(smart_ptr));
    if (s == NULL) {
        write(2, "Error: coudln't create structure pointer\n", 41);
        return NULL;
    }

    s->ptr = malloc(size);
    if (s->ptr == NULL) {
        write(2, "Error: couldn't create pointer\n", 31);
        free(s);
        return NULL;
    }

    s->size = size;
    s->destroy = &memory_destroy;
    s->recreate = &memory_recreate;
    s->set_str = &memory_set_str;

    return (s);
}
