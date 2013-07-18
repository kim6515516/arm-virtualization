Exclusive example
-----------------

This example illustrates the use of specific AMBA3 protocol control information
with exclusive accesses to a simple memory via exclusive access monitor.
It comprises the following components:
- a simple memory, class amba_pv_simple_memory
- an exclusive access monitor, class amba_pv_exclusive_monitor
- three masters competing for access to this memory, the first two ones
  perform exclusive accesses while the third performs regular accesses
- a bus decoder to route transactions from the masters to the exclusive access
  monitor, class amba_pv_decoder.
This example also features a PROBE version which includes an intermediate probe
component, class amba_pv_simple_probe, to print the contents of transactions
between the masters and the exclusive monitor.

The following environment variables have to be set:
SYSTEMC_HOME -> SystemC 2.2 installation
TLM_HOME     -> TLM 2.0 final kit installation

To build and run the Exclusive example, perform the following:

- Under Linux:
  1. make
  2. ./exclusive.x

- Under Windows:
  1. open exclusive_[VC2008|VC2010].[vcproj|vcxproj] with MSVC and build
     exclusive project, with Release configuration active
  2. exclusive.exe

You can observe the following trace from execution:

Simulation starts, 1 runs
master1.read(0x0, exclusive): 0x0
master2.read(0x0, exclusive): 0x0
master3.write(0x0, 0x12345678)
master2.write(0x0, 0x0, exclusive)
master2: exclusive access failed!
master1.write(0x0, 0x0, exclusive)
master1: exclusive access failed!
Simulation ends

To build and run the PROBE version of the example, perform the following:

- Under Linux:
  1. make clean
  2. make probe
  3. ./exclusive.x

- Under Windows:
  1. open exclusive_[VC2005|VC2008|VC2010].[vcproj|vcxproj] with MSVC and build
     exclusive project, with Probe configuration active
  2. exclusive.exe

You can observe the following trace from execution:

Simulation starts, 1 runs
probe: t=0 s read(addr=0, len=1, size=4, id=0x2, exclusive, {attr01=value01})
probe: t=0 s read(data=0x8238968): rsp=AMBA_PV_EXOKAY
probe: t=0 s read(addr=0, len=1, size=4, id=0x3, exclusive, {attr01=value01})
probe: t=0 s read(data=0x8228960): rsp=AMBA_PV_EXOKAY
probe: t=0 s write(addr=0, data=0x82188b0, len=1, size=4, id=0x6, {attr02=2})
probe: t=0 s write(): rsp=AMBA_PV_OKAY
probe: t=0 s write(addr=0, data=0x8228960, len=1, size=4, id=0x3, exclusive, {attr01=value01})
probe: t=0 s write(): rsp=AMBA_PV_OKAY
master2: exclusive access failed!
probe: t=0 s write(addr=0, data=0x8238968, len=1, size=4, id=0x2, exclusive, {attr01=value01})
probe: t=0 s write(): rsp=AMBA_PV_OKAY
master1: exclusive access failed!
Simulation ends

