##Modules 
###Explanation:
The program is separated into four pieces.
The main is GUI, it can start Scanner and Real-time protection modules, Scanner in his turn can start Virus Window.
The names of non-GUI modules must be "Scanner.exe", "rtp_new.exe", "WhatToDoWithVirus.exe".
Scanner scans stuff with the methods passed as argv parameters(it can scan both files and folders), if he finds something, he launches Virus Window, that can delete and quarantine files on user demand.
Rtp module looks for changes in registry subkeys that handle autoruns and he also looks for "hosts" file changes. If some changes occure, he tells user about it and asks if he wants to inverse these changes.
