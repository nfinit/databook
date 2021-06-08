Supporting multiuser SSH on the HP Media Vault
--------------------------------------------------------------------------------
For security reasons, the HP Media Vault and many other Marvell-based NAS 
systems do not permit non-root users to log in via SSH; such accounts are 
effectively disabled, lacking a specified home directory, login shell or 
password hash in `/etc/passwd`. To (likely) further protect against accidental 
or malicious tampering, the operating system completely rebuilds the password 
file during initialization sourcing from external configuration files, meaning 
any direct changes to the file to enable non-root SSH logins will be lost if 
the Media Vault is rebooted.

Although this may seem discouraging, the scripts responsible for this behavior
can be readily modified to permit multi-user SSH access to the system using
its native PHP API.
