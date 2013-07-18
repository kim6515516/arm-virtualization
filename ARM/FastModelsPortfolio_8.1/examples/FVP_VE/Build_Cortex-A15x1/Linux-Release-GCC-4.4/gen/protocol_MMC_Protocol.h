/*
 * 
 *
 * This is an automatically generated file. Do not edit.
 *
 * Copyright 2007 ARM Limited.
 * Copyright 2011 ARM Limited.
 *
 * All rights reserved.
 */

/** \file
 * Abstract interface class protocol_MMC_Protocol for protocol MMC_Protocol.
 */

#ifndef protocol_MMC_Protocol_h_
#define protocol_MMC_Protocol_h_

// Includes from the 'includes' section of this protocol
#line 20 "/home/sxcheng/Workspace/kvm/ARM/FastModelsPortfolio_8.1/LISA/MMC_Protocol.lisa"

        typedef enum {
            // Basic and Read stream commands (Class 0 & Class 1)
            MMC_GO_IDLE_STATE        = 0,
            MMC_SEND_OP_COND         = 1,
            MMC_ALL_SEND_CID         = 2,
            MMC_SET_RELATIVE_ADDR    = 3,
            MMC_SET_DSR              = 4,
            MMC_CMD5                 = 5, // reserved
            MMC_SWITCH               = 6,
            MMC_SELDESL_CARD         = 7,
            MMC_SEND_EXT_CSD         = 8,
            MMC_SEND_CSD             = 9,
            MMC_SEND_CID             = 10,
            MMC_READ_DAT_UNTIL_STOP  = 11,
            MMC_STOP_TRANSMISSION    = 12,
            MMC_SEND_STATUS          = 13,
            MMC_BUSTEST_R            = 14,
            MMC_GO_INACTIVE_STATE    = 15,
            MMC_BUSTEST_W            = 19,

            // Block oriented read commands (Class 2)
            MMC_SET_BLOCKLEN         = 16,
            MMC_READ_SINGLE_BLOCK    = 17,
            MMC_READ_MULTIPLE_BLOCK  = 18,

            // Stream write commands (Class 3)
            MMC_WRITE_DAT_UNTIL_STOP = 20,
            MMC_CMD21                = 21, // reserved
            MMC_CMD22                = 22, // reserved

            // Block oriented write commands (Class 4)
            MMC_SET_BLOCK_COUNT      = 23,
            MMC_WRITE_BLOCK          = 24,
            MMC_WRITE_MULTIPLE_BLOCK = 25,
            MMC_PROGRAM_CID          = 26,
            MMC_PROGRAM_CSD          = 27,

            // Block oriented write protection commands (Class 6)
            MMC_SET_WRITE_PROT       = 28,
            MMC_CLR_WRITE_PROT       = 29,
            MMC_SEND_WRITE_PROT      = 30,
            MMC_CMD31                = 31, // reserved

            // Erase commands (Class 5)
            MMC_CMD32                = 32, // reserved & unused to preserve
            MMC_CMD33                = 33, // backwards compatibility
            MMC_CMD34                = 34, // with older MMC versions
            MMC_ERASE_GROUP_START    = 35,
            MMC_ERASE_GROUP_END      = 36,
            MMC_CMD37                = 37, // reserved - as above
            MMC_ERASE                = 38,

            // I/O mode commands (Class 9)
            MMC_FAST_IO              = 39,
            MMC_GO_IRQ_STATE         = 40,
            MMC_CMD41                = 41, // reserved

            // Lock card (Class 7)
            MMC_LOCK_UNLOCK          = 42,
            MMC_CMD43                = 43, // reserved
            MMC_CMD44                = 44, // reserved
            MMC_CMD45                = 45, // reserved
            MMC_CMD46                = 46, // reserved
            MMC_CMD47                = 47, // reserved
            MMC_CMD48                = 48, // reserved
            MMC_CMD49                = 49, // reserved
            MMC_CMD50                = 50, // reserved
            MMC_CMD51                = 51, // reserved
            MMC_CMD52                = 52, // reserved
            MMC_CMD53                = 53, // reserved
            MMC_CMD54                = 54, // reserved

            // Application specific commands (Class 8)
            MMC_APP_CMD              = 55,
            MMC_GEN_CMD              = 56,
            MMC_CMD57                = 57, // reserved
            MMC_CMD58                = 58, // reserved
            MMC_CMD59                = 59, // reserved
            MMC_CMD60                = 60, // reserved by manufacturer
            MMC_CMD61                = 61, // as above
            MMC_CMD62                = 62, // as above
            MMC_CMD63                = 63, // as above
        } mmc_cmd_t;

        // The response can be
        // - R1:       (mirrored command and status)
        // - R2:       CID / CSD
        // - R3:       OCR register
        // - R4 or R5: RCA
        // ... or none
        typedef enum {
            MMC_RNONE   = 0,
            MMC_R32     = 32,  // 32-bit response
            MMC_R128    = 128, // CSR or CID (128-bit)
            MMC_RERROR  = 255,
        } mmc_resp_t;

        // Other response information:

        // The OCR is returned as a uint32_t:
        //   - bit     31 Power up status [0=Busy, 1=Ready]
        //   - bits 30:24 reserved
        //   - bits  8:23 [1 | 0] for each voltage from 2.0 to 3.6
        //                in 0.1v increments. E.g. bit 8=1 means the
        //                card supports 2.0-2.1v, bit 23: 3.5-3.6v
        //   - bits  7: 0 reserved
        typedef uint32_t mmc_ocr_resp_t;  // r3

        // The status bits are currently defined with the card implementation
        // (Though they're pretty generic)
        typedef uint32_t mmc_status_t;    // r1

        // Response type for the Card ID and the Card Specific Data Registers
        // Generic for transport - actual formats will depend on the card
        typedef struct {
            uint32_t   cxd[4];           // 128 bits of card ID.
        } mmc_cxd_resp_t;                // r2


        // RCA (relative card address register)
        // (note this is 16 bits on the hardware - we zero the MSBs)
        typedef uint32_t mmc_rca_t;

        // DSR (driver stage register)
        // (note this is 16 bits on the hardware - we zero the MSBs)
        typedef uint32_t mmc_dsr_t;

        // This is what a SWITCH argument looks like
        // Note SWITCH (CMD6) is not supported by MMC 3.3, but is by 4.x,
        // and SD 1.1, SD 2.0.
        typedef struct {
            uint32_t res1:5;   // bits 31:26 are reserved
            uint32_t access:2; // bits 25:24
            uint32_t index:8;  // bits 23:16
            uint32_t value:8;  // bits 15:8
            uint32_t res2:5;   // bits  7:3
            uint32_t cmd:3;    // bits  2:0
        } switch_arg_t;
    
#line 162 "./Linux-Release-GCC-4.4/gen/protocol_MMC_Protocol.h"


// Abstract interface for protocol MMC_Protocol
class protocol_MMC_Protocol
{
public:
        virtual ~protocol_MMC_Protocol() {}
        // Abstract protocol members
	virtual mmc_resp_t cmd(mmc_cmd_t cmd, uint32_t arg, void* resp) = 0;
	virtual bool Rx(const uint8_t* block, uint32_t len) = 0;
	virtual void Rx_rdy() = 0;
	virtual bool Tx(uint8_t* block, uint32_t len) = 0;
	virtual void Tx_done() = 0;
	virtual const char* cmd_name(mmc_cmd_t cmd) = 0;

};

#endif /* protocol_MMC_Protocol_h_ */

