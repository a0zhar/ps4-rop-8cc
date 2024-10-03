// Copyright 2012 Rui Ueyama. Released under the MIT license.

/*
 * Vectors are containers of void pointers that can change in size.
 */

#include <stdlib.h>
#include <string.h>
#include "8cc.h"

#define MIN_SIZE 8

// Rounds up an integer to the next power of two
static int roundup(int n) {
    // Return minimum size if n is zero or negative
    if (n == 0) return 0;

    int r = 1;
    // Double r until it is greater than n
    while (n > r) r *= 2;
    return r;
}

static int max(int a, int b) {
    return a > b ? a : b;
}
static Vector *do_make_vector(int size) {
    // Allocate memory for the Vector structure, if the
    // allucation fails, we return NULL
    Vector *r = malloc(sizeof(Vector));
    if (!r) return NULL;

    // Round up the initial size to the nearest power of two
    size = roundup(size);

    // If the rounded up size, is greater than zero we try to
    // allocate memory for the body, but if that fails we then
    // free any allocated memory, before returning NULL
    if (size > 0) {
        r->body = malloc(sizeof(void *) * size);
        if (r->body == NULL) {
            free(r);
            return NULL;
        }
    }
    r->len = 0;       // Initialize current length to 0
    r->nalloc = size; // Set the allocated size
    return r;         // Return the initialized Vector
}

Vector *make_vector() { return do_make_vector(0); }

// Extends the Vector's capacity if necessary.
static void extend(Vector *vec, int delta) {
    // If there's enough space, do nothing
    if (vec->len + delta <= vec->nalloc)
        return;

    // Calculate new capacity, ensuring it is at least MIN_SIZE
    int nelem = max(roundup(vec->len + delta), MIN_SIZE);

    // Allocate a new array with the updated capacity, and if it
    // fails, we free simply return early
    void **newbody = realloc(vec->body, sizeof(void *) * nelem);
    if (!newbody) return;

    // Set the New Values
    vec->body = newbody; // Update the vector's body to point to the new array
    vec->nalloc = nelem; // Update the allocated size
}

Vector *make_vector1(void *e) {
    Vector *r = do_make_vector(0);
    vec_push(r, e);
    return r;
}

Vector *vec_copy(Vector *src) {
    Vector *r = do_make_vector(src->len);
    memcpy(r->body, src->body, sizeof(void *) * src->len);
    r->len = src->len;
    return r;
}

void vec_push(Vector *vec, void *elem) {
    extend(vec, 1);
    vec->body[vec->len++] = elem;
}

void vec_append(Vector *a, Vector *b) {
    extend(a, b->len);
    memcpy(a->body + a->len, b->body, sizeof(void *) * b->len);
    a->len += b->len;
}

void *vec_pop(Vector *vec) {
    assert(vec->len > 0);
    return vec->body[--vec->len];
}

void *vec_get(Vector *vec, int index) {
    assert(0 <= index && index < vec->len);
    return vec->body[index];
}

void vec_set(Vector *vec, int index, void *val) {
    assert(0 <= index && index < vec->len);
    vec->body[index] = val;
}

void *vec_head(Vector *vec) {
    assert(vec->len > 0);
    return vec->body[0];
}

void *vec_tail(Vector *vec) {
    assert(vec->len > 0);
    return vec->body[vec->len - 1];
}

Vector *vec_reverse(Vector *vec) {
    Vector *r = do_make_vector(vec->len);
    for (int i = 0; i < vec->len; i++)
        r->body[i] = vec->body[vec->len - i - 1];
    r->len = vec->len;
    return r;
}

void *vec_body(Vector *vec) {
    return vec->body;
}

int vec_len(Vector *vec) {
    return vec->len;
}
