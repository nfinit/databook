Installing VAX/VMS 5.5
--------------------------------------------------------------------------------

This guide covers a basic installation of VAX/VMS 5.5, the last VAX-only version
of VMS contemporary to the last and fastest new generation of VAX systems. 
VMS 5.x, not only historically "proper" for many of the more desirable VAXen 
among hobbyists, also has a rather rich base of first-party software available, 
making it a reasonable choice.

For this guide, we will be using a simulated VAXstation 4000 VLC in a headless
configuration.

### Initial boot

After booting the VAX, the display/console will show a boot string:
```
KA48-A V1.2-32B-V4.0
```
And begin a long memory test. During this process, issue a **break** and
you will soon be dropped into the console, with a `>>>` prompt showing on 
the screen.

From here, you can now find the boot device hosting the VMS install media by
issuing the command:
```
SHOW DEVICE
```
...after which a table will be displayed of currently connected devices:
```
  VMS/VMB      ADDR      DEVTYPE    NUMBYTES     RM/FX    WP    DEVNAM      REV
  -------      ----      -------    --------     -----    --    ------      ---
  ESA0         08-00-2B-A6-72-6F
  DKA0         A/0/0     DISK       219.15MB      FX            RZ24        4041
  DKA100       A/1/0     RODISK     205.50MB      RM      WP    RRD40       250D
  DKA200       A/2/0     RODISK     623.25MB      RM      WP    RRD40       250D
  DKA300       A/3/0     RODISK     623.25MB      RM      WP    RRD40       250D
  DKA400       A/4/0     RODISK     650.30MB      RM      WP    RRD40       250D
  DKA500       A/5/0     RODISK     623.25MB      RM      WP    RRD40       250D
 ..HostID..    A/6       INITR
```

On this table, RZ24 disk `DKA0` appears to be our target disk while, of a number of
connected RRD40 CD-ROM drives, `DKA100` hosts our installation media. We can now
boot from it with the command:
```
BOOT DKA100
```
...which will start booting the VMS image from the disk. 

### Installing VMS

Once the CD image is booted, you will be prompted to enter in a date and time
in `DD-MMM-YYYY HH:MM` format, for example `06-MAY-2022 16:30`. After entering
the time, VMS will then configure system devices... and drop you directly into
a command prompt.

Although I mentioned the VMS installation process is generally easy, that's not
to say it isn't *different*. The CDs themselves do not have any kind of guided
installer, but rather a backup image (or *save set*) of a fresh VMS installation 
loaded on them and an extremely lightweight copy of VMS with just the bare 
minimum of tools needed to restore it to disk, namely the `BACKUP` utility.

To use the `BACKUP` utility, you will need to know the filename of the save set.
This is usually provided by documentation, but if you don't have it you can
make an educated guess based on the version of VMS you're installing. VMS
save sets from personal experience tend to take the form 
`VMS[Suffix][Version].B`, meaning VAX/VMS 5.5-2H4's save set would have the name
`VMS2H4055.B` while OpenVMS 6.1, which has no suffix, would simply be 
`VMS061.B`. We're installing the former version on our system, so we'll issue
the command:
```
BACKUP DKA100:VMS2H4055.B/SAVE_SET DKA0:
```
...which kicks off the backup restore process in an automated fashion. Once it
is complete, reboot the system. Depending on the state of your VAX and how you
booted it from the installation CD immediately, you may need to re-enter the
console and change or otherwise manually boot from the hard disk. Recall that
our VAX hard disk is `DKA0`.

After booting the newly imaged hard disk, the system will begin the installation 
process by asking for a label for the system volume. If you intend to join your
VAX to a cluster in the future, a unique label (for example in the format
`[nodename]$SYS`) will be worthwhile, otherwise you leave it to the default.

The installation procedure will then ask for the name of the drive hosting 
the distribution media, which in our case is `DKA100`. 
The media is ready to be mounted.

For optional libraries and software, we can select all options, or ignore
DECwindows-related content if your VAX is expected to run headless.

Once the optional software installation is completed, the installation
procedure will ask if the system will be part of a cluster. 
For the moment, we will answer no.

The installation procedure will now begin setting up the `SYSTEM`, `SYSTEST` 
and `FIELD` accounts. Provide an appropriate password for at least `SYSTEM`, 
the other accounts can then be given randomized passwords as they will be 
disabled when setup is complete.

After account setup is complete, the installation procedure will ask if you
have any Product Authorization Keys to register. We will do this afterwards,
so you can answer no.

Finally, the system will reboot.

--------------------------------------------------------------------------------

## Setting up the system

Our post-installation boot of VAX/VMS will look a lot like this:

