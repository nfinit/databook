Overview of Handheld PC Microprocessors and Architectures
--------------------------------------------------------------------------------
With the Handheld PC, Microsoft and its affiliates looked to the future and
elected to standardize on a variety of modern 32-bit RISCs rather than continue
to use the aging embedded derivatives of Intel's 8086 and 80386 that were
otherwise common in handheld and embedded computers at the time. To this end,
the HPC ultimately used a trio of architectures; the pioneering MIPS ISA,
Hitachi's innovative SuperH, and later the rapidly growing ARM architecture,
which would eventually usurp all of its competitors towards the end of the
HPC's brief but influential tenure in the consumer market when Microsoft
standardized on it exclusively in the early 2000s.

While Handheld PCs and similar devices made use of standard, off-the-shelf
architectures and platforms, these were generally implemented in ways unique
to the HPC/PDA world, with specific lines of CPUs such as NEC's VR4100 family
of MIPS application processors or Hitachi's competing SH7700 series. Some
vendors, such as Philips, even went as far as to develop their own designs
entirely.

This article serves as an overview of the various major families of CPUs
employed in the Handheld PC platform, covering mostly the MIPS, SuperH and
ARM architectures most commonly used in these devices.

## MIPS microprocessors

The established MIPS architecture was a mainstay in HPCs and other PDAs as
much as it was in workstations and high-performance computing throughout
the latter half of the 1990s, primarily through NEC's VR4100 family of 
application processors, but also through Toshiba's TX39 and Philips' R39x0 
microprocessor families. Both 32-bit and 64-bit MIPS variants were employed
in HPCs, with the Toshiba and Philips' faster 32-bit designs derived from
the desktop-class MIPS R3000 often out-pacing NEC's more modest, embedded
focused 64-bit MIPS III-compatible designs.

### NEC VR4100 series

NEC's VR4100 was immensely popular, designed from the ground up for the
Handheld PC platform and easily the most common family of MIPS 
microprocessors used in PDA applications. Although often compared or
even equated to the well-known MIPS R4000 used in a variety of workstations
and servers from the likes of Silicon Graphics, DEC, Tandem and NEC
themselves, the VR4100's design is entirely indigenous and the likeness 
between it and the R4000 is limited to their mutual implementation of the
64-bit MIPS III instruction set. VR4100 cores are optimized for low-power
applications, sporting a classic five-stage pipeline architecture (compare
to the R4000's 8-stage superpipelined implementation) and lacking features
such as floating-point acceleration and secondary cache support, as well as
multiprocessing support through the omittance of Load Linked/Store Conditional 
instructions important for facilitating atomic memory accesses 
in shared-memory multiprocessing configurations.

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

*Above: table of VR4100 series products*

The VR4100 series was first introduced with the VR4101 in August 1996, which
powered NEC's (and the world's) first Windows CE devices alongside the
SuperH-driven Cassiopeia series from Casio. Last to be used in PDAs were the 
VR4121 and VR4122, with their successors in the VR413x family shifting the
VR4100's focus toward network appliances and similar highly embedded roles
in light of Microsoft's decision to standardize the Windows CE PDA platform
on the ARM architecture starting with Pocket PC 2002.

### Toshiba TX39 series

Toshiba's TX39 series is a more conventional MIPS implementation derived
from the venerable 32-bit R3000A microprocessor once found in various
workstation-class systems such as SGI's Personal Iris and Indigo families,
designated the 'R3900' by Toshiba. The TX39 integrates cache memory onto
the processor die and omits certain unnecessary instruction groups mostly
concerning co-processor support. Earlier TX39 models also omit the R3000A's
"control processor" which included a memory management unit and translation
lookaside buffer.

### Philips PR31700 series

Philips' PR31700 is the least common MIPS application processor family
in the CE world, but also one of the fastest. Similar to Toshiba's approach
with the TX39, the PR31700 is designed around a MIPS R3000A-derived core
(designated 'PR3901') with on-die caches as well as additional multiply-add 
and branch-likely instructions to improve efficiency for embedded applications.
