/****************************************************************************
** Copyright (C) 2020 MikroElektronika d.o.o.
** Contact: https://www.mikroe.com/contact
**
** Permission is hereby granted, free of charge, to any person obtaining a copy
** of this software and associated documentation files (the "Software"), to deal
** in the Software without restriction, including without limitation the rights
** to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
** copies of the Software, and to permit persons to whom the Software is
** furnished to do so, subject to the following conditions:
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
** OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
** DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
** OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE
**  USE OR OTHER DEALINGS IN THE SOFTWARE.
****************************************************************************/

/*!
 * @file nfc5.h
 * @brief This file contains API for NFC 5 Click Driver.
 */

#ifndef NFC5_H
#define NFC5_H

#ifdef __cplusplus
extern "C"{
#endif

/**
 * Any initialization code needed for MCU to function properly.
 * Do not remove this line or clock might not be set correctly.
 */
#ifdef PREINIT_SUPPORTED
#include "preinit.h"
#endif

#ifdef MikroCCoreVersion
    #if MikroCCoreVersion >= 1
        #include "delays.h"
    #endif
#endif

#include "drv_digital_out.h"
#include "drv_digital_in.h"
#include "drv_i2c_master.h"
#include "drv_spi_master.h"
#include "spi_specifics.h"

/*!
 * @addtogroup nfc5 NFC 5 Click Driver
 * @brief API for configuring and manipulating NFC 5 Click driver.
 * @{
 */

/**
 * @defgroup nfc5_reg NFC 5 Registers List
 * @brief List of registers of NFC 5 Click driver.
 */

/**
 * @addtogroup nfc5_reg
 * @{
 */

/**
 * @brief NFC 5 List of registers - Space A.
 * @details Specified registers from Space A of NFC 5 Click driver.
 */
#define NFC5_REG_IO_CFG_1                       0x00
#define NFC5_REG_IO_CFG_2                       0x01
#define NFC5_REG_OP_CTRL                        0x02
#define NFC5_REG_MODE                           0x03
#define NFC5_REG_BIT_RATE                       0x04
#define NFC5_REG_ISO14443A_NFC                  0x05
#define NFC5_REG_ISO14443B                      0x06
#define NFC5_REG_ISO14443B_FELICA               0x07
#define NFC5_REG_PASSIVE_TARGET                 0x08
#define NFC5_REG_STREAM_MODE                    0x09
#define NFC5_REG_AUX                            0x0A
#define NFC5_REG_RX_CFG_1                       0x0B
#define NFC5_REG_RX_CFG_2                       0x0C
#define NFC5_REG_RX_CFG_3                       0x0D
#define NFC5_REG_RX_CFG_4                       0x0E
#define NFC5_REG_MASK_RX_TIMER                  0x0F
#define NFC5_REG_NO_RESPONSE_TIMER_1            0x10
#define NFC5_REG_NO_RESPONSE_TIMER_2            0x11
#define NFC5_REG_TIMER_EMV_CTRL                 0x12
#define NFC5_REG_GPT_1                          0x13
#define NFC5_REG_GPT_2                          0x14
#define NFC5_REG_PPON2                          0x15
#define NFC5_REG_IRQ_MASK_MAIN                  0x16
#define NFC5_REG_IRQ_MASK_TIMER_NFC             0x17
#define NFC5_REG_IRQ_MASK_ERROR_WUP             0x18
#define NFC5_REG_IRQ_MASK_TARGET                0x19
#define NFC5_REG_IRQ_MAIN                       0x1A
#define NFC5_REG_IRQ_TIMER_NFC                  0x1B
#define NFC5_REG_IRQ_ERROR_WUP                  0x1C
#define NFC5_REG_IRQ_TARGET                     0x1D
#define NFC5_REG_FIFO_STATUS_1                  0x1E
#define NFC5_REG_FIFO_STATUS_2                  0x1F
#define NFC5_REG_COLLISION_STATUS               0x20
#define NFC5_REG_PASSIVE_TARGET_STATUS          0x21
#define NFC5_REG_NUM_TX_BYTES_1                 0x22
#define NFC5_REG_NUM_TX_BYTES_2                 0x23
#define NFC5_REG_NFCIP1_BIT_RATE                0x24
#define NFC5_REG_ADC_OUTPUT                     0x25
#define NFC5_REG_ANT_TUNE_1                     0x26
#define NFC5_REG_ANT_TUNE_2                     0x27
#define NFC5_REG_TX_DRIVER                      0x28
#define NFC5_REG_PT_MOD                         0x29
#define NFC5_REG_FIELD_THLD_ACT                 0x2A
#define NFC5_REG_FIELD_THLD_DEACT               0x2B
#define NFC5_REG_REGULATOR_CTRL                 0x2C
#define NFC5_REG_RSSI_DISPLAY                   0x2D
#define NFC5_REG_GAIN_REDUCTION_STATE           0x2E
#define NFC5_REG_CAP_SENSOR_CTRL                0x2F
#define NFC5_REG_CAP_SENSOR_DISPLAY             0x30
#define NFC5_REG_AUX_DISPLAY                    0x31
#define NFC5_REG_WUP_TIMER_CTRL                 0x32
#define NFC5_REG_AMPLITUDE_MEAS_CFG             0x33
#define NFC5_REG_AMPLITUDE_MEAS_REF             0x34
#define NFC5_REG_AMPLITUDE_MEAS_AA_DISPLAY      0x35
#define NFC5_REG_AMPLITUDE_MEAS_DISPLAY         0x36
#define NFC5_REG_PHASE_MEAS_CFG                 0x37
#define NFC5_REG_PHASE_MEAS_REF                 0x38
#define NFC5_REG_PHASE_MEAS_AA_DISPLAY          0x39
#define NFC5_REG_PHASE_MEAS_DISPLAY             0x3A
#define NFC5_REG_CAP_MEAS_CFG                   0x3B
#define NFC5_REG_CAP_MEAS_REF                   0x3C
#define NFC5_REG_CAP_MEAS_AA_DISPLAY            0x3D
#define NFC5_REG_CAP_MEAS_DISPLAY               0x3E
#define NFC5_REG_IC_IDENTITY                    0x3F

/**
 * @brief NFC 5 List of registers - Space B.
 * @details Specified registers from Space B of NFC 5 Click driver.
 */
#define NFC5_REG_SPACE_B_MASK                   0x40
#define NFC5_REG_EMD_SUP_CFG                    0x45
#define NFC5_REG_SUBC_START_TIME                0x46
#define NFC5_REG_P2P_RX_CFG                     0x4B
#define NFC5_REG_CORR_CFG_1                     0x4C
#define NFC5_REG_CORR_CFG_2                     0x4D
#define NFC5_REG_SQUELCH_TIMER                  0x4F
#define NFC5_REG_FIELD_ON_GT                    0x55
#define NFC5_REG_AUX_MOD                        0x68
#define NFC5_REG_TX_DRIVER_TIMING               0x69
#define NFC5_REG_RES_AM_MOD                     0x6A
#define NFC5_REG_TX_DRIVER_TIMING_DISPLAY       0x6B
#define NFC5_REG_REGULATOR_DISPLAY              0x6C
#define NFC5_REG_OVERSHOOT_CFG_1                0x70
#define NFC5_REG_OVERSHOOT_CFG_2                0x71
#define NFC5_REG_UNDERSHOOT_CFG_1               0x72
#define NFC5_REG_UNDERSHOOT_CFG_2               0x73

/**
 * @brief NFC 5 List of direct commands.
 * @details Specified direct commands of NFC 5 Click driver.
 */
#define NFC5_CMD_SET_DEFAULT                    0xC1
#define NFC5_CMD_STOP                           0xC2
#define NFC5_CMD_TRANSMIT_WITH_CRC              0xC4
#define NFC5_CMD_TRANSMIT_WITHOUT_CRC           0xC5
#define NFC5_CMD_TRANSMIT_REQA                  0xC6
#define NFC5_CMD_TRANSMIT_WUPA                  0xC7
#define NFC5_CMD_NFC_INITIAL_FIELD_ON           0xC8
#define NFC5_CMD_NFC_RESPONSE_FIELD_ON          0xC9
#define NFC5_CMD_GOTO_SENSE                     0xCD
#define NFC5_CMD_GOTO_SLEEP                     0xCE
#define NFC5_CMD_MASK_RECEIVE_DATA              0xD0
#define NFC5_CMD_UNMASK_RECEIVE_DATA            0xD1
#define NFC5_CMD_CHANGE_AM_MOD_STATE            0xD2
#define NFC5_CMD_MEAS_AMPLITUDE                 0xD3
#define NFC5_CMD_RESET_RX_GAIN                  0xD5
#define NFC5_CMD_ADJUST_REGULATORS              0xD6
#define NFC5_CMD_CALIBRATE_DRIVER_TIMING        0xD8
#define NFC5_CMD_MEAS_PHASE                     0xD9
#define NFC5_CMD_CLEAR_RSSI                     0xDA
#define NFC5_CMD_CLEAR_FIFO                     0xDB
#define NFC5_CMD_TRANSPARENT_MODE               0xDC
#define NFC5_CMD_CALIBRATE_CAP_SENSOR           0xDD
#define NFC5_CMD_MEAS_CAPACITANCE               0xDE
#define NFC5_CMD_MEAS_POWER_SUPPLY              0xDF
#define NFC5_CMD_START_GP_TIMER                 0xE0
#define NFC5_CMD_START_WUP_TIMER                0xE1
#define NFC5_CMD_START_MASK_RECEIVE_TIMER       0xE2
#define NFC5_CMD_START_NO_RESPONSE_TIMER        0xE3
#define NFC5_CMD_START_PPON2_TIMER              0xE4
#define NFC5_CMD_STOP_NO_RESPONSE_TIMER         0xE8
#define NFC5_CMD_SPACE_B_ACCESS                 0xFB
#define NFC5_CMD_TEST_ACCESS                    0xFC

/*! @} */ // nfc5_reg

/**
 * @defgroup nfc5_set NFC 5 Registers Settings
 * @brief Settings for registers of NFC 5 Click driver.
 */

/**
 * @addtogroup nfc5_set
 * @{
 */

/**
 * @brief NFC 5 Communication operation mode setting.
 * @details Specified setting for communication operation mode of NFC 5 Click driver.
 */
#define NFC5_MODE_REG_WRITE                     0x00
#define NFC5_MODE_REG_READ                      0x40
#define NFC5_MODE_FIFO_LOAD                     0x80
#define NFC5_MODE_PT_MEM_LOAD_A_CFG             0xA0     
#define NFC5_MODE_PT_MEM_LOAD_F_CFG             0xA8
#define NFC5_MODE_PT_MEM_LOAD_TSN_DATA          0xAC
#define NFC5_MODE_PT_MEM_READ                   0xBF
#define NFC5_MODE_FIFO_READ                     0x9F
#define NFC5_MODE_DIRECT_COMMAND                0xC0

/**
 * @brief NFC 5 IC Identity default value.
 * @details Specified value for IC Identity of NFC 5 Click driver.
 */
#define NFC5_IC_TYPE_CODE                       0x05
#define NFC5_IC_REVISION_CODE_MASK              0x07

/**
 * @brief NFC 5 IRQ masks.
 * @details Specified masks for IRQ of NFC 5 Click driver.
 */
#define NFC5_IRQ_MASK_ALL                       0xFFFFFFFFul /**< All NFC 5 interrupt sources. */                             
#define NFC5_IRQ_MASK_NONE                      0x00000000ul /**< No NFC 5 interrupt source. */         
#define NFC5_IRQ_MASK_OSC                       0x00000080ul /**< NFC 5 oscillator stable interrupt. */                       
#define NFC5_IRQ_MASK_FWL                       0x00000040ul /**< NFC 5 FIFO water level interrupt. */                        
#define NFC5_IRQ_MASK_RXS                       0x00000020ul /**< NFC 5 start of receive interrupt. */                        
#define NFC5_IRQ_MASK_RXE                       0x00000010ul /**< NFC 5 end of receive interrupt. */                          
#define NFC5_IRQ_MASK_TXE                       0x00000008ul /**< NFC 5 end of transmission interrupt. */                     
#define NFC5_IRQ_MASK_COL                       0x00000004ul /**< NFC 5 bit collision interrupt. */                           
#define NFC5_IRQ_MASK_RX_REST                   0x00000002ul /**< NFC 5 automatic reception restart interrupt. */             
#define NFC5_IRQ_MASK_RFU                       0x00000001ul /**< NFC 5 RFU interrupt. */                       
#define NFC5_IRQ_MASK_DCT                       0x00008000ul /**< NFC 5 termination of direct command interrupt. */          
#define NFC5_IRQ_MASK_NRE                       0x00004000ul /**< NFC 5 no-response timer expired interrupt. */               
#define NFC5_IRQ_MASK_GPE                       0x00002000ul /**< NFC 5 general purpose timer expired interrupt. */           
#define NFC5_IRQ_MASK_EON                       0x00001000ul /**< NFC 5 external field on interrupt. */                       
#define NFC5_IRQ_MASK_EOF                       0x00000800ul /**< NFC 5 external field off interrupt. */                      
#define NFC5_IRQ_MASK_CAC                       0x00000400ul /**< NFC 5 collision during RF collision avoidance interrupt. */ 
#define NFC5_IRQ_MASK_CAT                       0x00000200ul /**< NFC 5 minimum guard time expired interrupt. */              
#define NFC5_IRQ_MASK_NFCT                      0x00000100ul /**< NFC 5 initiator bit rate recognised interrupt. */             
#define NFC5_IRQ_MASK_CRC                       0x00800000ul /**< NFC 5 CRC error interrupt. */                               
#define NFC5_IRQ_MASK_PAR                       0x00400000ul /**< NFC 5 parity error interrupt. */                            
#define NFC5_IRQ_MASK_ERR2                      0x00200000ul /**< NFC 5 soft framing error interrupt. */                      
#define NFC5_IRQ_MASK_ERR1                      0x00100000ul /**< NFC 5 hard framing error interrupt. */                      
#define NFC5_IRQ_MASK_WT                        0x00080000ul /**< NFC 5 wake-up interrupt. */                                 
#define NFC5_IRQ_MASK_WAM                       0x00040000ul /**< NFC 5 wake-up due to amplitude interrupt. */                
#define NFC5_IRQ_MASK_WPH                       0x00020000ul /**< NFC 5 wake-up due to phase interrupt. */                    
#define NFC5_IRQ_MASK_WCAP                      0x00010000ul /**< NFC 5 wake-up due to capacitance measurement. */ 
#define NFC5_IRQ_MASK_PPON2                     0x80000000ul /**< NFC 5 PPON2 Field on waiting Timer interrupt. */            
#define NFC5_IRQ_MASK_SL_WL                     0x40000000ul /**< NFC 5 Passive target slot number water level interrupt. */  
#define NFC5_IRQ_MASK_APON                      0x20000000ul /**< NFC 5 Anticollision done and Field On interrupt. */         
#define NFC5_IRQ_MASK_RXE_PTA                   0x10000000ul /**< NFC 5 RXE with an automatic response interrupt. */          
#define NFC5_IRQ_MASK_WU_F                      0x08000000ul /**< NFC 5 212/424b/s Passive target interrupt: Active. */       
#define NFC5_IRQ_MASK_RFU2                      0x04000000ul /**< NFC 5 RFU2 interrupt. */                                    
#define NFC5_IRQ_MASK_WU_A_X                    0x02000000ul /**< NFC 5 106kb/s Passive target state interrupt: Active. */ 
#define NFC5_IRQ_MASK_WU_A                      0x01000000ul /**< NFC 5 106kb/s Passive target state interrupt: Active. */ 

/**
 * @brief NFC 5 Click analog config values.
 * @details Specified values for the chip analog configuration.
 */
#define NFC5_TEST_REG_INDICATOR                 0x0080 /**< Test Register indicator. */ 
#define NFC5_ANALOG_CONFIG_LUT_NOT_FOUND        0xFF   /**< Index value indicating no Configuration IDs found. */           
#define NFC5_ANALOG_CONFIG_BITRATE_MASK         0x00F0 /**< Mask bits for Bit rate in Analog Configuration ID. */           
#define NFC5_ANALOG_CONFIG_DIRECTION_MASK       0x000F /**< Mask bits for Direction in Analog Configuration ID. */          
#define NFC5_ANALOG_CONFIG_BITRATE_SHIFT        4      /**< Shift value for Technology in Analog Configuration ID. */       
#define NFC5_ANALOG_CONFIG_DIRECTION_SHIFT      0      /**< Shift value for Direction in Analog Configuration ID. */        
#define NFC5_ANALOG_CONFIG_POLL                 0x0000 /**< Poll Mode bit setting in Analog Configuration ID. */            
#define NFC5_ANALOG_CONFIG_LISTEN               0x8000 /**< Listen Mode bit setting in Analog Configuration ID. */          
#define NFC5_ANALOG_CONFIG_TECH_CHIP            0x0000 /**< Chip-Specific bit setting in Analog Configuration ID. */        
#define NFC5_ANALOG_CONFIG_TECH_NFCA            0x0100 /**< NFC-A Technology bits setting in Analog Configuration ID. */    
#define NFC5_ANALOG_CONFIG_BITRATE_COMMON       0x0000 /**< Common settings for all bit rates in Analog Configuration ID. */
#define NFC5_ANALOG_CONFIG_BITRATE_106          0x0010 /**< 106kbits/s settings in Analog Configuration ID. */          
#define NFC5_ANALOG_CONFIG_TX                   0x0001 /**< Transmission bit setting in Analog Configuration ID. */         
#define NFC5_ANALOG_CONFIG_RX                   0x0002 /**< Reception bit setting in Analog Configuration ID. */            
#define NFC5_ANALOG_CONFIG_ANTICOL              0x0003 /**< Anticollision setting in Analog Configuration ID. */            
#define NFC5_ANALOG_CONFIG_CHIP_INIT            0x0000 /**< Chip-Specific event: Startup;Reset;Initialize. */               
#define NFC5_ANALOG_CONFIG_CHIP_DEINIT          0x0001 /**< Chip-Specific event: Deinitialize. */                           
#define NFC5_ANALOG_CONFIG_CHIP_FIELD_ON        0x0002 /**< Chip-Specific event: Field On. */                               
#define NFC5_ANALOG_CONFIG_CHIP_FIELD_OFF       0x0003 /**< Chip-Specific event: Field Off. */                              
#define NFC5_ANALOG_CONFIG_CHIP_POLL_COMMON     0x0008 /**< Chip-Specific event: Poll common. */

/**
 * @brief NFC 5 Click RFAL macros.
 * @details Specified macros for RFAL library.
 */
#define NFC5_1FC_IN_4096FC                      4096u  /**< Number of 1/fc cycles in one 4096/fc. */
#define NFC5_1FC_IN_512FC                       512u   /**< Number of 1/fc cycles in one 512/fc. */
#define NFC5_1FC_IN_64FC                        64u    /**< Number of 1/fc cycles in one 64/fc. */
#define NFC5_1FC_IN_8FC                         8u     /**< Number of 1/fc cycles in one 8/fc. */
#define NFC5_US_IN_MS                           1000u  /**< Number of us in one ms. */
#define NFC5_1MS_IN_1FC                         13560u /**< Number of 1/fc cycles in 1ms. */
#define NFC5_BITS_IN_BYTE                       8u     /**< Number of bits in one byte. */
#define NFC5_CRC_LEN                            2u     /**< RF CRC LEN. */
/**< Converts the given t from 1/fc  to 64/fc. */
#define NFC5_RFAL_CONV_1FC_TO_64FC( T )         ( uint32_t ) ( ( uint32_t ) ( T ) / NFC5_1FC_IN_64FC )  
/**< Converts the given t from 64/fc to 1/fc. */
#define NFC5_RFAL_CONV_64FC_TO_1FC( T )         ( uint32_t ) ( ( uint32_t ) ( T ) * NFC5_1FC_IN_64FC )  
/**< Converts the given n from bits to bytes. */
#define NFC5_RFAL_CONV_BITS_TO_BYTES( N )       ( uint16_t ) ( ( ( uint16_t ) ( N )+ ( NFC5_BITS_IN_BYTE-1u ) ) \
                                                                / ( NFC5_BITS_IN_BYTE ) ) 
