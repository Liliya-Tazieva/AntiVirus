##PM Defender
###Short description:

PM defender is a project that is being made by 2nd year students of Saint-Petersburg State University. 
Faculty: Applied Mathematics and  Control Processes.

###Used libraries and frameworks:
Right now we are using PE-bliss for reading headers of PE-files and Qt.

###Navigation:
1)antivirus_src is a folder with the source files of all the modules. For each logical part of the antivirus we use separate Qt projects, they are fairly small and easy to work with, and it also helps to make the things work asynchronously.

2)dequarantinner_src is a folder that is storing the dequarantinner program. It is located apart from the other code because it is a separate program, which should be run independently when you need it.

3)deployment_files stores files needed for building and deployment, see "Building"

4)test_data contains things that you can use for testing. There are a folder with files containing Eicar-test-signature and a code that is playing a role of a virus attacking the "hosts" file.

###Building:
For building PM Defender you will need qt creator, source codes and the contents of "deployment_files" folder. 
Build every project with qt creator(scanner must be only compiled with "release" mode, you will also need pe_bliss.lib file from "deployment_files" to compile it), put them all in one folder, also put there files that are situated in "executables_folder" from "deployment_files". 
After all you just need inject manifest file from "deployment_files" and you are done.
 

###Installation and use
To install PM defender you can go to "Releases" folder, find the newest release and download an installer package. When you open it, just follow the instructions to get installation done.
For using instructions just click "know more" link in the main window of the installed antivirus.

###License:

The code is distributed under GNU lesser general public license.

