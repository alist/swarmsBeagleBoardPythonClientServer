export LD_LIBRARY_PATH=.:LD_LIBRARY_PATH
gcc -I . -c -fPIC driveLib.cpp -o libDrive.o
gcc -shared -Wl,-soname,libDrive.so.1 -o libDrive.so.1.0.1 libDrive.o

ln -fs ./libDrive.so.1.0.1 ./libDrive.so.1
ln -fs ./libDrive.so.1 ./libDrive.so