/**< Converts the given n from bytes to bits. */
#define NFC5_RFAL_CONV_BYTES_TO_BITS( N )       ( uint32_t ) ( ( uint32_t) ( N ) * ( NFC5_BITS_IN_BYTE ) ) 
/**< Converts the given t from 1/fc to 4096/fc. */
#define NFC5_RFAL_CONV_1FC_TO_4096FC( T )       ( uint32_t ) ( ( uint32_t) ( T ) / NFC5_1FC_IN_4096FC )    
/**< Converts the given t from 4096/fc to 1/fc. */
#define NFC5_RFAL_CONV_4096FC_TO_1FC( T )       ( uint32_t ) ( ( uint32_t) ( T ) * NFC5_1FC_IN_4096FC )    
/**< Converts the given t from 1/fc to ms. */
#define NFC5_RFAL_CONV_1FC_TO_MS( T )           ( uint32_t ) ( ( uint32_t) ( T ) / NFC5_1MS_IN_1FC )       
/**< Converts the given t from ms to 1/fc. */
#define NFC5_RFAL_CONV_MS_TO_1FC( T )           ( uint32_t ) ( ( uint32_t) ( T ) * NFC5_1MS_IN_1FC )       
/**< Disabled FWT: Wait forever for a response. */
#define NFC5_FWT_NONE                           0xFFFFFFFFul  
/**< FWT adjustment: 64 : NRT jitter between TXE and NRT start. */
#define NFC5_FWT_ADJUSTMENT                     64u 
/**< FWT ISO14443A adjustment: 512 - 4bit length, 64 - Half a bit duration due to ST25R3918 Coherent receiver ( 1 / FC ). */
#define NFC5_FWT_A_ADJUSTMENT                   ( 512u + 64u )
/**< Max NRT steps in 1fc (0xFFFF steps of 4096/FC => 0xFFFF * 302us  = 19.8s ). */
#define NFC5_NRT_MAX_1FC                        NFC5_RFAL_CONV_4096FC_TO_1FC( 0xFFFFu ) 
/**< Min MRT steps in 1fc ( 0<=MRT<=4 ; 4 (64/FC)  => 0x0004 * 4.72us = 18.88us ). */
#define NFC5_MRT_MIN_1FC                        NFC5_RFAL_CONV_64FC_TO_1FC( 0x0004u ) 
/**< NRT Disabled: All 0 No-response timer is not started, wait forever. */
#define NFC5_NRT_DISABLED                       0u  
/**< Max Register value of NRT. */
#define NFC5_NRT_MAX                            0xFFFFu 
/**< Returns the number of bytes required to fit given the number of bits */
#define NFC5_RFAL_CALC_NUM_BYTES( NBITS )       ( ( ( uint32_t )( NBITS ) + 7u ) / 8u )  

/**
 * @brief NFC 5 Click rfal create byte flags tx rx context macro.
 * @details Computes a Transceive context @a CTX using lengths in bytes 
 * with the given flags and arguments
 *    @a CTX   : Transceive context to be assigned  
 *    @a TB    : tx_buf the pointer to the buffer to be sent
 *    @a TBL   : tx_buf length in bytes
 *    @a RB    : rx_buf the pointer to the buffer to place the received frame
 *    @a RBL   : rx_buf length in bytes
 *    @a RDL   : rx_rcvd_buf length in bytes
 *    @a FL    : transceive flags indication
 *    @a T     : FWT to be used on this transceive in 1/fc
 */
#define NFC5_RFAL_CREATE_BYTE_FLAGS_TX_RX_CONTEXT( CTX, TB, TBL, RB, RBL, RDL, FL, T ) \
    ( CTX ).tx_buf      = ( uint8_t* ) ( TB );                                         \
    ( CTX ).tx_buf_len  = ( uint16_t) NFC5_RFAL_CONV_BYTES_TO_BITS ( TBL );            \
    ( CTX ).rx_buf      = ( uint8_t* ) ( RB );                                         \
    ( CTX ).rx_buf_len  = ( uint16_t ) NFC5_RFAL_CONV_BYTES_TO_BITS ( RBL );           \
    ( CTX ).rx_rcvd_len = ( uint16_t* ) ( RDL );                                       \
    ( CTX ).flags       = ( uint32_t ) ( FL );                                         \
    ( CTX ).fwt         = ( uint32_t ) ( T );

/**
 * @brief NFC 5 Click RFAL NFC macros.
 * @details Specified macros for RFAL NFC.
 */
