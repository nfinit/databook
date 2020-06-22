NEC VR4100
--------------------------------------------------------------------------------

NEC's VR4100 family was a line of embedded 64-bit MIPS microprocessors developed
specifically for use in PDAs and other handheld devices, for which it was quite
popular especially in the Windows CE ecosystem where it became a cornerstone of
many of Microsoft's early mobile computing initiatives throughout the 1990s and
into the early 2000s. Although often compared and (erroneously) equated to the
venerable MIPS R4000, the VR4100 is an entirely new and indigenous design,
emphasizing energy efficiency and cost-effective implementation in small devices
over raw performance.

### Architecture

Like the R4000, the VR4100 family is fully 64-bit, implementing the same MIPS
III instruction set architecture. Unlike the R4000, this implementation is much
more simple for the sake of cost and energy efficiency; VR4100 cores omit 
several more complex, expensive or otherwise unnecessary features of the R4000 
such as a floating-point unit, secondary cache support and support for 
multiprocessing by way of the omission of the Load Linked instructions 
`LL`/`LLD` and Store Conditional intructions `SC`/`SCD`, which help facilitate 
atomic memory operations in shared-memory multiprocessor systems. 

This simplification continues even to the microarchitectural level, with the core
of the VR4100 being built around a simple 5-stage RISC pipeline far more similar 
to that used in the earlier R3000 and R2000 than the 8-stage superpipelined 
powerhouse of the R4000.

### Implementations and usage

| Model  | Year | Core    | Caches (I+D)     | Rated Frequency | Process    |
|--------|------|---------|------------------|-----------------|------------|
| VR4101 | 1996 | VR4100  | 2 KiB  +  1 KiB  |   33        MHz | 350 nm UC1 |
| VR4102 | 1997 | VR4100  | 4 KiB  +  1 KiB  |   66        MHz | 350 nm UC1 |
| VR4111 | 1998 | VR4110  | 16 KiB +  8 KiB  |   80  - 100 MHz | 250 nm UC2 |
| VR4181 | 1998 | VR4110  | 4  KiB +  4 KiB  |   66        MHz | 250 nm UC2 |
| VR4121 | 1999 | VR4120  | 16 KiB +  8 KiB  |   131 - 168 MHz | 250 nm UR2 |
| VR4122 | 1999 | VR4120A | 32 KiB + 16 KiB  |   150 - 180 MHz | 180 nm UC3 |
| VR4131 | 2001 | VR4130  | 16 KiB + 16 KiB  |   200       MHz | 130 nm UX4 |
| VR4133 | 2002 | VR4130  | 16 KiB + 16 KiB  |   266       MHz | 130 nm UX4 |

Active development on the VR4100 family began in 1995 with the 33 MHz VR4101
and ended with the 266 MHz VR4133 in 2002, through these 7 years the fundamental
design stayed the same with most innovation being focused on the manufacturing
process and peripheral sets, which improved significantly with each generation.
