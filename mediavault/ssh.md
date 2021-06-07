Hacking multi-user SSH onto the second-gen HP Media Vault
--------------------------------------------------------------------------------
As a network appliance, the HP Media Vault wasn't really designed to be remotely
accessed for anything other than administrative tasks, and as such does not
readily allow non-root users to log in to the system via SSH.

New users created through the Media Vault's web interface are given what are
effectively dummy Linux accounts to enable access through SMB and other
protocols, such as FTP. These accounts do not have home directories, login
shells or even passwords specified in `/etc/passwd`, this is done for security 
purposes. While this is easy enough to fix from a root shell, the changes
do not persist across reboots. Every time the Media Vault loses power or
otherwise must restart, `/etc/passwd` appears to revert back to its original
state.

After a bit of digging through key locations, mainly `/etc/init.d` and
`/etc/inc`, it turns out that `/etc/passwd` isn't merely reverted at
boot, rather it is entirely re-created during the init process, meaning
any customizations to users are completely lost and replaced with the
default, unusable configuration.

As the Media Vault is a fairly nice system for experimentation and development
with a package manager installed, this was quite dissappointing, and I set
out to find a solution.