#define NFC5_NFCA_CASCADE_1_UID_LEN             4u    /**< UID length of cascade level 1 only tag. */
#define NFC5_NFCA_CASCADE_2_UID_LEN             7u    /**< UID length of cascade level 2 only tag. */
#define NFC5_NFCA_CASCADE_3_UID_LEN             10u   /**< UID length of cascade level 3 only tag. */
#define NFC5_NFC_MAX_DEVICES                    5u    /**< Max number of devices supported. */
#define NFC5_THLD_DO_NOT_SET                    0xFFu /**< Indicates not to change this Threshold. */
/**< NFC-A minimum FDT( listen ) = ( ( n * 128 + ( 84 ) ) / fc ) with n_min = 9   Digital 1.1  6.10.1
 *                               = ( 1236 ) / fc
 * Relax with 3etu: ( 3 * 128 ) / fc as with multiple NFC-A cards, response may take longer ( JCOP cards )
 *                               = ( 1236 + 384 )/ fc = 1620 / fc                                      */
#define NFC5_NFCA_FDTMIN                        1620u
  
/**< Calculates SEL_CMD with the given cascade level   */
#define NFC5_RFAL_NFCA_CLN2_SEL_CMD( CL )       ( uint8_t )( ( uint8_t )( NFC5_NFCA_CMD_SEL_CL1 ) + ( 2u * ( CL ) ) ) 

/**< Calculates SEL_PAR with the bytes/bits to be sent */
#define NFC5_RFAL_NFCA_SEL_PAR( NBY, NBI )      ( uint8_t )( ( ( ( NBY ) << 4u ) & 0xF0u ) | ( ( NBI ) &0x0Fu ) )         
#define NFC5_RFAL_NFCA_NFC_ID_LEN_2CL( LEN )    ( ( LEN ) / 5u )      /**< Calculates cascade level by the NFCID length. */
#define NFC5_NFCA_SLP_FWT                       NFC5_RFAL_CONV_MS_TO_1FC ( 1 ) /**< Check 1ms for any modulation  ISO14443-3 6.4.3. */
#define NFC5_NFCA_SLP_CMD                       0x50u                 /**< SLP cmd (byte1)    Digital 1.1  6.9.1 & Table 20. */
#define NFC5_NFCA_SLP_BYTE2                     0x00u                 /**< SLP byte2          Digital 1.1  6.9.1 & Table 20. */
#define NFC5_NFCA_SLP_CMD_POS                   0u                    /**< SLP cmd position   Digital 1.1  6.9.1 & Table 20. */
#define NFC5_NFCA_SLP_BYTE2_POS                 1u                    /**< SLP byte2 position Digital 1.1  6.9.1 & Table 20. */
#define NFC5_NFCA_SDD_CT                        0x88u                 /**< Cascade Tag value Digital 1.1 6.7.2. */
#define NFC5_NFCA_SDD_CT_LEN                    1u                    /**< Cascade Tag length. */
#define NFC5_NFCA_SLP_REQ_LEN                   2u                    /**< SLP_REQ length. */
#define NFC5_NFCA_SEL_CMD_LEN                   1u                    /**< SEL_CMD length. */
#define NFC5_NFCA_SEL_PAR_LEN                   1u                    /**< SEL_PAR length. */
#define NFC5_NFCA_SEL_SELPAR                    NFC5_RFAL_NFCA_SEL_PAR( 7u, 0u ) /**< SEL_PAR on Select is always with 4 data/nfcid. */
#define NFC5_NFCA_BCC_LEN                       1u                    /**< BCC length. */
#define NFC5_NFCA_SDD_REQ_LEN                   ( NFC5_NFCA_SEL_CMD_LEN + NFC5_NFCA_SEL_PAR_LEN )   /**< SDD_REQ length. */
#define NFC5_NFCA_SDD_RES_LEN                   ( NFC5_NFCA_CASCADE_1_UID_LEN + NFC5_NFCA_BCC_LEN ) /**< SDD_RES length. */
#define NFC5_NFCA_N_RETRANS                     2u                    /**< Number of retries  EMVCo 2.6  9.6.1.3. */
#define NFC5_ISO14443A_SDD_RES_LEN              5u                    /**< SDD_RES | Anticollision (UID CLn) length. */
/**< Default TxRx flags: Tx CRC automatic, Rx CRC removed, NFCIP1 mode off, AGC On, Tx Parity automatic, Rx Parity removed */
#define NFC5_TXRX_FLAGS_DEFAULT                 ( ( uint32_t ) NFC5_TXRX_FLAGS_CRC_TX_AUTO | ( uint32_t ) NFC5_TXRX_FLAGS_CRC_RX_REMV | \
                                                  ( uint32_t ) NFC5_TXRX_FLAGS_NFCIP1_OFF | ( uint32_t ) NFC5_TXRX_FLAGS_AGC_ON | \
                                                  ( uint32_t ) NFC5_TXRX_FLAGS_PAR_RX_REMV | ( uint32_t ) NFC5_TXRX_FLAGS_PAR_TX_AUTO | \
                                                  ( uint32_t ) NFC5_TXRX_FLAGS_NFCV_FLAG_AUTO )

/**
 * @brief NFC 5 Click NFC FIFO macros.
 * @details Specified macros for NFC FIFO.
 */
#define NFC5_FIFO_DEPTH                         512u  /**< Depth of FIFO. */
#define NFC5_FIFO_STATUS_REG1                   0u    /**< Location of FIFO status register 1 in local copy. */
#define NFC5_FIFO_STATUS_REG2                   1u    /**< Location of FIFO status register 2 in local copy. */
#define NFC5_FIFO_STATUS_INVALID                0xFFu /**< Value indicating that the local FIFO status in invalid|cleared. */
#define NFC5_FIFO_IN_WL                         200u  /**< Number of bytes in the FIFO when WL interrupt occurs while Tx. */
#define NFC5_FIFO_OUT_WL                        ( NFC5_FIFO_DEPTH - NFC5_FIFO_IN_WL ) /**< Number of bytes sent/out of the FIFO 
                                                                                           when WL interrupt occurs while Tx. */

/**
 * @brief NFC 5 Click register bits value.
 * @details Specified values of registers bits.
 */
