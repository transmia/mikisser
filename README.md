# MiKisser Emulator

MiKisser is a hypothetical machine that has:
- RP2350B chip (150mhz)
- 8MB SRAM
- 16MB flash
- LCD from Casio Classwiz calculator series
- Keypad from Casio Classwiz FX 85CE X

The emulator currently emulates ONLY the lcd and the clock, everything else is TODO.
Also, it uses gcc to compile the "firmware" code and then it just links, the clock has a step function and lcd has hooks.

## References

- [Raylib](https://www.raylib.com)
- [nob.h](https://github.com/tsoding/nob.h)
- [Casio FX 85CE X](https://www.casio.com/europe/scientific-calculators/product.FX-85CEX/)
- [This video](https://www.youtube.com/watch?v=aV3LoSlSdGQ)
- [ZephRay](https://zephray.me/post/d991cn_screen_reverse_engineer/)

## LICENSE

[MIT LICENSE](./LICENSE)
