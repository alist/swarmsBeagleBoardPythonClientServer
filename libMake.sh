export LD_LIBRARY_PATH=.:LD_LIBRARY_PATH
#gcc -I . -c -fPIC *.cpp -o libDrive.o
#gcc -shared -Wl,-soname,libDrive.so.1 -o libDrive.so.1.0.1 libDrive.o

g++ -fPIC -shared -I . *.cpp -o libDrive.so.1.0.1 -lusb

ln -fs ./libDrive.so.1.0.1 ./libDrive.so.1
ln -fs ./libDrive.so.1 ./libDrive.so

