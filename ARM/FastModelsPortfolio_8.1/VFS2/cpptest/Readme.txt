Bare Metal C++ example and tests
--------------------------------

1/4/08 - Initial C++ version derived from C version

These files demonstrate how to use the vfs model from a bare metal implementation. 
They can be compiled with armcc (and maybe gcc) using

armcc -o test.axf -I../C messagebox.cpp vfs.cpp test.cpp

The test expects to run with the VFS device located at 0x10042000 in the cpu address
space (it fits into a gap in the FVP EmulationBaseboard example model.

Todo
----

- Lots! the tests are enough to prove that basic file operations work