#define NFC5_IO_CFG_1_SINGLE                    ( 1u << 7 )
#define NFC5_IO_CFG_1_RFO2                      ( 1u << 6 )
#define NFC5_IO_CFG_1_I2C_THD1                  ( 1u << 5 )
#define NFC5_IO_CFG_1_I2C_THD0                  ( 1u << 4 )
#define NFC5_IO_CFG_1_I2C_THD_MASK              ( 3u << 4 )
#define NFC5_IO_CFG_1_I2C_THD_SHIFT             ( 4u ) 
#define NFC5_IO_CFG_1_RFU                       ( 1u << 3 )
#define NFC5_IO_CFG_1_OUT_CL1                   ( 1u << 2 )
#define NFC5_IO_CFG_1_OUT_CL0                   ( 1u << 1 )
#define NFC5_IO_CFG_1_OUT_CL_DISABLED           ( 3u << 1 )
#define NFC5_IO_CFG_1_OUT_CL_13_56MHZ           ( 2u << 1 )
#define NFC5_IO_CFG_1_OUT_CL_4_78MHZ            ( 1u << 1 )
#define NFC5_IO_CFG_1_OUT_CL_3_39MHZ            ( 0u << 1 )
#define NFC5_IO_CFG_1_OUT_CL_MASK               ( 3u << 1 )
#define NFC5_IO_CFG_1_OUT_CL_SHIFT              ( 1u ) 
#define NFC5_IO_CFG_1_LF_CLK_OFF                ( 1u << 0 )
#define NFC5_IO_CFG_1_LF_CLK_OFF_ON             ( 1u << 0 )
#define NFC5_IO_CFG_1_LF_CLK_OFF_OFF            ( 0u << 0 )
#define NFC5_IO_CFG_2_SUP3V                     ( 1u << 7 )
#define NFC5_IO_CFG_2_SUP3V_3V                  ( 1u << 7 )
#define NFC5_IO_CFG_2_SUP3V_5V                  ( 0u << 7 )
#define NFC5_IO_CFG_2_VSPD_OFF                  ( 1u << 6 )
#define NFC5_IO_CFG_2_AAT_EN                    ( 1u << 5 )
#define NFC5_IO_CFG_2_MISO_PD2                  ( 1u << 4 )
#define NFC5_IO_CFG_2_MISO_PD1                  ( 1u << 3 )
#define NFC5_IO_CFG_2_IO_DRV_LVL                ( 1u << 2 )
#define NFC5_IO_CFG_2_SLOW_UP                   ( 1u << 0 )
#define NFC5_ISO14443A_NFC_NO_TX_PAR            ( 1u << 7 )
#define NFC5_ISO14443A_NFC_NO_TX_PAR_OFF        ( 0u << 7 )
#define NFC5_ISO14443A_NFC_NO_RX_PAR            ( 1u << 6 )
#define NFC5_ISO14443A_NFC_NO_RX_PAR_OFF        ( 0u << 6 )
#define NFC5_ISO14443A_NFC_NFC_F0               ( 1u << 5 )
#define NFC5_ISO14443A_NFC_NFC_F0_OFF           ( 0u << 5 )
#define NFC5_ISO14443A_NFC_P_LEN3               ( 1u << 4 )
#define NFC5_ISO14443A_NFC_P_LEN2               ( 1u << 3 )
#define NFC5_ISO14443A_NFC_P_LEN1               ( 1u << 2 )
#define NFC5_ISO14443A_NFC_P_LEN0               ( 1u << 1 )
#define NFC5_ISO14443A_NFC_P_LEN_MASK           ( 0xFu << 1 )
#define NFC5_ISO14443A_NFC_P_LEN_SHIFT          ( 1u )
#define NFC5_ISO14443A_NFC_ANTCL                ( 1u << 0 )
#define NFC5_RX_CFG_2_DEMOD_MODE                ( 1u << 7 )
#define NFC5_RX_CFG_2_AMD_SEL                   ( 1u << 6 )
#define NFC5_RX_CFG_2_AMD_SEL_MIXER             ( 1u << 6 )
#define NFC5_RX_CFG_2_AMD_SEL_PEAK              ( 0u << 6 )
#define NFC5_RX_CFG_2_SQM_DYN                   ( 1u << 5 )
#define NFC5_RX_CFG_2_PULZ_61                   ( 1u << 4 )
#define NFC5_RX_CFG_2_AGC_EN                    ( 1u << 3 )
#define NFC5_RX_CFG_2_AGC_M                     ( 1u << 2 )
#define NFC5_RX_CFG_2_AGC_ALG                   ( 1u << 1 )
#define NFC5_RX_CFG_2_AGC6_3                    ( 1u << 0 )
#define NFC5_OP_CTRL_EN                         ( 1u << 7 )
#define NFC5_OP_CTRL_RX_EN                      ( 1u << 6 )
#define NFC5_OP_CTRL_RX_CHN                     ( 1u << 5 )
#define NFC5_OP_CTRL_RX_MAN                     ( 1u << 4 )
#define NFC5_OP_CTRL_TX_EN                      ( 1u << 3 )
#define NFC5_OP_CTRL_WU                         ( 1u << 2 )
#define NFC5_OP_CTRL_EN_FD_C1                   ( 1u << 1 )
#define NFC5_OP_CTRL_EN_FD_C0                   ( 1u << 0 )
#define NFC5_OP_CTRL_EN_FD_EFD_OFF              ( 0u << 0 )
#define NFC5_OP_CTRL_EN_FD_MANUAL_EFD_CA        ( 1u << 0 )
#define NFC5_OP_CTRL_EN_FD_MANUAL_EFD_PDT       ( 2u << 0 )
#define NFC5_OP_CTRL_EN_FD_AUTO_EFD             ( 3u << 0 )
#define NFC5_OP_CTRL_EN_FD_SHIFT                ( 0u )
#define NFC5_OP_CTRL_EN_FD_MASK                 ( 3u << 0 )
#define NFC5_NFCIP1_BIT_RATE_NFC_RFU1           ( 1u << 7 )
#define NFC5_NFCIP1_BIT_RATE_NFC_RFU0           ( 1u << 6 )
#define NFC5_NFCIP1_BIT_RATE_NFC_RATE1          ( 1u << 5 )
#define NFC5_NFCIP1_BIT_RATE_NFC_RATE0          ( 1u << 4 )
#define NFC5_NFCIP1_BIT_RATE_NFC_RATE_MASK      ( 0x3u << 4 )
#define NFC5_NFCIP1_BIT_RATE_NFC_RATE_SHIFT     ( 4u )
#define NFC5_NFCIP1_BIT_RATE_PPT2_ON            ( 1u << 3 )
#define NFC5_NFCIP1_BIT_RATE_GPT_ON             ( 1u << 2 )
#define NFC5_NFCIP1_BIT_RATE_NRT_ON             ( 1u << 1 )
#define NFC5_NFCIP1_BIT_RATE_MRT_ON             ( 1u << 0 )
#define NFC5_AUX_DISPLAY_A_CHA                  ( 1u << 7 )
#define NFC5_AUX_DISPLAY_EFD_O                  ( 1u << 6 )
#define NFC5_AUX_DISPLAY_TX_ON                  ( 1u << 5 )
#define NFC5_AUX_DISPLAY_OSC_OK                 ( 1u << 4 )
#define NFC5_AUX_DISPLAY_RX_ON                  ( 1u << 3 )
#define NFC5_AUX_DISPLAY_RX_ACT                 ( 1u << 2 )
#define NFC5_AUX_DISPLAY_EN_PEER                ( 1u << 1 )
#define NFC5_AUX_DISPLAY_EN_AC                  ( 1u << 0 )
#define NFC5_FIFO_STATUS2_FIFO_B9               ( 1u << 7 )
#define NFC5_FIFO_STATUS2_FIFO_B8               ( 1u << 6 )
#define NFC5_FIFO_STATUS2_FIFO_B_MASK           ( 3u << 6 )
#define NFC5_FIFO_STATUS2_FIFO_B_SHIFT          ( 6u )
#define NFC5_FIFO_STATUS2_FIFO_UNF              ( 1u << 5 )
#define NFC5_FIFO_STATUS2_FIFO_OVR              ( 1u << 4 )
#define NFC5_FIFO_STATUS2_FIFO_LB2              ( 1u << 3 )
#define NFC5_FIFO_STATUS2_FIFO_LB1              ( 1u << 2 )
#define NFC5_FIFO_STATUS2_FIFO_LB0              ( 1u << 1 )
#define NFC5_FIFO_STATUS2_FIFO_LB_MASK          ( 7u << 1 )
#define NFC5_FIFO_STATUS2_FIFO_LB_SHIFT         ( 1u )
#define NFC5_FIFO_STATUS2_NP_LB                 ( 1u << 0 )
#define NFC5_MODE_TARG                          ( 1u << 7 )
#define NFC5_MODE_TARG_TARG                     ( 1u << 7 )
#define NFC5_MODE_TARG_INIT                     ( 0u << 7 )
#define NFC5_MODE_OM3                           ( 1u << 6 )
#define NFC5_MODE_OM2                           ( 1u << 5 )
#define NFC5_MODE_OM1                           ( 1u << 4 )
#define NFC5_MODE_OM0                           ( 1u << 3 )
#define NFC5_MODE_OM_BPSK_STREAM                ( 0xFu << 3 )
#define NFC5_MODE_OM_SUBCARRIER_STREAM          ( 0xEu << 3 )
#define NFC5_MODE_OM_TOPAZ                      ( 0x4u << 3 )
#define NFC5_MODE_OM_FELICA                     ( 0x3u << 3 )
#define NFC5_MODE_OM_ISO14443B                  ( 0x2u << 3 )
#define NFC5_MODE_OM_ISO14443A                  ( 0x1u << 3 )
#define NFC5_MODE_OM_TARG_NFCA                  ( 0x1u << 3 )
#define NFC5_MODE_OM_TARG_NFCB                  ( 0x2u << 3 )
#define NFC5_MODE_OM_TARG_NFCF                  ( 0x4u << 3 )
#define NFC5_MODE_OM_TARG_NFCIP                 ( 0x7u << 3 )
#define NFC5_MODE_OM_NFC                        ( 0x0u << 3 )
#define NFC5_MODE_OM_MASK                       ( 0xFu << 3 )
#define NFC5_MODE_OM_SHIFT                      ( 3u )
#define NFC5_MODE_TR_AM                         ( 1u << 2 )
#define NFC5_MODE_TR_AM_OOK                     ( 0u << 2 )
#define NFC5_MODE_TR_AM_AM                      ( 1u << 2 )
#define NFC5_MODE_NFC_AR1                       ( 1u << 1 )
#define NFC5_MODE_NFC_AR0                       ( 1u << 0 )
#define NFC5_MODE_NFC_AR_OFF                    ( 0u << 0 )
#define NFC5_MODE_NFC_AR_AUTO_RX                ( 1u << 0 )
#define NFC5_MODE_NFC_AR_EOF                    ( 2u << 0 )
#define NFC5_MODE_NFC_AR_RFU                    ( 3u << 0 )
#define NFC5_MODE_NFC_AR_MASK                   ( 3u << 0 )
#define NFC5_MODE_NFC_AR_SHIFT                  ( 0u )
#define NFC5_BIT_RATE_TXRATE_106                ( 0x0u << 4 )
#define NFC5_BIT_RATE_TXRATE_212                ( 0x1u << 4 )
#define NFC5_BIT_RATE_TXRATE_424                ( 0x2u << 4 )
#define NFC5_BIT_RATE_TXRATE_848                ( 0x3u << 4 )
#define NFC5_BIT_RATE_TXRATE_MASK               ( 0x3u << 4 )
#define NFC5_BIT_RATE_TXRATE_SHIFT              ( 4u )
#define NFC5_BIT_RATE_RXRATE_106                ( 0x0u << 0 )
#define NFC5_BIT_RATE_RXRATE_212                ( 0x1u << 0 )
#define NFC5_BIT_RATE_RXRATE_424                ( 0x2u << 0 )
#define NFC5_BIT_RATE_RXRATE_848                ( 0x3u << 0 )
#define NFC5_BIT_RATE_RXRATE_MASK               ( 0x3u << 0 )
#define NFC5_BIT_RATE_RXRATE_SHIFT              ( 0u )
#define NFC5_AUX_MOD_DIS_REG_AM                 ( 1u << 7 )
#define NFC5_AUX_MOD_LM_EXT_POL                 ( 1u << 6 )
#define NFC5_AUX_MOD_LM_EXT                     ( 1u << 5 )
#define NFC5_AUX_MOD_LM_DRI                     ( 1u << 4 )
#define NFC5_AUX_MOD_RES_AM                     ( 1u << 3 )
#define NFC5_AUX_MOD_RFU2                       ( 1u << 2 )
#define NFC5_AUX_MOD_RFU1                       ( 1u << 1 )
#define NFC5_AUX_MOD_RFU0                       ( 1u << 0 )
#define NFC5_PASSIVE_TARGET_FDEL_3              ( 1u << 7 )
#define NFC5_PASSIVE_TARGET_FDEL_2              ( 1u << 6 )
#define NFC5_PASSIVE_TARGET_FDEL_1              ( 1u << 5 )
#define NFC5_PASSIVE_TARGET_FDEL_0              ( 1u << 4 )
#define NFC5_PASSIVE_TARGET_FDEL_MASK           ( 0xFu << 4 )
#define NFC5_PASSIVE_TARGET_FDEL_SHIFT          ( 4u )
#define NFC5_PASSIVE_TARGET_D_AC_AP2P           ( 1u << 3 )
#define NFC5_PASSIVE_TARGET_D_212_424_1R        ( 1u << 2 )
#define NFC5_PASSIVE_TARGET_RFU                 ( 1u << 1 )
#define NFC5_PASSIVE_TARGET_D_106_AC_A          ( 1u << 0 )
#define NFC5_PT_MOD_PTM_RES3                    ( 1u << 7 )
#define NFC5_PT_MOD_PTM_RES2                    ( 1u << 6 )
#define NFC5_PT_MOD_PTM_RES1                    ( 1u << 5 )
#define NFC5_PT_MOD_PTM_RES0                    ( 1u << 4 )
#define NFC5_PT_MOD_PTM_RES_MASK                ( 0xFu << 4 )
#define NFC5_PT_MOD_PTM_RES_SHIFT               ( 4u )
#define NFC5_PT_MOD_PT_RES3                     ( 1u << 3 )
#define NFC5_PT_MOD_PT_RES2                     ( 1u << 2 )
#define NFC5_PT_MOD_PT_RES1                     ( 1u << 1 )
#define NFC5_PT_MOD_PT_RES0                     ( 1u << 0 )
#define NFC5_PT_MOD_PT_RES_MASK                 ( 0xFu << 0 )
#define NFC5_PT_MOD_PT_RES_SHIFT                ( 0u )  
#define NFC5_EMD_SUP_CFG_EMD_EMV                ( 1u << 7 )
#define NFC5_EMD_SUP_CFG_EMD_EMV_ON             ( 1u << 7 )
#define NFC5_EMD_SUP_CFG_EMD_EMV_OFF            ( 0u << 7 )
#define NFC5_EMD_SUP_CFG_RX_START_EMV           ( 1u << 6 )
#define NFC5_EMD_SUP_CFG_RX_START_EMV_ON        ( 1u << 6 )
#define NFC5_EMD_SUP_CFG_RX_START_EMV_OFF       ( 0u << 6 )
#define NFC5_EMD_SUP_CFG_RFU1                   ( 1u << 5 )
#define NFC5_EMD_SUP_CFG_RFU0                   ( 1u << 4 )
#define NFC5_EMD_SUP_CFG_EMD_THLD3              ( 1u << 3 )
#define NFC5_EMD_SUP_CFG_EMD_THLD2              ( 1u << 2 )
#define NFC5_EMD_SUP_CFG_EMD_THLD1              ( 1u << 1 )
#define NFC5_EMD_SUP_CFG_EMD_THLD0              ( 1u << 0 )
#define NFC5_EMD_SUP_CFG_EMD_THLD_MASK          ( 0xFu << 0 )
#define NFC5_EMD_SUP_CFG_EMD_THLD_SHIFT         ( 0u )
#define NFC5_AUX_NO_CRC_RX                      ( 1u << 7 )
#define NFC5_AUX_RFU                            ( 1u << 6 )
#define NFC5_AUX_NFC_ID1                        ( 1u << 5 )
#define NFC5_AUX_NFC_ID0                        ( 1u << 4 )
#define NFC5_AUX_NFC_ID_7BYTES                  ( 1u << 4 )
#define NFC5_AUX_NFC_ID_4BYTES                  ( 0u << 4 )
#define NFC5_AUX_NFC_ID_MASK                    ( 3u << 4 )
#define NFC5_AUX_NFC_ID_SHIFT                   ( 4u )
#define NFC5_AUX_MFAZ_CL90                      ( 1u << 3 )
#define NFC5_AUX_DIS_CORR                       ( 1u << 2 )
#define NFC5_AUX_DIS_CORR_COHERENT              ( 1u << 2 )
#define NFC5_AUX_DIS_CORR_CORRELATOR            ( 0u << 2 )
#define NFC5_AUX_NFC_N1                         ( 1u << 1 )
#define NFC5_AUX_NFC_N0                         ( 1u << 0 )
#define NFC5_AUX_NFC_N_MASK                     ( 3u << 0 )
#define NFC5_AUX_NFC_N_SHIFT                    ( 0u )
#define NFC5_TIMER_EMV_CONTROL_GPTC2            ( 1u << 7 )
#define NFC5_TIMER_EMV_CONTROL_GPTC1            ( 1u << 6 )
#define NFC5_TIMER_EMV_CONTROL_GPTC0            ( 1u << 5 )
#define NFC5_TIMER_EMV_CONTROL_GPTC_NO_TRIGGER  ( 0u << 5 )
#define NFC5_TIMER_EMV_CONTROL_GPTC_ERX         ( 1u << 5 )
#define NFC5_TIMER_EMV_CONTROL_GPTC_SRX         ( 2u << 5 )
#define NFC5_TIMER_EMV_CONTROL_GPTC_ETX_NFC     ( 3u << 5 )
#define NFC5_TIMER_EMV_CONTROL_GPTC_MASK        ( 7u << 5 )
#define NFC5_TIMER_EMV_CONTROL_GPTC_SHIFT       ( 5u )
#define NFC5_TIMER_EMV_CONTROL_RFU              ( 1u << 4 )
#define NFC5_TIMER_EMV_CONTROL_MRT_STEP         ( 1u << 3 )
#define NFC5_TIMER_EMV_CONTROL_MRT_STEP_512     ( 1u << 3 )
#define NFC5_TIMER_EMV_CONTROL_MRT_STEP_64      ( 0u << 3 )
#define NFC5_TIMER_EMV_CONTROL_NRT_NFC          ( 1u << 2 )
#define NFC5_TIMER_EMV_CONTROL_NRT_NFC_ON       ( 1u << 2 )
#define NFC5_TIMER_EMV_CONTROL_NRT_NFC_OFF      ( 0u << 2 )
#define NFC5_TIMER_EMV_CONTROL_NRT_EMV          ( 1u << 1 )
#define NFC5_TIMER_EMV_CONTROL_NRT_EMV_ON       ( 1u << 1 )
#define NFC5_TIMER_EMV_CONTROL_NRT_EMV_OFF      ( 0u << 1 )
#define NFC5_TIMER_EMV_CONTROL_NRT_STEP         ( 1u << 0 )
#define NFC5_TIMER_EMV_CONTROL_NRT_STEP_64FC    ( 0u << 0 )
#define NFC5_TIMER_EMV_CONTROL_NRT_STEP_4096_FC ( 1u << 0 )
#define NFC5_COLLISION_STATUS_C_BYTE3           ( 1u << 7 )
#define NFC5_COLLISION_STATUS_C_BYTE2           ( 1u << 6 )
#define NFC5_COLLISION_STATUS_C_BYTE1           ( 1u << 5 )
#define NFC5_COLLISION_STATUS_C_BYTE0           ( 1u << 4 )
#define NFC5_COLLISION_STATUS_C_BYTE_MASK       ( 0xFu << 4 )
#define NFC5_COLLISION_STATUS_C_BYTE_SHIFT      ( 4u )
#define NFC5_COLLISION_STATUS_C_BIT2            ( 1u << 3 )
#define NFC5_COLLISION_STATUS_C_BIT1            ( 1u << 2 )
#define NFC5_COLLISION_STATUS_C_BIT0            ( 1u << 1 )
#define NFC5_COLLISION_STATUS_C_PB              ( 1u << 0 )
#define NFC5_COLLISION_STATUS_C_BIT_MASK        ( 3u << 1 )
#define NFC5_COLLISION_STATUS_C_BIT_SHIFT       ( 1u )
#define NFC5_CORR_CFG_1_CORR_S7                 ( 1u << 7 )
#define NFC5_CORR_CFG_1_CORR_S6                 ( 1u << 6 )
#define NFC5_CORR_CFG_1_CORR_S5                 ( 1u << 5 )
#define NFC5_CORR_CFG_1_CORR_S4                 ( 1u << 4 )
#define NFC5_CORR_CFG_1_CORR_S3                 ( 1u << 3 )
#define NFC5_CORR_CFG_1_CORR_S2                 ( 1u << 2 )
#define NFC5_CORR_CFG_1_CORR_S1                 ( 1u << 1 )
#define NFC5_CORR_CFG_1_CORR_S0                 ( 1u << 0 )
#define NFC5_TX_DRIVER_AM_MOD3                  ( 1u << 7 )
#define NFC5_TX_DRIVER_AM_MOD2                  ( 1u << 6 )
#define NFC5_TX_DRIVER_AM_MOD1                  ( 1u << 5 )
#define NFC5_TX_DRIVER_AM_MOD0                  ( 1u << 4 )
#define NFC5_TX_DRIVER_AM_MOD_5PERCENT          ( 0x0u << 4 )
#define NFC5_TX_DRIVER_AM_MOD_6PERCENT          ( 0x1u << 4 )
#define NFC5_TX_DRIVER_AM_MOD_7PERCENT          ( 0x2u << 4 )
#define NFC5_TX_DRIVER_AM_MOD_8PERCENT          ( 0x3u << 4 )
#define NFC5_TX_DRIVER_AM_MOD_9PERCENT          ( 0x4u << 4 )
#define NFC5_TX_DRIVER_AM_MOD_10PERCENT         ( 0x5u << 4 )
#define NFC5_TX_DRIVER_AM_MOD_11PERCENT         ( 0x6u << 4 )
#define NFC5_TX_DRIVER_AM_MOD_12PERCENT         ( 0x7u << 4 )
#define NFC5_TX_DRIVER_AM_MOD_13PERCENT         ( 0x8u << 4 )
#define NFC5_TX_DRIVER_AM_MOD_14PERCENT         ( 0x9u << 4 )
#define NFC5_TX_DRIVER_AM_MOD_15PERCENT         ( 0xAu << 4 )
#define NFC5_TX_DRIVER_AM_MOD_17PERCENT         ( 0xBu << 4 )
#define NFC5_TX_DRIVER_AM_MOD_19PERCENT         ( 0xCu << 4 )
#define NFC5_TX_DRIVER_AM_MOD_22PERCENT         ( 0xDu << 4 )
#define NFC5_TX_DRIVER_AM_MOD_26PERCENT         ( 0xEu << 4 )
#define NFC5_TX_DRIVER_AM_MOD_40PERCENT         ( 0xFu << 4 )
#define NFC5_TX_DRIVER_AM_MOD_MASK              ( 0xFu << 4 )
#define NFC5_TX_DRIVER_AM_MOD_SHIFT             ( 4u )
#define NFC5_TX_DRIVER_D_RES3                   ( 1u << 3 )
#define NFC5_TX_DRIVER_D_RES2                   ( 1u << 2 )
#define NFC5_TX_DRIVER_D_RES1                   ( 1u << 1 )
#define NFC5_TX_DRIVER_D_RES0                   ( 1u << 0 )
#define NFC5_TX_DRIVER_D_RES_MASK               ( 0xFu << 0 )
#define NFC5_TX_DRIVER_D_RES_SHIFT              ( 0u )
#define NFC5_FIELD_THLD_ACT_TRG_L2A             ( 1u << 6 )
#define NFC5_FIELD_THLD_ACT_TRG_L1A             ( 1u << 5 )
#define NFC5_FIELD_THLD_ACT_TRG_L0A             ( 1u << 4 )
#define NFC5_FIELD_THLD_ACT_TRG_75MV            ( 0x0u << 4 )
#define NFC5_FIELD_THLD_ACT_TRG_105MV           ( 0x1u << 4 )
#define NFC5_FIELD_THLD_ACT_TRG_150MV           ( 0x2u << 4 )
#define NFC5_FIELD_THLD_ACT_TRG_205MV           ( 0x3u << 4 )
#define NFC5_FIELD_THLD_ACT_TRG_290MV           ( 0x4u << 4 )
#define NFC5_FIELD_THLD_ACT_TRG_400MV           ( 0x5u << 4 )
#define NFC5_FIELD_THLD_ACT_TRG_560MV           ( 0x6u << 4 )
#define NFC5_FIELD_THLD_ACT_TRG_800MV           ( 0x7u << 4 )
#define NFC5_FIELD_THLD_ACT_TRG_MASK            ( 7u << 4 )
#define NFC5_FIELD_THLD_ACT_TRG_SHIFT           ( 4u )
#define NFC5_FIELD_THLD_ACT_RFE_T3A             ( 1u << 3 )
#define NFC5_FIELD_THLD_ACT_RFE_T2A             ( 1u << 2 )
#define NFC5_FIELD_THLD_ACT_RFE_T1A             ( 1u << 1 )
#define NFC5_FIELD_THLD_ACT_RFE_T0A             ( 1u << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_75MV            ( 0x0u << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_105MV           ( 0x1u << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_150MV           ( 0x2u << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_205MV           ( 0x3u << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_290MV           ( 0x4u << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_400MV           ( 0x5u << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_560MV           ( 0x6u << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_800MV           ( 0x7u << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_25MV            ( 0x8u << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_33MV            ( 0x9u << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_47MV            ( 0xAu << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_64MV            ( 0xBu << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_90MV            ( 0xCu << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_125MV           ( 0xDu << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_175MV           ( 0xEu << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_250MV           ( 0xFu << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_MASK            ( 0xFu << 0 )
#define NFC5_FIELD_THLD_ACT_RFE_SHIFT           ( 0u ) 
#define NFC5_FIELD_THLD_DEACT_TRG_L2D           ( 1u << 6 )
#define NFC5_FIELD_THLD_DEACT_TRG_L1D           ( 1u << 5 )
#define NFC5_FIELD_THLD_DEACT_TRG_L0D           ( 1u << 4 )
#define NFC5_FIELD_THLD_DEACT_TRG_75MV          ( 0x0u << 4 )
#define NFC5_FIELD_THLD_DEACT_TRG_105MV         ( 0x1u << 4 )
#define NFC5_FIELD_THLD_DEACT_TRG_150MV         ( 0x2u << 4 )
#define NFC5_FIELD_THLD_DEACT_TRG_205MV         ( 0x3u << 4 )
#define NFC5_FIELD_THLD_DEACT_TRG_290MV         ( 0x4u << 4 )
#define NFC5_FIELD_THLD_DEACT_TRG_400MV         ( 0x5u << 4 )
#define NFC5_FIELD_THLD_DEACT_TRG_560MV         ( 0x6u << 4 )
#define NFC5_FIELD_THLD_DEACT_TRG_800MV         ( 0x7u << 4 )
#define NFC5_FIELD_THLD_DEACT_TRG_MASK          ( 7u << 4 )
#define NFC5_FIELD_THLD_DEACT_TRG_SHIFT         ( 4u )
#define NFC5_FIELD_THLD_DEACT_RFE_T3D           ( 1u << 3 )
#define NFC5_FIELD_THLD_DEACT_RFE_T2D           ( 1u << 2 )
#define NFC5_FIELD_THLD_DEACT_RFE_T1D           ( 1u << 1 )
#define NFC5_FIELD_THLD_DEACT_RFE_T0D           ( 1u << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_75MV          ( 0x0u << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_105MV         ( 0x1u << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_150MV         ( 0x2u << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_205MV         ( 0x3u << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_290MV         ( 0x4u << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_400MV         ( 0x5u << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_560MV         ( 0x6u << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_800MV         ( 0x7u << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_25MV          ( 0x8u << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_33MV          ( 0x9u << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_47MV          ( 0xAu << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_64MV          ( 0xBu << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_90MV          ( 0xCu << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_125MV         ( 0xDu << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_175MV         ( 0xEu << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_250MV         ( 0xFu << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_MASK          ( 0xFu << 0 )
#define NFC5_FIELD_THLD_DEACT_RFE_SHIFT         ( 0u )
#define NFC5_REGULATOR_CTRL_REG_S               ( 1u << 7 )
#define NFC5_REGULATOR_CTRL_REGE_3              ( 1u << 6 )
#define NFC5_REGULATOR_CTRL_REGE_2              ( 1u << 5 )
#define NFC5_REGULATOR_CTRL_REGE_1              ( 1u << 4 )
#define NFC5_REGULATOR_CTRL_REGE_0              ( 1u << 3 )
#define NFC5_REGULATOR_CTRL_REGE_MASK           ( 0xFu << 3 )
#define NFC5_REGULATOR_CTRL_REGE_SHIFT          ( 3u )
#define NFC5_REGULATOR_CTRL_MPSV2               ( 2u << 2 )
#define NFC5_REGULATOR_CTRL_MPSV1               ( 1u << 1 )
#define NFC5_REGULATOR_CTRL_MPSV0               ( 1u << 0 )
#define NFC5_REGULATOR_CTRL_MPSV_VDD            ( 0u )
#define NFC5_REGULATOR_CTRL_MPSV_VDD_A          ( 1u )
#define NFC5_REGULATOR_CTRL_MPSV_VDD_D          ( 2u )
#define NFC5_REGULATOR_CTRL_MPSV_VDD_RF         ( 3u )
#define NFC5_REGULATOR_CTRL_MPSV_VDD_AM         ( 4u )
#define NFC5_REGULATOR_CTRL_RFU                 ( 5u )
#define NFC5_REGULATOR_CTRL_RFU1                ( 6u )
#define NFC5_REGULATOR_CTRL_RFU2                ( 7u )
#define NFC5_REGULATOR_CTRL_MPSV_MASK           ( 7u )
#define NFC5_REGULATOR_CTRL_MPSV_SHIFT          ( 0u )

