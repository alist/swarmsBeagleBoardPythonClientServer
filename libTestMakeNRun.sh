export LD_LIBRARY_PATH=.:LD_LIBRARY_PATH
g++ ./test/main.cpp -I . -o ./test/libTestExec -L. -lDrive
./test/libTestExec
