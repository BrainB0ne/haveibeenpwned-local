## Qt GUI application to check passwords against a locally stored HaveIBeenPwned SQLite Database

**Build Requirements:**

[Windows]

- Microsoft Visual Studio 2022
- Qt SDK 6.9.3 / Qt Creator 18

This application can also convert a NTLM-hash text file to a SQLite database by running: hibp2sqlite.

More information: [https://github.com/BrainB0ne/hibp2sqlite](<https://github.com/BrainB0ne/hibp2sqlite>) or [https://codeberg.org/BrainB0ne/hibp2sqlite](<https://codeberg.org/BrainB0ne/hibp2sqlite>)

To obtain the NTLM-hash text file, use PwnedPasswordsDownloader from HaveIBeenPwned.

[https://github.com/HaveIBeenPwned/PwnedPasswordsDownloader](<https://github.com/HaveIBeenPwned/PwnedPasswordsDownloader>)

Install PwnedPasswordsDownloader by following the instructions described on the link above.

Then, download all NTLM hashes to a single txt file called pwnedpasswords\_ntlm.txt

```batch
haveibeenpwned-downloader.exe -n pwnedpasswords_ntlm
```

_Menu -> Database -> Convert_ starts a conversion process with hibp2sqlite.

Note: Make sure hibp2sqlite.exe is located in the same folder as haveibeenpwned-local.exe if you want to use the Convert feature.

**Caution!**

Make sure there is enough free space on your drive since this file is at the time of writing \~70 GB.
The conversion to SQLite with hibp2sqlite takes another \~180 GB for the SQLite database file.

Credits to the author of the following article since it gave me the idea to create this tool.

[creating-a-local-version-of-the-haveibeenpwned-password-database-with-python-and-sqlite](<https://medium.com/analytics-vidhya/creating-a-local-version-of-the-haveibeenpwned-password-database-with-python-and-sqlite-918a7b6a238a> "creating-a-local-version-of-the-haveibeenpwned-password-database-with-python-and-sqlite")

**Icons**

Iconset: [Tabler Icons](<https://github.com/tabler/tabler-icons>) - [MIT License](<./images/tabler/LICENSE-ICONS>)

**Screenshots**

![haveibeenpwned-local-password-check.png](<./screenshots/haveibeenpwned-local-password-check.png>)

![haveibeenpwned-local-password-check-linux.png](<./screenshots/haveibeenpwned-local-password-check-linux.png>)

And last, but not least... Read the disclaimer below. :)

**Disclaimer**

- I'm not responsible for bricked devices, dead SD cards, thermonuclear war, or you getting fired because the alarm app failed.
- YOU are choosing to run these tools, and if you point the finger at me for messing up your device, I will laugh at you.

