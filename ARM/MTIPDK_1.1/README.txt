========================================================================
Fast Models MTI Plugin Development Kit (MTI-PDK) 1.1 Release Notes
========================================================================

This confidential and proprietary software may be used only as
authorized by a licensing agreement from ARM Limited.

Copyright (c) 2008-2010 ARM(R) Limited
All rights reserved.

The entire notice above must be reproduced on all authorised copies
and copies may only be made to the extent permitted by a licensing
agreement from ARM Limited.

------------
General Note
------------

Version 1.1 of the Fast Models Plugin Development Kit (MTI-PDK) is an 
updated version of the MTI PDK for version 1 of the  Model Trace 
Interface. This is compatible with virtual platforms built with Fast 
Models  version 5.1 or later.

The version numbering of the Fast Models Plugin Development Kit has been
changed to be aligned to the version number of the Model Trace Interface.

---------------
Support contact
---------------

In case of questions please contact support-esl@arm.com.


========================================================================
README.txt contents:

  Platform requirements for Windows
  Platform requirements for Linux
  Overview
  Known limitations
  The example trace plugins

========================================================================

---------------------------------
Platform requirements for Windows
---------------------------------

When running Microsoft Windows XP or Vista it is recommended to use 
machines with at least 1GB RAM, and preferably at least 2GB for best 
performance. To use audio a 2GHz, or faster, Intel Core2Duo, or similar
performing, processor is recommended.

Operating system: 
Microsoft Windows XP and Vista (32-bit version).

Compiler:
Microsoft Visual Studio 2005 with Service Pack 1, or Visual Studio 2008
with Service Pack 1. 

Fast Model Portfolio does not contain the Microsoft Visual Studio 
2005sp1 or Microsoft Visual Studio 2008sp1 runtime libraries. If 
Microsoft Visual Studio 2005 is not installed, you must download
and install the Microsoft Visual C++ 2005 SP1 Redistribution Package to
run models on your workstation. Likewise, if Microsoft Visual Studio 
2008 SP1 is not installed, you must download and install the 
Microsoft Visual C++ 2008 SP1 Redistribution Package to run models on
your workstation. The service packages are available from the Microsoft
web site.

Note:

* ARM is planning to deprecate support for Windows Vista for the Fast 
  Models in the next release of Fast Models.
* ARM is planning to deprecate support for Windows Visual Studio 2005sp1 
  when support for Visual Studio 2010 is provided. This may be in the next 
  release of the Fast Models product. 
Please email support-esl@arm.com with any comments.

To view the documentation, Adobe Acrobat reader (Version 8 or higher) 
needs to be installed on the system.

In order to compile the example source code an existing Fast Models 
installation is required with the 'MAXCORE_HOME' environment variable 
pointing to the installation directory.

-------------------------------
Platform requirements for Linux
-------------------------------

When running on Linux it is recommended to use machines with at least 1GB
RAM, and preferably at least 2GB for best performance. To use audio a 2GHz,
or faster, Intel Core2Duo, or similar performing, processor is recommended.

Operating system: 
Red Hat Enterprise Linux 4 (on either 32 or 64 bit architecture)
Red Hat Enterprise Linux 5 (on either 32 or 64 bit architecture)

The following packages need to be installed:
Red Hat Enterprise Linux 4 (RHEL 4)
  - xorg-x11-devel (makedepend)
Red Hat Enterprise Linux 5 (RHEL 5)  
  - imake-1.0.2-3 (makedepend)

Compiler:
Fast Models 5.2 for Linux supports 
 - gcc 3.4.3, and 
 - gcc 4.1.2. (with binutils 2.1.17 installed)

Note:
* ARM is planning to deprecate support for gcc 3.4.3 and Red Hat Enterprise
  Linux 4 in a future release of the Fast Models product.
Please email support-esl@arm.com with any comments.

For machines supplying a  different compiler a separate GNU tool chain
package can be downloaded from the esl-support ftp server:
ftp://esl-support.arm.com/tools/gnu/binary/enterprise-linux/GNUToolchain_1-1-002_Linux.tgz

The gcc toolchain must be 32 bit, even if running on 64 bit architecture.

To view the documentation, Adobe Acrobat reader (Version 8 or higher) 
needs to be installed on the system.

In order to compile the example source code an existing Fast Models 
installation is required with the 'MAXCORE_HOME' environment variable 
pointing to the installation directory.

--------
Overview
--------

This is the MTI (Model Trace Interface) Plugin Development Kit (MTIPDK) 
1.1. It contains the MTI headers used to develop trace plugins for Fast 
Models, example plugin source code including Makefiles and Microsoft 
Visual Studio projects and documentation.

