#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>

typedef struct smart_ptr {
    void *ptr;
    size_t size;

    int (*destroy)(struct smart_ptr *);
    int (*recreate)(struct smart_ptr *, size_t);
    int (*set_str)(struct smart_ptr *, const char *);
} smart_ptr;

/*
 * create_ptr: creates a new smart_ptr * object
 * @param size : size of the new pointer
 * @return smart_ptr * : the new smart_ptr * object
*/
smart_ptr *create_ptr(size_t size);

/*
* memory_recreate : reallocates to new size
* @param self : the smart_ptr *object
* @param size : the new size
* @return int : 1 if error, else 0
*/
int memory_recreate(smart_ptr *self, size_t size);

/*
* memory_destroy : frees the pointer correctly
* @param self : the smart_ptr * object you want to destroy
* @return int : 1 if error, else 0
*/
int memory_destroy(smart_ptr *self);

/*
* free_em_all : free multiple smart_ptr * object at once
* @param objectNumber : number of objects you want to free
* @param ... : the objects you want to free (smart_ptr *)
* @return int : 1 if error, else 0
*
*/
int free_em_all(size_t objectNumber, ...);


/*
* memory_set_str : if your ptr is a char *, you can set it with this function
* @param self : the smart_ptr * object
* @param str : the string you want to set it to
* @return 1 if error, else 0
*/
int memory_set_str(smart_ptr *self, const char *str);
