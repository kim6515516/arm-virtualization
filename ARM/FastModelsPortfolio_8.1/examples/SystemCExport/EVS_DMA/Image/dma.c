/*
 * dma.c - DMA example's application.
 *
 * Copyright 2007, 2011-2012 ARM Limited.
 * All rights reserved.
 */

/* Includes */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* Typedefs */

typedef void (* handler_t)(void);

/* Globals */

#define JUMP_TABLE_BASE      0x00000000
#define HANDLER_TABLE_OFFSET 0x40

#define DMA_BASE_ADDRESS ((uint32_t *) 0x34004000)
static volatile uint32_t * SRC_ADDR = DMA_BASE_ADDRESS + 0;
static volatile uint32_t * DST_ADDR = DMA_BASE_ADDRESS + 2;
static volatile uint32_t * LENGTH = DMA_BASE_ADDRESS + 4;
static volatile uint8_t * CONTROL = (uint8_t *) (DMA_BASE_ADDRESS + 6);
static const uint8_t START = 0x01;
static const uint8_t IRQ = 0x10;
static volatile int end_transfer = 0;

/* Functions */

/* Compiler intrinsics */
extern void __enable_irq(void);
extern void __wfi(void);

#if defined(__TARGET_CPU_CORTEX_M3)
/*
 * Updates contents of 'vector' to contain address of 'handler'.
 */
static void install_handler(handler_t handler, uint32_t * vector) {
  (* (vector + (JUMP_TABLE_BASE / sizeof(uint32_t)))) = (uint32_t) handler;
}
#else   /* Assumes --cpu=6 or equivalent */
/*
 * Updates contents of 'vector' to contain LDR pc, [pc, #offset]
 * instruction to cause long branch to 'handler'.
 */
static void install_handler(handler_t handler, uint32_t * vector) {

    /* Updates contents of 'vector' to contain
     * LDR pc, [pc, #offset] instruction */
    (* (vector + (JUMP_TABLE_BASE / sizeof(uint32_t)))) =
        0xe59ff000 | (HANDLER_TABLE_OFFSET - 0x8);

    /* store address of 'handler' at a small fixed offset from the 'vector'
     * base */
    (* (vector + (HANDLER_TABLE_OFFSET / sizeof(uint32_t)))) =
        (uint32_t) handler;
}

/*
 * Setup a "small" stack for IRQ (and SVC).
 */
__asm void setup_irq_stack(void) {
    cps #0x12       ; Switch to IRQ mode
    mov r13, #0x800
    cps #0x13       ; Back to SVC mode
    bx r14
}
#endif  /* defined(__TARGET_CPU_CORTEX_M3) */

/*
 * IRQ handler.
 */
__irq void irq_handler(void) {
    if (! end_transfer) {
        uint8_t value = 0;

        /* Transfer done */
        printf("dma.c: irq_handler(): end of DMA transfer received\n");
        end_transfer = 1;

        /* Clears DMA interrupt */
        printf("dma.c: irq_handler(): clears DMA interrupt...\n");

        /* Read DMA control register */
        value = (* CONTROL);

        /* Clears the IRQ bit of the DMA control register */
        value &= ~IRQ;      
        (* CONTROL) = value;
    }
}

/*
 * Testbench process.
 */
static void run(void) {
    uint32_t value = 0;

    /*
     * Programs DMA transfer...
     */
    printf("dma.c: run(): programs DMA transfer...\n");

    /* Write DMA source address register */
    value = 0x20;
    (* SRC_ADDR) = value;

    /* Write DMA destination address register */
    value = 0x34002000;
    (* DST_ADDR) = value;

    /* Write DMA length register */
    value = 1024 /* bytes */;
    (* LENGTH) = value;

    /*
     * Starts DMA transfer...
     */
    printf("dma.c: run(): starts DMA transfer...\n");

    /* Start the DMA transfer (control register witdh is 8 bits, the write value
     * must be aligned before write) */
    end_transfer = 0;
    (* CONTROL) = START;

    /* Verification: read DMA control register (8 bits value) */
    value = (* CONTROL);

    /*
     * Waiting for end of DMA transfer
     */
    while (1) {
        if (end_transfer) {
            break;
        }
    }
    printf("dma.c: run(): end of DMA transfer\n");
}

/*
 * User's entry point.
 */
int main(void) {

    /* Initialisations  */
    printf("dma.c: main()\n");

    /* Installs IRQ handler */
#if defined(__TARGET_CPU_CORTEX_M3)
    install_handler((handler_t) irq_handler, (uint32_t *) 0x8);
#else   /* Assumes --cpu=6 or equivalent */
    setup_irq_stack();
    install_handler((handler_t) irq_handler, (uint32_t *) 0x18);
#endif

    /* Enables IRQ */
    __enable_irq();

    /* Initialize globals */
    end_transfer = 0;

    /* Single transfer */
    run();

#if defined(USE_WFI)
    /* Wait for interrupts */
    __wfi();
#endif
    exit(EXIT_SUCCESS);
    return EXIT_SUCCESS;
}
