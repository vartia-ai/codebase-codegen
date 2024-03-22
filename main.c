// main.c

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

//enum of the possible types of data
typedef enum
{
    UNKNOWN,
    ODD,
    EVEN
} num_type_t;

struct even_struct
{
    int value;
};
typedef struct even_struct even_t;

struct odd_struct
{
    int value;
};
typedef struct odd_struct odd_t;

struct wrapper_struct
{
    void *data;
    num_type_t type;
    int count;
};
typedef struct wrapper_struct wrapper_t;


wrapper_t* divide_by_2(wrapper_t *wrapper)
{
    assert(wrapper != NULL);

    even_t *even = (even_t *)wrapper->data;
    int value = even->value / 2;
    if (value % 2 == 0)
    {
        even->value = value;
    }
    else
    {
        free(even);
        odd_t *odd = malloc(sizeof(odd_t));
        odd->value = value;
        wrapper->data = (void *)odd;
        wrapper->type = ODD;
    }
    
    return wrapper;
}

wrapper_t* multiply_by_3_plus_one(wrapper_t *wrapper)
{
    assert(wrapper != NULL);
    
    odd_t *odd = (odd_t *)wrapper->data;
    int value = odd->value * 3 + 1;
    if (value % 2 == 0)
    {
        free(odd);
        even_t *even = malloc(sizeof(even_t));
        even->value = value;
        wrapper->data = even;
        wrapper->type = EVEN;
    }
    else
    {
        odd->value = value;
    }

    return wrapper;
}

wrapper_t* choose(wrapper_t *wrapper)
{   
    if (wrapper->type == EVEN)
    {
        return divide_by_2(wrapper);
    }
    else if (wrapper->type == ODD)
    {
       return multiply_by_3_plus_one(wrapper);
    }
    else
    {
        printf("Unknown type\n");
    }
    assert (false);
    return NULL;
}

bool is_wrapper_done(wrapper_t *wrapper)
{

    if (wrapper->type == EVEN)
    {
        even_t *even = (even_t *)wrapper->data;
        if (even->value <= 0)
        {
            return true;
        }
    }
    else if (wrapper->type == ODD)
    {
        odd_t *odd = (odd_t *)wrapper->data;
        if (odd->value <= 1)
        {
            return true;
        }
    }
    return false;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <integer>\n", argv[0]);
        return 1;
    }

    int start_num = atoi(argv[1]);

    even_t *e = malloc(sizeof(even_t));
    e->value = start_num;

    wrapper_t *wrapper = malloc(sizeof(wrapper_t));
    wrapper->data = (void *)e;
    wrapper->type = EVEN;
    wrapper->count = 0;
    while (is_wrapper_done(wrapper) == false)
    {
        wrapper = choose(wrapper);
        wrapper->count++;
    }

    printf("Count: %d\n", wrapper->count);

    free(wrapper->data);
    free(wrapper);
}
