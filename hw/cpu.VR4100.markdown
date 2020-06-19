NEC VR4100
--------------------------------------------------------------------------------

NEC's VR4100 family was a line of embedded 64-bit MIPS microprocessors developed
specifically for use in PDAs and other handheld devices, for which it was quite
popular especially in the Windows CE ecosystem where it became a cornerstone of
many of Microsoft's early mobile computing initiatives throughout the 1990s and
into the early 2000s. Although often compared and (erroneously) equated to the
venerable MIPS R4000, the VR4100 is an entirely novel and indigenous design,
emphasizing energy efficiency and cost-effective implementation in small devices
over raw performance.

### Architecture

All members of the VR4100 family implement a classic five-stage pipeline design
closer to that of the older R3000 and R2000 than the 8-stage superpipelined 
R4000, and omit some of the more expensive, complex or otherwise unnecessary
features of the R4000 such as a floating-point unit, secondary cache support
and support for multiprocessing by way of the omission of the Load Linked
instructions `LL`/`LLD` and Store Conditional intructions `SC`/`SCD`, which
help facilitate atomic memory operations in shared-memory multiprocessor
systems.

In full compliance with the MIPS III instruction set, all VR4100 designs are
internally 64-bit, with 32-bit external data and address buses to reduce system
complexity and cost of implementation. Although any VR4100 core can theoretically 
address up to 4 GiB of memory, in practice they are significantly limited by 
their accompanying on-die memory controller to a much smaller amount; the VR4101 
only able to address up to 8 MiB, while the later VR4121 could address up to 64 
MiB.

### Implementations

| Model  | Year | Core    | Caches (I+D)     | Rated Frequency | Process    |
|--------|------|---------|------------------|-----------------|------------|
| VR4101 | 1996 | VR4100  | 2 KiB  +  1 KiB  |   33        MHz | 350 nm     |
| VR4102 | 1997 | VR4100  | 4 KiB  +  1 KiB  |   66        MHz | 350 nm     |
| VR4111 | 1998 | VR4110  | 16 KiB +  8 KiB  |   80  - 100 MHz | 250 nm UC2 |
| VR4181 | 1998 | VR4110  | 4  KiB +  4 KiB  |   66        MHz | 250 nm UC2 |
| VR4121 | 1999 | VR4120  | 16 KiB +  8 KiB  |   131 - 168 MHz | 250 nm UR2 |
| VR4122 | 1999 | VR4120A | 32 KiB + 16 KiB  |   150 - 180 MHz | 180 nm UC3 |
| VR4131 | 2001 | VR4130  | 16 KiB + 16 KiB  |   200       MHz | 130 nm UX4 |
| VR4133 | 2002 | VR4130  | 16 KiB + 16 KiB  |   266       MHz | 130 nm UX4 |
