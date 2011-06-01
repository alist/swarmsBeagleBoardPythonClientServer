gcc -I . -c -fPIC driveLib.cpp -o libDrive.o
gcc -shared -Wl,-soname,libDrive.so.1 -o libDrive.so.1.0.1 libDrive.o