MTI plugins can be loaded by ModelShell or ModelDebugger version 5.2 or 
higher in order to extract trace sources from virtual platforms generated 
with Fast Models version 5.2 or higher.

In the following an overview of the package content will be given:

The folder 'doc' contains documentation on the MTI headers. Furthermore
a text file which provides the available MTI trace sources of an ARM 
Cortex-A8 model as listed by the ListTraceSources plugin is included.

The folder 'examples' contains source code of example plugins 
demonstrating aspects of MTI plugin implementations.

The folder 'include' contains the MTI header files.

-----------------
Known limitations
-----------------

- MTI trace sources for cache or TLB related events should be considered to 
  be of Beta quality.  These sources may change or be removed in future
  releases of Fast Models.

- Functional cache models are provided to assist in the development of
  software that manages caches. They will also provide a performance
  benefit in a system C environment that does not use DMI.
  
  The access patterns in the models, as seen by the cache, cannot be 
  regarded as representative of any particular device. Instruction
  accesses, in particular, are optimized for speed of the model and
  may not correlate well with access patterns seen with a hardware 
  implementation of a core. 

  Fast Models do not support Neon cache bypassing, as documented 
  in the Fast Model Portfolio Reference Manual. This means that
  such operations will have a different impact on the cache usage
  compared to a hardware implementation.

- If a store operation does not succeed due to a memory abort a CORE_STORES
  event will still be generated, when no such event should be generated. 
  However, CORE_LOADS events will only be generated for successful loads.
  (ARM DE721673)

- The events produced by M profile cores (ARM Cortex-M3 and M4)
  have the following limitations:
  - Changes of the xPSR register are currently reported via the CPSR
    event. The name may be changed in future releases.
    (ARM DE723213)
  - Trace events in the ARM Cortex-M3 and M4 models are currently
    incomplete. Future releases may add further events and may also remove
    or change the behaviour of the existing exception related events.
    (ARM DE722972)
 
-------------------------
The example trace plugins
-------------------------

There are a number of examples included in the MTIPDK. These will
demonstrate different aspects of programming plugins, with different
levels of complexity.

The examples are:

SimpleTraceExample:
-------------------
 This is the simplest possible trace plugin, showing how to do a simple
 trace of the instructions executed by tracing the "PC".


ListTraceSources:
-----------------
 This demonstrates how the available trace sources of a model can be
 queried. It is a programming example and also a useful tool to get a
 complete and self-documenting list of trace sources of a model.  The
 plugin will generate a "General Error" ON PURPOSE, to prevent the
 model from running.


GenericTraceExample:
--------------------
 This is a useful tool for experimenting to understand the trace
 events of a model. It allows comfortable configuration of which
 events should be traced into a text file (or to console) using a
 comma separated list of patterns. When using Model Debugger the trace
 configuration can be changed at run-time through editing a parameter.
 This is also a programming example showing the querying of trace
 sources, the registration/unregistering of callbacks, the
 implementation of run-time parameters, as well as the use of the
 DumpState() method.


RunTimeParameterTest:
---------------------
 This programming example shows how to implement run-time parameters
 in a trace plugin.


CacheStatistics:
----------------
 This is a full blown example demonstrating how to gather cache
 statistics using a combination of counters and callbacks. By avoiding
 certain trace events and substituting these by equivalent figures
 calculated from other counts, high performance is achieved.


LinuxSyscallTrace:
------------------
 This demonstrates the use of the DumpState() method to trace the
 arguments stored in registers of Linux system calls. It maintains
 high simulation performance by avoiding tracing all register events.


All examples are delivered in source form. In order to use them they first
need to be compiled. To compile the example code into a shared object
or DLL, change to the 'source' directory of the particular
example, for example:

/examples/ListTraceSources/source

Make sure to set the MTIPLUGINDEVKIT_HOME environment variable to the
location of the installation of the MTI Plugin Development Kit.

On Linux type 'make'. On Windows, start the Microsoft Visual Studio
solution 'ListTraceSources_2005.sln' and build.

A plugin can be loaded by ModelShell or ModelDebugger running a
model which supports MTI using the '--trace-plugin' option.  If you
execute

$MAXCORE_HOME/bin/model_shell -m <YOUR_MODEL> --trace-plugin ListTraceSources.so

under Linux, or

$MAXCORE_HOME/bin/model_shell.exe -m <YOUR_MODEL> --trace-plugin ListTraceSources.dll

under Windows, the plugin will print out the list of available MTI
trace sources of the model. Alternatively you can set the
FM_TRACE_PLUGINS environment variable to point to the trace plugin.

Date:  2013/04/19
Build: 1.1.86

Confidential 

==============================================================================
END
==============================================================================
