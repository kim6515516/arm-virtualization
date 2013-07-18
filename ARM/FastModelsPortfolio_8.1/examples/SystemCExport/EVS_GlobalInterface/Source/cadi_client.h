/*
 * cadi_client.h
 *
 * Copyright 2011-2013 ARM Limited.
 * All rights reserved.
 */

#ifndef CADI_CLIENT_H_
#define CADI_CLIENT_H_

void* cadi_thread_fxn(void* target_num_);

void connect(bool verbose);

void registers(bool verbose);
void registers_read();
void registers_write();
void registers_extended_feature();

void memory(void);
void memory_spaces();
void memory_read();

void callbacks(void);

void runcontrol(void);
void runcontrol_step();
void runcontrol_breakpoints(void);

void close(bool verbose);

const char* CADIReturnToString(eslapi::CADIReturn_t status);
#endif 

