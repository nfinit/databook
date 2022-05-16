The VAX/VMS 5.5 environment
--------------------------------------------------------------------------------

This guide assumes your VAX has been freshly set up with VAX/VMS 5.5-2H4 
similarly to our example system in the [installation guide](010-install.md), 
which is now cleanly set up to the point that it boots warning-free but lacks 
any kind of essential application software, networking or further 
configuration.

### DCL: the VMS shell

Now that you've logged into the `SYSTEM` account of your clean installation,
you're greeted with a familiar sight: a shell

```
        Welcome to VAX/VMS version V5.5-2H4
    Last interactive login on Wednesday, 11-MAY-2022 15:01
$ 
```

But as you may have found out if you tried some commands you already
know from other operating systems you've used, this is no `bash` or `ksh` 
clone, rather it's DCL, VMS' proprietary command language. Just as capable as
any other shell scripting language, but with some very different ways of 
doing things.

One command that isn't so different, however, is the `DIRECTORY` command that,
like most other DCL commands, have a shorthand form: `DIR`

```
$ DIR

Directory SYS$SYSROOT:[SYSMGR]

OPERATOR.LOG;8      SYLOGICALS_COM.TPU$JOURNAL;1            
SYLOGIN_COM.TPU$JOURNAL;1               VMSIMAGES.DAT;1     

Total of 4 files.

Directory SYS$COMMON:[SYSMGR]

ALFMAINT.COM;1      AUDIT_SERVER.DAT;1  CLUSTER_CONFIG.COM;3
DBLSTRTUP.COM;1     DECW$CHECK_PARAMS.COM;1                 DECW$DEVICE.COM;11 
DECW$LOGICALS.COM;1 DECW$STARTLIBS.COM;1                    DECW$STARTUP.COM;1 
DECW$STARTXTERMINAL.COM;1               DNS$CHANGE_DEF_FILE.COM;1
DNS$CLIENT_STARTUP.COM;1                DNS$CLIENT_STOP.COM;1
EDTINI.TEMPLATE;1   LAT$SYSTARTUP.COM;1 LAT$SYSTARTUP.TEMPLATE;1
LIB$DT_STARTUP.COM;1                    LOADNET.COM;1       LOGIN.COM;1        
LOGIN.TEMPLATE;1    LPA11STRT.COM;1     LTLOAD.COM;1        MAKEROOT.COM;1     
NETCONFIG.COM;3     RTTLOAD.COM;1       SECURITY_AUDIT.AUDIT$JOURNAL;1
SMISERVER.COM;1     STARTNET.COM;1      SYCONFIG.COM;1      SYCONFIG.TEMPLATE;1
SYLOGICALS.COM;5    SYLOGICALS.COM;4    SYLOGICALS.COM;3    SYLOGICALS.COM;2   
SYLOGICALS.COM;1    SYLOGICALS.TEMPLATE;1                   SYLOGIN.COM;1      
SYLOGIN.TEMPLATE;1  SYPAGSWPFILES.COM;1 SYPAGSWPFILES.TEMPLATE;1
SYSECURITY.COM;1    SYSECURITY.TEMPLATE;1                   SYSHUTDWN.COM;1    
SYSHUTDWN.TEMPLATE;1                    SYSTARTUP_V5.COM;1  
SYSTARTUP_V5.TEMPLATE;1                 TFF$STARTUP.COM;1   
VMS$IMAGES_MASTER.DAT;3                 VMSIMAGES.DAT;1     WELCOME.TEMPLATE;1 
WELCOME.TXT;1       

Total of 51 files.

Grand total of 2 directories, 55 files.
$ 
```

Like on other systems, `DIR` without qualifiers will simply give you a
list of files in your current directory, which in VMS is known as the 
*default* directory.

You may also notice that your `DIR` command actually produced a listing
for *two* directories, that's because your starting default directory
is not an actual directory but a *logical name* pointing to a "search
list" of two separate directories. Logical names are a powerful feature
of VMS used similarly to environment variables on Unix and Windows, and
we will discuss them a bit more later. For now, let's continue on
with system navigation.

You may have noticed that VMS does not recognize the Unix/Windows staple
`cd` command for changing directories, nor is there an obvious counterpart.
In VMS, you instead use the `SET` command to set a new default directory, in
the format `SET DEFAULT <directory>`.

VMS directory notation is a bit different from any major modern operating
system, taking the format '[directory.subdirectory]' with an optional
'DEVICE:' prefix similar to what is found on MS-DOS or Windows. Thus,
if we want to change our default directory to the root of our system disk
`DKA0`, we will issue the command:

```
SET DEFAULT DKA0:[000000]
```

`[000000]` is is the *master file directory*, also known as the top or
root directory of a given volume.

```
$ DIR

Directory DKA0:[000000]

000000.DIR;1        BACKUP.SYS;1        BADBLK.SYS;1        BADLOG.SYS;1       
BITMAP.SYS;1        CONTIN.SYS;1        CORIMG.SYS;1        INDEXF.SYS;1       
SYS0.DIR;1          SYSEXE.DIR;1        VMS$COMMON.DIR;1    VOLSET.SYS;1       

Total of 12 files.
$ 
```

### Directories and files

The master directory of the system disk contains a number of `.SYS`
files, all created by VMS to help manage the volume:

* `BACKUP.SYS`: The volume backup log file
* `BADBLK.SYS`: The bad block file, recording bad blocks on the volume 
                to keep the system from attempting to use them. 
* `BADLOG.SYS`: The pending bad block file, recording *suspected* bad 
                blocks on the volume.
* `BITMAP.SYS`: The bitmap file, keeping track of available space on the
                volume and helps optimize its usage.
* `CONTIN.SYS`: The continuation file, used to keep track of files that
                extend across multiple volumes in a "volume set".
* `CORIMG.SYS`: The core image file, not used by the operating system.
* `INDEXF.SYS`: The index file, recording the headers of every file on the
                volume.
* `VOLSET.SYS`: The volume set list file, only present on the first volume
                in a volume set, which contains a list of all volume labels
                in the set.

Also present in the master directory are a number of subdirectories:

* `000000`: The master directory itself
* `SYS0`: Operating system files
* `SYSEXE`: Stores only the boot program (`SYSBOOT.EXE`) and `INSTALL.KIT`.
* `VMS$COMMON`: Common cluster files

Of particular interest is the `SYS0` directory:

```
$ SET DEFAULT [.SYS0]
$ DIR

Directory DKA0:[000000.SYS0]

MOM$SYSTEM.DIR;1    SYS$LDR.DIR;1       SYS$STARTUP.DIR;1   SYSCBI.DIR;1       
SYSCOMMON.DIR;1     SYSERR.DIR;1        SYSEXE.DIR;1        SYSHLP.DIR;1       
SYSLIB.DIR;1        SYSMAINT.DIR;1      SYSMGR.DIR;1        SYSMSG.DIR;1       
SYSTEST.DIR;1       SYSUPD.DIR;1        

Total of 14 files.
$ 
```
