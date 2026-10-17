/**
 * Vector implementation.
 *
 * - Implement each of the functions to create a working growable array (vector).
 * - Do not change any of the structs
 * - When submitting, You should not have any 'printf' statements in your vector 
 *   functions.
 *
 * IMPORTANT: The initial capacity and the vector's growth factor should be 
 * expressed in terms of the configuration constants in vect.h
 */
#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "vect.h"

/** Main data structure for the vector. */
struct vect {
  char **data;             /* Array containing the actual data. */
  unsigned int size;       /* Number of items currently in the vector. */
  unsigned int capacity;   /* Maximum number of items the vector can hold before growing. */
};

/** Construct a new empty vector. */
vect_t *vect_new() {

  /* [TODO] Complete the function */

  vect_t *v = (vect_t *) malloc(sizeof(vect_t));
  assert(v != NULL);

  v->data = (char **) malloc(sizeof(char *) * VECT_INITIAL_CAPACITY);
  assert(v->data != NULL);

  v->size = 0;
  v->capacity = VECT_INITIAL_CAPACITY;

  return v;
}

/** Delete the vector, freeing all memory it occupies. */
void vect_delete(vect_t *v) {

  /* [TODO] Complete the function */

  assert(v != NULL);

  for (unsigned int i = 0; i < v->size; i++) {
    free(v->data[i]);
  }
  free(v->data);
  free(v);

}

/** Get the element at the given index. */
const char *vect_get(vect_t *v, unsigned int idx) {
  assert(v != NULL);
  assert(idx < v->size);

  /* [TODO] Complete the function */
  
  return v->data[idx];
}

/** Get a copy of the element at the given index. The caller is responsible
 *  for freeing the memory occupied by the copy. */
char *vect_get_copy(vect_t *v, unsigned int idx) {
  assert(v != NULL);
  assert(idx < v->size);

  /* [TODO] Complete the function */

  char *copy = (char *) malloc(strlen(v->data[idx]) + 1);
  assert(copy != NULL);
  strcpy(copy, v->data[idx]);

  return copy;
}

/** Set the element at the given index. */
void vect_set(vect_t *v, unsigned int idx, const char *elt) {
  assert(v != NULL);
  assert(idx < v->size);

  /* [TODO] Complete the function */

  char *copy = (char *) malloc(strlen(elt) + 1);
  assert(copy != NULL);
  strcpy(copy, elt);

  free(v->data[idx]);
  v->data[idx] = copy;

}

/** Add an element to the back of the vector. */
void vect_add(vect_t *v, const char *elt) {
  assert(v != NULL);

  /* [TODO] Complete the function */

  if (v->size == v->capacity) {
    assert(v->capacity < VECT_MAX_CAPACITY);
 
    /* Use a wider type so the multiplication cannot overflow. */
    unsigned long long new_capacity =
        (unsigned long long) v->capacity * VECT_GROWTH_FACTOR;
    if (new_capacity > VECT_MAX_CAPACITY) {
      new_capacity = VECT_MAX_CAPACITY;
    }
 
    char **new_data = (char **) realloc(v->data, sizeof(char *) * new_capacity);
    assert(new_data != NULL);
 
    v->data = new_data;
    v->capacity = (unsigned int) new_capacity;
  }
 
  char *copy = (char *) malloc(strlen(elt) + 1);
  assert(copy != NULL);
  strcpy(copy, elt);
 
  v->data[v->size] = copy;
  v->size++;

}

/** Remove the last element from the vector. */
void vect_remove_last(vect_t *v) {
  assert(v != NULL);

  /* [TODO] Complete the function */

  assert(v->size > 0);

  v->size--;
  free(v->data[v->size]);
  v->data[v->size] = NULL;

}

/** The number of items currently in the vector. */
unsigned int vect_size(vect_t *v) {
  assert(v != NULL);

  /* [TODO] Complete the function */

  return v->size;

  return 0;
}

/** The maximum number of items the vector can hold before it has to grow. */
unsigned int vect_current_capacity(vect_t *v) {
  assert(v != NULL);

  /* [TODO] Complete the function */

  return v->capacity;

  return 0;
}

