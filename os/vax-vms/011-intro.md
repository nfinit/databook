The basic VAX/VMS 5.5 environment
--------------------------------------------------------------------------------

This guide assumes your VAX has been freshly set up with VAX/VMS 5.5-2H4 
similarly to our example system in the [installation guide](010-install.md), 
which is now cleanly set up to the point that it boots warning-free but lacks 
any kind ofessential application software, networking or further configuration.

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
list" of two separate directories:

```
$ SHOW LOGICAL SYS$SYSROOT
   "SYS$SYSROOT" = "DKA0:[SYS0.]" (LNM$SYSTEM_TABLE)
	= "SYS$COMMON:"
1  "SYS$COMMON" = "DKA0:[SYS0.SYSCOMMON.]" (LNM$SYSTEM_TABLE)
$ 
```

The `SHOW` command demonstrated above can be used to get the
value of any logical name along with a lot of other system variables,
such as for example your current default directory:

```
$ SHOW DEFAULT
  SYS$SYSROOT:[SYSMGR]
  =   SYS$SYSROOT:[SYSMGR]
  =   SYS$COMMON:[SYSMGR]
$ 
```

...or your current user (or any other) process:

```
$ SHOW PROCESS

11-MAY-2022 16:47:32.49   User: SYSTEM           Process ID:   00000113
                                                  Process name: "SYSTEM"

Terminal:           OPA0:
User Identifier:    [SYSTEM]
Base priority:      4
Default file spec:  SYS$SYSROOT:[SYSMGR]

Devices allocated:  OPA0:
$ 
```

...or *all* logical names currently defined on your VAX:

```
$ SHOW LOGICAL

(LNM$PROCESS_TABLE)

  "SYS$COMMAND" = "_OPA0:"
  "SYS$DISK" = "SYS$SYSROOT:"
  "SYS$ERROR" = "_OPA0:"
  "SYS$INPUT" = "_OPA0:"
  "SYS$OUTPUT" [super] = "_OPA0:"
  "SYS$OUTPUT" [exec] = "_OPA0:"
  "TT" = "OPA0:"

(LNM$JOB_809D7A50)

  "SYS$LOGIN" = "SYS$SYSROOT:[SYSMGR]"
  "SYS$LOGIN_DEVICE" = "SYS$SYSROOT:"
  "SYS$SCRATCH" = "SYS$SYSROOT:[SYSMGR]"

(LNM$GROUP_000001)

(LNM$SYSTEM_TABLE)

  "$CONSOLE" = "_OPA0:"
  "$DISK1" = "_DKA0:"
  "$TERMINAL0" = "_TTA0:"
  "$TERMINAL1" = "_TTA1:"
  "$TERMINAL2" = "_TTA2:"
  "ACP$BADBLOCK_MBX" = "MBA4:"
  "AGEN$IMAGES" = "SYS$MANAGER:VMS$IMAGES_MASTER.DAT"
  "DBG$INPUT" = "SYS$INPUT:"
  "DBG$OUTPUT" = "SYS$OUTPUT:"
  "DISK$BOSTON$SYS" = "DKA0:"
  "LIB$DT_FORMAT" = "LIB$DATE_FORMAT_001"
	= "LIB$TIME_FORMAT_001"
  "LIB$DT_INPUT_FORMAT" = "!DB-!MAAU-!Y4 !H04:!M0:!S0.!C2"
  "LMF$CHARGE_TABLE" = "SYS$COMMON:[SYSEXE]LMF$LURT.DAT"
  "LMF$LICENSE" = "SYS$COMMON:[SYSEXE]LMF$LICENSE.LDB"
  "MTHRTL" = "SYS$SHARE:UVMTHRTL.EXE"
  "OPC$OPCOM_STARTED" = "TRUE"
  "STARTUP$PHASES" = "SYS$STARTUP:VMS$PHASES.DAT"
  "STARTUP$STARTUP_LAYERED" = "SYS$STARTUP:VMS$LAYERED.DAT"
  "STARTUP$STARTUP_LIST" = "STARTUP$STARTUP_VMS"
	= "STARTUP$STARTUP_LAYERED"
  "STARTUP$STARTUP_VMS" = "SYS$STARTUP:VMS$VMS.DAT"
  "SYS$ANNOUNCE" = ".Welcome to VAX/VMS V5.5-2H4"
  "SYS$COMMON" = "DKA0:[SYS0.SYSCOMMON.]"
  "SYS$DECDTM_INHIBIT" = "YES"
  "SYS$DECDTM_NODE_ADDRESS" = "0"
  "SYS$DECDTM_NODE_NAME" = " "
  "SYS$DISK" = "DKA0:"
  "SYS$ERRORLOG" = "SYS$SYSROOT:[SYSERR]"
  "SYS$EXAMPLES" = "SYS$SYSROOT:[SYSHLP.EXAMPLES]"
  "SYS$HELP" = "SYS$SYSROOT:[SYSHLP]"
  "SYS$INSTRUCTION" = "SYS$SYSROOT:[SYSCBI]"
  "SYS$JOURNAL" = "SYS$COMMON:[SYSEXE]"
  "SYS$LANGUAGE" = "ENGLISH"
  "SYS$LIBRARY" = "SYS$SYSROOT:[SYSLIB]"
  "SYS$LOADABLE_IMAGES" = "SYS$SYSROOT:[SYS$LDR]"
  "SYS$MAINTENANCE" = "SYS$SYSROOT:[SYSMAINT]"
  "SYS$MANAGER" = "SYS$SYSROOT:[SYSMGR]"
  "SYS$MESSAGE" = "SYS$SYSROOT:[SYSMSG]"
  "SYS$MICROVAX" = "1"
  "SYS$PS_FONT_METRICS" = "SYS$COMMON:[SYSFONT.PS_FONT_METRICS.USER]"
	= "SYS$COMMON:[SYSFONT.PS_FONT_METRICS.SYSTEM]"
  "SYS$SHARE" = "SYS$SYSROOT:[SYSLIB]"
  "SYS$SPECIFIC" = "DKA0:[SYS0.]"
  "SYS$STARTUP" = "SYS$SYSROOT:[SYS$STARTUP]"
	= "SYS$MANAGER"
  "SYS$SYLOGIN" = "SYS$MANAGER:SYLOGIN"
  "SYS$SYSDEVICE" = "DKA0:"
  "SYS$SYSDISK" = "SYS$SYSROOT:"
  "SYS$SYSROOT" = "DKA0:[SYS0.]"
	= "SYS$COMMON:"
  "SYS$SYSTEM" = "SYS$SYSROOT:[SYSEXE]"
  "SYS$TEST" = "SYS$SYSROOT:[SYSTEST]"
  "SYS$TOPSYS" = "SYS0"
  "SYS$UPDATE" = "SYS$SYSROOT:[SYSUPD]"
  "TPU$DEFAULTS" = "SYS$LIBRARY:EVE"
  "TPU$JOURNAL" = "SYS$SCRATCH:"
  "TPU$SECTION" = "EVE$SECTION"

(DECW$LOGICAL_NAMES)

  "CDA$LIBRARY" = "SYS$COMMON:[CDA$LIBRARY]"
  "DECW$EXAMPLES" = "SYS$COMMON:[SYSHLP.EXAMPLES.DECW]"
  "DECW$INCLUDE" = "SYS$COMMON:[DECW$INCLUDE]"
  "DECW$SYSCOMMON" = "SYS$COMMON"
  "DECW$SYSTEM_DEFAULTS" = "SYS$COMMON:[DECW$DEFAULTS.USER]"
	= "SYS$COMMON:[DECW$DEFAULTS.SYSTEM]"
	= "SYS$LIBRARY:"
  "DECW$USER_DEFAULTS" = "SYS$LOGIN:"
  "DECW$XLIBERRDB" = "SYS$MESSAGE:DECW$XLIBERRDB.DAT"
  "UIL$INCLUDE" = "DECW$INCLUDE"
  "XDPS$EXAMPLES" = "SYS$SYSROOT:[SYSHLP.EXAMPLES.XDPS]"
  "XDPS$INCLUDE" = "SYS$SYSROOT:[XDPS$INCLUDE]"
$
```

...and much more.

Our final demonstration of `SHOW` also demonstrates the power of logical
names and their pervasive usage throughout VMS to define all kinds of
variables, such as `SYS$DECDTM_INHIBIT` which you may have previously
defined to disable DECdtm and its transaction log warnings at startup.

The use of logical names over raw paths and similar settings allows DCL
scripts and VMS software in general to be generally more portable over
a wider variety of system configurations, and are similar to environment
variables in Unix or Windows.
