#define _GNU_SOURCE
#include <stdio.h>
#include <dlfcn.h>
#include "malloc_interceptor.h"

/* Function pointer to the original malloc function. */
void *(*ori_malloc)(size_t size) = NULL;

/* Total number of bytes allocated so far. */
size_t bytes = 0;

/* The intercepted malloc. */
void *malloc(size_t size) {
  if (!ori_malloc) {
    ori_malloc = dlsym(RTLD_NEXT, "malloc");
  }

  void *fptr = ori_malloc(size);
  bytes += size;

  fprintf(stderr, "Total bytes allocated so far: %zu\n", bytes);
  return fptr;
}
