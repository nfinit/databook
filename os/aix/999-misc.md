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
use the flag. To do this in Vi, simply open the file and run the following
substitution command:

```
:%s/options    = /options    = -qnolm,/g
```

This should add -qnolm to the flags automatically invoked by each VisualAge
compiler binary, suppressing the license check and allowing compilation to
occur without this warning or the associated slowdown.
