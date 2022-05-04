Installing VMS on your VAX
--------------------------------------------------------------------------------

### Preparation

The VAX/VMS installation process is guided and generally straightforward, but
before starting it will be helpful to prepare with a few things:
* The name of your installation device (CD-ROM, tape, etc.)
* The name of your target device to which VMS will be installed (hard disk)
* A *maximum* six character long hostname that will be used to identify the VAX
* *If installing TCP/IP services*: a static IP address you intend to assign to
  the VAX on your network
* A DECnet address consisting of an area number and a node number. DECnet
  addressing supports an area number range of 1-63 and a node range of 1-1023.
  If you are installing TCP/IP on your VAX, it's recommended to also use the 
  last octet of its static IP as its DECnet node number.
* A system ID computed from the DECnet address using the formula `A * 1024 + N`
  where `A` and `N` correspond to DECnet area and node numbers, respectively.

For the VAX used in this example, we will use the following parameters:

| Attribute           | Value       |
|---------------------|-------------|
| Installation device | `DKA400`    |
| Target device       | `DKA100`    |
| Hostname            | `NASHUA`    |
| TCP/IP address      | `10.0.0.40` |
| DECnet address      | `1.40`      |
| System ID           | `1064`      |

### Initial boot

After booting your VAX, the display or console should show a boot message,
usually the CPU type (in our case `KA48`) followed by self-test information.
Issue a **break** at this point and you will soon be dropped into the console,
with a `>>>` prompt showing on the screen.

From here, you can now find the boot device hosting the VMS install media by
issuing the command:

`                                SHOW DEVICE                                   `

...after which a table will be displayed of currently connected devices,
most importantly their names and types. Our VAX has an attached RRD42 CD-ROM
drive with the label `DKA400` and type `RODISK` that we will be booting from.

Now that we have determined `DKA400` to be our boot device, we can boot from
it by issuing the command:

`                                BOOT DKA400                                   `

...which will start booting the VMS image from the disk. 

### Installing VMS

Although I mentioned the VMS installation process is generally easy, that's not
to say it isn't *different*. The CDs themselves do not have any kind of guided
installer, but rather a *backup image* of a fresh VMS installation loaded on
them and an extremely lightweight copy of VMS with just the bare minimum of
tools needed to restore it. As such, once the CD boots you will be dumped into
a command prompt, from which you only need to run the following command:

`                   BACKUP DKA400:VMS061.B/SAVE_SET DKA100:                    `

...which kicks off the backup restore process in an automated fashion. Once it
is complete, reboot the system. Depending on the state of your VAX and how you
booted it from the installation CD immediately, you may need to re-enter the
console and change or otherwise manually boot from the hard disk. Our VAX
hard disk is `DKA100`.

After booting the newly imaged hard disk, the system will begin the installation 
process by asking for a label for the system volume it's worthwhile to give your 
system a unique volume label if you would like to configure it as part of a 
cluster. For NASHUA, the *volume label* is `NASHUA$SYS`.

The system will then ask for the name of the drive hosting the distribution
media, in NASHUA's case this is `DKA400`. The media is ready to be mounted.

For optional software, select all options *except* DECwindows support; as
NASHUA is running in a headless configuration, a graphical environment is
unneeded. After a few confirmation steps, the system will begin installing 
the selected options.

Once this step is complete, the installation procedure will begin setting up
the `SYSTEM`, `SYSTEST` and `FIELD` accounts. Provide an appropriate password
for at least `SYSTEM`, the other accounts can then be given randomized passwords 
as they will be disabled when setup is complete.

The system will now begin setting up DECnet starting by asking for the SCSNODE
name, which in this case is `NASHUA`. SCSNODE names can be only six characters
long.

Setup then asks for an SCSSYSTEMID, which for NASHUA is `1064`. This is
calculated from the formula `A * 1024 + N`, where A is the DECnet area and
N is the DECnet node number. For NASHUA we have chosen area `1` and the
last octet of the system's static IP address as the node number, `40`.

Finally, enter the system time zone information to complete the setup process.

--------------------------------------------------------------------------------

### Basic system setup: accounts, quotas, security

After installing the base system, it is recommended to perform some account
maintenance, this can be performed using the `AUTHORIZE` utility that can be
invoked with the following commands:

```DCL   

SET DEFAULT SYS$SYSTEM
RUN AUTHORIZE 

```

If successful, you should see a `UAF>` prompt.

#### Disabling special accounts

The first step involves disabling the accounts `SYSTEST` and `FIELD`,
which are special accounts intended to be used for verifying an OpenVMS
installation with the User Environment Test Package or for access by field
representatives, respectively. Since neither case applies much to a home
hobbyist-maintained system or a platform that has not been supported since
2013, these accounts can be safely disabled by applying the `DISUSER` flag
with the following command sequence:

```UAF

MODIFY SYSTEST/FLAGS=DISUSER
MODIFY FIELD/FLAGS=DISUSER

```

#### Setting new quotas and limits

As a multi-user system, VMS has many means of controlling access to resources
in order to ensure an appropriate service level for all users, the main methods
being *limits* and *quotas*. All accounts have these 16 limits and quotas:

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

The parameters of these quotas can be modified using the `AUTHORIZE` program.
In particular, we will want to adjust these values for the `SYSTEM` super-user,
to allow for the installation of certain demanding software packages.

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

Some of these limits have been raised significantly, but as NASHUA is expected
to have very low overall system load given its use case, it is not likely they 
will interfere with regular users.

--------------------------------------------------------------------------------

### Software stack and license loading

NASHUA features a rich software environment for terminal-driven computing with
many productivity and development tools, each of which must be licensed. The
following licenses will be needed prior to installing the remaining software:

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

### Creating new users

After all software has been installed and configured, you can now create new
user accounts with full integration using ALL-IN-1.