/**
 * @brief NFC 5 device address setting.
 * @details Specified setting for device slave address selection of
 * NFC 5 Click driver.
 */
#define NFC5_DEVICE_ADDRESS                     0x50

/**
 * @brief Data sample selection.
 * @details This macro sets data samples for SPI modules.
 * @note Available only on Microchip PIC family devices.
 * This macro will set data sampling for all SPI modules on MCU. 
 * Can be overwritten with @b nfc5_init which will set
 * @b SET_SPI_DATA_SAMPLE_MIDDLE by default on the mapped mikrobus.
 */
#define NFC5_SET_DATA_SAMPLE_EDGE               SET_SPI_DATA_SAMPLE_EDGE
#define NFC5_SET_DATA_SAMPLE_MIDDLE             SET_SPI_DATA_SAMPLE_MIDDLE

/*! @} */ // nfc5_set

/**
 * @defgroup nfc5_map NFC 5 MikroBUS Map
 * @brief MikroBUS pin mapping of NFC 5 Click driver.
 */

/**
 * @addtogroup nfc5_map
 * @{
 */

/**
 * @brief MikroBUS pin mapping.
 * @details Mapping pins of NFC 5 Click to the selected MikroBUS.
 */
#define NFC5_MAP_MIKROBUS( cfg, mikrobus ) \
    cfg.scl  = MIKROBUS( mikrobus, MIKROBUS_SCL ); \
    cfg.sda  = MIKROBUS( mikrobus, MIKROBUS_SDA ); \
    cfg.miso = MIKROBUS( mikrobus, MIKROBUS_MISO ); \
    cfg.mosi = MIKROBUS( mikrobus, MIKROBUS_MOSI ); \
    cfg.sck  = MIKROBUS( mikrobus, MIKROBUS_SCK ); \
    cfg.cs   = MIKROBUS( mikrobus, MIKROBUS_CS ); \
    cfg.irq  = MIKROBUS( mikrobus, MIKROBUS_INT )

