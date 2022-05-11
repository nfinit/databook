Getting and installing first-party VAX software
--------------------------------------------------------------------------------

It's reasonable to assume that software is hard to find for something as
uncommon as a VAX, and that assumption is generally true, at least to the
extent of third-party products. Luckily for hobbyists, the VAX, like so many
other large systems, has a rich base of first-party products from Digital
themselves that are readily available online, typically in the form of a
*consolidated software distribution*, or *condist*.

Condist sets consist of multiple disks/tapes and have almost everything you
need for a functional, useful system from system utilities to compilers to
fully-featured productivity software, all installed in a more-or-less
automated fashion. 

### Preparation

Before we start installing software, we'll want to make sure we're logged in
as the `SYSTEM` user and focus on two things:

#### Fixing quotas

VMS is built with large multi-user systems in mind and as such has a system of
*quotas* that help limit access to resources to keep performance consistent in
such environments. The default settings for these quotas are stifling even on
the `SYSTEM` account and will cause most large application install attempts to
fail. For this reason, we will need to increase the quotas on `SYSTEM`, which
can be done using the familiar built-in `AUTHORIZE` utility.

Each user account on the system has 16 specific manageable quotas:

| Quota       | Description                                    | Default (s/u) |
|-------------|------------------------------------------------|---------------|
| ASTLM       | Max. outstanding asynchronous system traps     | 50/0          |
| BIOLM       | Max. outstanding buffered I/O requests         | 40            |
| BYTLM       | Max. byte count of outstanding buffered I/Os   | 32768         |
| CPU         | Max. amount of CPU time per session            | no limit      |
| DIOLM       | Number of outstanding direct I/O requests      | 40            |
| ENQLM       | Max. number of locks process can own           | 300/200       |
| FILLM       | Max. number of files process can open          | 300/300       |
| JTQUOTA     | Bytes allocated for JOB logical names          | 4096/4096     |
| MAXACCTJOBS | Max. interactive, batch, detatched processes   | no limit      |
| MAXDETACH   | Max. detached processes                        | no limit      |
| MAXJOBS     | MAXACCTJOBS + network jobs                     | no limit      |
| PRCLM       | Max. number of subprocesses                    | 10/2          |
| TQELM       | Max. number of outstanding timer queue entries | 30/40         |
| PGFLQUOTA   | Page-file quota (in pages)                     | 20480/32768   |
| WSDEF       | Default working set limit                      | 256 pages     |
| WSEXTENT    | Working set extent limit                       | 40960/1024 p. |
| WSQUOTA     | Working set quota limit                        | 512 pages     |

For `SYSTEM`, we'll make the following limit and quota adjustments:

| Quota       | Value  |
|-------------|--------|
| ASTLM       | 150    |
| BIOLM       | 150    |
| BYTLM       | 131072 |
| DIOLM       | 120    |
| ENQLM       | 32767  |
| FILLM       | 500    |
| PRCLM       | 50     |
| TQELM       | 50     |
| PGFLQUOTA   | 32768  |

Since our VAX is unlikely to see more than perhaps 2 or 3 active users at a
time, we can probably safely raise these quotas to the point that they are
effectively unlimited.

As we did in the previous page when we installed VMS for the first time, we
will again run the `AUTHORIZE` utility with the following commands:

```DCL   

SET DEFAULT SYS$SYSTEM
RUN AUTHORIZE 

```

#### Volume labels

Assuming you have a condist CD set in hand, you'll most importantly want the
*volume label* of each disk, which often follow the format 
`[Arch]BIN[MMM][YY][CD#]`. As an example, the May 1994 OpenVMS VAX set is
labeled `VAXBINMAY940` through `VAXBINMAY94A`* with a total of 12 disks. These
labels are important to remember as they are required to mount these CDs for
installation.

\* (CDs are numbered hexadecimally)

Now, we are ready:

### Working with Consolidated Software Distributions

The Consolidated Software Distribution CDs feature menu-driven interfaces for
installing software and viewing documentation. Software tends to be spread
somewhat haphazardly around the discs, so if you are fortunate enough to have
matching documentation with your CD set, printing the *master index* is
worthwhile.

If you don't have such documentation, simply insert the first disc, which will
have a copy of the index onboard and allow you to find what is needed from
there in the software menu. 

After inserting the CD and making sure to note its volume label, mount it
using a similar command sequence:

```DCL

MOUNT DKA400: VAXBINMAY941

```

Where `DKA400` and `VAXBINMAY941` can be replaced by the name of your optical
drive and volume label, respectively.

Now that the volume is mounted, we can access the CD menu utility by
first defining the logical name `CD_DIRECTORY` and then running `CDMENU`:

```DCL

DEFINE CD_DIRECTORY DKA400:[CDROM]
RUN CD_DIRECTORY:CDMENU

```

#### Installing Software

#### Licensing Software

If you have previously read the VMS installation guide in this document set, you
are already somewhat familiar with software licensing on VAX/VMS, which is
relatively quite advanced compared to contemporary consumer systems. The
software provided by DEC on their condist sets are *not* freeware, rather
commercial-grade and very expensive products, all of which require a license
registered to run or even install on your VAX. Digital and subsequent
maintainers of VMS traditionally have offered a hobbyist licensing program to
allow home users to run these machines without paying considerable costs to
license them, however in the case of the VAX, end of support and the current
legal situation of VAX/VMS prevent such licenses being issued for VAX systems,
though solutions from the likes of the VLF still exist today.

In the heyday of the VAX, licenses were issued as physical certificates with
license information, known as a Product Authorization Key or more commonly a
*PAK*, whose information must be registered with the VAX/VMS License Management
Facility, *LMF*.

The most basic valid PAK consists of a **product code**, **authorization code** 
and **producer**. 

* Product codes tend to be short forms of the product name, such
as `VAX-VMS`, `FORTRAN` or `ALLIN1`. If you are unsure of what your product
code is, it will usually be stated during the license check phase of the
installation.

* As condists only contain first-party software, the producer field is always
  `DEC`.
  
* The authorization code is a long string generated as a function of the
  product code and producer string.

### Example condist product codes

The following is a list of useful product codes for any VAX/VMS system:

| Product                  | Description                                       |
|--------------------------|---------------------------------------------------|
| VAX-VMS                  | OpenVMS operating system                          |
| DVNETEND                 | DECnet                                            |
| UCX                      | TCP/IP services                                   |
| BASIC                    | VAX BASIC                                         |
| CXX-V                    | DEC C++                                           |
| PASCAL                   | DEC Pascal                                        |
| FORTRAN                  | DEC Fortran                                       |
| COBOL                    | VAX COBOL                                         |
| ADA                      | DEC Ada                                           |
| DIBOL                    | VAX DIBOL                                         |
| APL                      | VAX APL                                           |
| BLISS                    | VAX BLISS                                         | 
| VAXSET                   | DECset development tool suite                     |
| LSE                      | Language-sensitive editor                         |
| MMS                      | Module Management System                          |
| CMS                      | Code Management System                            |
| PCA                      | Performance and Coverage Analyzer                 |
| DTM                      | Test Manager                                      | 
| FMS                      | VAX Forms Management System                       |
| RDB                      | DEC Rdb database management system                |
| FORMS                    | DECforms (full/development)                       |
| NOTES                    | DEC Notes conferencing system                     |
| DECALC-PLUS              | DECalc-PLUS spreadsheet                           |
| MESSAGE-ROUTER           | VAX Message Router (VMSmail gateway)              |
| ALLIN1                   | ALL-IN-1 Integrated Office Server                 |

--------------------------------------------------------------------------------
