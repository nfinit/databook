NEC VR4100
--------------------------------------------------------------------------------

The NEC VR4100 family was a popular line of high-end embedded microprocessors
in PDAs and other handheld devices through much of the late 1990s and early
2000s. As a cornerstone of Microsoft's Handheld PC reference platform, they were
an important part of the Windows CE ecosystem alongside Hitachi's SH-3 family
until Microsoft's Pocket PC platform standardized on the ARM architecture in 
2002. All VR4100 microprocessors implement the 64-bit MIPS III instruction set
alongside the MIPS16 ISA for greater code density in memory-constrained systems
like PDAs and embedded appliances, and also include a host of integrated
peripherals on-chip catering heavily to the Handheld PC specification, including
keyboard, LCD and touch digitizer controllers.

*Table of VR4100 series products*           
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

Most resources on the web tend to erroneously label VR4100 series chips as 
"MIPS R4000" processors due to their shared instruction set and mutual 
compatibility, however the VR4100 is an entirely indigenous design that differs 
significantly from the more complex R4000 family in implementation with a focus 
on low-power operation than computing performance. All VR4100 cores implement 
a classic 5-stage RISC pipeline closer to that of the older R2000/R3000 family 
than the 8-stage superpipelined R4000 family, and also omit some more complex 
features such as floating-point acceleration and multiprocessing by use of the 
Load Linked instructions `LL`/`LLD` and Store Conditional intructions `SC`/`SCD`,
which help facilitate atomic memory operations in shared-memory multiprocessor
systems.

In full compliance with the MIPS III instruction set, all VR4100 designs are
internally 64-bit, with 32-bit external data and address buses to reduce system
complexity and cost of implementation. Although any VR4100 core can theoretically 
address up to 4 GiB of memory, in practice they are significantly limited by 
their accompanying on-die memory controller to a much smaller amount; the VR4101 
only able to address up to 8 MiB, while the later VR4121 could address up to 64 
MiB.
