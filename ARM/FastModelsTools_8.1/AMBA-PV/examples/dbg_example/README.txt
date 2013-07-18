Debug Access example
--------------------

This example illustrates the use of AMBA-PV debug transfers between a master and
a slave.

The following environment variables have to be set:
SYSTEMC_HOME -> SystemC 2.2 installation
TLM_HOME     -> TLM 2.0 final kit installation

To build and run the Debug example, perform the following:

- Under Linux:
  1. make
  2. ./dbg.x

- Under Windows:
  1. open dbg_[VC2008|VC2010].[vcproj|vcxproj] with MSVC and build dbg
     project, with Release configuration active
  2. dbg.exe

You can observe the following trace from execution:

Simulation starts...
dbg_master: start of transfer()...
dbg_device: call to debug_write(), addr=0xf0000000

dbg_device: call to debug_read(), addr=0xf0000000

DEBUG   dbg_master: debug transaction block (0x10)
        0xf0000000: 0x33221100: 0x77665544: 0xbbaa9988: 0xffeeddcc
dbg_master: end of transfer()...
Simulation ends

