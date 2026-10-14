#ifndef FLASH_H
#define FLASH_H

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define FLASH_CAPACITY (16u * 1024u * 1024u)
#define FLASH_SECTOR_SIZE 4096u
#define FLASH_PAGE_SIZE 256u

bool flash_init(void);
void flash_shutdown(void);

bool flash_read(uint32_t address, void* buffer, size_t size);
bool flash_program(uint32_t address, const void* data, size_t size);
bool flash_erase(uint32_t address, size_t size);

size_t flash_capacity(void);
size_t flash_sector_size(void);
size_t flash_page_size(void);

#endif
