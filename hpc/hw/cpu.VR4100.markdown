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
peripherals on-chip catering heavily to the Windows CE platform and similar PDA
applications, such as keyboard, LCD and touch digitizer controllers.

The VR4100 family of microprocessors was developed and introduced by NEC in 1996
as a cornerstone of Microsoft's new Windows CE Handheld PC reference platform,
and perhaps also as a response to the announcement of the MIPS16 instruction set
supported by all VR4100 implementations alongside the traditional MIPS III ISA.
Designed from the ground up for handheld computing, VR4100 designs were
immensely popular in PDAs and other mobile devices prior to Microsoft's decision
to standardize the Pocket PC platform on the ARM architecture in the early 2000s
and the VR4100's subsequent shift of focus to network appliances and similar
high-end embedded roles. All VR4100 designs include a host of on-chip
peripherals catering heavily to the basic Handheld PC specification, sporting
keyboard, LCD, touch digitizer and IrDA communications controllers as standard
on-chip features.

Most resources on the web tend to mislabel VR4100 series chips as "MIPS R4000"
due to their shared instruction set and mutual compatibility, however the
VR4100 is an entirely indigenous design that differs significantly from the
complex R4000 family in implementation with more focus on low-power operation 
than computing performance. All VR4100 cores implement a classic 5-stage RISC 
pipeline closer to that of the older R2000/R3000 family than the 8-stage 
superpipelined R4000 family, and also omit some more complex features
such as floating-point acceleration and multiprocessing by use of the Load
Linked instructions `LL`/`LLD` and Store Conditional intructions `SC`/`SCD`
which help facilitate atomic memory operations in shared-memory multiprocessor
systems.

In full compliance with the MIPS III instruction set, all VR4100 designs are
internally 64-bit, with 32-bit external data buses to reduce system complexity
and cost of implementation.

| Model  | Frequency      | Caches (I+D)     | Date         |
|--------|----------------|------------------|--------------|
| VR4101 | 33 MHz         | 2 KiB  +  1 KiB  |  August 1996 |
| VR4102 | 54 MHz         | 4 KiB  +  1 KiB  |         1997 |
| VR4111 | 80  or 100 MHz | 16 KiB +  8 KiB  | January 1998 |
| VR4181 | 66 MHz         | 4  KiB +  4 KiB  |         1998 |
| VR4121 | 131 or 168 MHz | 16 KiB +  8 KiB  |         1999 |
| VR4122 | 150 or 180 MHz | 32 KiB + 16 KiB  |         1999 |
| VR4131 | 200 MHz        | 16 KiB + 16 KiB  |   March 2001 |
| VR4133 | 266 MHz        | 16 KiB + 16 KiB  |         2002 |
