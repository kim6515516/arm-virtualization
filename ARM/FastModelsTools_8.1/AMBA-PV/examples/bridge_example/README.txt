Bridge example
--------------

This example illustrates bridging to and from the OSCI TLM BP using
amba_pv_to_tlm_bridge and amba_pv_from_tlm_bridge classes. It is based on the
Exclusive example and features:
- a simple memory, class amba_pv_simple_memory
- an exclusive access monitor, class amba_pv_exclusive_monitor
- two masters competing for access to this memory, the first one performing
  exclusive accesses while the second performs regular accesses
- an amba_pv_to_tlm_bridge - amba_pv_from_tlm_bridge bridges chain inserted
  between the masters and the memory
- a bus decoder, class amba_pv_bus_decoder, to route transactions from the
  masters to the exclusive access monitor.

The following environment variables have to be set:
SYSTEMC_HOME -> SystemC 2.2 installation
TLM_HOME     -> TLM 2.0 final kit installation

To build and run the Bridge example, perform the following:

- Under Linux:
  1. make
  2. ./bridge.x

- Under Windows:
  1. open bridge_[VC2008|VC2010].[vcproj|vcxproj] with MSVC and build
     bridge project, with Release configuration active
  2. bridge.exe

You can observe the following trace from execution:

Simulation starts, 1 runs
master1.read(0x0, exclusive): 0x0
master2.write(0x0, 0x12345678)
master1.write(0x0, 0x0, exclusive)
master1: exclusive access failed!
Simulation ends

