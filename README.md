USYD INFO1111 C++  Coding Challenge

a.out:
A macOS executable, it is currently not up to date. Is not optimized and containes some platform spesific bugs. The give solution for problem 2 converts "count --;" to "count-;" causing a syntax error that can be fixed by simply changing this before running the code against the test cases. The colours make it hard to see on this platform. 

Info:
Written in c++
wxWidgets is used to create this project, to compile it you must have is installed.
https://www.wxwidgets.org/downloads/

The makefile:
Is for Linux. Note that to compile from source on mac one must not include the headerfiles in the compile statement. Also it may be advised to use standardation flags such as -std=c++11.
Command: "make" to compile
Command "./Challenge_Linux" to run
Command: "make clean" to delete compiled files

Note on Sign In:
The logic for the sign in functionality had to be adjusted so that its contained within the main frame/window. This is due to extensive bugs when attempting to allow for interaction between seperate windows. It now works such that upon a successful log in, access to the rest of the application is granted.

Bugs:
The Save Code functionality has a few bugs:
1: Some chars such as \ or " may cause issues.
2: Upon a user returning their code is presented without any new-lines. Making for some effort to fix the code.
3: The Save Code button is only properly implemented for Problem 1. Using it on Problem 2 will result in issues.