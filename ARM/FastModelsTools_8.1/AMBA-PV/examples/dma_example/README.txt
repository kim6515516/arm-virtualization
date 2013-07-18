DMA example
-----------

This example illustrates the use of AMBA-PV amd the Signal API in a system comprising a simple DMA model programmed to perform transfers between 2 memories. Additionally, it illustrates the use of DMI for simulation performances optimisation.
This example comprises the following components:
- a simple testbench to program the DMA transfers
- an AMBA-PV bus decoder, class amba_pv_decoder, to route transactions between
  the components
- a simple DMA model, implementing a producer-consumer scheme and capable of
  using DMI for memory transfers
- two AMBA-PV memories, class amba_pv_memory.

The following environment variables have to be set:
SYSTEMC_HOME -> SystemC 2.2 installation
TLM_HOME     -> TLM 2.0 final kit installation

To build and run the DMA example, perform the following:

- Under Linux:
  1. make
  2. ./dma.x

- Under Windows:
  1. open dma_[VC2008|VC2010].[vcproj|vcxproj] with MSVC and build dma
     project, with Release configuration active
  2. dma.exe

You can observe the following trace from execution:

tb module created - 1 run
dma module created

Simulation starts...
DEBUG   dma: write 0 in DMA source address register
DEBUG   dma: write 0x3f00 in DMA destination address register
DEBUG   dma: write 0x100 in DMA length register
DEBUG   dma: write 0x1 in DMA control register
DEBUG   dma: DMA started
DEBUG   dma: DMA transfer started. Source address: 0 - destination address: 0x3f00 - length: 256 (bytes)
DEBUG   dma: source block (64 bytes) at 0:
        0x0: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x10: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x20: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x30: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
DEBUG   tb: DMA source address: 0
DEBUG   tb: DMA destination address: 0x3f00
DEBUG   tb: DMA length: 0x100
DEBUG   tb: DMA control: 0x1
DEBUG   dma: destination block (64 bytes) at 0x3f00:
        0x3f00: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x3f10: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x3f20: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x3f30: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
DEBUG   dma: source block (64 bytes) at 0x40:
        0x40: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x50: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x60: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x70: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
DEBUG   dma: destination block (64 bytes) at 0x3f40:
        0x3f40: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x3f50: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x3f60: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x3f70: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
DEBUG   dma: source block (64 bytes) at 0x80:
        0x80: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x90: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0xa0: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0xb0: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
DEBUG   dma: destination block (64 bytes) at 0x3f80:
        0x3f80: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x3f90: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x3fa0: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x3fb0: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
DEBUG   dma: source block (64 bytes) at 0xc0:
        0xc0: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0xd0: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0xe0: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0xf0: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
DEBUG   dma: destination block (64 bytes) at 0x3fc0:
        0x3fc0: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x3fd0: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x3fe0: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
        0x3ff0: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf: 0xdfdfdfdf
DEBUG   dma: rise transfer end IRQ 
DEBUG   dma: read DMA control register, returns 0x10
DEBUG   dma: write 0 in DMA control register
DEBUG   dma: clear transfer end IRQ 
Simulation ends

To run the DMA example with additional statistics over a giving number of
transfers, enter the following at the command line:

- Under Linux:
  1. ./dma.x 400000

- Under Windows:
  1. dma.exe 400000

You can observe the following trace from execution:

tb module created - 400000 runs
dma module created

Simulation starts...
Simulation ends

--- Simulation statistics: ---------------------------------------------
Total transactions executed : 4400000
Total KBytes transferred    : 210938
Total simulation time       : 18446744.000000 sec.
Real simulation time        : 10.200000 sec.
Transactions per sec.       : 431372.557
KBytes transferred per sec. : 20680.147
------------------------------------------------------------------------

To run the DMA example with DMI enabled, enter the following at the command
line:

- Under Linux:
  1. ./dma.x --dmi 400000

- Under Windows:
  1. dma.exe --dmi 400000

You can observe the following trace from execution:

tb module created - 400000 runs
dma module created

Simulation starts...
Simulation ends

--- Simulation statistics: ---------------------------------------------
Total transactions executed : 4400000
Total KBytes transferred    : 210938
Total simulation time       : 18446744.000000 sec.
Real simulation time        : 2.180000 sec.
Transactions per sec.       : 2018348.562
KBytes transferred per sec. : 96760.318
------------------------------------------------------------------------

NOTE: These figures are given here as examples they do not constitute any
      reference in terms of timing. They may vary according to the host
      configuration the example is running on.
      For information, those figures were obtained on a RedHat Entreprise 4,
      Intel 32bits, Linux 2.6.9 host.
