NEC VR4100
--------------------------------------------------------------------------------
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

The many members of the VR4100 family are often erroneously labeled as "MIPS
R4000" processors around the web due to their shared usage of the 64-bit MIPS
III instruction set and overall compatibility with the R4000 line, however
the VR4100 core is a far simpler and completely indigenous NEC design that
differs markedly from the R4000 in many areas relating to its embededd,
low-power focus, which is most visible in the omission of a floating-point 
unit as well as various instructions often used in shared memory 
multi-processing systems; namely the Load Linked instructions `LL` and 
`LLD`, and the Store Conditional instructions `SC` and `SCD`, which better
facilitate atomic memory operations in such arrangements.

The VR4100 series was also among the first implementations of the then-new
MIPS16 instruction set, which implemented a series of shrunken 16-bit
instructions in a bid inspired by Hitachi's SuperH architecture to improve
code density and therefore more efficiently use the tiny memories and caches 
of handhelds and other highly constrained embedded systems of the time.

## Cores, models and overview

### 1996-1998: VR4100

The VR4100 core was the original design released by NEC, which implemented
a more-or-less classic five-stage MIPS/RISC pipeline (compare to the *real*
R4000's eight-stage implementation) that differed mainly in the accomodation
of small on-chip instruction and data caches. The VR4100 could yield roughly
1 VAX MIPS/MHz under optimal conditions, achieving integer computation
performance of roughly 80486DX/2 class in more PC-friendly terms. VR4100-based
designs are fabricated in NEC's 350-nanometer 3LI CMOS process.

#### VR4101

The VR4101 was the first member of the VR4100 family debuted by NEC in
August 1996, seeing its first application in NEC's new MobilePro Handheld
PC which was itself one of the earliest Windows CE devices on the market.
The VR4101 paired the VR4100 core with small instruction and data caches of
2 and 1 KiB, respectively, and was rated for a 33 MHz clock frequency. The
VR4101 drew only 250-300 milliwatts under typical operation and ~30 in a
standby state, making it especially suitable for tiny PDAs that could run
for weeks on a pair of disposable AA batteries.

#### VR4102

The VR4102 succeeded the VR4101 in 1997, sporting the same VR4100 core but
doubling the instruction cache to 4 KiB and integrating a 10-bit ADC on-die
along with a number of additional I/O enhancements. The VR4102 also receives 
a healthy frequency rating boost up to 66 MHz, though most VR4102-powered NEC
devices run at a more conservative 54 MHz clock.

### 1998: VR4110

The VR4110 is a 250-nanometer die shrink of the VR4100 and architecturally 
almost identical to its predecessor, the main difference appearing to be the 
lack of support for parity error checking in the instruction and data caches.

#### VR4111

#### VR4181

### 1999-2000: VR4120

The VR4120 improves on the VR4110 with the addition of some extra instructions
(most notably a 32-bit multiply-add instruction) as well as the inclusion of
a sixth pipeline stage when operating on MIPS16 instructions, quickly
translating them to their 32-bit counterparts prior to execution. Early VR4120
implementations were fabricated on a 250-nanometer CMOS process similar to the
VR4110, while later designs were fabricated on a 180-nanometer process.

#### VR4121

The VR4121 was first available in early 1999 and offered a significant improvement
in clock frequency over the VR4111, rated at 131 or 168 MHz. The VR4121 most notably
powered a number of peculiar "Jupiter"-class Handheld PCs including NEC's own
MobilePro 880, IBM's WorkPad z50 and the Vadem Clio.

#### VR4122

The VR4122 was introduced in 2000 as one of the last members of the VR4100 family
oriented for use in handheld devices. Built on a new 180-nanometer CMOS process,
the VR4122 carries a relatively impressive 150-180 MHz frequency rating and also
implements a subset of the PCI bus to supersede the aging ISA bus implemented in
previous products. Most importantly, the VR4122 also doubles the instruction and
data caches of the VR4121 to 32 KiB and 16 KiB, respectively.

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
