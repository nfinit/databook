NEC VR4100
--------------------------------------------------------------------------------
The VR4100 family of microprocessors was developed and introduced by NEC in 1996
likely as a direct response to the announcement of the MIPS16 instruction set,
which all VR4100 implementations support alongside the traditional MIPS III ISA.
Designed for high-end, low-power embedded applications, VR4100 designs were
popular in PDAs and other mobile devices, with their most visible application 
being their inclusion in many early Windows CE handhelds from Casio, Compaq 
and NEC themselves prior to the Pocket PC's standardization on the ARM
architecture in the early 2000s.

Members of the VR4100 family are often erroneously labeled as "MIPS R4000"
designs due to their shared usage of the 64-bit MIPS III ISA and overall
compatibility with the earlier MIPS designs, however the VR4100 core is
an entirely indigenous NEC design that differs markedly from the R4000 in
certain areas relating to its embedded focus, mainly the omission of a
floating-point unit and related instructions as well as instructions for
facilitating atomic memory access in multi-processor shared memory systems
(namely the Load Linked instructions `LL` and `LLD`, and the Store
Conditional instructions `SC` and `SCD`), but also in its support for the
new MIPS16 instruction set, a Hitachi-inspired bid to increase code
density and reduce memory footprint through the use of smaller 16-bit 
instructions.

The VR4100 family was first introduced with the 40 MHz VR4101 in August 
1996, and saw its first application in NEC's new MobilePro 400/200
Handheld PC, also one of the first commercially available Windows CE 
devices. NEC continued to manufacture VR4100 series products into the 
mid 2000s, culminating with the 266 MHz network appliance-focused VR4133. 
The following table lists known VR4100 family members:

| Model  | Frequency      | Caches (I+D)     | Date         |
|--------|----------------|------------------|--------------|
| VR4101 | 40 MHz         | 2 KiB  +  1 KiB  |  August 1996 |
| VR4102 | 54 MHz         | 4 KiB  +  1 KiB  |         1997 |
| VR4111 | 80  or 100 MHz | 16 KiB +  8 KiB  | January 1998 |
| VR4181 | 66 MHz         | 4  KiB +  4 KiB  |         1998 |
| VR4121 | 131 or 168 MHz | 16 KiB +  8 KiB  |         1999 |
| VR4122 | 150 or 180 MHz | 32 KiB + 16 KiB  |         1999 |
| VR4131 | 200 MHz        | 16 KiB + 16 KiB  |   March 2001 |
| VR4133 | 266 MHz        | 16 KiB + 16 KiB  |         2002 |
