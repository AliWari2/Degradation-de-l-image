#include "stack2.h"
#include <stdlib.h>

#define STACK_EMPTY (-1)
#define STACK_FULL  (-2)

struct _stack_t {
    void **elements;
    int top;
    int capacity;
};

struct _stack_iterator_t {
    my_stack_t *stack;
    int current;
};

my_stack_t *stack_create(int nbMaxElement) {
    my_stack_t *stack = (my_stack_t *)malloc(sizeof(my_stack_t));
    if (stack == NULL) {
        return NULL; // Memory allocation failed
    }

    stack->elements = (void **)malloc(sizeof(void *) * nbMaxElement);
    if (stack->elements == NULL) {
        free(stack);
        return NULL; // Memory allocation failed
    }

    stack->top = STACK_EMPTY;
    stack->capacity = nbMaxElement;
    return stack;
}

void stack_remove(my_stack_t *stack) {
    if (stack != NULL) {
        free(stack->elements);
        free(stack);
    }
}

void stack_init(my_stack_t *stack) {
    if (stack != NULL) {
        stack->top = STACK_EMPTY;
    }
}

int stack_push(my_stack_t *stack, void *valeur) {
    if (stack == NULL) {
        return STACK_EMPTY; // Invalid stack
    }

    if (stack->top == stack->capacity - 1) {
        return STACK_FULL; // Stack is full
    }

    stack->elements[++stack->top] = valeur;
    return 0; // Success
}

void *stack_pop(my_stack_t *stack) {
    if (stack == NULL || stack->top == STACK_EMPTY) {
        return NULL; // Invalid stack or stack is empty
    }

    return stack->elements[stack->top--];
}

int stack_pop2(my_stack_t *stack, void **value) {
    if (stack == NULL || stack->top == STACK_EMPTY || value == NULL) {
        return STACK_EMPTY; // Invalid stack or stack is empty
    }

    *value = stack->elements[stack->top--];
    return 0; // Success
}

stack_iterator_t *stack_iterator_create(my_stack_t *stack) {
    if (stack == NULL) {
        return NULL; // Invalid stack
    }

    stack_iterator_t *it = (stack_iterator_t *)malloc(sizeof(stack_iterator_t));
    if (it == NULL) {
        return NULL; // Memory allocation failed
    }

    it->stack = stack;
    it->current = stack->top;
    return it;
}

void stack_iterator_free(stack_iterator_t *it) {
    free(it);
}

void *stack_iterator_next(stack_iterator_t *it) {
    if (it == NULL || it->current == STACK_EMPTY) {
        return NULL; // Invalid iterator or no more elements
    }

    return it->stack->elements[it->current--];
}

int stack_iterator_next2(stack_iterator_t *it, void **value) {
    if (it == NULL || it->current == STACK_EMPTY || value == NULL) {
        return STACK_EMPTY; // Invalid iterator or no more elements
    }

    *value = it->stack->elements[it->current--];
    return 0; // Success
}

int stack_capacity(const my_stack_t *stack) {
    return (stack != NULL) ? stack->capacity : STACK_EMPTY;
}

int stack_is_empty(const my_stack_t *stack) {
    return (stack != NULL && stack->top == STACK_EMPTY);
}

int stack_has_value_available(const my_stack_t *stack) {
    return (stack != NULL && stack->top != STACK_EMPTY);
}

int stack_mem_available(const my_stack_t *stack) {
    return (stack != NULL) ? (stack->capacity - stack->top - 1) : STACK_EMPTY;
}

int stack_mem_used(const my_stack_t *stack) {
    return (stack != NULL) ? (stack->top + 1) : STACK_EMPTY;
}
