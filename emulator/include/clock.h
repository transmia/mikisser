#ifndef CLOCK_H
#define CLOCK_H

#include <stdbool.h>
#include <stdint.h>

#define CLOCK_MAX_HZ 150000000u

bool clock_init(uint32_t frequency_hz);
void clock_shutdown(void);

bool clock_set_frequency(uint32_t frequency_hz);
uint32_t clock_get_frequency(void);
uint64_t clock_get_time_us(void);
void clock_sleep_us(uint64_t duration_us);

/* basically a step, on real hw would be just return true, on emulation it might actually wait */
bool clock_wait(void);

#endif
