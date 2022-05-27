### Suppressing license warnings from the VisualAge C/C++ compilers

When attempting to compile a program using the VisualAge C/C++ compilers, you may
see the following message:

```
1506-507 (W) No licenses available. Contact your program supplier to add additional users. Compilation will proceed shortly.
```

Even if you have correctly enrolled licenses for VisualAge, for whatever reason
the compiler sometimes cannot contact a license server, generating this message
and slowing down compilation.

To suppress this message, you can use the `-qnolm` flag at compilation time, or
you can edit the VisualAge configuration file `/etc/vac.cfg` to automatically
use the flag by inserting it into the options line in the "common definitions"
section towards the end of the file.