/*! @} */ // nfc5_map
/*! @} */ // nfc5

/**
 * @brief NFC 5 Click driver selector.
 * @details Selects target driver interface of NFC 5 Click driver.
 */
typedef enum
{
    NFC5_DRV_SEL_SPI,      /**< SPI driver descriptor. */
    NFC5_DRV_SEL_I2C       /**< I2C driver descriptor. */

} nfc5_drv_t;

/**
 * @brief NFC 5 Click driver interface.
 * @details Definition of driver interface of NFC 5 Click driver.
 */
struct nfc5_s;
typedef err_t ( *nfc5_master_io_t )( struct nfc5_s*, uint8_t, uint8_t*, uint16_t ); /**< Driver serial interface. */

/**
 * @brief NFC 5 Click Struct for Analog Config Look Up Table Update.
 * @details Analog Config Look Up Table object definition of NFC 5 Click driver.
 */
typedef struct 
{
    const uint8_t *an_cfg_table;        /**< Reference to start of current Analog Configuration. */     
    uint16_t      an_cfg_table_size;    /**< Total size of Analog Configuration. */                     
    bool          ready;                /**< Indicate if Look Up Table is complete and ready for use. */

} nfc5_an_cfg_mgmt_t;

/**
 * @brief NFC 5 Click Struct for Analog Config Reg Address Mask values.
 * @details Struct that contain the Register-Mask-Value set. 
 * Make sure that the whole structure size is even and unaligned!
 */
typedef struct 
{
    uint8_t addr[ 2 ];  /**< Register Address. */   
    uint8_t mask;       /**< Register Mask Value. */
    uint8_t val;        /**< Register Value. */

} nfc5_an_cfg_reg_t;

/**
 * @brief NFC 5 Click rfal transceive context structure.
 * @details Struct that holds all context to be used on a Transceive.
 */
typedef struct 
{
    uint8_t*  tx_buf;      /**< (In)  Buffer where outgoing message is located. */
    uint16_t  tx_buf_len;  /**< (In)  Length of the outgoing message in bits. */
    
    uint8_t*  rx_buf;      /**< (Out) Buffer where incoming message will be placed. */
    uint16_t  rx_buf_len;  /**< (In)  Maximum length of the incoming message in bits. */
    uint16_t* rx_rcvd_len; /**< (Out) Actual received length in bits. */
    
    uint32_t  flags;       /**< (In)  Transceive Flags indication special handling. */
    uint32_t  fwt;         /**< (In)  Frame Waiting Time in 1/fc. */

} nfc5_rfal_trx_ctx_t;

/**
 * @brief NFC 5 Click rfal transceive states enum.
 * @details Predefined enum values for RFAL transceive states.
 */
typedef enum 
{
    NFC5_TXRX_STATE_IDLE             = 0,
    NFC5_TXRX_STATE_INIT             = 1,
    NFC5_TXRX_STATE_START            = 2,
    NFC5_TXRX_STATE_TX_IDLE          = 11,
    NFC5_TXRX_STATE_TX_WAIT_GT       = 12,
    NFC5_TXRX_STATE_TX_WAIT_FDT      = 13,
    NFC5_TXRX_STATE_TX_TRANSMIT      = 14,
    NFC5_TXRX_STATE_TX_WAIT_WL       = 15,
    NFC5_TXRX_STATE_TX_RELOAD_FIFO   = 16,
    NFC5_TXRX_STATE_TX_WAIT_TXE      = 17,
    NFC5_TXRX_STATE_TX_DONE          = 18,
    NFC5_TXRX_STATE_TX_FAIL          = 19,
    NFC5_TXRX_STATE_RX_IDLE          = 81,
    NFC5_TXRX_STATE_RX_WAIT_EON      = 82,
    NFC5_TXRX_STATE_RX_WAIT_RXS      = 83,
    NFC5_TXRX_STATE_RX_WAIT_RXE      = 84,
    NFC5_TXRX_STATE_RX_READ_FIFO     = 85,
    NFC5_TXRX_STATE_RX_ERR_CHECK     = 86,
    NFC5_TXRX_STATE_RX_READ_DATA     = 87,
    NFC5_TXRX_STATE_RX_WAIT_EOF      = 88,
    NFC5_TXRX_STATE_RX_DONE          = 89,
    NFC5_TXRX_STATE_RX_FAIL          = 90
    
} nfc5_rfal_trx_state_t;

/**
 * @brief NFC 5 Click RFAL RX TX structure.
 * @details Struct that holds all involved on a Transceive including the context passed by the caller.
 */
typedef struct 
{
    nfc5_rfal_trx_state_t   state;       /**< Current transceive state. */
    nfc5_rfal_trx_state_t   last_state;  /**< Last transceive state (debug purposes). */
    nfc5_rfal_trx_ctx_t     ctx;         /**< The transceive context given by the caller. */
    err_t                   status;      /**< Current status/error of the transceive. */

} nfc5_rfal_txrx_t;

/**
 * @brief NFC 5 Click RFAL FIFO structure.
 * @details Struct that holds counters to control the FIFO on Tx and Rx.
 */
typedef struct 
{    
    uint16_t  exp_wl;        /**< The amount of bytes expected to be Tx when a WL interrupt occours. */
    uint16_t  bytes_total;   /**< Total bytes to be transmitted OR the total bytes received. */
    uint16_t  bytes_written; /**< Amount of bytes already written on FIFO (Tx) OR read (RX) from FIFO and written on rxBuffer. */
    uint8_t   status[ 2 ];   /**< FIFO Status Registers. */

} nfc5_rfal_fifo_t;

/**
 * @brief NFC 5 Click RFAL structure.
 * @details Struct that contain RFAL field state and transceive and FIFO management.
 */
typedef struct 
{
    bool              field; /**< Current field state (On / Off). */
    nfc5_rfal_txrx_t  tx_rx; /**< RFAL's transceive management. */
    nfc5_rfal_fifo_t  fifo;  /**< RFAL's FIFO management. */

} nfc5_rfal_t;

/**
 * @brief NFC 5 Click RFAL NFCA sens res structure.
 * @details SENS_RES (ATQA) format Digital 1.1  6.6.3 & Table 7.
 */
typedef struct
{ 
    uint8_t anticollision_info; /**< SENS_RES Anticollision Information. */
    uint8_t platform_info;      /**< SENS_RES Platform Information. */

} nfc5_rfal_nfca_sens_res_t;

/**
 * @brief NFC 5 Click RFAL NFCA sel res structure.
 * @details SEL_RES (SAK) format Digital 1.1  6.8.2 & Table 19.
 */
typedef struct
{
    uint8_t      sak;                /**< Select Acknowledge. */

} nfc5_rfal_nfca_sel_res_t;

/**
 * @brief NFC 5 Click RFAL NFCA listen device structure.
 * @details NFC-A listener device (PICC) struct.
 */
typedef struct
{
    nfc5_rfal_nfca_sens_res_t   sens_res;                               /**< SENS_RES (ATQA). */
    nfc5_rfal_nfca_sel_res_t    sel_res;                                /**< SEL_RES  (SAK). */
    uint8_t                     nfc_id1_len;                            /**< NFCID1 Length. */
    uint8_t                     nfc_id1[ NFC5_NFCA_CASCADE_3_UID_LEN ]; /**< NFCID1   (UID). */
    bool                        is_sleep;                               /**< Device sleeping flag. */

} nfc5_rfal_nfca_listen_dev_t;

/**
 * @brief NFC 5 Click RFAL NFC device structure.
 * @details Device struct containing all its details.
 */
typedef struct
{
    nfc5_rfal_nfca_listen_dev_t  nfca;       /**< NFC-A Listen Device instance. */ 
    uint8_t                      *nfc_id;    /**< Device's NFCID. */
    uint8_t                      nfc_id_len; /**< Device's NFCID length. */

} nfc5_rfal_nfc_device_t;

/**
 * @brief NFC 5 Click RFAL NFC state enum.
 * @details Predefined enum valus for RFAL NFC main state.
 */
typedef enum
{
    NFC5_NFC_STATE_NOTINIT           =  0,   /**< Not Initialized state. */
    NFC5_NFC_STATE_IDLE              =  1,   /**< Initialize state. */
    NFC5_NFC_STATE_START_DISCOVERY   =  2,   /**< Start Discovery loop state. */
    NFC5_NFC_STATE_POLL_COLAVOIDANCE =  11,  /**< Collision Avoidance state. */
    NFC5_NFC_STATE_POLL_ACTIVATION   =  13,  /**< Activation state. */
    NFC5_NFC_STATE_ACTIVATED         =  30,  /**< Activated state. */
    NFC5_NFC_STATE_DEACTIVATION      =  34   /**< Deactivation state. */

} nfc5_rfal_nfc_state_t;

/**
 * @brief NFC 5 Click RFAL NFC structure.
 * @details RFAL NFC main struct.
 */
typedef struct
{
    nfc5_rfal_nfc_state_t   state;               /**< Main state. */
    uint8_t                 sel_dev_idx;         /**< Selected device index. */
    nfc5_rfal_nfc_device_t  *active_dev;         /**< Active device pointer. */
    nfc5_rfal_nfc_device_t  dev_list[ NFC5_NFC_MAX_DEVICES ];   /**< Location of device list. */
    uint8_t                 dev_cnt;             /**< Decices found counter. */
    bool                    is_tech_init;        /**< Flag indicating technology has been set. */
    bool                    is_oper_ongoing;     /**< Flag indicating opration is ongoing. */

} nfc5_rfal_nfc_t;

/**
 * @brief NFC 5 Click RFAL NFCA sel req structure.
 * @details SEL_REQ (Select) format Digital 1.1  6.8.1 & Table 17.
 */
typedef struct
{
    uint8_t sel_cmd;   /**< SDD_REQ SEL_CMD: cascade Level. */
    uint8_t sel_par;   /**< SDD_REQ SEL_PAR: Byte Count[4b] | Bit Count[4b] (NVB: Number of Valid Bits). */
    uint8_t nfc_id1[ NFC5_NFCA_CASCADE_1_UID_LEN ]; /**< NFCID1 data. */
    uint8_t bcc;       /**< Checksum calculated as exclusive-OR over the 4 bytes of NFCID1 CLn. */

} nfc5_rfal_nfca_sel_req_t;

/**
 * @brief NFC 5 Click Colission Resolution states enum.
 * @details Predefined enum values for Colission Resolution states.
 */
typedef enum
{
    NFC5_NFCA_CR_CL,                                /**< New Cascading Level state. */
    NFC5_NFCA_CR_SDD,                               /**< Perform anticollsion state. */
    NFC5_NFCA_CR_SEL,                               /**< Perform CL Selection state. */
    NFC5_NFCA_CR_DONE                               /**< Collision Resolution done state. */

} nfc5_col_res_state_t;

