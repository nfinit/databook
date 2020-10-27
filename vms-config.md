NTS OpenVMS VAX Configuration Notes
--------------------------------------------------------------------------------

### Initial boot and OpenVMS installation

After booting from `DKA400`, the following command will begin restoring the 
OpenVMS installation save set to the disk:

`                   BACKUP DKA400:VMS061.B/SAVE_SET DKA100:                    `

After restoration is complete, reboot the system from `DKA100`.

After booting, the system will begin the installation process by asking
for a label for the system volume it's worthwhile to give your system a unique 
volume label if you would like to configure it as part of a cluster. For HUDSON,
the *volume label* is `HUDSON$SYS`.

The system will then ask for the name of the drive hosting the distribution
media, in HUDSON's case this is `DKA400`. The media is ready to be mounted.

For optional software, select all options *except* DECwindows support; as
HUDSON is running in a headless configuration, a graphical environment is
unneeded. After a few confirmation steps, the system will begin installing 
the selected options.

Once this step is complete, the installation procedure will begin setting up
the `SYSTEM`, `SYSTEST` and `FIELD` accounts. Provide an appropriate password
for at least `SYSTEM`, the other accounts can then be given randomized passwords 
as they will be disabled when setup is complete.

The system will now begin setting up DECnet starting by asking for the SCSNODE
name, which in this case is `HUDSON`. SCSNODE names can be only six characters
long.

Setup then asks for an SCSSYSTEMID, which for HUDSON is `1064`. This is
calculated from the formula `A * 1024 + N`, where A is the DECnet area and
N is the DECnet node number. For HUDSON we have chosen area `1` and the
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

Some of these limits have been raised significantly, but as HUDSON is expected
to have very low overall system load given its use case, it is not likely they 
will interfere with regular users.

--------------------------------------------------------------------------------

### Software stack and license loading

HUDSON features a rich software environment for terminal-driven computing with
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