```
-DKA0
   VAX/VMS Version V5.5-2H4 Major version id = 1 Minor version id = 0


    ***************************************************************

    VAX/VMS V5.5-2H4

    You have SUCCESSFULLY installed the VMS operating system.

    The system is now executing the STARTUP procedure.  Please
    wait for the completion of STARTUP before logging in to the
    system.

    ***************************************************************

%STDRV-I-STARTUP, VMS startup begun at 10-MAY-2022 12:42:24.56

The VAX/VMS system is now executing the system startup procedure.

%%%%%%%%%%%  OPCOM  10-MAY-2022 12:42:36.18  %%%%%%%%%%%
Operator _OPA0: has been enabled, username SYSTEM

%%%%%%%%%%%  OPCOM  10-MAY-2022 12:42:36.18  %%%%%%%%%%%
Operator status for operator _OPA0:
CENTRAL, PRINTER, TAPES, DISKS, DEVICES, CARDS, NETWORK, CLUSTER, SECURITY,
LICENSE, OPER1, OPER2, OPER3, OPER4, OPER5, OPER6, OPER7, OPER8, OPER9, OPER10,
OPER11, OPER12

%%%%%%%%%%%  OPCOM  10-MAY-2022 12:42:36.20  %%%%%%%%%%%
Logfile has been initialized by operator _OPA0:
Logfile is SYS$SYSROOT:[SYSMGR]OPERATOR.LOG;1

%%%%%%%%%%%  OPCOM  10-MAY-2022 12:42:36.20  %%%%%%%%%%%
Operator status for operator SYS$SYSROOT:[SYSMGR]OPERATOR.LOG;1
CENTRAL, PRINTER, TAPES, DISKS, DEVICES, CARDS, NETWORK, CLUSTER, SECURITY,
LICENSE, OPER1, OPER2, OPER3, OPER4, OPER5, OPER6, OPER7, OPER8, OPER9, OPER10,
OPER11, OPER12

%%%%%%%%%%%  OPCOM  10-MAY-2022 12:42:36.37  %%%%%%%%%%%
Message from user AUDIT$SERVER
Security alarm (SECURITY) and security audit (SECURITY), system id: 65534
Auditable event:        Audit server starting up
Event time:             10-MAY-2022 12:42:36.35

%SET-I-NEWAUDSRV, identification of new audit server process is 00000108
%%%%%%%%%%%  OPCOM  10-MAY-2022 12:42:36.48  %%%%%%%%%%%
Message from user JOB_CONTROL
%JBC-E-OPENERR, error opening SYS$COMMON:[SYSEXE]QMAN$MASTER.DAT;

%%%%%%%%%%%  OPCOM  10-MAY-2022 12:42:36.48  %%%%%%%%%%%
Message from user JOB_CONTROL
-RMS-E-FNF, file not found

%LICENSE-F-EMTLDB, license database contains no license records
%%%%%%%%%%%  OPCOM  10-MAY-2022 12:42:38.75  %%%%%%%%%%%
Message from user SYSTEM
%LICENSE-E-NOAUTH, DEC VAX-VMS use is not authorized on this node
-LICENSE-F-NOLICENSE, no license is active for this software product
-LICENSE-I-SYSMGR, please see your system manager


%LICENSE-E-NOAUTH, DEC VAX-VMS use is not authorized on this node
-LICENSE-F-NOLICENSE, no license is active for this software product
-LICENSE-I-SYSMGR, please see your system manager
Startup processing continuing...

%%%%%%%%%%%  OPCOM  10-MAY-2022 12:42:38.82  %%%%%%%%%%%
Message from user SYSTEM
Warning: DECdtm log file not found (SYS$JOURNAL:SYSTEM$.LM$JOURNAL)
        %RMS-E-FNF, file not found
        TP server process waiting



The VAX/VMS system is now executing the site-specific startup commands.

%SET-I-INTSET, login interactive limit = 64, current interactive value = 0
  10-MAY-2022 12:42:39
  SYSTEM       job terminated at 10-MAY-2022 12:42:41.10

  Accounting information:
  Buffered I/O count:            1214         Peak working set size:     807
  Direct I/O count:               582         Peak page file size:      3344
  Page faults:                   3882         Mounted volumes:             0
  Charged CPU time:           0 00:00:02.19   Elapsed time:     0 00:00:17.02

```

There are a few errors to resolve, but of primary interest to start are
the licensing-related messages

```
%LICENSE-F-EMTLDB, license database contains no license records
%%%%%%%%%%%  OPCOM  10-MAY-2022 12:42:38.75  %%%%%%%%%%%
Message from user SYSTEM
%LICENSE-E-NOAUTH, DEC VAX-VMS use is not authorized on this node
-LICENSE-F-NOLICENSE, no license is active for this software product
-LICENSE-I-SYSMGR, please see your system manager
```

With this in mind, log on to the `SYSTEM` account using the new password
you gave it and begin our first step...

### Licensing your system

VAX/VMS and the software that ran on it was fairly expensive, and Digital
took licensing quite seriously. To this end, the operating system includes
a fairly extensive, centralized `License Management Facility` (LMF) unlike 
that found even on many modern operating systems. Most commercial VMS 
applications require a license to be registered in the LMF database to
install or run, including the operating system itself, which you may
have noticed was throwing license warnings and booting into a single-user
mode after installation.

In the heyday of the VAX, software licenses were distributed as physical
certificates known as *Product Authorization Keys* (PAKs). PAKs document
license information of importance to both humans and the machine,
including start and expiration dates, vendor information and an
"authorization code" generated as a function of that information. From
personal experience, the most basic valid PAK is composed of an 
authorization checksum, product code and a producer.