/**
 * @brief NFC 5 Click Colission Resolution context structure.
 * @details Colission Resolution context structure.
 */
typedef struct
{
    nfc5_rfal_nfca_listen_dev_t*    nfca_dev_list;  /**< Location of the device list. */
    uint8_t*                        dev_cnt;        /**< Location of the device counter. */
    bool                            coll_pending;   /**< Collision pending flag. */
    bool*                           coll_pend;      /**< Location of collision pending flag (Single CR). */
    nfc5_rfal_nfca_sel_req_t        sel_req;        /**< SelReqused during anticollision (Single CR). */
    nfc5_rfal_nfca_sel_res_t*       sel_res;        /**< Location to place of the SEL_RES(SAK) (Single CR). */
    uint8_t*                        nfc_id1;        /**< Location to place the NFCID1 (Single CR). */
    uint8_t*                        nfc_id1_len;    /**< Location to place the NFCID1 length (Single CR). */
    uint8_t                         cascade_lvl;    /**< Current Cascading Level (Single CR). */
    nfc5_col_res_state_t            state;          /**< Single Collision Resolution state (Single CR). */
    uint8_t                         bytes_tx_rx;    /**< TxRx bytes used during anticollision loop (Single CR). */
    uint8_t                         bits_tx_rx;     /**< TxRx bits used during anticollision loop (Single CR). */
    uint16_t                        rx_len;

} nfc5_col_res_par_t;

/**
 * @brief NFC 5 Click RFAL NFC-A instance structure.
 * @details RFAL NFC-A instance structure.
 */
typedef struct
{
    nfc5_col_res_par_t col_res;             /**< Collision Resolution context. */

} nfc5_rfal_nfca_t;


/**
 * @brief NFC 5 Click context object.
 * @details Context object definition of NFC 5 Click driver.
 */
typedef struct nfc5_s
{
    digital_in_t irq;                       /**< IRQ pin. */

    i2c_master_t i2c;                       /**< I2C driver object. */
    spi_master_t spi;                       /**< SPI driver object. */

    uint8_t      slave_address;             /**< Device slave address (used for I2C driver). */
    pin_name_t   chip_select;               /**< Chip select pin descriptor (used for SPI driver). */
    nfc5_drv_t   drv_sel;                   /**< Master driver interface selector. */

    nfc5_master_io_t write_f;               /**< Master write function. */
    nfc5_master_io_t read_f;                /**< Master read function. */

    uint32_t            int_status;         /**< Interrupt status. */
    nfc5_an_cfg_mgmt_t  an_cfg_mgmt;        /**< Analog Configuration LUT management. */
    nfc5_rfal_t         rfal;               /**< RFAL module instance. */
    nfc5_rfal_nfc_t     nfc_dev;            /**< RFAL NFC device instance. */
    nfc5_rfal_nfca_t    nfca;               /**< RFAL NFC-A instance. */

} nfc5_t;

/**
 * @brief NFC 5 Click configuration object.
 * @details Configuration object definition of NFC 5 Click driver.
 */
typedef struct
{
    pin_name_t scl;                         /**< Clock pin descriptor for I2C driver. */
    pin_name_t sda;                         /**< Bidirectional data pin descriptor for I2C driver. */
    pin_name_t miso;                        /**< Master input - slave output pin descriptor for SPI driver. */
    pin_name_t mosi;                        /**< Master output - slave input pin descriptor for SPI driver. */
    pin_name_t sck;                         /**< Clock pin descriptor for SPI driver. */
    pin_name_t cs;                          /**< Chip select pin descriptor for SPI driver. */
    pin_name_t irq;                         /**< IRQ pin. */

    uint32_t   i2c_speed;                   /**< I2C serial speed. */
    uint8_t    i2c_address;                 /**< I2C slave address. */

    uint32_t                          spi_speed;    /**< SPI serial speed. */
    spi_master_mode_t                 spi_mode;     /**< SPI master mode. */
    spi_master_chip_select_polarity_t cs_polarity;  /**< Chip select pin polarity. */

    nfc5_drv_t drv_sel;                     /**< Master driver interface selector. */

} nfc5_cfg_t;

/**
 * @brief NFC 5 Click return value data.
 * @details Predefined enum values for driver return values.
 */
typedef enum
{
    NFC5_OK = 0,
    NFC5_ERROR = -1

} nfc5_return_value_t;

/**
 * @brief NFC 5 Click RFAL library return value data.
 * @details Predefined enum values for RFAL library return values.
 */
typedef enum
{
    NFC5_RFAL_ERR_NONE                = 0,  /**< no error occurred. */
    NFC5_RFAL_ERR_NOMEM               = 1,  /**< not enough memory to perform the requested operation. */
    NFC5_RFAL_ERR_BUSY                = 2,  /**< device or resource busy. */
    NFC5_RFAL_ERR_IO                  = 3,  /**< generic IO error. */
    NFC5_RFAL_ERR_TIMEOUT             = 4,  /**< error due to timeout. */
    NFC5_RFAL_ERR_REQUEST             = 5,  /**< invalid request or requested function can't be executed at the moment. */
    NFC5_RFAL_ERR_NOMSG               = 6,  /**< No message of desired type. */
    NFC5_RFAL_ERR_PARAM               = 7,  /**< Parameter error. */
    NFC5_RFAL_ERR_SYSTEM              = 8,  /**< System error. */
    NFC5_RFAL_ERR_FRAMING             = 9,  /**< Framing error. */
    NFC5_RFAL_ERR_OVERRUN             = 10, /**< lost one or more received bytes. */  
    NFC5_RFAL_ERR_PROTO               = 11, /**< protocol error. */  
    NFC5_RFAL_ERR_INTERNAL            = 12, /**< Internal Error. */  
    NFC5_RFAL_ERR_AGAIN               = 13, /**< Call again. */  
    NFC5_RFAL_ERR_MEM_CORRUPT         = 14, /**< memory corruption. */  
    NFC5_RFAL_ERR_NOT_IMPLEMENTED     = 15, /**< not implemented. */  
    NFC5_RFAL_ERR_PC_CORRUPT          = 16, /**< Program Counter has been manipulated or spike/noise 
                                                 trigger illegal operation. */  
    NFC5_RFAL_ERR_SEND                = 17, /**< error sending. */  
    NFC5_RFAL_ERR_IGNORE              = 18, /**< indicates error detected but to be ignored. */  
    NFC5_RFAL_ERR_SEMANTIC            = 19, /**< indicates error in state machine (unexpected cmd). */  
    NFC5_RFAL_ERR_SYNTAX              = 20, /**< indicates error in state machine (unknown cmd). */  
    NFC5_RFAL_ERR_CRC                 = 21, /**< crc error. */   
    NFC5_RFAL_ERR_NOTFOUND            = 22, /**< transponder not found. */   
    NFC5_RFAL_ERR_NOTUNIQUE           = 23, /**< transponder not unique - more than one transponder in field. */   
    NFC5_RFAL_ERR_NOTSUPP             = 24, /**< requested operation not supported. */   
    NFC5_RFAL_ERR_WRITE               = 25, /**< write error. */   
    NFC5_RFAL_ERR_FIFO                = 26, /**< fifo over or underflow error. */   
    NFC5_RFAL_ERR_PAR                 = 27, /**< parity error. */   
    NFC5_RFAL_ERR_DONE                = 28, /**< transfer has already finished. */  
    NFC5_RFAL_ERR_RF_COLLISION        = 29, /**< collision error (Bit Collision or during RF Collision avoidance ). */  
    NFC5_RFAL_ERR_HW_OVERRUN          = 30, /**< lost one or more received bytes. */  
    NFC5_RFAL_ERR_RELEASE_REQ         = 31, /**< device requested release. */  
    NFC5_RFAL_ERR_SLEEP_REQ           = 32, /**< device requested sleep. */  
    NFC5_RFAL_ERR_WRONG_STATE         = 33, /**< incorrent state for requested operation. */  
    NFC5_RFAL_ERR_MAX_RERUNS          = 34, /**< blocking procedure reached maximum runs. */  
    NFC5_RFAL_ERR_DISABLED            = 35, /**< operation aborted due to disabled configuration. */   
    NFC5_RFAL_ERR_HW_MISMATCH         = 36, /**< expected hw do not match. */  
    NFC5_RFAL_ERR_LINK_LOSS           = 37, /**< Other device's field didn't behave as expected: 
                                                 turned off by Initiator in Passive mode, or AP2P did not turn on field. */  
    NFC5_RFAL_ERR_INVALID_HANDLE      = 38, /**< invalid or not initalized device handle. */  
    NFC5_RFAL_ERR_INCOMPLETE_BYTE     = 40, /**< Incomplete byte rcvd. */  
    NFC5_RFAL_ERR_INCOMPLETE_BYTE_01  = 41, /**< Incomplete byte rcvd - 1 bit. */      
    NFC5_RFAL_ERR_INCOMPLETE_BYTE_02  = 42, /**< Incomplete byte rcvd - 2 bit. */  
    NFC5_RFAL_ERR_INCOMPLETE_BYTE_03  = 43, /**< Incomplete byte rcvd - 3 bit. */  
    NFC5_RFAL_ERR_INCOMPLETE_BYTE_04  = 44, /**< Incomplete byte rcvd - 4 bit. */  
    NFC5_RFAL_ERR_INCOMPLETE_BYTE_05  = 45, /**< Incomplete byte rcvd - 5 bit. */  
    NFC5_RFAL_ERR_INCOMPLETE_BYTE_06  = 46, /**< Incomplete byte rcvd - 6 bit. */  
    NFC5_RFAL_ERR_INCOMPLETE_BYTE_07  = 47  /**< Incomplete byte rcvd - 7 bit. */ 

} nfc5_rfal_return_t;

/**
 * @brief NFC 5 Click TXRX flags values.
 * @details Predefined enum values for TXRX flags.
 */
typedef enum 
{
    NFC5_TXRX_FLAGS_CRC_TX_AUTO      = ( 0u << 0 ), /**< CRC will be generated automatic upon transmission. */
    NFC5_TXRX_FLAGS_CRC_TX_MANUAL    = ( 1u << 0 ), /**< CRC was calculated manually, included in txBuffer. */
    NFC5_TXRX_FLAGS_CRC_RX_KEEP      = ( 1u << 1 ), /**< Upon Reception keep the CRC in rxBuffer (reflected 
                                                         on rcvd length). */
    NFC5_TXRX_FLAGS_CRC_RX_REMV      = ( 0u << 1 ), /**< Enable CRC check and remove the CRC from rxBuffer. */
    NFC5_TXRX_FLAGS_NFCIP1_ON        = ( 1u << 2 ), /**< Enable NFCIP1 mode: Add SB(F0) and LEN bytes during 
                                                         Tx and skip SB(F0) byte during Rx. */
    NFC5_TXRX_FLAGS_NFCIP1_OFF       = ( 0u << 2 ), /**< Disable NFCIP1 mode: do not append protocol bytes while 
                                                         Tx nor skip while Rx. */
    NFC5_TXRX_FLAGS_AGC_OFF          = ( 1u << 3 ), /**< Disable Automatic Gain Control, improving multiple 
                                                         devices collision detection. */
    NFC5_TXRX_FLAGS_AGC_ON           = ( 0u << 3 ), /**< Enable Automatic Gain Control, improving single 
                                                         device reception. */
    NFC5_TXRX_FLAGS_PAR_RX_KEEP      = ( 1u << 4 ), /**< Disable Parity and CRC check and keep the Parity and 
                                                         CRC bits in the received buffer. */
    NFC5_TXRX_FLAGS_PAR_RX_REMV      = ( 0u << 0 ), /**< Enable Parity check and remove the parity bits from 
                                                         the received buffer. */
    NFC5_TXRX_FLAGS_PAR_TX_NONE      = ( 1u << 5 ), /**< Disable automatic Parity generation (ISO14443A) and use 
                                                         the one provided in the buffer. */
    NFC5_TXRX_FLAGS_PAR_TX_AUTO      = ( 0u << 5 ), /**< Enable automatic Parity generation (ISO14443A). */
    NFC5_TXRX_FLAGS_NFCV_FLAG_MANUAL = ( 1u << 6 ), /**< Disable automatic adaption of flag byte (ISO15693) 
                                                         according to current comm params. */
    NFC5_TXRX_FLAGS_NFCV_FLAG_AUTO   = ( 0u << 6 )  /**< Enable automatic adaption of flag byte (ISO115693) 
                                                         according to current comm params. */

} nfc5_tx_rx_flags_t;

