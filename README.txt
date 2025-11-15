Qt GUI application to check passwords against a locally stored HaveIBeenPwned SQLite Database
---------------------------------------------------------------------------------------------

Build Requirements:

[Windows]
- Microsoft Visual Studio 2022
- Qt SDK 6.9.x / Qt Creator 18

This application can also convert a NTLM-hash text file to a SQLite database by running: hibp2sqlite
More information: https://github.com/BrainB0ne/hibp2sqlite or https://codeberg.org/BrainB0ne/hibp2sqlite

To obtain the NTLM-hash text file, use PwnedPasswordsDownloader from HaveIBeenPwned.

https://github.com/HaveIBeenPwned/PwnedPasswordsDownloader

Install PwnedPasswordsDownloader by following the instructions described on the link above.

Then, download all NTLM hashes to a single txt file called pwnedpasswords_ntlm.txt
haveibeenpwned-downloader.exe -n pwnedpasswords_ntlm

Menu -> Database -> Convert starts a conversion process with hibp2sqlite.

Caution!
Make sure there is enough free space on your drive since this file is at the time of writing ~70 GB.
The conversion to SQLite with hibp2sqlite takes another ~180 GB for the SQLite database file.

And last, but not least... Read the disclaimer below. :)

Disclaimer
* I'm not responsible for bricked devices, dead SD cards, thermonuclear war, or you getting fired because the alarm app failed.
* YOU are choosing to run these tools, and if you point the finger at me for messing up your device, I will laugh at you.