Although VMS PAKs can be priced quite steeply for commercial customers,
Digital and its successors have consistently maintained a hobbyist
program for VMS allowing home users to use and learn the operating
system for free, though it's unfortunately quite complicated for
the VAX, as the latest of VMS' developers, VMS Software Inc, is
no longer able to issue VAX software licenses for VMS or any
former first-party Digital products. To this end, one will have
to turn to grey area solutions if they are unable to acquire PAKs
in any other way.

#### Loading licenses

For our freshly installed VAX/VMS system, we will need to load
a license for `VAX-VMS`, produced by `DEC`.

Once you have a valid PAK on hand, obtained or 
[generated](../../prog/c/pakgen.c), you must first register it
into the database, which can be done with the `LICENSE` utility:

```DCL
LICENSE REGISTER <product code> /PRODUCER=<producer code> /CHECKSUM=<checksum>
```

Once you have performed this action for all needed products,
simply load them with the command:

```DCL
LICENSE LOAD <product code>
```

After all licenses are registered and loaded, reboot VMS, and you will now have a fully functional system.

### Disabling unused accounts

Next, we should secure the machine a little bit by disabling the unnecessary accounts `SYSTEST` 
and `FIELD` which are intended for field service and advanced system testing, neither of which
neatly apply to a modern-day hobbyist system. To do this we will have to use the `AUTHORIZE` utility 
to edit the User Authorization File. The utility is located in the `SYS$SYSTEM` directory and can be 
invoked with the following commands:

```DCL   

SET DEFAULT SYS$SYSTEM
RUN AUTHORIZE 

```

If successful, you should see a `UAF>` prompt.

From here, we will modify the UAF records of these accounts to set the `DISUSER` flag to prevent
logins with their credentials:

```UAF

MODIFY SYSTEST/FLAGS=DISUSER
MODIFY FIELD/FLAGS=DISUSER

```
As you perform these tasks, you will see OPCOM messages noting the record modification:

```
%%%%%%%%%%%  OPCOM  10-MAY-2022 13:25:15.50  %%%%%%%%%%%
Message from user AUDIT$SERVER
Security alarm (SECURITY) and security audit (SECURITY) on , system id: 65534
Auditable event:        System UAF record modification
Event time:             10-MAY-2022 13:25:15.50
PID:                    0000010C        
Username:               SYSTEM          
Image name:             DKA0:[SYS0.SYSCOMMON.][SYSEXE]AUTHORIZE.EXE
Object name:            SYS$COMMON:[SYSEXE]SYSUAF.DAT;1
Object type:            file
User record modified:   FIELD
Fields modified:        FLAGS
```

Once both accounts are disabled, you can `exit` UAF.

### Initializing queues

Our next set of OPCOM error messages come from the `JOB_CONTROL`
user:

```
%%%%%%%%%%%  OPCOM  10-MAY-2022 12:42:36.48  %%%%%%%%%%%
Message from user JOB_CONTROL
%JBC-E-OPENERR, error opening SYS$COMMON:[SYSEXE]QMAN$MASTER.DAT;

%%%%%%%%%%%  OPCOM  10-MAY-2022 12:42:36.48  %%%%%%%%%%%
Message from user JOB_CONTROL
-RMS-E-FNF, file not found
```

These concern the queue manager, which currently has no queue
database. We can remedy this by starting the queue manager
manually and instructing it to create a new database file:

```DCL
START/QUEUE/MANAGER/NEW_VERSION
```

...after which you should see the following OPCOM message:

```
%%%%%%%%%%%  OPCOM  10-MAY-2022 14:23:30.45  %%%%%%%%%%%
Message from user JOB_CONTROL
%JBC-I-CREATED,  created
```

Now that `QMAN$MASTER.DAT` has been created, you should
no longer job control error messages during the startup
process.

### Disabling DECdtm

The last OPCOM message to resolve is a warning from `SYSTEM`:

```
%%%%%%%%%%%  OPCOM  10-MAY-2022 14:28:04.29  %%%%%%%%%%%
Message from user SYSTEM
Warning: DECdtm log file not found (SYS$JOURNAL:SYSTEM$.LM$JOURNAL)
        %RMS-E-FNF, file not found
        TP server process waiting
```

DECdtm is a Distributed Transaction Manager designed mainly to
help ensure integrity and consistency of transactions between
multiple resources, especially in VAX cluster environments. In
order for DECdtm and applications using it (such as Rdb) to
function properly, DECdtm requires a log file to record
transactions to, named `SYS$JOURNAL:SYSTEM$node.LM$JOURNAL`
where `node` corresponds to the DECnet node name of your VAX.

We can create a transaction log using the Log Manager Control
Program `LCMP`, run using the following command:
```
RUN SYS$SYSTEM:LCMP
```
After which you will see an `LCMP>` prompt.

From here, you can create the file with the command:
```
CREATE LOG SYS$JOURNAL:SYSTEM$[node].LM$JOURNAL
```

Once the log file is created, `REBOOT` the VAX.
