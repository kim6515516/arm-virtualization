/*
 * SC: sc_sg_callbacks.h - SystemGenerator callback class 
 *
 * The confidential and proprietary information contained in this file may
 * only be used by a person authorised under and to the extent permitted
 * by a subsisting licensing agreement from ARM Limited.
 *
 * Copyright 2008 ARM Limited.
 * All rights reserved.
 *
 * This entire notice must be reproduced on all copies of this file
 * and copies of this file may only be made by a person if such person is
 * permitted to do so under the terms of a subsisting license agreement
 * from ARM Limited.
 */

#ifndef SG_SG_CALLBACKS__H
#define SG_SG_CALLBACKS__H

/* defines */
#define SG_MODE_INIT    0
#define SG_MODE_STOP    1
#define SG_MODE_RUN        2
#define SG_MODE_BPT        3

/*
 * SystemGenerator callbacks
 */
namespace sc 
{

    class sc_sg_callbacks
    {
    public:
        virtual ~sc_sg_callbacks(){};
        
// the callbacks
    public:
        virtual void start_of_quantum(int /* mode */){}; 
           /*Called by the EVS at the start of each quantum.
            *This default implementation does nothing.
            *mode - one of:
            *SG_MODE_INIT
            *SG_MODE_STOP
            *SG_MODE_RUN
            *SG_MODE_BPT */
        
        virtual void wait(double time, int mode);  
           /*Called by the EVS to synchronize with SystemC.
            *This default implementation calls sc_wait() with the
            *appropriate sc_time argument.
            *t - time to wait in seconds
            *mode - one of:
            *SG_MODE_INIT
            *SG_MODE_STOP
            *SG_MODE_RUN
            *SG_MODE_BPT*/ 
        virtual void proceed_quantum(int /* mode */){}; 
           /* Called by the EVS before continuing to execute the scheduler.
            *This default implementation does nothing.
            *mode - one of:
            *SG_MODE_INIT
            *SG_MODE_STOP
            *SG_MODE_RUN
            *SG_MODE_BPT */
        virtual void simulation_quit(int /* mode */ );
           /* Called by the EVS before simulation quits.
            *This default implementation calls sc_stop().
            *mode - one of:
            *SG_MODE_INIT
            *SG_MODE_STOP
            *SG_MODE_RUN
            *SG_MODE_BPT */
        virtual void simulation_stop(int /* mode */ ){};
           /* Called by the EVS after simulation stops, e.g. after application exit.
            *This default implementation does nothing.
            *mode - one of:
            *SG_MODE_INIT
            *SG_MODE_STOP
            *SG_MODE_RUN
            *SG_MODE_BPT */        
        virtual double get_global_quantum();
        /* Only to be used internally.
           Called during the update phase of a quantum
           Can be overrided to define own semantics of a quantum
        */
    };
    
};

#endif  /* defined(SG_SG_CALLBACKS__H) */
