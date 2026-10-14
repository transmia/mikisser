#ifndef PSRAM_H
#define PSRAM_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define PSRAM_CAPACITY (8u * 1024u * 1024u)

bool psram_init(void);
void psram_shutdown(void);

void* psram_alloc(size_t size);
void* psram_calloc(size_t count, size_t size);
void* psram_realloc(void* ptr, size_t size);
void psram_free(void* ptr);

size_t psram_capacity(void);
size_t psram_used(void);
size_t psram_available(void);

#endif