/**
 * @brief NFC 5 Click RFAL ISO 14443A Short Frame Command values.
 * @details Predefined enum values for RFAL ISO 14443A Short Frame Command.
 */
typedef enum
{
     NFC5_14443A_SHORTFRAME_CMD_WUPA = 0x52,  /**< ISO14443A WUPA / NFC-A ALL_REQ. */
     NFC5_14443A_SHORTFRAME_CMD_REQA = 0x26   /**< ISO14443A REQA / NFC-A SENS_REQ. */ 

} nfc5_rfal_14443a_short_frame_cmd_t;

/**
 * @brief NFC 5 Click SDD_REQ (Select) Cascade Levels values.
 * @details Predefined enum values for SDD_REQ (Select) Cascade Levels.
 */
typedef enum
{
    NFC5_NFCA_SEL_CASCADE_L1 = 0,  /**< SDD_REQ Cascade Level 1. */
    NFC5_NFCA_SEL_CASCADE_L2 = 1,  /**< SDD_REQ Cascade Level 2. */
    NFC5_NFCA_SEL_CASCADE_L3 = 2   /**< SDD_REQ Cascade Level 3. */

} nfc5_nfca_sel_t;

/**
 * @brief NFC 5 Click SDD_REQ (Select) request Cascade Level command values.
 * @details Predefined enum values for SDD_REQ (Select) request Cascade Level command Digital 1.1 Table 15.
 */
typedef enum
{
    NFC5_NFCA_CMD_SEL_CL1 = 0x93, /**< SDD_REQ command Cascade Level 1. */
    NFC5_NFCA_CMD_SEL_CL2 = 0x95, /**< SDD_REQ command Cascade Level 2. */
    NFC5_NFCA_CMD_SEL_CL3 = 0x97  /**< SDD_REQ command Cascade Level 3. */

} nfc5_nfca_cmd_t;

/**
 * @brief NFC 5 Click SLP_REQ (HLTA) format structure.
 * @details SLP_REQ (HLTA) format Digital 1.1  6.9.1 & Table 20.
 */
typedef struct
{
    uint8_t frame[ NFC5_NFCA_SLP_REQ_LEN ];  /**< SLP:  0x50 0x00. */

} nfc5_rfal_nfca_slp_req_t;

/*!
 * @addtogroup nfc5 NFC 5 Click Driver
 * @brief API for configuring and manipulating NFC 5 Click driver.
 * @{
 */

/**
 * @brief NFC 5 configuration object setup function.
 * @details This function initializes Click configuration structure to initial
 * values.
 * @param[out] cfg : Click configuration structure.
 * See #nfc5_cfg_t object definition for detailed explanation.
 * @return Nothing.
 * @note The all used pins will be set to unconnected state.
 */
void nfc5_cfg_setup ( nfc5_cfg_t *cfg );

/**
 * @brief NFC 5 driver interface setup function.
 * @details This function sets a serial driver interface which will be used
 * further in the Click driver.
 * @param[out] cfg : Click configuration structure.
 * See #nfc5_cfg_t object definition for detailed explanation.
 * @param[in] drv_sel : Driver interface selection.
 * See #nfc5_drv_t object definition for detailed explanation.
 * @return Nothing.
 * @note This driver selection should be called before init function to configure
 * the driver to work with the serial interface which is consistent with the
 * real state of the hardware. If this function is not called, the default
 * driver interface will be set.
 */
void nfc5_drv_interface_sel ( nfc5_cfg_t *cfg, nfc5_drv_t drv_sel );

/**
 * @brief NFC 5 initialization function.
 * @details This function initializes all necessary pins and peripherals used
 * for this Click board.
 * @param[out] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] cfg : Click configuration structure.
 * See #nfc5_cfg_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_init ( nfc5_t *ctx, nfc5_cfg_t *cfg );

/**
 * @brief NFC 5 default configuration function.
 * @details This function executes a default configuration of NFC 5
 * Click board.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note This function can consist any necessary configuration or setting to put
 * device into operating mode.
 */
err_t nfc5_default_cfg ( nfc5_t *ctx );

/**
 * @brief NFC 5 data writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_generic_write ( nfc5_t *ctx, uint8_t reg, uint8_t *data_in, uint16_t len );

/**
 * @brief NFC 5 data reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_generic_read ( nfc5_t *ctx, uint8_t reg, uint8_t *data_out, uint16_t len );

/**
 * @brief NFC 5 send direct command function.
 * @details This function is used to start so-called direct command. These commands
 * are implemented inside the chip and each command has unique code (see datasheet).
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] cmd : Code of the direct command to be executed.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_send_cmd ( nfc5_t *ctx, uint8_t cmd );

/**
 * @brief NFC 5 send direct command with result function.
 * @details This function executes the direct command given by @a cmd waits for
 * @a timeout for I_dct and returns the result read from register @a result_reg.
 * The value of cmd is not checked.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] cmd : Code of the direct command to be executed.
 * @param[in] result_reg : Address of the register containing the result.
 * @param[in] timeout : Time in microseconds to wait before reading the result.
 * @param[out] result: Result.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_send_cmd_with_res ( nfc5_t *ctx, uint8_t cmd, uint8_t result_reg, uint32_t timeout, uint8_t *result );

/**
 * @brief NFC 5 write register function.
 * @details This function writes a desired data to the selected register.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_write_reg ( nfc5_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief NFC 5 read register function.
 * @details This function reads a desired data from the selected register.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[out] data_out : Output data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_read_reg ( nfc5_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief NFC 5 write multiple registers function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_write_regs ( nfc5_t *ctx, uint8_t reg, uint8_t *data_in, uint16_t len );

/**
 * @brief NFC 5 read multiple registers function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_read_regs ( nfc5_t *ctx, uint8_t reg, uint8_t *data_out, uint16_t len );

/**
 * @brief NFC 5 clear register bits function.
 * @details This function clears the given bitmask on the selected register.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] clr_mask : Bitmask of bits to be cleared.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_clear_reg_bits ( nfc5_t *ctx, uint8_t reg, uint8_t clr_mask );

/**
 * @brief NFC 5 set register bits function.
 * @details This function sets the given bitmask on the selected register.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] set_mask : Bitmask of bits to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_set_reg_bits ( nfc5_t *ctx, uint8_t reg, uint8_t set_mask );

/**
 * @brief NFC 5 modify register bits function.
 * @details This function modifies desired bits of the selected register.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] reg : Register address.
 * @param[in] clr_mask : Bitmask of bits to be cleared.
 * @param[in] set_mask : Bitmask of bits to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_modify_reg_bits ( nfc5_t *ctx, uint8_t reg, uint8_t clr_mask, uint8_t set_mask );

/**
 * @brief NFC 5 write fifo function.
 * @details This function writes a desired number of data bytes to FIFO.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of data bytes (up to 512).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_write_fifo ( nfc5_t *ctx, uint8_t *data_in, uint16_t len );

/**
 * @brief NFC 5 read fifo function.
 * @details This function reads a desired number of data bytes from FIFO.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of data bytes (up to 512).
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_read_fifo ( nfc5_t *ctx, uint8_t *data_out, uint16_t len );

/**
 * @brief NFC 5 write test register function.
 * @details This function writes a desired data to the selected test register.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] reg : Test register address.
 * @param[in] data_in : Data to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_write_test_register ( nfc5_t *ctx, uint8_t reg, uint8_t data_in );

/**
 * @brief NFC 5 read test register function.
 * @details This function reads a desired data from the selected test register.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] reg : Test register address.
 * @param[out] data_out : Output data read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_read_test_register ( nfc5_t *ctx, uint8_t reg, uint8_t *data_out );

/**
 * @brief NFC 5 modify test register bits function.
 * @details This function modifies desired bits of the selected test register.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] reg : Test register address.
 * @param[in] clr_mask : Bitmask of bits to be cleared.
 * @param[in] set_mask : Bitmask of bits to be set.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_modify_test_reg_bits ( nfc5_t *ctx, uint8_t reg, uint8_t clr_mask, uint8_t set_mask );

/**
 * @brief NFC 5 enable interrupt function.
 * @details This function enables all interrupts given by @a mask, 
 * NFC5_IRQ_MASK_ALL enables all interrupts.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] mask : Mask indicating the interrupts to be enabled.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_enable_interrupt ( nfc5_t *ctx, uint32_t mask );

/**
 * @brief NFC 5 disable interrupt function.
 * @details This function disables all interrupts given by @a mask, 
 * NFC5_IRQ_MASK_ALL disables all interrupts.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] mask : Mask indicating the interrupts to be disabled.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_disable_interrupt ( nfc5_t *ctx, uint32_t mask );

/**
 * @brief NFC 5 clear interrupts function.
 * @details This function clears all interrupt flags.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_clear_interrupts ( nfc5_t *ctx );

/**
 * @brief NFC 5 check for received interrupts function.
 * @details This function checks the received interrupts and saves the result into 
 * the int_status variable of the Click context object structure.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_check_interrupts ( nfc5_t *ctx );

/**
 * @brief NFC 5 wait for interrupt function.
 * @details This function checks the received interrupts and waits
 * for maximal @a timeout ( microseconds ) for the @b first interrupt indicated
 * with @a mask to occur.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] mask : Mask indicating the interrupts to wait for.
 * @param[in] timeout : Time in microseconds until timeout occurs.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint32_t nfc5_wait_interrupt ( nfc5_t *ctx, uint32_t mask, uint32_t timeout );

/**
 * @brief NFC 5 get interrupt function.
 * @details This function is used to check whether the interrupt given by @a mask 
 * is set in the int_status variable of the Click context object structure. 
 * If yes the interrupt gets cleared. This function returns
 * only status bits which are inside @a mask.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] mask : Mask indicating the interrupts to check for.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
uint32_t nfc5_get_interrupt ( nfc5_t *ctx, uint32_t mask );

/**
 * @brief NFC 5 check chip ID function.
 * @details This function checks if the chip ID is as expected.
 * 5 bit IC type code for ST25R3918: 00101, the 3 lsb contain the IC revision code.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[out] revision : The IC revision code.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_check_chip_id ( nfc5_t *ctx, uint8_t *revision );

/**
 * @brief NFC 5 enable oscillator and regulator function.
 * @details This function turns on oscillator and regulator and waits for the 
 * oscillator to become stable.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_enable_osc ( nfc5_t *ctx );

/**
 * @brief NFC 5 measure voltage function.
 * @details This function measures the voltage on one of VDD and VDD_* and returns 
 * the result in mV.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[in] mpsv_src : one of NFC5_REGULATOR_CTRL_MPSV_VDD,
 *                              NFC5_REGULATOR_CTRL_MPSV_VDD_A,
 *                              NFC5_REGULATOR_CTRL_MPSV_VDD_D,
 *                              NFC5_REGULATOR_CTRL_MPSV_VDD_RF,
 *                              NFC5_REGULATOR_CTRL_MPSV_VDD_AM.
 * @param[out] res_mv : The measured voltage in mV.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t nfc5_measure_voltage ( nfc5_t *ctx, uint8_t mpsv_src, uint16_t *res_mv );

/**
 * @brief NFC 5 get irq pin function.
 * @details This function returns the IRQ pin logic state.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @return Pin logic state.
 * @note None.
 */
uint8_t nfc5_get_irq_pin ( nfc5_t *ctx );

/**
 * @brief NFC 5 get mifare tag UID function.
 * @details This function reads the UID of a mifare tag.
 * @param[in] ctx : Click context object.
 * See #nfc5_t object definition for detailed explanation.
 * @param[out] uid : Mifare tag UID (up to 10 bytes).
 * @param[out] uid_len : Tag UID length in bytes.
 * @return @li @c  0 - Success - Tag UID read successfully,
 *         @li @c -1 - Error - There's no tag detected.
 *
 * See #err_t definition for detailed explanation.
 * @note This function should be called in a loop.
 */
err_t nfc5_get_mifare_tag_uid ( nfc5_t *ctx, uint8_t *uid, uint8_t *uid_len );

#ifdef __cplusplus
}
#endif
#endif // NFC5_H

/*! @} */ // nfc5

// ------------------------------------------------------------------------ END
