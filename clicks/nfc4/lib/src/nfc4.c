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
 * @file nfc4.c
 * @brief NFC 4 Click Driver.
 */

#include "nfc4.h"

/**
 * @brief Dummy data.
 * @details Definition of dummy data.
 */
#define DUMMY             0x00

/**
 * @brief NFC 4 Click MODE ENTRY 1 REG macro.
 * @details Macro for Configuration Setting with only 1 register-mask-value set:
 *  - Configuration ID[2], Number of Register sets to follow[1], Register[2], Mask[1], Value[1] 
 */
#define MODE_ENTRY_1_REG(MODE, R0, M0, V0) \
                        (MODE >> 8), (MODE & 0xFF), 1, (R0 >> 8), (R0 & 0xFF), (M0), (V0)

/**
 * @brief NFC 4 Click MODE ENTRY 5 REG macro.
 * @details Macro for Configuration Setting with only 5 register-mask-value set:
 *  - Configuration ID[2], Number of Register sets to follow[1], Register[2], Mask[1], Value[1], 
 *                                                               Register[2], Mask[1], Value[1], Register[2]... 
*/
#define MODE_ENTRY_5_REG(MODE, R0, M0, V0, R1, M1, V1, R2, M2, V2, R3, M3, V3, R4, M4, V4) \
                        (MODE >> 8), (MODE & 0xFF), 5, (R0 >> 8), (R0 & 0xFF), (M0), (V0) \
                                                     , (R1 >> 8), (R1 & 0xFF), (M1), (V1) \
                                                     , (R2 >> 8), (R2 & 0xFF), (M2), (V2) \
                                                     , (R3 >> 8), (R3 & 0xFF), (M3), (V3) \
                                                     , (R4 >> 8), (R4 & 0xFF), (M4), (V4)

/**
 * @brief NFC 4 Click MODE ENTRY 6 REG macro.
 * @details Macro for Configuration Setting with only 6 register-mask-value set:
 *  - Configuration ID[2], Number of Register sets to follow[1], Register[2], Mask[1], Value[1], 
 *                                                               Register[2], Mask[1], Value[1], Register[2]... 
 */
#define MODE_ENTRY_6_REG(MODE, R0, M0, V0, R1, M1, V1, R2, M2, V2, R3, M3, V3, R4, M4, V4, R5, M5, V5) \
                        (MODE >> 8), (MODE & 0xFF), 6, (R0 >> 8), (R0 & 0xFF), (M0), (V0) \
                                                     , (R1 >> 8), (R1 & 0xFF), (M1), (V1) \
                                                     , (R2 >> 8), (R2 & 0xFF), (M2), (V2) \
                                                     , (R3 >> 8), (R3 & 0xFF), (M3), (V3) \
                                                     , (R4 >> 8), (R4 & 0xFF), (M4), (V4) \
                                                     , (R5 >> 8), (R5 & 0xFF), (M5), (V5)

/**
 * @brief NFC 4 Click MODE ENTRY 17 REG macro.
 * @details Macro for Configuration Setting with only 17 register-mask-value set:
 *  - Configuration ID[2], Number of Register sets to follow[1], Register[2], Mask[1], Value[1], 
 *                                                               Register[2], Mask[1], Value[1], Register[2]... 
 */
#define MODE_ENTRY_17_REG(MODE, R0, M0, V0, R1, M1, V1, R2, M2, V2, R3, M3, V3, R4, M4, V4, R5, M5, V5, \
                                R6, M6, V6, R7, M7, V7, R8, M8, V8, R9, M9, V9, R10, M10, V10, R11, M11, \
                                V11, R12, M12, V12, R13, M13, V13, R14, M14, V14, R15, M15, V15, R16, M16, V16) \
                         (MODE >> 8), (MODE & 0xFF), 17, (R0 >> 8), (R0 & 0xFF), (M0), (V0) \
                                                       , (R1 >> 8), (R1 & 0xFF), (M1), (V1) \
                                                       , (R2 >> 8), (R2 & 0xFF), (M2), (V2) \
                                                       , (R3 >> 8), (R3 & 0xFF), (M3), (V3) \
                                                       , (R4 >> 8), (R4 & 0xFF), (M4), (V4) \
                                                       , (R5 >> 8), (R5 & 0xFF), (M5), (V5) \
                                                       , (R6 >> 8), (R6 & 0xFF), (M6), (V6) \
                                                       , (R7 >> 8), (R7 & 0xFF), (M7), (V7) \
                                                       , (R8 >> 8), (R8 & 0xFF), (M8), (V8) \
                                                       , (R9 >> 8), (R9 & 0xFF), (M9), (V9) \
                                                       , (R10 >> 8), (R10 & 0xFF), (M10), (V10) \
                                                       , (R11 >> 8), (R11 & 0xFF), (M11), (V11) \
                                                       , (R12 >> 8), (R12 & 0xFF), (M12), (V12) \
                                                       , (R13 >> 8), (R13 & 0xFF), (M13), (V13) \
                                                       , (R14 >> 8), (R14 & 0xFF), (M14), (V14) \
                                                       , (R15 >> 8), (R15 & 0xFF), (M15), (V15) \
                                                       , (R16 >> 8), (R16 & 0xFF), (M16), (V16)                            


/**
 * @brief NFC 4 Click GETU16 macro.
 * @details Cast two Big Endian 8-bits byte array to 16-bits unsigned. 
 */
#define GETU16( a )           ( ( ( uint16_t )( a )[ 0 ] << 8 ) | ( uint16_t )( a )[ 1 ] )

/**
 * @brief NFC 4 Click analog config default settings.
 * @details Analog config default settings.
 */
static const uint8_t nfc4_analog_config_settings [ ] = 
{
    /****** Default Analog Configuration for Chip-Specific Reset ******/
    MODE_ENTRY_17_REG( ( NFC4_ANALOG_CONFIG_TECH_CHIP | NFC4_ANALOG_CONFIG_CHIP_INIT )
        , NFC4_REG_IO_CFG_1, ( NFC4_IO_CFG_1_OUT_CL_MASK | NFC4_IO_CFG_1_LF_CLK_OFF ), 0x07                               
        /* Disable MCU_CLK */
        , NFC4_REG_IO_CFG_2, ( NFC4_IO_CFG_2_MISO_PD1 | NFC4_IO_CFG_2_MISO_PD2 ), 0x18                                   
        /* SPI Pull downs */
        , NFC4_REG_IO_CFG_2, NFC4_IO_CFG_2_AAT_EN, NFC4_IO_CFG_2_AAT_EN                                                
        /* Enable AAT */
        , NFC4_REG_TX_DRIVER, NFC4_TX_DRIVER_D_RES_MASK, 0x00                                                                    
        /* Set RFO resistance Active Tx */
        , NFC4_REG_RES_AM_MOD, 0xFF, 0x80                                                                                                 
        /* Use minimum non-overlap */
        , NFC4_REG_FIELD_THLD_ACT, NFC4_FIELD_THLD_ACT_TRG_MASK, NFC4_FIELD_THLD_ACT_TRG_105MV      
        /* Lower activation threshold (higher than deactivation)*/
        , NFC4_REG_FIELD_THLD_ACT, NFC4_FIELD_THLD_ACT_RFE_MASK, NFC4_FIELD_THLD_ACT_RFE_105MV      
        /* Lower activation threshold (higher than deactivation)*/
        , NFC4_REG_FIELD_THLD_DEACT, NFC4_FIELD_THLD_DEACT_TRG_MASK, NFC4_FIELD_THLD_DEACT_TRG_75MV   
        /* Lower deactivation threshold */
        , NFC4_REG_FIELD_THLD_DEACT, NFC4_FIELD_THLD_DEACT_RFE_MASK, NFC4_FIELD_THLD_DEACT_RFE_75MV   
        /* Lower deactivation threshold */
        , NFC4_REG_AUX_MOD, NFC4_AUX_MOD_LM_EXT, 0x00                                                                            
        /* Disable External Load Modulation */
        , NFC4_REG_AUX_MOD, NFC4_AUX_MOD_LM_DRI, NFC4_AUX_MOD_LM_DRI                                                    
        /* Use internal Load Modulation */
        , NFC4_REG_PASSIVE_TARGET, NFC4_PASSIVE_TARGET_FDEL_MASK, ( 5U << NFC4_PASSIVE_TARGET_FDEL_SHIFT )                  
        /* Adjust the FDT to be aligned with the bitgrid  */
        , NFC4_REG_PT_MOD, ( NFC4_PT_MOD_PTM_RES_MASK | NFC4_PT_MOD_PT_RES_MASK ), 0x5f                                   
        /* Reduce RFO resistance in Modulated state */
        , NFC4_REG_EMD_SUP_CFG, NFC4_EMD_SUP_CFG_RX_START_EMV, NFC4_EMD_SUP_CFG_RX_START_EMV_ON                      
        /* Enable start on first 4 bits */
        , NFC4_REG_ANT_TUNE_1, 0xFF, 0x82                                                                                                 
        /* Set Antenna Tuning (Poller): ANTL */
        , NFC4_REG_ANT_TUNE_2, 0xFF, 0x82                                                                                                 
        /* Set Antenna Tuning (Poller): ANTL */
        , 0x84U, 0x10, 0x10                                                                                                                     
        /* Avoid chip internal overheat protection */
        )

    /****** Default Analog Configuration for Poll NFC-A Tx 106 ******/
    , MODE_ENTRY_5_REG( ( NFC4_ANALOG_CONFIG_POLL | NFC4_ANALOG_CONFIG_TECH_NFCA | 
                          NFC4_ANALOG_CONFIG_BITRATE_106 | NFC4_ANALOG_CONFIG_TX )
        , NFC4_REG_MODE, NFC4_MODE_TR_AM, NFC4_MODE_TR_AM_OOK                                              
        /* Use OOK */
        , NFC4_REG_OVERSHOOT_CFG_1,  0xFF, 0x40                                                                              
        /* Set default Overshoot Protection */
        , NFC4_REG_OVERSHOOT_CFG_2,  0xFF, 0x03                                                                              
        /* Set default Overshoot Protection */
        , NFC4_REG_UNDERSHOOT_CFG_1, 0xFF, 0x40                                                                              
        /* Set default Undershoot Protection */
        , NFC4_REG_UNDERSHOOT_CFG_2, 0xFF, 0x03                                                                              
        /* Set default Undershoot Protection */
        )
                      
    /****** Default Analog Configuration for Poll NFC-A Rx 106 ******/
    , MODE_ENTRY_6_REG( ( NFC4_ANALOG_CONFIG_POLL | NFC4_ANALOG_CONFIG_TECH_NFCA | 
                          NFC4_ANALOG_CONFIG_BITRATE_106 | NFC4_ANALOG_CONFIG_RX )
        , NFC4_REG_RX_CFG_1,   0xFF, 0x08
        , NFC4_REG_RX_CFG_2,   0xFF, 0x2D
        , NFC4_REG_RX_CFG_3,   0xFF, 0x00
        , NFC4_REG_RX_CFG_4,   0xFF, 0x00
        , NFC4_REG_CORR_CFG_1, 0xFF, 0x51
        , NFC4_REG_CORR_CFG_2, 0xFF, 0x00
        )

    /****** Default Analog Configuration for Poll NFC-A Anticolision setting ******/
    , MODE_ENTRY_1_REG( ( NFC4_ANALOG_CONFIG_POLL | NFC4_ANALOG_CONFIG_TECH_NFCA | 
                          NFC4_ANALOG_CONFIG_BITRATE_COMMON | NFC4_ANALOG_CONFIG_ANTICOL )
        , NFC4_REG_CORR_CFG_1, NFC4_CORR_CFG_1_CORR_S6, 0x00                                                            
        /* Set collision detection level different from data */
        )
};

/** 
 * @brief NFC 4 perform collision avoidance function. 
 * @details This function performs Collision Avoidance with the given threshold.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] field_on_cmd  : Field ON command to be executed NFC4_CMD_NFC_INITIAL_FIELD_ON
 *                            or NFC4_CMD_NFC_RESPONSE_FIELD_ON  
 * @param[in] pd_threshold  : Peer Detection Threshold  (NFC4_FIELD_THLD_ACT_TRG_xx)
 *                            0xff : don't set Threshold (NFC4_THLD_DO_NOT_SET)
 * @param[in] ca_threshold  : Collision Avoidance Threshold (NFC4_FIELD_THLD_ACT_RFE_xx)
 *                            0xff : don't set Threshold (NFC4_THLD_DO_NOT_SET)
 * @return  @li @c NFC4_RFAL_ERR_NONE         : No collision detected
 *          @li @c NFC4_RFAL_ERR_RF_COLLISION : Collision detected
 *          @li @c NFC4_RFAL_ERR_PARAM        : Invalid parameter
 */
static err_t nfc4_perform_collision_avoidance( nfc4_t *ctx, uint8_t field_on_cmd, 
                                               uint8_t pd_threshold, uint8_t ca_threshold );

/** 
 * @brief NFC 4 set num tx bits function. 
 * @details This function sets internal registers with correct number of complete bytes and
 * bits to be sent.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] n_bits : Number of bits to be set/transmitted.
 * @return None.
 */
static void nfc4_set_num_tx_bits ( nfc4_t *ctx, uint16_t n_bits );

/** 
 * @brief NFC 4 set no response time function. 
 * @details This function sets the No Response Time with the given value.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] nrt_64fcs : No response time in steps of 64/fc (4.72us).
 * @return  @li @c NFC4_RFAL_ERR_NONE         : No error
 *          @li @c NFC4_RFAL_ERR_PARAM        : Invalid parameter (time is too large)
 */
static err_t nfc4_set_no_response_time( nfc4_t *ctx, uint32_t nrt_64fcs );

/** 
 * @brief NFC 4 rfal iso14443a transceive anticollision frame function. 
 * @details This function performs ISO14443A anti-collision. 
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in]   buf           : Reference to ANTICOLLISION command (with known UID if any) to be sent (also out param)
 *                              reception will be place on this buf after bytes_to_send 
 * @param[in]   bytes_to_send : Reference number of full bytes to be sent (including CMD byte and SEL_PAR)
 *                              if a collision occurs will contain the number of clear bytes  
 * @param[in]   bits_to_send  : Reference to number of bits (0-7) to be sent; and received (also out param)
 *                              if a collision occurs will indicate the number of clear bits (also out param)
 * @param[out]  rx_length     : Reference to the return the received length
 * @param[in]   fwt           : Frame Waiting Time in 1/fc
 * @return  @li @c NFC4_RFAL_ERR_NONE      : No error
 */
static err_t nfc4_rfal_iso14443a_transceive_anticollision_frame( nfc4_t *ctx, uint8_t *buf, uint8_t *bytes_to_send, 
                                                                 uint8_t *bits_to_send, uint16_t *rx_length, uint32_t fwt );

/** 
 * @brief NFC 4 rfal iso14443a transceive short frame function. 
 * @details This function sends REQA to detect if there is any PICC in the field.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in]  tx_cmd      : Type of short frame to be sent:
 *                              0x52 WUPA / ALL_REQ
 *                              0x26 REQA / SENS_REQ
 * @param[out] rx_buf      : Buffer to place the response
 * @param[in]  rx_buf_len  : Length of rx_buf
 * @param[out] rx_rcvd_len : Received length
 * @param[in]  fwt         : Frame Waiting Time in 1/fc
 * @return  @li @c NFC4_RFAL_ERR_COLLISION : Collision has occurred
 *          @li @c NFC4_RFAL_ERR_TIMEOUT   : No response
 *          @li @c NFC4_RFAL_ERR_NONE      : No error
 */
static err_t nfc4_rfal_iso14443a_transceive_short_frame( nfc4_t *ctx, nfc4_rfal_14443a_short_frame_cmd_t tx_cmd, 
                                                         uint8_t* rx_buf, uint8_t rx_buf_len, uint16_t* rx_rcvd_len, 
                                                         uint32_t fwt );

/** 
 * @brief NFC 4 rfal nfca poller initialize function. 
 * @details This function configures RFAL RF layer to perform as a 
 * NFC-A Poller/RW (ISO14443A PCD) including all default timings and bit rate to 106 kbps.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return  @li @c NFC4_RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 *          @li @c NFC4_RFAL_ERR_NONE         : No error
 */
static err_t nfc4_rfal_nfca_poller_initialize( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal nfca poller sleep function. 
 * @details This function sends a SLP_REQ (HLTA)
 * No response is expected afterwards   Digital 1.1  6.9.2.1 
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return  @li @c NFC4_RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 *          @li @c NFC4_RFAL_ERR_PARAM        : Invalid parameters
 *          @li @c NFC4_RFAL_ERR_IO           : Generic internal error
 *          @li @c NFC4_RFAL_ERR_NONE         : No error
 */
static err_t nfc4_rfal_nfca_poller_sleep( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal nfca poller select function. 
 * @details This function selects a NFC-A Listener device (PICC).
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return  @li @c NFC4_RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 *          @li @c NFC4_RFAL_ERR_PARAM        : Invalid parameters
 *          @li @c NFC4_RFAL_ERR_IO           : Generic internal error
 *          @li @c NFC4_RFAL_ERR_TIMEOUT      : Timeout error
 *          @li @c NFC4_RFAL_ERR_PAR          : Parity error detected
 *          @li @c NFC4_RFAL_ERR_CRC          : CRC error detected
 *          @li @c NFC4_RFAL_ERR_FRAMING      : Framing error detected
 *          @li @c NFC4_RFAL_ERR_PROTO        : Protocol error detected
 *          @li @c NFC4_RFAL_ERR_NONE         : No error, SEL_RES received
 */
static err_t nfc4_rfal_nfca_poller_select( nfc4_t *ctx, uint8_t *nfc_id1, uint8_t nfc_id_len, 
                                           nfc4_rfal_nfca_sel_res_t *sel_res );

/** 
 * @brief NFC 4 rfal nfca poller check presence function. 
 * @details This function checks if a NFC-A Listen device (PICC) is present on the field
 * by sending an ALL_REQ (WUPA) or SENS_REQ (REQA).
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return  @li @c NFC4_RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 *          @li @c NFC4_RFAL_ERR_PARAM        : Invalid parameters
 *          @li @c NFC4_RFAL_ERR_IO           : Generic internal error
 *          @li @c NFC4_RFAL_ERR_RF_COLLISION : Collision detected one or more device in the field
 *          @li @c NFC4_RFAL_ERR_TIMEOUT      : Timeout error, no listener device detected
 *          @li @c NFC4_RFAL_ERR_PAR          : Parity error detected, one or more device in the field
 *          @li @c NFC4_RFAL_ERR_CRC          : CRC error detected, one or more device in the field
 *          @li @c NFC4_RFAL_ERR_FRAMING      : Framing error detected, one or more device in the field
 *          @li @c NFC4_RFAL_ERR_PROTO        : Protocol error detected, one or more device in the field
 *          @li @c NFC4_RFAL_ERR_NONE         : No error, one or more device in the field
 */
static err_t nfc4_rfal_nfca_poller_check_presence( nfc4_t *ctx, nfc4_rfal_14443a_short_frame_cmd_t cmd, 
                                                   nfc4_rfal_nfca_sens_res_t *sens_res );

/** 
 * @brief NFC 4 rfal nfca poller get single collision resolution status function. 
 * @details This function returns the single Collision Resolution status
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return  @li @c NFC4_RFAL_ERR_BUSY         : Operation is ongoing
 *          @li @c NFC4_RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 *          @li @c NFC4_RFAL_ERR_PARAM        : Invalid parameters
 *          @li @c NFC4_RFAL_ERR_IO           : Generic internal error
 *          @li @c NFC4_RFAL_ERR_TIMEOUT      : Timeout error
 *          @li @c NFC4_RFAL_ERR_PAR          : Parity error detected
 *          @li @c NFC4_RFAL_ERR_CRC          : CRC error detected
 *          @li @c NFC4_RFAL_ERR_FRAMING      : Framing error detected
 *          @li @c NFC4_RFAL_ERR_PROTO        : Protocol error detected
 *          @li @c NFC4_RFAL_ERR_NONE         : No error, activation successful
 */
static err_t nfc4_rfal_nfca_poller_get_single_collision_resolution_status( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal nfca poller start single collision resolution function. 
 * @details This function starts the single Collision resolution.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] coll_pending  : Collision pending flag.
 * @param[in] sel_res       : SEL_RES(SAK) (Single CR).
 * @param[in] nfc_id1       : NFCID1 (Single CR).
 * @param[in] nfc_id1_len   : NFCID1 length (Single CR).
 * @return  @li @c NFC4_RFAL_ERR_NONE         : No error
 *          @li @c NFC4_RFAL_ERR_PARAM        : Invalid parameters
 */
static err_t nfc4_rfal_nfca_poller_start_single_collision_resolution( nfc4_t *ctx, bool *coll_pending, 
                                                                                   nfc4_rfal_nfca_sel_res_t *sel_res, 
                                                                                   uint8_t *nfc_id1, 
                                                                                   uint8_t *nfc_id1_len );

/** 
 * @brief NFC 4 rfal nfca poller get full collision resolution status function. 
 * @details This function returns the Collision Resolution status
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return  @li @c NFC4_RFAL_ERR_BUSY         : Operation is ongoing
 *          @li @c NFC4_RFAL_ERR_WRONG_STATE  : RFAL not initialized or incorrect mode
 *          @li @c NFC4_RFAL_ERR_PARAM        : Invalid parameters
 *          @li @c NFC4_RFAL_ERR_IO           : Generic internal error
 *          @li @c NFC4_RFAL_ERR_TIMEOUT      : Timeout error
 *          @li @c NFC4_RFAL_ERR_PAR          : Parity error detected
 *          @li @c NFC4_RFAL_ERR_CRC          : CRC error detected
 *          @li @c NFC4_RFAL_ERR_FRAMING      : Framing error detected
 *          @li @c NFC4_RFAL_ERR_PROTO        : Protocol error detected
 *          @li @c NFC4_RFAL_ERR_NONE         : No error, activation successful
 */
static err_t nfc4_rfal_nfca_poller_get_full_collision_resolution_status( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal nfca poller start full collision resolution function. 
 * @details This function starts the full Collision resolution.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[out] nfca_dev_list : NFC-A listener device info
 * @param[out] dev_cnt       : Devices found counter
 * @return  @li @c NFC4_RFAL_ERR_NONE         : No error
 *          @li @c NFC4_RFAL_ERR_WRONG_STATE  : RFAL not initialized
 *          @li @c NFC4_RFAL_ERR_IO           : Generic internal error
 *          @li @c NFC4_RFAL_ERR_PARAM        : Invalid parameters
 */
static err_t nfc4_rfal_nfca_poller_start_full_collision_resolution( nfc4_t *ctx, 
                                                                    nfc4_rfal_nfca_listen_device_t *nfca_dev_list, 
                                                                    uint8_t *dev_cnt );

/** 
 * @brief NFC 4 rfal nfca calculate bcc function. 
 * @details This function calculates bcc checksum of @a buf.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] buf : Buffer from which it will calculate BCC
 * @param[in] buf_len : Buffer length
 * @return Calculated BCC checksum.
 */
static uint8_t nfc4_rfal_nfca_calculate_bcc( uint8_t* buf, uint8_t buf_len );

/** 
 * @brief NFC 4 rfal nfc poll coll resolution function. 
 * @details This function implements the Collision Resolution on all technologies that
 * have been detected before.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return  @li @c NFC4_RFAL_ERR_NONE  : Operation completed with no error
 *          @li @c NFC4_RFAL_ERR_BUSY  : Operation ongoing
 *          @li @c NFC4_RFAL_ERR_XXXX  : Error occurred
 */
static err_t nfc4_rfal_nfc_poll_coll_resolution( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal nfc poll activation function. 
 * @details This function activates a given device according to it's type and 
 * protocols supported.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] dev_idx : Device's position on the list to be activated.
 * @return  @li @c NFC4_RFAL_ERR_NONE  : Operation completed with no error
 *          @li @c NFC4_RFAL_ERR_BUSY  : Operation ongoing
 *          @li @c NFC4_RFAL_ERR_XXXX  : Error occurred
 */
static err_t nfc4_rfal_nfc_poll_activation( nfc4_t *ctx, uint8_t dev_idx );

/** 
 * @brief NFC 4 rfal nfc discover function. 
 * @details This function sets the device in Discovery state.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return  @li @c NFC4_RFAL_ERR_NONE         : No error
 *          @li @c NFC4_RFAL_ERR_WRONG_STATE  : Incorrect state for this operation
 */
static err_t nfc4_rfal_nfc_discover( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal nfc get active device function. 
 * @details This function returns the location of the device current Active device.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] dev : Device info location.
 * @return  @li @c NFC4_RFAL_ERR_NONE         : No error
 *          @li @c NFC4_RFAL_ERR_WRONG_STATE  : Incorrect state for this operation
 *                                              No device activated
 *          @li @c NFC4_RFAL_ERR_PARAM        : Invalid parameters
 */
static err_t nfc4_rfal_nfc_get_active_device( nfc4_t *ctx, nfc4_rfal_nfc_device_t **dev );

/** 
 * @brief NFC 4 rfal nfc deactivate function. 
 * @details This function triggers the deactivation procedure to terminate communications with
 * remote device. At the end the field will be turned off.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] discovery : TRUE if after deactivation go back into discovery
 *                      : FALSE if after deactivation remain in idle
 * @return  @li @c NFC4_RFAL_ERR_NONE         : No error
 *          @li @c NFC4_RFAL_ERR_WRONG_STATE  : Incorrect state for this operation
 */
static err_t nfc4_rfal_nfc_deactivate( nfc4_t *ctx, bool discovery );

/** 
 * @brief NFC 4 rfal field on function. 
 * @details This function turns the Field On, performing Initial Collision Avoidance.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return  @li @c NFC4_RFAL_ERR_NONE         : Field turned On
 * @return  @li @c NFC4_RFAL_RF_COLLISION     : External field detected
 */
static err_t nfc4_rfal_field_on( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal field off function. 
 * @details This function turns the Field Off.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return  @li @c NFC4_RFAL_ERR_NONE         : Field turned Off
 */
static err_t nfc4_rfal_field_off( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal fifo status update function. 
 * @details This function reads and updates the internal FIFO status.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return None.
 */
static void nfc4_rfal_fifo_status_update( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal fifo status get num bytes function. 
 * @details This function returns the number of bytes retrieved from the internal FIFO status.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return Number of bytes from FIFO status.
 */
static uint16_t nfc4_rfal_fifo_status_get_num_bytes( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal fifo get num incomplete bits function. 
 * @details This function returns the number of incomplete bits retrieved from the internal FIFO status.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return Number of incomplete bits from FIFO status.
 */
static uint8_t nfc4_rfal_fifo_get_num_incomplete_bits( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal fifo status is incomplete byte function. 
 * @details This function returns the bit state of the incomplete byte indicator retrieved from the internal FIFO status.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return The bit state of the incomplete byte indicator from FIFO status.
 */
static bool nfc4_rfal_fifo_status_is_incomplete_byte( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal fifo status is missing par function. 
 * @details This function returns the bit state of the missing par indicator retrieved from the internal FIFO status.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return The bit state of the missing par indicator from FIFO status.
 */
static bool nfc4_rfal_fifo_status_is_missing_par( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal start transceive function. 
 * @details This function sets the context that will be used for the following Transceive
 * Output and input buffers that have to be passed and all other details prior to 
 * the Transceive itself has been started.
 * This method only sets the context, once set nfc4_rfal_worker has
 * to be executed until is done.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] ctx_tx : the context for the following Transceive.
 * See #nfc4_rfal_worker and #nfc4_rfal_get_transceive_status functions.
 * @return  @li @c NFC4_RFAL_ERR_NONE         : Transceive done with no error
 *          @li @c NFC4_RFAL_ERR_WRONG_STATE  : Not initialized properly 
 *          @li @c NFC4_RFAL_ERR_PARAM        : Invalid parameter or configuration
 */
static err_t nfc4_rfal_start_transceive( nfc4_t *ctx, nfc4_rfal_transceive_context_t *ctx_tx );

/** 
 * @brief NFC 4 rfal prepare transceive function. 
 * @details This function prepares transceive.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return None.
 */
static void nfc4_rfal_prepare_transceive( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal cleanup transceive function. 
 * @details This function cleanups transceive.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return None.
 */
static void nfc4_rfal_cleanup_transceive( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal transceive tx function. 
 * @details This function executes transceive tx.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return None.
 */
static void nfc4_rfal_transceive_tx( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal transceive rx function. 
 * @details This function executes transceive rx.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return None.
 */
static void nfc4_rfal_transceive_rx( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal is transceive in tx function. 
 * @details This function checks if Transceive is in Transmission state.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return  @li @c true   : Transmission ongoing
 *          @li @c false  : Not in transmission state
 */
static bool nfc4_rfal_is_transceive_in_tx( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal is transceive in rx function. 
 * @details This function checks if Transceive is in Reception state.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return  @li @c true   : Transmission done/reception ongoing
 *          @li @c false  : Not in reception state
 */
static bool nfc4_rfal_is_transceive_in_rx( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal transceive run blocking tx function. 
 * @details This function executes transceive blocking until the 
 * Tx has been completed.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return  @li @c NFC4_RFAL_ERR_NONE         : Transceive done with no error
 *          @li @c NFC4_RFAL_ERR_BUSY         : Transceive ongoing
 *          @li @c NFC4_RFAL_ERR_XXXX         : Error occurred
 *          @li @c NFC4_RFAL_ERR_LINK_LOSS    : Link Loss - External Field is Off
 *          @li @c NFC4_RFAL_ERR_RF_COLLISION : Collision detected
 *          @li @c NFC4_RFAL_ERR_IO           : Internal error
 */
static err_t nfc4_rfal_transceive_run_blocking_tx( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal transceive blocking tx function. 
 * @details This function triggers a Transceive and executes it blocking until the 
 * Tx has been completed
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in]  tx_buf     : Buffer where outgoing message is located
 * @param[in]  tx_buf_len : Length of the outgoing message in bytes
 * @param[out] rx_buf     : Buffer where incoming message will be placed
 * @param[in]  rx_buf_len : Maximum length of the incoming message in bytes
 * @param[out] act_len    : Actual received length in bytes
 * @param[in]  flags      : TransceiveFlags indication special handling
 * @param[in]  fwt        : Frame Waiting Time in 1/fc
 * @return  @li @c NFC4_RFAL_ERR_NONE         : Transceive done with no error
 *          @li @c NFC4_RFAL_ERR_BUSY         : Transceive ongoing
 *          @li @c NFC4_RFAL_ERR_XXXX         : Error occurred
 *          @li @c NFC4_RFAL_ERR_LINK_LOSS    : Link Loss - External Field is Off
 *          @li @c NFC4_RFAL_ERR_RF_COLLISION : Collision detected
 *          @li @c NFC4_RFAL_ERR_IO           : Internal error
 */
static err_t nfc4_rfal_transceive_blocking_tx( nfc4_t *ctx, uint8_t* tx_buf, uint16_t tx_buf_len, uint8_t* rx_buf, 
                                               uint16_t rx_buf_len, uint16_t* act_len, uint32_t flags, uint32_t fwt );

/** 
 * @brief NFC 4 rfal transceive blocking rx function. 
 * @details This function executes the reception of an ongoing Transceive triggered 
 * before by nfc4_rfal_transceive_blocking_tx( ).
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return  @li @c NFC4_RFAL_ERR_NONE         : Transceive done with no error
 *          @li @c NFC4_RFAL_ERR_BUSY         : Transceive ongoing
 *          @li @c NFC4_RFAL_ERR_XXXX         : Error occurred
 *          @li @c NFC4_RFAL_ERR_TIMEOUT      : No response
 *          @li @c NFC4_RFAL_ERR_FRAMING      : Framing error detected
 *          @li @c NFC4_RFAL_ERR_PAR          : Parity error detected
 *          @li @c NFC4_RFAL_ERR_CRC          : CRC error detected
 *          @li @c NFC4_RFAL_ERR_LINK_LOSS    : Link Loss - External Field is Off
 *          @li @c NFC4_RFAL_ERR_RF_COLLISION : Collision detected
 *          @li @c NFC4_RFAL_ERR_IO           : Internal error
 */
static err_t nfc4_rfal_transceive_blocking_rx( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal transceive blocking tx rx function. 
 * @details This function triggers a Transceive and executes it blocking until it 
 * has been completed.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in]  tx_buf     : Buffer where outgoing message is located
 * @param[in]  tx_buf_len : Length of the outgoing message in bytes
 * @param[out] rx_buf     : Buffer where incoming message will be placed
 * @param[in]  rx_buf_len : Maximum length of the incoming message in bytes
 * @param[out] act_len    : Actual received length in bytes
 * @param[in]  flags      : TransceiveFlags indication special handling
 * @param[in]  fwt        : Frame Waiting Time in 1/fc
 * @return  @li @c NFC4_RFAL_ERR_NONE         : Transceive done with no error
 *          @li @c NFC4_RFAL_ERR_BUSY         : Transceive ongoing
 *          @li @c NFC4_RFAL_ERR_XXXX         : Error occurred
 *          @li @c NFC4_RFAL_ERR_TIMEOUT      : No response
 *          @li @c NFC4_RFAL_ERR_FRAMING      : Framing error detected
 *          @li @c NFC4_RFAL_ERR_PAR          : Parity error detected
 *          @li @c NFC4_RFAL_ERR_CRC          : CRC error detected
 *          @li @c NFC4_RFAL_ERR_LINK_LOSS    : Link Loss - External Field is Off
 *          @li @c NFC4_RFAL_ERR_RF_COLLISION : Collision detected
 *          @li @c NFC4_RFAL_ERR_IO           : Internal error
 */
static err_t nfc4_rfal_transceive_blocking_tx_rx( nfc4_t *ctx, uint8_t* tx_buf, uint16_t tx_buf_len, uint8_t* rx_buf, 
                                                  uint16_t rx_buf_len, uint16_t* act_len, uint32_t flags, uint32_t fwt );

/** 
 * @brief NFC 4 rfal worker function. 
 * @details This function runs RFAL layer, which drives the actual Transceive procedure
 * It MUST be executed frequently in order to execute the RFAL internal
 * states and perform the requested operations.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return  @li @c NFC4_RFAL_ERR_NONE         : Transceive done with no error
 *          @li @c NFC4_RFAL_ERR_BUSY         : Transceive ongoing
 *          @li @c NFC4_RFAL_ERR_XXXX         : Error occurred
 *          @li @c NFC4_RFAL_ERR_TIMEOUT      : No response
 *          @li @c NFC4_RFAL_ERR_FRAMING      : Framing error detected
 *          @li @c NFC4_RFAL_ERR_PAR          : Parity error detected
 *          @li @c NFC4_RFAL_ERR_CRC          : CRC error detected
 *          @li @c NFC4_RFAL_ERR_LINK_LOSS    : Link Loss - External Field is Off
 *          @li @c NFC4_RFAL_ERR_RF_COLLISION : Collision detected
 *          @li @c NFC4_RFAL_ERR_IO           : Internal error
 */
static err_t nfc4_rfal_worker( nfc4_t *ctx );

/** 
 * @brief NFC 4 rfal nfc worker function. 
 * @details This function runs the internal state machine and runs the RFAL RF worker.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @return None.
 */
static void nfc4_rfal_nfc_worker( nfc4_t *ctx );

/** 
 * @brief NFC 4 initialize analog config function. 
 * @details This function initializes the analog config by setting the Analog Configuration 
 * LUT pointer to @a an_cfg_settings.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] an_cfg_settings: Analog configuration settings (default: @b nfc4_analog_config_settings).
 * @return None.
 */
static void nfc4_initialize_analog_config( nfc4_t *ctx, const uint8_t *an_cfg_settings );

/**
 * @brief NFC 4 set analog config function.
 * @details This function updates the chip with indicated analog settings of indicated Configuration ID.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] config_id : Configuration ID.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 */
static err_t nfc4_set_analog_config( nfc4_t *ctx, uint16_t config_id );

/** 
 * @brief NFC 4 Analog config Search function. 
 * @details Search the Analog Configuration LUT for a specific Configuration ID.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] config_id: Configuration ID to search for.
 * @param[in] config_offset: Configuration Offset in LUT Table.
 * 
 * @return Number of Configuration Sets, or 
 * #NFC4_ANALOG_CONFIG_LUT_NOT_FOUND in case Configuration ID is not found.
 */
static uint8_t nfc4_analog_config_search( nfc4_t *ctx, uint16_t config_id, uint16_t *config_offset );

/**
 * @brief NFC 4 I2C writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nfc4_i2c_write ( nfc4_t *ctx, uint8_t reg, uint8_t *data_in, uint16_t len );

/**
 * @brief NFC 4 I2C reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using I2C serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nfc4_i2c_read ( nfc4_t *ctx, uint8_t reg, uint8_t *data_out, uint16_t len );

/**
 * @brief NFC 4 SPI writing function.
 * @details This function writes a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[in] data_in : Data to be written.
 * @param[in] len : Number of bytes to be written.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nfc4_spi_write ( nfc4_t *ctx, uint8_t reg, uint8_t *data_in, uint16_t len );

/**
 * @brief NFC 4 SPI reading function.
 * @details This function reads a desired number of data bytes starting from
 * the selected register by using SPI serial interface.
 * @param[in] ctx : Click context object.
 * See #nfc4_t object definition for detailed explanation.
 * @param[in] reg : Start register address.
 * @param[out] data_out : Output read data.
 * @param[in] len : Number of bytes to be read.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nfc4_spi_read ( nfc4_t *ctx, uint8_t reg, uint8_t *data_out, uint16_t len );

void nfc4_cfg_setup ( nfc4_cfg_t *cfg ) 
{
    cfg->scl  = HAL_PIN_NC;
    cfg->sda  = HAL_PIN_NC;
    cfg->sck  = HAL_PIN_NC;
    cfg->miso = HAL_PIN_NC;
    cfg->mosi = HAL_PIN_NC;
    cfg->cs   = HAL_PIN_NC;
    cfg->irq  = HAL_PIN_NC;

    cfg->i2c_speed   = I2C_MASTER_SPEED_STANDARD;
    cfg->i2c_address = NFC4_SET_DEV_ADDR;

    cfg->spi_speed   = 100000;
    cfg->spi_mode    = SPI_MASTER_MODE_1;
    cfg->cs_polarity = SPI_MASTER_CHIP_SELECT_POLARITY_ACTIVE_LOW;

    cfg->drv_sel = NFC4_DRV_SEL_SPI;
}

void nfc4_drv_interface_selection ( nfc4_cfg_t *cfg, nfc4_drv_t drv_sel ) 
{
    cfg->drv_sel = drv_sel;
}

err_t nfc4_init ( nfc4_t *ctx, nfc4_cfg_t *cfg ) 
{
    ctx->drv_sel = cfg->drv_sel;

    if ( NFC4_DRV_SEL_I2C == ctx->drv_sel ) 
    {
        i2c_master_config_t i2c_cfg;

        i2c_master_configure_default( &i2c_cfg );

        i2c_cfg.scl = cfg->scl;
        i2c_cfg.sda = cfg->sda;

        ctx->slave_address = cfg->i2c_address;

        if ( I2C_MASTER_ERROR == i2c_master_open( &ctx->i2c, &i2c_cfg ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_slave_address( &ctx->i2c, ctx->slave_address ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        if ( I2C_MASTER_ERROR == i2c_master_set_speed( &ctx->i2c, cfg->i2c_speed ) ) 
        {
            return I2C_MASTER_ERROR;
        }

        ctx->read_f  = nfc4_i2c_read;
        ctx->write_f = nfc4_i2c_write;
    } 
    else 
    {
        spi_master_config_t spi_cfg;

        spi_master_configure_default( &spi_cfg );

        spi_cfg.sck  = cfg->sck;
        spi_cfg.miso = cfg->miso;
        spi_cfg.mosi = cfg->mosi;

        ctx->chip_select = cfg->cs;

        if ( SPI_MASTER_ERROR == spi_master_open( &ctx->spi, &spi_cfg ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_default_write_data( &ctx->spi, DUMMY ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_mode( &ctx->spi, cfg->spi_mode ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        if ( SPI_MASTER_ERROR == spi_master_set_speed( &ctx->spi, cfg->spi_speed ) ) 
        {
            return SPI_MASTER_ERROR;
        }

        spi_master_set_chip_select_polarity( cfg->cs_polarity );
        spi_master_deselect_device( ctx->chip_select );

        ctx->read_f  = nfc4_spi_read;
        ctx->write_f = nfc4_spi_write;
    }

    digital_in_init( &ctx->irq, cfg->irq );

    return NFC4_OK;
}

err_t nfc4_default_cfg ( nfc4_t *ctx ) 
{
    ctx->int_status = 0;
    ctx->nfc_dev.state = NFC4_NFC_STATE_NOTINIT;
    
    /* Set default state on the ST25R3916 */
    err_t error_flag = nfc4_send_direct_command( ctx, NFC4_CMD_SET_DEFAULT );
    
    if ( NFC4_DRV_SEL_SPI == ctx->drv_sel )
    {
        /* Increase MISO driving level as SPI can go up to 10MHz */
        error_flag |= nfc4_write_register( ctx, NFC4_REG_IO_CFG_2, NFC4_IO_CFG_2_IO_DRV_LVL );
    }
    
    if ( NFC4_ERROR == nfc4_check_chip_id( ctx, NULL ) )
    {
        return NFC4_ERROR;
    }
    
    if ( NFC4_DRV_SEL_SPI == ctx->drv_sel )
    {
        /* Enable pull downs on MISO line */
        error_flag |= nfc4_set_register_bits( ctx, NFC4_REG_IO_CFG_2, NFC4_IO_CFG_2_MISO_PD1 | NFC4_IO_CFG_2_MISO_PD2 );
    }
    
    /* Disable internal overheat protection */
    error_flag |= nfc4_modify_test_register_bits ( ctx, 0x04, 0x10, 0x10 );
    
    /* Enable Oscillator and wait until it gets stable */
    error_flag |=  nfc4_enable_osc ( ctx );
    
    /* Set sup3V bit according to Power supplied  */
    error_flag |= nfc4_write_register( ctx, NFC4_REG_IO_CFG_2, NFC4_IO_CFG_2_SUP3V_3V );
    
    /* Make sure Transmitter and Receiver are disabled */
    error_flag |= nfc4_clear_register_bits( ctx, NFC4_REG_OP_CTRL, NFC4_OP_CTRL_RX_EN | NFC4_OP_CTRL_TX_EN );
    
    /* After reset all interrupts are enabled, so disable them at first */
    error_flag |= nfc4_disable_interrupt ( ctx, NFC4_IRQ_MASK_ALL );

    /* And clear them, just to be sure */
    error_flag |= nfc4_clear_interrupts ( ctx );
    
    /* Disable any previous observation mode */
    error_flag |= nfc4_write_test_register ( ctx, 0x01, 0x40 );
    
    /* Apply RF Chip generic initialization */
    nfc4_initialize_analog_config( ctx, &nfc4_analog_config_settings );
    nfc4_set_analog_config ( ctx, NFC4_ANALOG_CONFIG_CHIP_INIT );
    
    /* Enable External Field Detector as: Automatics */
    error_flag |= nfc4_modify_register_bits( ctx, NFC4_REG_OP_CTRL, NFC4_OP_CTRL_EN_FD_MASK, 
                                             NFC4_OP_CTRL_EN_FD_MASK & NFC4_OP_CTRL_EN_FD_AUTO_EFD );
    /* Clear FIFO status local copy */
    ctx->rfal.fifo.status[ NFC4_FIFO_STATUS_REG2 ] = NFC4_FIFO_STATUS_INVALID;
    ctx->rfal.field            = false;
    /* Transceive set to IDLE */
    ctx->rfal.tx_rx.last_state = NFC4_TXRX_STATE_IDLE;
    ctx->rfal.tx_rx.state      = NFC4_TXRX_STATE_IDLE;
    
    /* Perform Automatic Calibration (if configured to do so).                     *
     * Registers set by RF Chip generic initialization will tell what to perform */
    uint8_t reg_data = 0;
    error_flag |= nfc4_read_register( ctx, NFC4_REG_REGULATOR_CTRL, &reg_data );
    if ( NFC4_REGULATOR_CTRL_REG_S != ( reg_data & NFC4_REGULATOR_CTRL_REG_S ) )
    {
        /* Reset logic and set regulated voltages to be defined by result of Adjust Regulators command */
        error_flag |= nfc4_set_register_bits( ctx, NFC4_REG_REGULATOR_CTRL, NFC4_REGULATOR_CTRL_REG_S );
        error_flag |= nfc4_clear_register_bits( ctx, NFC4_REG_REGULATOR_CTRL, NFC4_REGULATOR_CTRL_REG_S );
        
        error_flag |= nfc4_send_direct_command_with_result( ctx, NFC4_CMD_ADJUST_REGULATORS, 
                                                                 NFC4_REG_REGULATOR_DISPLAY, 
                                                                 10000, 
                                                                 &reg_data );
    }
    ctx->nfc_dev.state = NFC4_NFC_STATE_IDLE;
    nfc4_rfal_nfc_discover ( ctx );
    error_flag |= nfc4_clear_interrupts( ctx );
    return error_flag;
}

err_t nfc4_generic_write ( nfc4_t *ctx, uint8_t reg, uint8_t *data_in, uint16_t len ) 
{
    return ctx->write_f( ctx, reg, data_in, len );
}

err_t nfc4_generic_read ( nfc4_t *ctx, uint8_t reg, uint8_t *data_out, uint16_t len ) 
{
    return ctx->read_f( ctx, reg, data_out, len );
}

err_t nfc4_send_direct_command ( nfc4_t *ctx, uint8_t cmd )
{
    return nfc4_generic_write ( ctx, cmd | NFC4_MODE_DIRECT_COMMAND, 0, 0 );
}

err_t nfc4_send_direct_command_with_result ( nfc4_t *ctx, uint8_t cmd, uint8_t result_reg, uint32_t timeout, uint8_t *result )
{
    err_t error_flag = nfc4_check_for_received_interrupts ( ctx );
    nfc4_get_interrupt( ctx, NFC4_IRQ_MASK_DCT );
    error_flag |= nfc4_enable_interrupt ( ctx, NFC4_IRQ_MASK_DCT );
        
    error_flag |= nfc4_generic_write ( ctx, cmd | NFC4_MODE_DIRECT_COMMAND, 0, 0 );
        
    nfc4_wait_for_interrupt( ctx, NFC4_IRQ_MASK_DCT, timeout );
        
    error_flag |= nfc4_disable_interrupt ( ctx, NFC4_IRQ_MASK_DCT );
    
    error_flag |= nfc4_read_register ( ctx, result_reg, result );
    
    return error_flag;
}

err_t nfc4_write_register ( nfc4_t *ctx, uint8_t reg, uint8_t data_in )
{
    return nfc4_generic_write ( ctx, reg, &data_in, 1 );
}

err_t nfc4_read_register ( nfc4_t *ctx, uint8_t reg, uint8_t *data_out )
{
    return nfc4_generic_read ( ctx, reg, data_out, 1 );
}

err_t nfc4_write_multiple_registers ( nfc4_t *ctx, uint8_t reg, uint8_t *data_in, uint16_t len )
{
    return nfc4_generic_write ( ctx, reg, data_in, len );
}

err_t nfc4_read_multiple_registers ( nfc4_t *ctx, uint8_t reg, uint8_t *data_out, uint16_t len )
{
    return nfc4_generic_read ( ctx, reg, data_out, len );
}

err_t nfc4_clear_register_bits ( nfc4_t *ctx, uint8_t reg, uint8_t clr_mask )
{
    uint8_t rx_data = 0;
    uint8_t tx_data = 0;
    
    err_t error_flag = nfc4_read_register( ctx, reg, &rx_data );
    
    tx_data = rx_data & ~clr_mask;
    
    if ( rx_data != tx_data )
    {
        error_flag |= nfc4_write_register( ctx, reg, tx_data );
    }
    
    return error_flag;
}

err_t nfc4_set_register_bits ( nfc4_t *ctx, uint8_t reg, uint8_t set_mask )
{
    uint8_t rx_data = 0;
    uint8_t tx_data = 0;
    
    err_t error_flag = nfc4_read_register( ctx, reg, &rx_data );
    
    tx_data = rx_data | set_mask;
    
    if ( rx_data != tx_data )
    {
        error_flag |= nfc4_write_register( ctx, reg, tx_data );
    }
    
    return error_flag;
}

err_t nfc4_modify_register_bits ( nfc4_t *ctx, uint8_t reg, uint8_t clr_mask, uint8_t set_mask )
{
    uint8_t rx_data = 0;
    uint8_t tx_data = 0;
    
    err_t error_flag = nfc4_read_register( ctx, reg, &rx_data );
    
    tx_data = ( rx_data & ~clr_mask ) | set_mask;
    
    if ( rx_data != tx_data )
    {
        error_flag |= nfc4_write_register( ctx, reg, tx_data );
    }
    
    return error_flag;
}

err_t nfc4_write_fifo ( nfc4_t *ctx, uint8_t *data_in, uint16_t len )
{
    if ( ( len > NFC4_FIFO_DEPTH ) && ( 0 == len ) )
    {
        return NFC4_ERROR;
    }
    
    return nfc4_generic_write ( ctx, NFC4_MODE_FIFO_LOAD, data_in, len );
}

err_t nfc4_read_fifo ( nfc4_t *ctx, uint8_t *data_out, uint16_t len )
{
    if ( ( len > NFC4_FIFO_DEPTH ) && ( 0 == len ) )
    {
        return NFC4_ERROR;
    }
    
    return nfc4_generic_read ( ctx, NFC4_MODE_FIFO_READ, data_out, len );
}

err_t nfc4_write_test_register ( nfc4_t *ctx, uint8_t reg, uint8_t data_in )
{
    uint8_t tx_buf[ 2 ] = { reg, data_in };
    return nfc4_generic_write ( ctx, NFC4_CMD_TEST_ACCESS, tx_buf, 2 );
}

err_t nfc4_read_test_register ( nfc4_t *ctx, uint8_t reg, uint8_t *data_out )
{
    *data_out = reg;
    return nfc4_generic_read ( ctx, NFC4_CMD_TEST_ACCESS, data_out, 1 );
}

err_t nfc4_modify_test_register_bits ( nfc4_t *ctx, uint8_t reg, uint8_t clr_mask, uint8_t set_mask )
{
    uint8_t rx_data = 0;
    uint8_t tx_data = 0;
    
    err_t error_flag = nfc4_read_test_register( ctx, reg, &rx_data );
    
    tx_data = ( rx_data & ~clr_mask ) | set_mask;
    
    if ( rx_data != tx_data )
    {
        error_flag |= nfc4_write_test_register( ctx, reg, tx_data );
    }
    
    return error_flag;
}

err_t nfc4_enable_interrupt ( nfc4_t *ctx, uint32_t mask )
{
    uint8_t rx_buf[ 4 ] = { 0 };
    uint8_t tx_data = 0;
    err_t error_flag = nfc4_read_multiple_registers ( ctx, NFC4_REG_IRQ_MASK_MAIN, rx_buf, 4 );
    
    for ( uint8_t cnt = 0; cnt < 4; cnt++ )
    { 
        tx_data = ( uint8_t ) ( ( mask >> ( cnt * 8 ) ) & 0xFF );
        
        if ( 0 != tx_data )
        {
            tx_data = rx_buf[ cnt ] & ~tx_data;
            error_flag |= nfc4_write_register ( ctx, NFC4_REG_IRQ_MASK_MAIN + cnt, tx_data );
        }
    }
    
    return error_flag;
}

err_t nfc4_disable_interrupt ( nfc4_t *ctx, uint32_t mask )
{
    uint8_t rx_buf[ 4 ] = { 0 };
    uint8_t tx_data = 0;
    err_t error_flag = nfc4_read_multiple_registers ( ctx, NFC4_REG_IRQ_MASK_MAIN, rx_buf, 4 );
    
    for ( uint8_t cnt = 0; cnt < 4; cnt++ )
    { 
        tx_data = ( uint8_t ) ( ( mask >> ( cnt * 8 ) ) & 0xFF );
        
        if ( 0 != tx_data )
        {
            tx_data |= rx_buf[ cnt ];
            error_flag |= nfc4_write_register ( ctx, NFC4_REG_IRQ_MASK_MAIN + cnt, tx_data );
        }
    }
    return error_flag;
}

err_t nfc4_clear_interrupts ( nfc4_t *ctx )
{
    uint8_t rx_buf[ 4 ] = { 0 };
    ctx->int_status = NFC4_IRQ_MASK_NONE;
    return nfc4_read_multiple_registers ( ctx, NFC4_REG_IRQ_MAIN, rx_buf, 4 );
}

err_t nfc4_check_for_received_interrupts ( nfc4_t *ctx )
{
    uint8_t rx_buf[ 4 ] = { 0 };
    err_t error_flag = NFC4_OK;
    
    while ( nfc4_get_irq_pin ( ctx ) )
    {
        error_flag |= nfc4_read_multiple_registers ( ctx, NFC4_REG_IRQ_MAIN, rx_buf, 4 );
        ctx->int_status |= ( uint32_t ) rx_buf[ 0 ];
        ctx->int_status |= ( uint32_t ) rx_buf[ 1 ] << 8;
        ctx->int_status |= ( uint32_t ) rx_buf[ 2 ] << 16;
        ctx->int_status |= ( uint32_t ) rx_buf[ 3 ] << 24;
    }
    
    return error_flag;
}

uint32_t nfc4_wait_for_interrupt ( nfc4_t *ctx, uint32_t mask, uint32_t timeout )
{
    do 
    {
        nfc4_check_for_received_interrupts ( ctx );
        Delay_1us( );
    } while ( ( timeout-- > 0 ) && ( NFC4_IRQ_MASK_NONE == ctx->int_status ) );
    
    return nfc4_get_interrupt ( ctx, mask );
}

uint32_t nfc4_get_interrupt ( nfc4_t *ctx, uint32_t mask )
{
    uint32_t status = ctx->int_status & mask;

    if ( NFC4_IRQ_MASK_NONE != status )
    {
        ctx->int_status &= ~status;
    }
    return status;
}

err_t nfc4_check_chip_id ( nfc4_t *ctx, uint8_t *revision )
{
    uint8_t chip_id = 0;
    err_t error_flag = nfc4_read_register ( ctx, NFC4_REG_IC_IDENTITY, &chip_id );
    
    if ( ( NFC4_IC_TYPE_CODE == ( chip_id >> 3 ) ) && ( NFC4_OK == error_flag ) )
    {
        if ( NULL != revision )
        {
            *revision = ( chip_id & ~NFC4_IC_REVISION_CODE_MASK );
        }
        return NFC4_OK;
    }
    return NFC4_ERROR;
}

err_t nfc4_enable_osc ( nfc4_t *ctx )
{
    uint8_t reg_data = 0;
    err_t error_flag = nfc4_read_register ( ctx, NFC4_REG_OP_CTRL, &reg_data );
    
    if ( NFC4_OP_CTRL_EN != ( reg_data & NFC4_OP_CTRL_EN ) )
    {
        error_flag |= nfc4_check_for_received_interrupts ( ctx );
        
        nfc4_get_interrupt ( ctx, NFC4_IRQ_MASK_OSC );
        
        error_flag |= nfc4_enable_interrupt ( ctx, NFC4_IRQ_MASK_OSC );
        
        error_flag |= nfc4_set_register_bits( ctx, NFC4_REG_OP_CTRL, NFC4_OP_CTRL_EN );
        
        error_flag |= nfc4_wait_for_interrupt( ctx, NFC4_IRQ_MASK_OSC, 10000 );
        
        error_flag |= nfc4_disable_interrupt ( ctx, NFC4_IRQ_MASK_OSC );
    }
    
    error_flag |= nfc4_read_register( ctx, NFC4_REG_AUX_DISPLAY, &reg_data );
    
    if ( NFC4_AUX_DISPLAY_OSC_OK == ( reg_data & NFC4_AUX_DISPLAY_OSC_OK ) )
    {
        return error_flag;
    }
    
    return NFC4_ERROR;
}

err_t nfc4_measure_voltage ( nfc4_t *ctx, uint8_t mpsv_src, uint16_t *res_mv )
{
    uint8_t reg_data = 0;
    
    if ( mpsv_src > 0x07 )
    {
        return NFC4_ERROR;
    }
    
    err_t error_flag = nfc4_read_register( ctx, NFC4_REG_REGULATOR_CTRL, &reg_data );
    reg_data &= ~0x07;
    reg_data |= mpsv_src;
    error_flag |= nfc4_write_register( ctx, NFC4_REG_REGULATOR_CTRL, reg_data );
    
    error_flag |= nfc4_send_direct_command_with_result( ctx, NFC4_CMD_MEAS_POWER_SUPPLY, 
                                                             NFC4_REG_ADC_OUTPUT, 
                                                             10000, 
                                                             &reg_data );
    
    /* Each step represents 23.4 mV */
    *res_mv = ( ( uint16_t ) reg_data ) * 23;
    *res_mv += ( ( ( ( ( uint16_t ) reg_data ) * 4 ) + 5 ) / 10 );
    
    return error_flag;
}

uint8_t nfc4_get_irq_pin ( nfc4_t *ctx )
{
    return digital_in_read ( &ctx->irq );
}

err_t nfc4_get_mifare_tag_uid ( nfc4_t *ctx, uint8_t *uid, uint8_t *uid_len )
{
    nfc4_rfal_nfc_worker( ctx );  /* Run RFAL worker periodically */
    
    if ( NFC4_NFC_STATE_ACTIVATED == ctx->nfc_dev.state )
    {
        static nfc4_rfal_nfc_device_t *nfc_device;
        nfc4_rfal_nfc_get_active_device( ctx, &nfc_device );
        memcpy ( uid, nfc_device->nfc_id, nfc_device->nfc_id_len );
        nfc4_rfal_nfc_deactivate( ctx, false );
        nfc4_rfal_nfc_discover( ctx );
        *uid_len = nfc_device->nfc_id_len;
        return NFC4_OK;
    }
    return NFC4_ERROR;
}

static err_t nfc4_perform_collision_avoidance( nfc4_t *ctx, uint8_t field_on_cmd, 
                                               uint8_t pd_threshold, uint8_t ca_threshold )
{
    uint8_t    tre_mask = 0;
    uint32_t   irqs = 0;
    err_t      error_flag = NFC4_RFAL_ERR_INTERNAL;
    
    if ( ( NFC4_CMD_NFC_INITIAL_FIELD_ON != field_on_cmd ) && ( NFC4_CMD_NFC_RESPONSE_FIELD_ON != field_on_cmd ) )
    {
        return NFC4_RFAL_ERR_PARAM;
    }
    
    /* Check if new thresholds are to be applied */
    if ( ( NFC4_THLD_DO_NOT_SET != pd_threshold ) || ( NFC4_THLD_DO_NOT_SET != ca_threshold ) )
    {
        tre_mask = 0;
        
        if ( NFC4_THLD_DO_NOT_SET != pd_threshold )
        {
            tre_mask |= NFC4_FIELD_THLD_ACT_TRG_MASK;
        }
        
        if ( NFC4_THLD_DO_NOT_SET != ca_threshold )
        {
            tre_mask |= NFC4_FIELD_THLD_ACT_RFE_MASK;
        }
            
        /* Set Detection Threshold and|or Collision Avoidance Threshold */
        nfc4_modify_register_bits( ctx, NFC4_REG_FIELD_THLD_ACT, tre_mask, 
                                        tre_mask & ( ( pd_threshold & NFC4_FIELD_THLD_ACT_TRG_MASK ) | 
                                                     ( ca_threshold & NFC4_FIELD_THLD_ACT_RFE_MASK ) ) );
    }
        
    /* Enable and clear CA specific interrupts and execute command */
    nfc4_check_for_received_interrupts( ctx );
    nfc4_get_interrupt( ctx, ( NFC4_IRQ_MASK_CAC | NFC4_IRQ_MASK_CAT | NFC4_IRQ_MASK_APON ) );
    nfc4_enable_interrupt( ctx, ( NFC4_IRQ_MASK_CAC | NFC4_IRQ_MASK_CAT | NFC4_IRQ_MASK_APON ) );
    
    nfc4_send_direct_command( ctx, field_on_cmd );
    
    /* Wait for initial APON interrupt, indicating anticollision avoidance done and ST25R3916's 
     * field is now on, or a CAC indicating a collision */   
    irqs = nfc4_wait_for_interrupt( ctx, ( NFC4_IRQ_MASK_CAC | NFC4_IRQ_MASK_APON ), 10000 );

    if ( 0U != ( NFC4_IRQ_MASK_CAC & irqs ) )        /* Collision occurred */
    {
        error_flag = NFC4_RFAL_ERR_RF_COLLISION;
    }
    else if ( 0U != ( NFC4_IRQ_MASK_APON & irqs ) )
    {
        /* After APON wait for CAT interrupt, indication field was switched on minimum guard time has been fulfilled */
        irqs = nfc4_wait_for_interrupt( ctx, ( NFC4_IRQ_MASK_CAT ), 10000 );

        if ( 0U != ( NFC4_IRQ_MASK_CAT & irqs ) )  /* No Collision detected, Field On */
        {
            error_flag = NFC4_RFAL_ERR_NONE;
        }
    }

    /* Clear any previous External Field events and disable CA specific interrupts */
    nfc4_check_for_received_interrupts( ctx );
    nfc4_get_interrupt( ctx, ( NFC4_IRQ_MASK_EOF | NFC4_IRQ_MASK_EON ) );
    nfc4_disable_interrupt( ctx, ( NFC4_IRQ_MASK_CAC | NFC4_IRQ_MASK_CAT | NFC4_IRQ_MASK_APON ) );
    
    return error_flag;
}

static void nfc4_set_num_tx_bits ( nfc4_t *ctx, uint16_t n_bits )
{
    nfc4_write_register( ctx, NFC4_REG_NUM_TX_BYTES_2, ( uint8_t )( ( n_bits >> 0 ) & 0xFFU ) );
    nfc4_write_register( ctx, NFC4_REG_NUM_TX_BYTES_1, ( uint8_t )( ( n_bits >> 8 ) & 0xFFU ) );
}

static err_t nfc4_set_no_response_time( nfc4_t *ctx, uint32_t nrt_64fcs )
{    
    err_t      error_flag;
    uint8_t    nrt_step;    
    uint32_t   tmp_nrt;

    tmp_nrt    = nrt_64fcs;       /* MISRA 17.8 */
    error_flag = NFC4_RFAL_ERR_NONE;
    
    nrt_step = NFC4_TIMER_EMV_CONTROL_NRT_STEP_64FC;  /* Set default NRT in steps of 64/fc */
    
    if ( tmp_nrt > NFC4_NRT_MAX )                     /* Check if the given NRT value fits using 64/fc steps */
    {
        nrt_step = NFC4_TIMER_EMV_CONTROL_NRT_STEP_4096_FC;  /* If not, change NRT set to 4096/fc */
        tmp_nrt  = ( ( tmp_nrt + 63U ) / 64U );              /* Calculate number of steps in 4096/fc */
        
        if ( tmp_nrt > NFC4_NRT_MAX )                        /* Check if the NRT value fits using 64/fc steps */
        {
            tmp_nrt = NFC4_NRT_MAX;                          /* Assign the maximum possible */
            error_flag = NFC4_RFAL_ERR_PARAM;                /* Signal parameter error */
        }
    }

    /* Set the ST25R3916 NRT step units and the value */
    nfc4_modify_register_bits( ctx, NFC4_REG_TIMER_EMV_CTRL, NFC4_TIMER_EMV_CONTROL_NRT_STEP, 
                                                             NFC4_TIMER_EMV_CONTROL_NRT_STEP & nrt_step );
    nfc4_write_register( ctx, NFC4_REG_NO_RESPONSE_TIMER_1, ( uint8_t ) ( tmp_nrt >> 8U ) );
    nfc4_write_register( ctx, NFC4_REG_NO_RESPONSE_TIMER_2, ( uint8_t ) ( tmp_nrt & 0xFFU ) );

    return error_flag;
}

static err_t nfc4_rfal_iso14443a_transceive_anticollision_frame( nfc4_t *ctx, uint8_t *buf, uint8_t *bytes_to_send, 
                                                                 uint8_t *bits_to_send, uint16_t *rx_length, uint32_t fwt )
{
    err_t                          error_flag;
    nfc4_rfal_transceive_context_t ctx_tx;
    uint8_t                        coll_byte;
    uint8_t                        coll_data;
    
    /* Check for valid parameters */
    if ( ( NULL == buf ) || ( NULL == bytes_to_send ) || ( NULL == bits_to_send ) || ( NULL == rx_length ) )
    {
        return NFC4_RFAL_ERR_PARAM;
    }
    
    /* Set speficic Analog Config for Anticolission if needed */
    nfc4_set_analog_config( ctx, ( NFC4_ANALOG_CONFIG_POLL | NFC4_ANALOG_CONFIG_TECH_NFCA | 
                                   NFC4_ANALOG_CONFIG_BITRATE_COMMON | NFC4_ANALOG_CONFIG_ANTICOL ) );

    /* Enable anti collision to recognise collision in first byte of SENS_REQ */
    nfc4_set_register_bits( ctx, NFC4_REG_ISO14443A_NFC, NFC4_ISO14443A_NFC_ANTCL );
    
    /* Disable CRC while receiving */
    nfc4_set_register_bits( ctx, NFC4_REG_AUX, NFC4_AUX_NO_CRC_RX );

    /* Prepare for Transceive */
    ctx_tx.flags       = ( ( uint32_t ) NFC4_TXRX_FLAGS_CRC_TX_MANUAL | ( uint32_t ) NFC4_TXRX_FLAGS_CRC_RX_KEEP );
    ctx_tx.tx_buf      = buf;
    ctx_tx.tx_buf_len  = ( uint16_t ) ( NFC4_RFAL_CONV_BYTES_TO_BITS( *bytes_to_send ) + *bits_to_send );
    ctx_tx.rx_buf      = &buf[ *bytes_to_send ];
    ctx_tx.rx_buf_len  = ( uint16_t ) NFC4_RFAL_CONV_BYTES_TO_BITS( NFC4_ISO14443A_SDD_RES_LEN );
    ctx_tx.rx_rcvd_len = rx_length;
    ctx_tx.fwt         = fwt;
    
    /* Disable Automatic Gain Control (AGC) for better detection of collisions if using Coherent Receiver */
    uint8_t rx_data = 0;
    nfc4_read_register( ctx, NFC4_REG_AUX, &rx_data );
    ctx_tx.flags |= ( ( NFC4_AUX_DIS_CORR == ( rx_data & NFC4_AUX_DIS_CORR ) ) ? ( uint32_t ) NFC4_TXRX_FLAGS_AGC_OFF : 0x00U );
    
    nfc4_rfal_start_transceive( ctx, &ctx_tx );
    
    /* Additionally enable bit collision interrupt */
    nfc4_get_interrupt( ctx, NFC4_IRQ_MASK_COL );
    nfc4_enable_interrupt( ctx, NFC4_IRQ_MASK_COL );

    coll_byte = 0;
    /* save the collision byte */
    if ( ( *bits_to_send ) > 0U )
    {
        buf[ ( *bytes_to_send ) ] <<= ( NFC4_BITS_IN_BYTE - ( *bits_to_send ) );
        buf[ ( *bytes_to_send ) ] >>= ( NFC4_BITS_IN_BYTE - ( *bits_to_send ) );
        coll_byte = buf[ ( *bytes_to_send ) ];
    }
    
    /* Run Transceive blocking */
    error_flag = nfc4_rfal_transceive_run_blocking_tx( ctx );
    if ( NFC4_RFAL_ERR_NONE == error_flag )
    {
       error_flag = nfc4_rfal_transceive_blocking_rx( ctx );

       if ( ( *bits_to_send ) > 0U )
       {
           buf[ ( *bytes_to_send ) ] >>= ( *bits_to_send );
           buf[ ( *bytes_to_send ) ] <<= ( *bits_to_send );
           buf[ ( *bytes_to_send ) ] |= coll_byte;
       }
       
       if ( ( NFC4_RFAL_ERR_RF_COLLISION == error_flag ) )
       {                      
           /* read out collision register */
           nfc4_read_register( ctx, NFC4_REG_COLLISION_STATUS, &coll_data );

           ( *bytes_to_send ) = ( ( coll_data >> NFC4_COLLISION_STATUS_C_BYTE_SHIFT ) & 0x0FU ); // 4-bits Byte information
           ( *bits_to_send )  = ( ( coll_data >> NFC4_COLLISION_STATUS_C_BIT_SHIFT )  & 0x07U ); // 3-bits bit information
       }
    }
    /* Disable Collision interrupt */
    nfc4_disable_interrupt( ctx, NFC4_IRQ_MASK_COL );
    
    /* Disable anti collision again */
    nfc4_clear_register_bits( ctx, NFC4_REG_ISO14443A_NFC, NFC4_ISO14443A_NFC_ANTCL );

    /* ReEnable CRC on Rx */
    nfc4_clear_register_bits( ctx, NFC4_REG_AUX, NFC4_AUX_NO_CRC_RX );
    
    return error_flag;
}

static err_t nfc4_rfal_iso14443a_transceive_short_frame( nfc4_t *ctx, nfc4_rfal_14443a_short_frame_cmd_t tx_cmd, 
                                                         uint8_t* rx_buf, uint8_t rx_buf_len, uint16_t* rx_rcvd_len, 
                                                         uint32_t fwt )
{
    err_t      error_flag;
    uint8_t    direct_cmd;

    /* Check if RFAL is properly initialized */
    uint8_t    rx_data = 0;
    
    nfc4_read_register( ctx, NFC4_REG_OP_CTRL, &rx_data );
    
    if ( NFC4_OP_CTRL_TX_EN != ( rx_data & NFC4_OP_CTRL_TX_EN ) )
    {
        return NFC4_RFAL_ERR_WRONG_STATE;
    }
    /* Check for valid parameters */
    if ( ( NULL == rx_buf ) || ( NULL == rx_buf_len ) || ( NFC4_FWT_NONE == fwt ) )
    {
        return NFC4_RFAL_ERR_PARAM;
    }
    /* Select the Direct Command to be performed */
    switch ( tx_cmd )
    {
        case NFC4_14443A_SHORTFRAME_CMD_WUPA:
        {
            direct_cmd = NFC4_CMD_TRANSMIT_WUPA;
            break;
        }
        case NFC4_14443A_SHORTFRAME_CMD_REQA:
        {
            direct_cmd = NFC4_CMD_TRANSMIT_REQA;
            break;
        }
        default:
        {
            return NFC4_RFAL_ERR_PARAM;
        }
    }
    /* Disable CRC while receiving since ATQA has no CRC included */
    nfc4_set_register_bits( ctx, NFC4_REG_AUX, NFC4_AUX_NO_CRC_RX );
    /* Prepare for Transceive, Receive only (bypass Tx states) */
    ctx->rfal.tx_rx.ctx.flags       = ( uint32_t ) NFC4_TXRX_FLAGS_CRC_TX_MANUAL | NFC4_TXRX_FLAGS_CRC_RX_KEEP;
    ctx->rfal.tx_rx.ctx.rx_buf      = rx_buf;
    ctx->rfal.tx_rx.ctx.rx_buf_len  = rx_buf_len;
    ctx->rfal.tx_rx.ctx.rx_rcvd_len = rx_rcvd_len;
    ctx->rfal.tx_rx.ctx.fwt         = fwt;
    /* Load NRT with FWT */
    nfc4_set_no_response_time( ctx, NFC4_RFAL_CONV_1FC_TO_64FC ( MIN( ( fwt + NFC4_FWT_ADJUSTMENT + NFC4_FWT_A_ADJUSTMENT ), 
                                                                      NFC4_NRT_MAX_1FC ) ) );
    nfc4_rfal_prepare_transceive( ctx );
    
    /* Also enable bit collision interrupt */
    nfc4_get_interrupt( ctx, NFC4_IRQ_MASK_COL );
    nfc4_enable_interrupt( ctx, NFC4_IRQ_MASK_COL );
    /* Clear nbtx bits before sending WUPA/REQA - otherwise ST25R3916 will report parity error, Note2 of the register */
    nfc4_write_register( ctx, NFC4_REG_NUM_TX_BYTES_2, 0 );
    
    /* Send either WUPA or REQA. All affected tags will backscatter ATQA and change to READY state */
    nfc4_send_direct_command( ctx, direct_cmd );
    /* Wait for TXE */
    if ( NFC4_IRQ_MASK_NONE == nfc4_wait_for_interrupt( ctx, NFC4_IRQ_MASK_TXE, 
                                                       ( uint32_t ) MAX( NFC4_RFAL_CONV_1FC_TO_MS( fwt ), 1 ) * 1000 ) )
    {
        error_flag = NFC4_RFAL_ERR_IO;
    }
    else
    {
        /* Jump into a transceive Rx state for reception (bypass Tx states) */
        ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_IDLE;
        ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_BUSY;
        /* Execute Transceive Rx blocking */
        error_flag = nfc4_rfal_transceive_blocking_rx( ctx );
    }
    /* Disable Collision interrupt */
    nfc4_disable_interrupt( ctx, NFC4_IRQ_MASK_COL );
    /* ReEnable CRC on Rx */
    nfc4_clear_register_bits( ctx, NFC4_REG_AUX, NFC4_AUX_NO_CRC_RX );
    
    return error_flag;
}

static err_t nfc4_rfal_nfca_poller_initialize ( nfc4_t *ctx )
{
    /* Disable wake up mode, if set */
    err_t error_flag = nfc4_clear_register_bits( ctx, NFC4_REG_OP_CTRL, NFC4_OP_CTRL_WU );
    
    /* Enable ISO14443A mode */
    error_flag |= nfc4_write_register( ctx, NFC4_REG_MODE, NFC4_MODE_OM_ISO14443A );
    Delay_10ms( );
    
    /* Set Analog configurations for this mode and bit rate */
    error_flag |= nfc4_set_analog_config( ctx, ( NFC4_ANALOG_CONFIG_POLL | NFC4_ANALOG_CONFIG_TECH_NFCA | 
                                                 NFC4_ANALOG_CONFIG_BITRATE_COMMON | NFC4_ANALOG_CONFIG_TX ) );
    error_flag |= nfc4_set_analog_config( ctx, ( NFC4_ANALOG_CONFIG_POLL | NFC4_ANALOG_CONFIG_TECH_NFCA | 
                                                 NFC4_ANALOG_CONFIG_BITRATE_COMMON | NFC4_ANALOG_CONFIG_RX ) );
    return error_flag;
}

static err_t nfc4_rfal_nfca_poller_sleep( nfc4_t *ctx )
{
    nfc4_rfal_nfca_slp_req_t slp_req;
    uint8_t                  rx_buf; /* dummy buffer, just to perform Rx */

    slp_req.frame[ NFC4_NFCA_SLP_CMD_POS ]   = NFC4_NFCA_SLP_CMD;
    slp_req.frame[ NFC4_NFCA_SLP_BYTE2_POS ] = NFC4_NFCA_SLP_BYTE2;

    nfc4_rfal_transceive_blocking_tx_rx( ctx, ( uint8_t* ) &slp_req, sizeof( nfc4_rfal_nfca_slp_req_t ), 
                                         &rx_buf, sizeof( rx_buf ), NULL, NFC4_TXRX_FLAGS_DEFAULT, NFC4_NFCA_SLP_FWT );

    /* ISO14443-3 6.4.3  HLTA - If PICC responds with any modulation during 1 ms this response shall be interpreted as not acknowledge
       Digital 2.0  6.9.2.1 & EMVCo 3.0  5.6.2.1 - consider the HLTA command always acknowledged
       No check to be compliant with NFC and EMVCo, and to improve interoprability (Kovio RFID Tag)
    */

    return NFC4_RFAL_ERR_NONE;
}

static err_t nfc4_rfal_nfca_poller_select( nfc4_t *ctx, uint8_t *nfc_id1, uint8_t nfc_id_len, 
                                           nfc4_rfal_nfca_sel_res_t *sel_res )
{
    uint8_t        cl;
    uint8_t        nfc_id_offset;
    uint16_t       rx_len;
    err_t          error_flag;
    nfc4_rfal_nfca_sel_req_t sel_req;

    if ( ( NULL == nfc_id1 ) || ( nfc_id_len > NFC4_NFCA_CASCADE_3_UID_LEN ) || ( NULL == sel_res ) )
    {
        return NFC4_RFAL_ERR_PARAM;
    }

    /* Calculate Cascate Level */
    cl            = NFC4_RFAL_NFCA_NFC_ID_LEN_2CL( nfc_id_len );
    nfc_id_offset = 0;

    /* Go through all Cascade Levels     Activity 1.1  9.4.4 */
    for ( uint8_t cnt = NFC4_NFCA_SEL_CASCADE_L1; cnt <= cl; cnt++ )
    {
        /* Assign SEL_CMD according to the CLn and SEL_PAR*/
        sel_req.sel_cmd = NFC4_RFAL_NFCA_CLN2_SEL_CMD( cnt );
        sel_req.sel_par = NFC4_NFCA_SEL_SELPAR;

        /* Compute NFCID/Data on the SEL_REQ command   Digital 1.1  Table 18 */
        if ( cl != cnt )
        {
            *sel_req.nfc_id1 = NFC4_NFCA_SDD_CT;
            memcpy( &sel_req.nfc_id1[ NFC4_NFCA_SDD_CT_LEN ], &nfc_id1[ nfc_id_offset ], 
                    ( NFC4_NFCA_CASCADE_1_UID_LEN - NFC4_NFCA_SDD_CT_LEN ) );
            nfc_id_offset += ( NFC4_NFCA_CASCADE_1_UID_LEN - NFC4_NFCA_SDD_CT_LEN );
        }
        else
        {
            memcpy( sel_req.nfc_id1, &nfc_id1[ nfc_id_offset ], NFC4_NFCA_CASCADE_1_UID_LEN );
        }

        /* Calculate nfcid's BCC */
        sel_req.bcc = nfc4_rfal_nfca_calculate_bcc( ( uint8_t* ) &sel_req.nfc_id1, sizeof( sel_req.nfc_id1 ) );

        /* Send SEL_REQ  */
        EXIT_ON_ERR( error_flag, nfc4_rfal_transceive_blocking_tx_rx( ctx, ( uint8_t* ) &sel_req, sizeof( nfc4_rfal_nfca_sel_req_t ), 
                                                                      ( uint8_t* ) sel_res, sizeof( nfc4_rfal_nfca_sel_res_t ), &rx_len, 
                                                                      NFC4_TXRX_FLAGS_DEFAULT, NFC4_NFCA_FDTMIN ) );
        /* Ensure proper response length */
        if ( sizeof( nfc4_rfal_nfca_sel_res_t ) != rx_len )
        {
            return NFC4_RFAL_ERR_PROTO;
        }
    }
    return NFC4_RFAL_ERR_NONE;
}

static err_t nfc4_rfal_nfca_poller_check_presence( nfc4_t *ctx, nfc4_rfal_14443a_short_frame_cmd_t cmd, 
                                                   nfc4_rfal_nfca_sens_res_t *sens_res )
{
    err_t error_flag;
    uint16_t rcv_len;

    /* Digital 1.1 6.10.1.3  For Commands ALL_REQ, SENS_REQ, SDD_REQ, and SEL_REQ, the NFC Forum Device      *
     *              MUST treat receipt of a Listen Frame at a time after FDT(Listen, min) as a Timeour Error */
    
    error_flag = nfc4_rfal_iso14443a_transceive_short_frame( ctx, cmd, ( uint8_t* ) sens_res, 
                                                 ( uint8_t ) NFC4_RFAL_CONV_BYTES_TO_BITS ( sizeof ( nfc4_rfal_nfca_sens_res_t ) ), 
                                                             &rcv_len, NFC4_NFCA_FDTMIN  );
    if ( ( NFC4_RFAL_ERR_RF_COLLISION == error_flag ) || ( NFC4_RFAL_ERR_CRC == error_flag ) || 
         ( NFC4_RFAL_ERR_NOMEM == error_flag ) || ( NFC4_RFAL_ERR_FRAMING == error_flag ) || 
         ( NFC4_RFAL_ERR_PAR == error_flag ) )
    {
       error_flag = NFC4_RFAL_ERR_NONE;
    }
    return error_flag;
}

static err_t nfc4_rfal_nfca_poller_get_single_collision_resolution_status( nfc4_t *ctx )
{
    err_t     error_flag;
    uint8_t   coll_bit = 1U;  /* standards mandate or recommend collision bit to be set to One. */

    /* Go through all Cascade Levels     Activity 1.1  9.3.4 */
    if ( ctx->nfca.col_res.cascade_lvl > ( uint8_t ) NFC4_NFCA_SEL_CASCADE_L3 )
    {
        return NFC4_RFAL_ERR_INTERNAL;
    }

    switch ( ctx->nfca.col_res.state )
    {
        case NFC4_NFCA_CR_CL:
        {
            /* Initialize the SDD_REQ to send for the new cascade level */
            memset( ( uint8_t* ) &ctx->nfca.col_res.sel_req, 0x00, sizeof( nfc4_rfal_nfca_sel_req_t ) );

            ctx->nfca.col_res.bytes_tx_rx = NFC4_NFCA_SDD_REQ_LEN;
            ctx->nfca.col_res.bits_tx_rx  = 0U;
            ctx->nfca.col_res.state       = NFC4_NFCA_CR_SDD;
            /* fall through */
        }
        case NFC4_NFCA_CR_SDD:   /*  PRQA S 2003 # MISRA 16.3 - Intentional fall through */
        {
            /* Calculate SEL_CMD and SEL_PAR with the bytes/bits to be sent */
            ctx->nfca.col_res.sel_req.sel_cmd = NFC4_RFAL_NFCA_CLN2_SEL_CMD( ctx->nfca.col_res.cascade_lvl );
            ctx->nfca.col_res.sel_req.sel_par = NFC4_RFAL_NFCA_SEL_PAR( ctx->nfca.col_res.bytes_tx_rx, 
                                                                        ctx->nfca.col_res.bits_tx_rx );
            /* Send SDD_REQ (Anticollision frame) */
            error_flag = nfc4_rfal_iso14443a_transceive_anticollision_frame( ctx, ( uint8_t* ) &ctx->nfca.col_res.sel_req, 
                                                                                  &ctx->nfca.col_res.bytes_tx_rx, 
                                                                                  &ctx->nfca.col_res.bits_tx_rx, 
                                                                                  &ctx->nfca.col_res.rx_len, 
                                                                                  NFC4_NFCA_FDTMIN );
            /* Covert rxLen into bytes */
            ctx->nfca.col_res.rx_len = NFC4_RFAL_CONV_BITS_TO_BYTES( ctx->nfca.col_res.rx_len );
            if ( NFC4_RFAL_ERR_RF_COLLISION == error_flag )
            {
                /* Check received length */
                if ( ( ctx->nfca.col_res.bytes_tx_rx + ( ( 0U != ctx->nfca.col_res.bits_tx_rx ) ? 1U : 0U ) ) > 
                     ( NFC4_NFCA_SDD_RES_LEN + NFC4_NFCA_SDD_REQ_LEN ) )
                {
                    return NFC4_RFAL_ERR_PROTO;
                }

                if ( ( ( ctx->nfca.col_res.bytes_tx_rx + ( ( 0U != ctx->nfca.col_res.bits_tx_rx ) ? 1U : 0U ) ) > 
                       ( NFC4_NFCA_CASCADE_1_UID_LEN + NFC4_NFCA_SDD_REQ_LEN ) ) )
                { 
                    /* Collision in BCC: Anticollide only UID part */
                    ctx->nfca.col_res.bytes_tx_rx = NFC4_NFCA_CASCADE_1_UID_LEN + NFC4_NFCA_SDD_REQ_LEN - 1U;
                    ctx->nfca.col_res.bits_tx_rx  = 7;
                    
                    /* Not a real collision, extract the actual bit for the subsequent code */
                    coll_bit = ( uint8_t ) ( ( ( uint8_t* ) &ctx->nfca.col_res.sel_req )[ ctx->nfca.col_res.bytes_tx_rx ] & 
                                             ( 1U << ctx->nfca.col_res.bits_tx_rx ) ); 
                }
                if ( !( *ctx->nfca.col_res.coll_pend ) )
                {
                    /* Activity 1.0 & 1.1  9.3.4.12: If CON_DEVICES_LIMIT has a value of 0, then
                     * NFC Forum Device is configured to perform collision detection only       */
                    *ctx->nfca.col_res.coll_pend = true;
                    return NFC4_RFAL_ERR_IGNORE;
                }
                *ctx->nfca.col_res.coll_pend = true;
                /* Set and select the collision bit, with the number of bytes/bits successfully TxRx */
                if ( coll_bit != 0U )
                {
                    ( ( uint8_t* ) &ctx->nfca.col_res.sel_req )[ ctx->nfca.col_res.bytes_tx_rx ] = 
                                  ( uint8_t ) ( ( ( uint8_t* ) &ctx->nfca.col_res.sel_req )[ ctx->nfca.col_res.bytes_tx_rx ] | 
                                  ( 1U << ctx->nfca.col_res.bits_tx_rx ) );   /* MISRA 10.3 */
                }
                else
                {
                    ( ( uint8_t* ) &ctx->nfca.col_res.sel_req )[ ctx->nfca.col_res.bytes_tx_rx ] = 
                                  ( uint8_t ) ( ( ( uint8_t* ) &ctx->nfca.col_res.sel_req )[ ctx->nfca.col_res.bytes_tx_rx ] & 
                                  ~( 1U << ctx->nfca.col_res.bits_tx_rx ) );  /* MISRA 10.3 */
                }
                ctx->nfca.col_res.bits_tx_rx++;
                /* Check if number of bits form a byte */
                if ( NFC4_BITS_IN_BYTE == ctx->nfca.col_res.bits_tx_rx )
                {
                    ctx->nfca.col_res.bits_tx_rx = 0;
                    ctx->nfca.col_res.bytes_tx_rx++;
                }
                break;
            }
            /* Check if Collision loop has failed */
            if ( NFC4_RFAL_ERR_NONE != error_flag )
            {
                return error_flag;
            }
            /* Check if the received BCC match */
            if ( ctx->nfca.col_res.sel_req.bcc != nfc4_rfal_nfca_calculate_bcc( ctx->nfca.col_res.sel_req.nfc_id1, 
                                                                                NFC4_NFCA_CASCADE_1_UID_LEN ) )
            {
                return NFC4_RFAL_ERR_PROTO;
            }
            /* Anticollision OK, Select this Cascade Level */
            ctx->nfca.col_res.sel_req.sel_par = NFC4_NFCA_SEL_SELPAR;
            ctx->nfca.col_res.state = NFC4_NFCA_CR_SEL;
            break;
        }
        case NFC4_NFCA_CR_SEL:
        {
            /* Send SEL_REQ (Select command) - Retry upon timeout  EMVCo 2.6  9.6.1.3 */
            error_flag = nfc4_rfal_transceive_blocking_tx_rx( ctx, ( uint8_t* ) &ctx->nfca.col_res.sel_req, 
                                                                   sizeof( nfc4_rfal_nfca_sel_req_t ), 
                                                                   ( uint8_t* ) ctx->nfca.col_res.sel_res, 
                                                                   sizeof( nfc4_rfal_nfca_sel_res_t ), 
                                                                   &ctx->nfca.col_res.rx_len, 
                                                                   NFC4_TXRX_FLAGS_DEFAULT, 
                                                                   NFC4_NFCA_FDTMIN );
            if ( NFC4_RFAL_ERR_NONE != error_flag )
            {
                return error_flag;
            }
            /* Ensure proper response length */
            if ( sizeof( nfc4_rfal_nfca_sel_res_t ) != ctx->nfca.col_res.rx_len )
            {
                return NFC4_RFAL_ERR_PROTO;
            }
            /* Check cascade byte, if cascade tag then go next cascade level */
            if ( NFC4_NFCA_SDD_CT == ctx->nfca.col_res.sel_req.nfc_id1[ 0 ] )
            {
                /* Cascade Tag present, store nfcid1 bytes (excluding cascade tag) and continue for next CL */
                memcpy( &ctx->nfca.col_res.nfc_id1[ *ctx->nfca.col_res.nfc_id1_len ], 
                        &( ( uint8_t* )&ctx->nfca.col_res.sel_req.nfc_id1 )[ NFC4_NFCA_SDD_CT_LEN ], 
                        ( NFC4_NFCA_CASCADE_1_UID_LEN - NFC4_NFCA_SDD_CT_LEN ) );
                *ctx->nfca.col_res.nfc_id1_len += ( NFC4_NFCA_CASCADE_1_UID_LEN - NFC4_NFCA_SDD_CT_LEN );
                /* Go to next cascade level */
                ctx->nfca.col_res.state = NFC4_NFCA_CR_CL;
                ctx->nfca.col_res.cascade_lvl++;
            }
            else
            {
                /* UID Selection complete, Stop Cascade Level loop */
                memcpy( &ctx->nfca.col_res.nfc_id1[ *ctx->nfca.col_res.nfc_id1_len ], 
                        ( uint8_t* ) &ctx->nfca.col_res.sel_req.nfc_id1, 
                        NFC4_NFCA_CASCADE_1_UID_LEN );
                *ctx->nfca.col_res.nfc_id1_len += NFC4_NFCA_CASCADE_1_UID_LEN;

                ctx->nfca.col_res.state = NFC4_NFCA_CR_DONE;
                break; /* Only flag operation complete on the next execution */
            }
            break;
        }
        case NFC4_NFCA_CR_DONE:
        {
            return NFC4_RFAL_ERR_NONE;
        }
        default:
        {
            return NFC4_RFAL_ERR_WRONG_STATE;
        }
    }
    return NFC4_RFAL_ERR_BUSY;
}

static err_t nfc4_rfal_nfca_poller_start_single_collision_resolution( nfc4_t *ctx, bool *coll_pending, 
                                                                                   nfc4_rfal_nfca_sel_res_t *sel_res, 
                                                                                   uint8_t *nfc_id1, 
                                                                                   uint8_t *nfc_id1_len )
{
    /* Check parameters */
    if ( ( NULL == coll_pending ) || ( NULL == sel_res ) || ( NULL == nfc_id1 ) || ( NULL == nfc_id1_len ) )
    {
        return NFC4_RFAL_ERR_PARAM;
    }

    /* Initialize output parameters */
    *coll_pending = false;  /* Activity 1.1  9.3.4.6 */
    *nfc_id1_len  = 0;
    memset( nfc_id1, 0x00, NFC4_NFCA_CASCADE_3_UID_LEN );

    /* Save parameters */
    ctx->nfca.col_res.coll_pend    = coll_pending;
    ctx->nfca.col_res.sel_res      = sel_res;
    ctx->nfca.col_res.nfc_id1      = nfc_id1;
    ctx->nfca.col_res.nfc_id1_len  = nfc_id1_len;

    ctx->nfca.col_res.cascade_lvl  = ( uint8_t ) NFC4_NFCA_SEL_CASCADE_L1;
    ctx->nfca.col_res.state        = NFC4_NFCA_CR_CL;

    return NFC4_RFAL_ERR_NONE;
}

static err_t nfc4_rfal_nfca_poller_get_full_collision_resolution_status( nfc4_t *ctx )
{
    err_t error_flag;

    if ( ( NULL == ctx->nfca.col_res.nfca_dev_list ) || ( NULL == ctx->nfca.col_res.dev_cnt ) )
    {
        return NFC4_RFAL_ERR_WRONG_STATE;
    }
    EXIT_ON_ERR( error_flag, nfc4_rfal_nfca_poller_get_single_collision_resolution_status( ctx ) );
    
    /* Assign Listen Device */
    /* PRQA S 4342 1 # MISRA 10.5 - Guaranteed that no invalid enum values are created: see guard_eq_NFC4_NFCA_T2T, .... */
    ctx->nfca.col_res.nfca_dev_list[ *ctx->nfca.col_res.dev_cnt ].is_sleep = false;
    ( *ctx->nfca.col_res.dev_cnt )++;
    
    /* If a collision was detected and device counter is lower than limit  Activity 1.1  9.3.4.21 */
    if ( ctx->nfca.col_res.coll_pending )
    {
        /* Put this device to Sleep  Activity 1.1  9.3.4.22 */
        nfc4_rfal_nfca_poller_sleep( ctx );
        ctx->nfca.col_res.nfca_dev_list[ ( *ctx->nfca.col_res.dev_cnt - 1U ) ].is_sleep = true;
        /* Send a new SENS_REQ to check for other cards  Activity 1.1  9.3.4.23 */
        error_flag = nfc4_rfal_nfca_poller_check_presence( ctx, NFC4_14443A_SHORTFRAME_CMD_REQA, 
                                                           &ctx->nfca.col_res.nfca_dev_list[ *ctx->nfca.col_res.dev_cnt ].sens_res );
        if ( NFC4_RFAL_ERR_TIMEOUT == error_flag )
        {
            /* No more devices found, exit */
            ctx->nfca.col_res.coll_pending = false;
        }
        else
        {
            /* Another device found, continue loop */
            ctx->nfca.col_res.coll_pending = true;
        }
    }
    else
    {
        /* Exit loop */
        ctx->nfca.col_res.coll_pending = false;
    }
    /* Check if collision resolution shall continue */
    if ( ctx->nfca.col_res.coll_pending )
    {
        EXIT_ON_ERR( error_flag, nfc4_rfal_nfca_poller_start_single_collision_resolution( ctx, 
                                            &ctx->nfca.col_res.coll_pending,
                                            &ctx->nfca.col_res.nfca_dev_list[ *ctx->nfca.col_res.dev_cnt ].sel_res,
                                            ( uint8_t* ) &ctx->nfca.col_res.nfca_dev_list[ *ctx->nfca.col_res.dev_cnt ].nfc_id1,
                                            &ctx->nfca.col_res.nfca_dev_list[ *ctx->nfca.col_res.dev_cnt ].nfc_id1_len ) );

        return NFC4_RFAL_ERR_BUSY;
    }
    return NFC4_RFAL_ERR_NONE;
}

static err_t nfc4_rfal_nfca_poller_start_full_collision_resolution( nfc4_t *ctx, 
                                                                    nfc4_rfal_nfca_listen_device_t *nfca_dev_list, 
                                                                    uint8_t *dev_cnt )
{
    err_t      error_flag;
    uint16_t   rcv_len;
    if ( ( NULL == nfca_dev_list ) || ( NULL == dev_cnt ) )
    {
        return NFC4_RFAL_ERR_PARAM;
    }

    *dev_cnt   = 0;
    error_flag = NFC4_RFAL_ERR_NONE;

    /* Send ALL_REQ before Anticollision if a Sleep was sent before  Activity 1.1  9.3.4.1 and EMVco 2.6  9.3.2.1 */
    error_flag = nfc4_rfal_iso14443a_transceive_short_frame( ctx, NFC4_14443A_SHORTFRAME_CMD_WUPA, 
                                                             ( uint8_t* ) &nfca_dev_list->sens_res, 
                                                             ( uint8_t ) NFC4_RFAL_CONV_BYTES_TO_BITS( 
                                                             sizeof ( nfc4_rfal_nfca_sens_res_t ) ), 
                                                             &rcv_len, NFC4_NFCA_FDTMIN );

    /* Check proper SENS_RES/ATQA size */
    if ( ( NFC4_RFAL_ERR_NONE == error_flag ) && 
         ( NFC4_RFAL_CONV_BYTES_TO_BITS ( sizeof ( nfc4_rfal_nfca_sens_res_t ) ) != rcv_len ) )
    {
        return NFC4_RFAL_ERR_PROTO;
    }

    /* Save parameters */
    ctx->nfca.col_res.dev_cnt       = dev_cnt;
    ctx->nfca.col_res.nfca_dev_list = nfca_dev_list;

    return nfc4_rfal_nfca_poller_start_single_collision_resolution( ctx, &ctx->nfca.col_res.coll_pending, 
                                                                         &nfca_dev_list->sel_res, 
                                                            ( uint8_t* ) &nfca_dev_list->nfc_id1, 
                                                                         &nfca_dev_list->nfc_id1_len );
}

static uint8_t nfc4_rfal_nfca_calculate_bcc( uint8_t* buf, uint8_t buf_len )
{
    uint8_t bcc = 0;
    /* BCC is XOR over first 4 bytes of the SDD_RES  Digital 1.1 6.7.2 */
    for ( uint8_t cnt = 0; cnt < buf_len; cnt++ )
    {
        bcc ^= buf[ cnt ];
    }
    return bcc;
}

static err_t nfc4_rfal_nfc_poll_coll_resolution( nfc4_t *ctx )
{
    static uint8_t dev_cnt;
    err_t error_flag = NFC4_RFAL_ERR_NONE;
    /* Check if device limit has been reached */
    if ( ctx->nfc_dev.dev_cnt >= 1 )
    {
        return NFC4_RFAL_ERR_NONE;
    }
    
    /* NFC-A Collision Resolution */
    static nfc4_rfal_nfca_listen_device_t nfca_dev_list[ NFC4_NFC_MAX_DEVICES ];

    if ( !ctx->nfc_dev.is_tech_init )
    {
        EXIT_ON_ERR( error_flag, nfc4_rfal_nfca_poller_initialize( ctx ) ); /* Initialize RFAL for NFC-A */
        EXIT_ON_ERR( error_flag, nfc4_rfal_field_on( ctx ) );               /* Turns the Field On */
        ctx->nfc_dev.is_tech_init    = true;                        /* Technology has been initialized */
        ctx->nfc_dev.is_oper_ongoing = false;                       /* No operation currently ongoing  */
    }

    if ( !ctx->nfc_dev.is_oper_ongoing )
    {
        EXIT_ON_ERR( error_flag, nfc4_rfal_nfca_poller_start_full_collision_resolution( ctx, nfca_dev_list, &dev_cnt ) );
        ctx->nfc_dev.is_oper_ongoing = true;
        return NFC4_RFAL_ERR_BUSY;
    }
    error_flag = nfc4_rfal_nfca_poller_get_full_collision_resolution_status( ctx );
    if ( NFC4_RFAL_ERR_BUSY != error_flag )
    {
        ctx->nfc_dev.is_tech_init = false;

        if ( ( NFC4_RFAL_ERR_NONE == error_flag ) && ( 0U != dev_cnt ) )
        {
            for ( uint8_t cnt = 0; cnt < dev_cnt; cnt++ ) /* Copy devices found form local Nfca list into global device list */
            {
                ctx->nfc_dev.dev_list[ ctx->nfc_dev.dev_cnt ].nfca = nfca_dev_list[ cnt ];
                ctx->nfc_dev.dev_cnt++;
            }
        }
    }
    return NFC4_RFAL_ERR_BUSY;
}

static err_t nfc4_rfal_nfc_poll_activation( nfc4_t *ctx, uint8_t dev_idx )
{
    err_t error_flag;
    
    error_flag = NFC4_RFAL_ERR_NONE;
    
    if ( dev_idx > ctx->nfc_dev.dev_cnt )
    {
        return NFC4_RFAL_ERR_WRONG_STATE;
    }
    
    if ( !ctx->nfc_dev.is_tech_init )
    {
        nfc4_rfal_nfca_poller_initialize( ctx );
        ctx->nfc_dev.is_tech_init    = true;
        ctx->nfc_dev.is_oper_ongoing = false;
        return NFC4_RFAL_ERR_BUSY;
    }

    if ( ctx->nfc_dev.dev_list[ dev_idx ].nfca.is_sleep )                             /* Check if desired device is in Sleep */
    {
        nfc4_rfal_nfca_sens_res_t sens_res;
        nfc4_rfal_nfca_sel_res_t  sel_res;

        if ( !ctx->nfc_dev.is_oper_ongoing )
        {
            /* Wake up all cards  */
            EXIT_ON_ERR( error_flag, nfc4_rfal_nfca_poller_check_presence( ctx, NFC4_14443A_SHORTFRAME_CMD_WUPA, &sens_res ) );
            ctx->nfc_dev.is_oper_ongoing = true;
        }
        else
        {
            /* Select specific device */
            EXIT_ON_ERR( error_flag, nfc4_rfal_nfca_poller_select( ctx, ctx->nfc_dev.dev_list[dev_idx].nfca.nfc_id1, 
                                                                   ctx->nfc_dev.dev_list[dev_idx].nfca.nfc_id1_len, &sel_res ) );
            ctx->nfc_dev.dev_list[ dev_idx ].nfca.is_sleep = false;
            ctx->nfc_dev.is_oper_ongoing = false;
        }
        return NFC4_RFAL_ERR_BUSY;
    }

    /* Set NFCID */
    ctx->nfc_dev.dev_list[ dev_idx ].nfc_id     = ctx->nfc_dev.dev_list[ dev_idx ].nfca.nfc_id1;
    ctx->nfc_dev.dev_list [dev_idx ].nfc_id_len = ctx->nfc_dev.dev_list[ dev_idx ].nfca.nfc_id1_len;

    ctx->nfc_dev.active_dev = &ctx->nfc_dev.dev_list[ dev_idx ]; /* Assign active device to be used further on */
    return NFC4_RFAL_ERR_NONE;
}

static err_t nfc4_rfal_nfc_discover( nfc4_t *ctx )
{
    if ( NFC4_NFC_STATE_IDLE != ctx->nfc_dev.state )
    {
        return NFC4_RFAL_ERR_WRONG_STATE;
    }
    /* Initialize context for discovery */
    ctx->nfc_dev.active_dev       = NULL;
    ctx->nfc_dev.dev_cnt          = 0;
    ctx->nfc_dev.is_tech_init     = false;
    
    ctx->nfc_dev.state = NFC4_NFC_STATE_START_DISCOVERY;
    
    return NFC4_RFAL_ERR_NONE; 
}

static err_t nfc4_rfal_nfc_get_active_device( nfc4_t *ctx, nfc4_rfal_nfc_device_t **dev )
{
    /* Check for valid state */
    if ( ctx->nfc_dev.state < NFC4_NFC_STATE_ACTIVATED )
    {
        return NFC4_RFAL_ERR_WRONG_STATE;
    }
    
    /* Check valid parameter */
    if ( NULL == dev )
    {
        return NFC4_RFAL_ERR_PARAM;
    }
    
    /* Check for valid state */
    if ( ( 0U == ctx->nfc_dev.dev_cnt ) || ( NULL == ctx->nfc_dev.active_dev )  )
    {
        return NFC4_RFAL_ERR_REQUEST;
    }
    
    *dev = ctx->nfc_dev.active_dev;
    return NFC4_RFAL_ERR_NONE;
}

static err_t nfc4_rfal_nfc_deactivate( nfc4_t *ctx, bool discovery )
{
    /* Check for valid state */
    if ( NFC4_NFC_STATE_IDLE >= ctx->nfc_dev.state )
    {
        return NFC4_RFAL_ERR_WRONG_STATE;
    }
    
    /* Check if discovery is to continue afterwards */
    if ( true == discovery )
    {
        /* If so let the state machine continue*/
        ctx->nfc_dev.state = NFC4_NFC_STATE_DEACTIVATION;
    }
    else
    {
        /* Otherwise deactivate immediately and go to IDLE */
        nfc4_rfal_field_off( ctx );
        ctx->nfc_dev.active_dev = NULL;
        ctx->nfc_dev.state = NFC4_NFC_STATE_IDLE;
    }
    return NFC4_RFAL_ERR_NONE;
}

static err_t nfc4_rfal_field_on( nfc4_t *ctx )
{
    err_t error_flag = NFC4_RFAL_ERR_NONE;
    
    /* Check if RFAL has been initialized (Oscillator should be running) and also
     * if a direct register access has been performed and left the Oscillator Off */
    uint8_t rx_data = 0;
    error_flag |= nfc4_read_register( ctx, NFC4_REG_OP_CTRL, &rx_data );
    
    if ( NFC4_OP_CTRL_EN != ( rx_data & NFC4_OP_CTRL_EN ) )
    {
        return NFC4_RFAL_ERR_WRONG_STATE;
    }
    
    /* Set Analog configurations for Field On event */
    error_flag |= nfc4_set_analog_config( ctx, ( NFC4_ANALOG_CONFIG_TECH_CHIP | NFC4_ANALOG_CONFIG_CHIP_FIELD_ON ) );
    
    /* Perform collision avoidance and turn field On if not already On */
    error_flag |= nfc4_read_register( ctx, NFC4_REG_OP_CTRL, &rx_data );
    
    if ( ( NFC4_OP_CTRL_TX_EN != ( rx_data & NFC4_OP_CTRL_TX_EN ) ) || !ctx->rfal.field )
    {
        /* Use Thresholds set by AnalogConfig */
        error_flag |= nfc4_perform_collision_avoidance( ctx, NFC4_CMD_NFC_INITIAL_FIELD_ON, 
                                                             NFC4_THLD_DO_NOT_SET, 
                                                             NFC4_THLD_DO_NOT_SET );
        
        error_flag |= nfc4_read_register( ctx, NFC4_REG_OP_CTRL, &rx_data );
        ctx->rfal.field = ( NFC4_OP_CTRL_TX_EN == ( rx_data & NFC4_OP_CTRL_TX_EN ) );
        
        /* Only turn on Receiver and Transmitter if field was successfully turned On */
        if ( ctx->rfal.field )
        {
            /* Enable Tx and Rx (Tx is already On) */
            error_flag |= nfc4_set_register_bits( ctx, NFC4_REG_OP_CTRL, ( NFC4_OP_CTRL_RX_EN | NFC4_OP_CTRL_TX_EN ) ); 
        }
    }
    return error_flag;
}

static err_t nfc4_rfal_field_off( nfc4_t *ctx )
{
    /* Check whether a TxRx is not yet finished */
    if ( NFC4_TXRX_STATE_IDLE != ctx->rfal.tx_rx.state )
    {
        nfc4_rfal_cleanup_transceive( ctx );
    }
    
    /* Disable Tx and Rx */
    nfc4_clear_register_bits( ctx, NFC4_REG_OP_CTRL, ( NFC4_OP_CTRL_RX_EN | NFC4_OP_CTRL_TX_EN ) );
    
    /* Set Analog configurations for Field Off event */
    nfc4_set_analog_config( ctx, ( NFC4_ANALOG_CONFIG_TECH_CHIP | NFC4_ANALOG_CONFIG_CHIP_FIELD_OFF ) );
    ctx->rfal.field = false;
    
    return NFC4_RFAL_ERR_NONE;
}

static void nfc4_rfal_fifo_status_update( nfc4_t *ctx )
{
    if ( NFC4_FIFO_STATUS_INVALID == ctx->rfal.fifo.status[ NFC4_FIFO_STATUS_REG2 ] )
    {
        nfc4_read_multiple_registers( ctx, NFC4_REG_FIFO_STATUS_1, ctx->rfal.fifo.status, 2 );
    }
}

static uint16_t nfc4_rfal_fifo_status_get_num_bytes( nfc4_t *ctx )
{
    uint16_t result;
    nfc4_rfal_fifo_status_update( ctx );
    result = ( ( ( ( uint16_t ) ctx->rfal.fifo.status[ NFC4_FIFO_STATUS_REG2 ] & NFC4_FIFO_STATUS2_FIFO_B_MASK ) >> 
                                NFC4_FIFO_STATUS2_FIFO_B_SHIFT ) << NFC4_BITS_IN_BYTE );
    result |= ( ( ( uint16_t ) ctx->rfal.fifo.status[ NFC4_FIFO_STATUS_REG1 ] ) & 0x00FFU );
    return result;
}

static uint8_t nfc4_rfal_fifo_get_num_incomplete_bits( nfc4_t *ctx )
{
    nfc4_rfal_fifo_status_update( ctx );
    return ( ( ctx->rfal.fifo.status[ NFC4_FIFO_STATUS_REG2 ] & NFC4_FIFO_STATUS2_FIFO_LB_MASK ) >> 
               NFC4_FIFO_STATUS2_FIFO_LB_SHIFT );
}

static bool nfc4_rfal_fifo_status_is_incomplete_byte( nfc4_t *ctx )
{
    nfc4_rfal_fifo_status_update( ctx );
    return ( 0U != ( ctx->rfal.fifo.status[ NFC4_FIFO_STATUS_REG2 ] & NFC4_FIFO_STATUS2_FIFO_LB_MASK ) );
}

static bool nfc4_rfal_fifo_status_is_missing_par( nfc4_t *ctx )
{
    nfc4_rfal_fifo_status_update( ctx );
    return ( 0U != ( ctx->rfal.fifo.status[ NFC4_FIFO_STATUS_REG2 ] & NFC4_FIFO_STATUS2_NP_LB ) );
}

static err_t nfc4_rfal_start_transceive( nfc4_t *ctx, nfc4_rfal_transceive_context_t *ctx_tx )
{
    uint32_t fx_t_adj;  /* FWT or FDT adjustment calculation */
    
    /* Check for valid parameters */
    if ( NULL == ctx_tx )
    {
        return NFC4_RFAL_ERR_PARAM;
    }
    
    /* Check whether the field is already On, otherwise no TXE will be received  */
    uint8_t rx_data = 0;
    nfc4_read_register( ctx, NFC4_REG_OP_CTRL, &rx_data);
    if ( ( NFC4_OP_CTRL_TX_EN != ( rx_data & NFC4_OP_CTRL_TX_EN ) ) && 
         ( NULL != ctx_tx->tx_buf ) )
    {
        return NFC4_RFAL_ERR_WRONG_STATE;
    }
    ctx->rfal.tx_rx.ctx = *ctx_tx;

    if ( ( NFC4_FWT_NONE != ctx->rfal.tx_rx.ctx.fwt ) && ( 0U != ctx->rfal.tx_rx.ctx.fwt ) )
    {
        fx_t_adj = NFC4_FWT_ADJUSTMENT;
        fx_t_adj += ( uint32_t ) NFC4_FWT_A_ADJUSTMENT;
        
        /* Ensure that the given FWT doesn't exceed NRT maximum */
        ctx->rfal.tx_rx.ctx.fwt = MIN( ( ctx->rfal.tx_rx.ctx.fwt + fx_t_adj ), NFC4_NRT_MAX_1FC );
        
        /* Set FWT in the NRT */
        nfc4_set_no_response_time( ctx, NFC4_RFAL_CONV_1FC_TO_64FC( ctx->rfal.tx_rx.ctx.fwt ) );
    }
    else
    {
        /* Disable NRT, no NRE will be triggered, therefore wait endlessly for Rx */
        nfc4_set_no_response_time( ctx, NFC4_NRT_DISABLED );
    }
    ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_TX_IDLE;
    ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_BUSY;

    /* Check if the Transceive start performing Tx or goes directly to Rx */
    if ( ( NULL == ctx->rfal.tx_rx.ctx.tx_buf ) || ( 0U == ctx->rfal.tx_rx.ctx.tx_buf_len ) )
    {
        /* Clear FIFO, Clear and Enable the Interrupts */
        nfc4_rfal_prepare_transceive( ctx );
        
        /* No Tx done, enable the Receiver */
        nfc4_send_direct_command( ctx, NFC4_CMD_UNMASK_RECEIVE_DATA );

        /* Start NRT manually, if FWT = 0 (wait endlessly for Rx) chip will ignore anyhow */
        nfc4_send_direct_command( ctx, NFC4_CMD_START_NO_RESPONSE_TIMER );

        ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_RX_IDLE;
    }
    return NFC4_RFAL_ERR_NONE;
}

static void nfc4_rfal_prepare_transceive( nfc4_t *ctx )
{
    uint32_t mask_interrupts;
    uint8_t  reg;

    mask_interrupts = ( NFC4_IRQ_MASK_FWL  | NFC4_IRQ_MASK_TXE  |
                        NFC4_IRQ_MASK_RXS  | NFC4_IRQ_MASK_RXE  |
                        NFC4_IRQ_MASK_PAR  | NFC4_IRQ_MASK_CRC  |
                        NFC4_IRQ_MASK_ERR1 | NFC4_IRQ_MASK_ERR2 |
                        NFC4_IRQ_MASK_NRE );

    /* Transceive flags */
    reg = ( NFC4_ISO14443A_NFC_NO_TX_PAR_OFF | 
            NFC4_ISO14443A_NFC_NO_RX_PAR_OFF | 
            NFC4_ISO14443A_NFC_NFC_F0_OFF );

    /* Apply current TxRx flags on ISO14443A and NFC 106kb/s Settings Register */
    nfc4_modify_register_bits( ctx, NFC4_REG_ISO14443A_NFC, ( NFC4_ISO14443A_NFC_NO_TX_PAR | 
                                                              NFC4_ISO14443A_NFC_NO_RX_PAR | 
                                                              NFC4_ISO14443A_NFC_NFC_F0 ), 
                                                            ( NFC4_ISO14443A_NFC_NO_TX_PAR | 
                                                              NFC4_ISO14443A_NFC_NO_RX_PAR | 
                                                              NFC4_ISO14443A_NFC_NFC_F0 ) & reg );
    
    /* Clear and enable these interrupts */
    nfc4_get_interrupt ( ctx, mask_interrupts );
    nfc4_enable_interrupt ( ctx, mask_interrupts );

    /* Clear FIFO status local copy */
    ctx->rfal.fifo.status[ NFC4_FIFO_STATUS_REG2 ] = NFC4_FIFO_STATUS_INVALID;
}

static void nfc4_rfal_cleanup_transceive( nfc4_t *ctx )
{
    /* Restore default settings on NFCIP1 mode, Receiving parity + CRC bits and manual Tx Parity*/
    nfc4_clear_register_bits( ctx, NFC4_REG_ISO14443A_NFC, ( NFC4_ISO14443A_NFC_NO_TX_PAR | 
                                                             NFC4_ISO14443A_NFC_NO_RX_PAR | 
                                                             NFC4_ISO14443A_NFC_NFC_F0 ) );
    /* Restore AGC enabled */
    nfc4_set_register_bits( ctx, NFC4_REG_RX_CFG_2, NFC4_RX_CFG_2_AGC_EN );
}

static void nfc4_rfal_transceive_tx( nfc4_t *ctx )
{
    volatile uint32_t irqs;
    uint16_t          tmp;
    
    irqs = NFC4_IRQ_MASK_NONE;
    
    switch ( ctx->rfal.tx_rx.state )
    {
        case NFC4_TXRX_STATE_TX_IDLE:
        {
            ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_TX_TRANSMIT;
            /* fall through */
        }
        case NFC4_TXRX_STATE_TX_TRANSMIT: /*  PRQA S 2003 # MISRA 16.3 - Intentional fall through */
        {
            /* Clear FIFO, Clear and Enable the Interrupts */
            nfc4_rfal_prepare_transceive( ctx );

            /* ST25R3916 has a fixed FIFO water level */
            ctx->rfal.fifo.exp_wl = NFC4_FIFO_OUT_WL;
            
            /* Calculate the bytes needed to be Written into FIFO (a incomplete byte will be added as 1byte) */
            ctx->rfal.fifo.bytes_total = ( uint16_t ) NFC4_RFAL_CALC_NUM_BYTES( ctx->rfal.tx_rx.ctx.tx_buf_len );
            
            /* Set the number of full bytes and bits to be transmitted */
            nfc4_set_num_tx_bits( ctx, ctx->rfal.tx_rx.ctx.tx_buf_len );
            
            /* Load FIFO with total length or FIFO's maximum */
            ctx->rfal.fifo.bytes_written = MIN( ctx->rfal.fifo.bytes_total, NFC4_FIFO_DEPTH );
            nfc4_write_fifo( ctx, ctx->rfal.tx_rx.ctx.tx_buf, ctx->rfal.fifo.bytes_written );
            
            /* Trigger/Start transmission                                                  */
            if ( 0U != ( ctx->rfal.tx_rx.ctx.flags & ( uint32_t ) NFC4_TXRX_FLAGS_CRC_TX_MANUAL )  )
            {
                nfc4_send_direct_command( ctx, NFC4_CMD_TRANSMIT_WITHOUT_CRC );
            }
            else
            {
                nfc4_send_direct_command( ctx, NFC4_CMD_TRANSMIT_WITH_CRC );
            }
             
            /* Check if a WL level is expected or TXE should come */
            if ( ctx->rfal.fifo.bytes_written < ctx->rfal.fifo.bytes_total )
            {
                ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_TX_WAIT_WL;
            }
            else
            {
                ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_TX_WAIT_TXE;
            }
            break;
        }
        case NFC4_TXRX_STATE_TX_WAIT_WL:
        {
            nfc4_check_for_received_interrupts ( ctx );
            irqs = nfc4_get_interrupt( ctx, NFC4_IRQ_MASK_FWL | NFC4_IRQ_MASK_TXE );
            if ( NFC4_IRQ_MASK_NONE == irqs )
            {
               break;  /* No interrupt to process */
            }

            if ( ( 0U != ( irqs & NFC4_IRQ_MASK_FWL ) ) && ( 0U == (irqs & NFC4_IRQ_MASK_TXE ) ) )
            {
                ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_TX_RELOAD_FIFO;
            }
            else
            {
                ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_IO;
                ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_TX_FAIL;
                break;
            }
            /* fall through */
        }
        case NFC4_TXRX_STATE_TX_RELOAD_FIFO:   /*  PRQA S 2003 # MISRA 16.3 - Intentional fall through */
        {
            /* Load FIFO with the remaining length or maximum available */
            tmp = MIN( ( ctx->rfal.fifo.bytes_total - ctx->rfal.fifo.bytes_written ), ctx->rfal.fifo.exp_wl );       
            /* tmp holds the number of bytes written on this iteration */
            nfc4_write_fifo( ctx, &ctx->rfal.tx_rx.ctx.tx_buf[ ctx->rfal.fifo.bytes_written ], tmp );

            /* Update total written bytes to FIFO */
            ctx->rfal.fifo.bytes_written += tmp;

            /* Check if a WL level is expected or TXE should come */
            if ( ctx->rfal.fifo.bytes_written < ctx->rfal.fifo.bytes_total )
            {
                ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_TX_WAIT_WL;
            }
            else
            {
                ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_TX_WAIT_TXE;
            }
            break;
        }
        case NFC4_TXRX_STATE_TX_WAIT_TXE:
        {
            nfc4_check_for_received_interrupts ( ctx );
            irqs = nfc4_get_interrupt( ctx, NFC4_IRQ_MASK_FWL | NFC4_IRQ_MASK_TXE );
            if ( NFC4_IRQ_MASK_NONE == irqs )
            {
               break;  /* No interrupt to process */
            }

            if ( 0U != ( irqs & NFC4_IRQ_MASK_TXE ) )
            {
                ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_TX_DONE;
            }
            else if ( 0U != ( irqs & NFC4_IRQ_MASK_FWL ) )
            {
                break;  /* Ignore ST25R3916 FIFO WL if total TxLen is already on the FIFO */
            }
            else
            {
                ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_IO;
                ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_TX_FAIL;
                break;
            }
            /* fall through */
        }  
        case NFC4_TXRX_STATE_TX_DONE:   /*  PRQA S 2003 # MISRA 16.3 - Intentional fall through */
        {
            /* If no rxBuf is provided do not wait/expect Rx */
            if ( NULL == ctx->rfal.tx_rx.ctx.rx_buf )
            {
                /* Clean up Transceive */
                nfc4_rfal_cleanup_transceive( ctx );
                                
                ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_NONE;
                ctx->rfal.tx_rx.state  =  NFC4_TXRX_STATE_IDLE;
                break;
            }
            /* Goto Rx */
            ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_RX_IDLE;
            break;
        }
        case NFC4_TXRX_STATE_TX_FAIL:
        {
            /* Error should be assigned by previous state */
            if ( NFC4_RFAL_ERR_BUSY == ctx->rfal.tx_rx.status )
            {                
                ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_SYSTEM;
            }
            /* Clean up Transceive */
            nfc4_rfal_cleanup_transceive( ctx );
            
            ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_IDLE;
            break;
        }
        default:
        {
            ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_SYSTEM;
            ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_TX_FAIL;
            break;
        }
    }
}

static void nfc4_rfal_transceive_rx( nfc4_t *ctx )
{
    volatile uint32_t irqs;
    uint32_t          status = 0;
    uint16_t          tmp;
    uint16_t          aux;
    
    irqs = NFC4_IRQ_MASK_NONE;
    
    if ( ctx->rfal.tx_rx.state != ctx->rfal.tx_rx.last_state )
    {        
        ctx->rfal.tx_rx.last_state = ctx->rfal.tx_rx.state;
    }
    
    switch ( ctx->rfal.tx_rx.state )
    {
        case NFC4_TXRX_STATE_RX_IDLE:
        {
            /* Clear rx counters */
            ctx->rfal.fifo.bytes_written   = 0;  /* Total bytes written on RxBuffer         */
            ctx->rfal.fifo.bytes_total     = 0;  /* Total bytes in FIFO will now be from Rx */
            if ( NULL != ctx->rfal.tx_rx.ctx.rx_rcvd_len )
            {
                *ctx->rfal.tx_rx.ctx.rx_rcvd_len = 0;
            }
            ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_RX_WAIT_RXS;
            break;
        }
        case NFC4_TXRX_STATE_RX_WAIT_RXS:
        {
            nfc4_check_for_received_interrupts ( ctx );
            irqs = nfc4_get_interrupt( ctx, ( NFC4_IRQ_MASK_RXS | NFC4_IRQ_MASK_NRE | NFC4_IRQ_MASK_EOF ) );
            if ( irqs == NFC4_IRQ_MASK_NONE )
            {
                break;  /* No interrupt to process */
            }
            /* Only raise Timeout if NRE is detected with no Rx Start (NRT EMV mode) */
            if ( ( 0U != ( irqs & NFC4_IRQ_MASK_NRE ) ) && ( 0U == ( irqs & NFC4_IRQ_MASK_RXS ) ) )
            {
                ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_TIMEOUT;
                ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_FAIL;
                break;
            }
            /* Only raise Link Loss if EOF is detected with no Rx Start */
            if ( ( 0U != ( irqs & NFC4_IRQ_MASK_EOF ) ) && ( 0U == ( irqs & NFC4_IRQ_MASK_RXS ) ) )
            {
                ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_LINK_LOSS;
                ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_FAIL;
                break;
            }
            
            if ( 0U != ( irqs & NFC4_IRQ_MASK_RXS ) )
            {
                ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_WAIT_RXE;
            }
            else
            {
                ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_IO;
                ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_FAIL;
                break;
            }
            /* remove NRE that might appear together (NRT EMV mode), and remove RXS, 
             * but keep EOF if present for next state 
             */
            irqs &= ~(NFC4_IRQ_MASK_RXS | NFC4_IRQ_MASK_NRE);
            /* fall through */
        }
        case NFC4_TXRX_STATE_RX_WAIT_RXE:   /*  PRQA S 2003 # MISRA 16.3 - Intentional fall through */
        {
            nfc4_check_for_received_interrupts ( ctx );
            irqs |= nfc4_get_interrupt( ctx, ( NFC4_IRQ_MASK_RXE  | 
                                               NFC4_IRQ_MASK_FWL | 
                                               NFC4_IRQ_MASK_EOF | 
                                               NFC4_IRQ_MASK_RX_REST | 
                                               NFC4_IRQ_MASK_WU_F ) );
            if ( NFC4_IRQ_MASK_NONE == irqs )
            {
                break;  /* No interrupt to process */
            }
            
            if ( 0U != ( irqs & NFC4_IRQ_MASK_RX_REST ) )
            {
                /* RX_REST indicates that Receiver has been reseted due to EMD, therefore a RXS + RXE should *
                 * follow if a good reception is followed within the valid initial timeout                   */
                
                /* Check whether NRT has expired already, if so signal a timeout */
                if ( NFC4_IRQ_MASK_NONE != nfc4_get_interrupt( ctx, NFC4_IRQ_MASK_NRE ) )
                {
                    ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_TIMEOUT;
                    ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_FAIL;
                    break;
                }
                uint8_t rx_data = 0;
                nfc4_read_register( ctx, NFC4_REG_NFCIP1_BIT_RATE, &rx_data );
                if ( 0 == ( rx_data & NFC4_NFCIP1_BIT_RATE_NRT_ON ) )   /* MISRA 13.5 */
                {
                    ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_TIMEOUT;
                    ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_FAIL;
                    break;
                }
                /* Discard any previous RXS */
                nfc4_get_interrupt( ctx, NFC4_IRQ_MASK_RXS );
                
                /* Check whether a following reception has already started */
                nfc4_read_register( ctx, NFC4_REG_AUX_DISPLAY, &rx_data );
                if ( NFC4_AUX_DISPLAY_RX_ACT == ( rx_data & NFC4_AUX_DISPLAY_RX_ACT ) )   /* MISRA 13.5 */
                {
                    ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_WAIT_RXE;
                    break;
                }
                ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_WAIT_RXS;
                break;
            }
            
            if ( ( 0U != ( irqs & NFC4_IRQ_MASK_FWL ) ) && ( 0U == ( irqs & NFC4_IRQ_MASK_RXE ) ) )
            {
                ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_RX_READ_FIFO;
                break;
            }
            
            /* Automatic responses allowed during TxRx only for the SENSF_REQ */
            if ( 0U != ( irqs & NFC4_IRQ_MASK_WU_F ) )
            {
                ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_RX_WAIT_RXS;
                break;
            }
            
            /* After RXE retrieve and check for any error irqs */
            irqs |= nfc4_get_interrupt( ctx, ( NFC4_IRQ_MASK_CRC | 
                                               NFC4_IRQ_MASK_PAR | 
                                               NFC4_IRQ_MASK_ERR1 | 
                                               NFC4_IRQ_MASK_ERR2 | 
                                               NFC4_IRQ_MASK_COL ) );
            ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_RX_ERR_CHECK;
            /* fall through */
        }
        case NFC4_TXRX_STATE_RX_ERR_CHECK:   /*  PRQA S 2003 # MISRA 16.3 - Intentional fall through */
        {
            if ( 0U != ( irqs & NFC4_IRQ_MASK_ERR1 ) )
            {
                ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_FRAMING;
                ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_READ_DATA;
                break;
            }
            /* Discard Soft Framing errors in AP2P and CE */
            else if ( 0U != ( irqs & NFC4_IRQ_MASK_ERR2 ) )
            {
                ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_FRAMING;
                ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_READ_DATA;
                break;
            }
            else if ( 0U != ( irqs & NFC4_IRQ_MASK_PAR ) )
            {
                ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_PAR;
                ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_READ_DATA;
                break;
            }
            else if ( 0U != ( irqs & NFC4_IRQ_MASK_CRC ) )
            {
                ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_CRC;
                ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_READ_DATA;
                break;
            }
            else if ( 0U != ( irqs & NFC4_IRQ_MASK_COL ) )
            {
                ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_RF_COLLISION;
                ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_READ_DATA;
                break;
            }
            else if ( 0U != ( irqs & NFC4_IRQ_MASK_RXE ) )
            {
                /* Reception ended without any error indication,
                 * check FIFO status for malformed or incomplete frames           
                 */
                
                /* Check if the reception ends with an incomplete byte (residual bits) */
                if ( nfc4_rfal_fifo_status_is_incomplete_byte( ctx ) )
                {
                   ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_INCOMPLETE_BYTE;
                }
                /* Check if the reception ends missing parity bit */
                else if ( nfc4_rfal_fifo_status_is_missing_par( ctx ) )
                {
                   ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_FRAMING;
                }
                ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_RX_READ_DATA;
            }
            else
            {
                ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_IO;
                ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_FAIL;
                break;
            }
            /* fall through */
        }
        case NFC4_TXRX_STATE_RX_READ_DATA:   /*  PRQA S 2003 # MISRA 16.3 - Intentional fall through */
        {
            tmp = nfc4_rfal_fifo_status_get_num_bytes( ctx );
            /* Check if CRC should not be placed in rxBuf */
            if ( 0U == ( ctx->rfal.tx_rx.ctx.flags & ( uint32_t ) NFC4_TXRX_FLAGS_CRC_RX_KEEP ) )
            {
                /* if received frame was bigger than CRC */
                if ( ( uint16_t )( ctx->rfal.fifo.bytes_total + tmp ) > 0U )
                {
                    /* By default CRC will not be placed into the rxBuffer */
                    if ( ( tmp > NFC4_CRC_LEN ) )  
                    {
                        tmp -= NFC4_CRC_LEN;
                    }
                    /* If the CRC was already placed into rxBuffer (due to WL interrupt where CRC was already in FIFO Read)
                     * cannot remove it from rxBuf. Can only remove it from rxBufLen not indicate the presence of CRC    */ 
                    else if ( ctx->rfal.fifo.bytes_total > NFC4_CRC_LEN )                       
                    {                        
                        ctx->rfal.fifo.bytes_total -= NFC4_CRC_LEN;
                    }
                }
            }
            ctx->rfal.fifo.bytes_total += tmp;  /* add to total bytes counter */
            /* Check if remaining bytes fit on the rxBuf available                         */
            if ( ctx->rfal.fifo.bytes_total > NFC4_RFAL_CONV_BITS_TO_BYTES( ctx->rfal.tx_rx.ctx.rx_buf_len ) )
            {
                tmp = ( uint16_t )( NFC4_RFAL_CONV_BITS_TO_BYTES( ctx->rfal.tx_rx.ctx.rx_buf_len ) - 
                                    ctx->rfal.fifo.bytes_written );
                /* Transmission errors have precedence over buffer error */
                if ( NFC4_RFAL_ERR_BUSY == ctx->rfal.tx_rx.status )
                {
                    ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_NOMEM;
                }
            }
            /* Retrieve remaining bytes from FIFO to rxBuf, and assign total length rcvd   */
            nfc4_read_fifo( ctx, &ctx->rfal.tx_rx.ctx.rx_buf[ ctx->rfal.fifo.bytes_written ], tmp );
            if ( NULL != ctx->rfal.tx_rx.ctx.rx_rcvd_len )
            {
                *ctx->rfal.tx_rx.ctx.rx_rcvd_len = ( uint16_t ) NFC4_RFAL_CONV_BYTES_TO_BITS( ctx->rfal.fifo.bytes_total );
                if ( nfc4_rfal_fifo_status_is_incomplete_byte( ctx ) )
                {
                    *ctx->rfal.tx_rx.ctx.rx_rcvd_len -= ( NFC4_BITS_IN_BYTE - nfc4_rfal_fifo_get_num_incomplete_bits( ctx ) );
                }
            }
            
            /* If an error as been marked/detected don't fall into to RX_DONE  */
            if ( NFC4_RFAL_ERR_BUSY != ctx->rfal.tx_rx.status )
            {
                ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_RX_FAIL;
                break;
            }
            ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_RX_DONE;
            /* fall through */
        }
        case NFC4_TXRX_STATE_RX_DONE:   /*  PRQA S 2003 # MISRA 16.3 - Intentional fall through */
        {
            /* Clean up Transceive */
            nfc4_rfal_cleanup_transceive( ctx );
            ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_NONE;
            ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_IDLE;
            break;
        }    
        case NFC4_TXRX_STATE_RX_READ_FIFO:
        {
            tmp = nfc4_rfal_fifo_status_get_num_bytes( ctx );
            ctx->rfal.fifo.bytes_total += tmp;
            /* Calculate the amount of bytes that still fits in rxBuf                      */
            aux = ( ( ctx->rfal.fifo.bytes_total > NFC4_RFAL_CONV_BITS_TO_BYTES( ctx->rfal.tx_rx.ctx.rx_buf_len ) ) ? 
                  ( NFC4_RFAL_CONV_BITS_TO_BYTES( ctx->rfal.tx_rx.ctx.rx_buf_len ) - ctx->rfal.fifo.bytes_written ) : tmp );
            /* Retrieve incoming bytes from FIFO to rxBuf, and store already read amount   */
            nfc4_read_fifo( ctx, &ctx->rfal.tx_rx.ctx.rx_buf[ ctx->rfal.fifo.bytes_written ], aux );
            ctx->rfal.fifo.bytes_written += aux;
            /* If the bytes already read were not the full FIFO WL, dump the remaining     *
             * FIFO so that ST25R391x can continue with reception                          */
            if ( aux < tmp )
            {
                nfc4_read_fifo( ctx, NULL, ( tmp - aux ) );
            }
            /* Clear FIFO status local copy */
            ctx->rfal.fifo.status[ NFC4_FIFO_STATUS_REG2 ] = NFC4_FIFO_STATUS_INVALID;
            ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_RX_WAIT_RXE;
            break;
        }
        case NFC4_TXRX_STATE_RX_FAIL:
        {
            /* Clean up Transceive */
            nfc4_rfal_cleanup_transceive( ctx );
            /* Error should be assigned by previous state */
            if ( NFC4_RFAL_ERR_BUSY == ctx->rfal.tx_rx.status )
            {                
                ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_SYSTEM;
            }
            ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_IDLE;
            break;
        }
        case NFC4_TXRX_STATE_RX_WAIT_EOF:
        {
            nfc4_check_for_received_interrupts( ctx );
            irqs = nfc4_get_interrupt( ctx, ( NFC4_IRQ_MASK_CAT | NFC4_IRQ_MASK_CAC ) );
            if ( NFC4_IRQ_MASK_NONE == irqs )
            {
               break;  /* No interrupt to process */
            }
            
            if ( 0U != ( irqs & NFC4_IRQ_MASK_CAT ) )
            {
               ctx->rfal.tx_rx.state = NFC4_TXRX_STATE_RX_DONE;
            }
            else if ( 0U != ( irqs & NFC4_IRQ_MASK_CAC ) )
            {
               ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_RF_COLLISION;
               ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_FAIL;
            }
            else
            {
               ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_IO;
               ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_FAIL;
            }
            break;
        }
        default:
        {
            ctx->rfal.tx_rx.status = NFC4_RFAL_ERR_SYSTEM;
            ctx->rfal.tx_rx.state  = NFC4_TXRX_STATE_RX_FAIL;
            break;    
        }
    }    
}

static bool nfc4_rfal_is_transceive_in_tx( nfc4_t *ctx )
{
    return ( ( ctx->rfal.tx_rx.state >= NFC4_TXRX_STATE_TX_IDLE ) && 
             ( ctx->rfal.tx_rx.state < NFC4_TXRX_STATE_RX_IDLE ) );
}

static bool nfc4_rfal_is_transceive_in_rx( nfc4_t *ctx )
{
    return ( ctx->rfal.tx_rx.state >= NFC4_TXRX_STATE_RX_IDLE );
}

static err_t nfc4_rfal_transceive_run_blocking_tx( nfc4_t *ctx )
{
    err_t error_flag;
    do
    {
        error_flag = nfc4_rfal_worker( ctx );
    }
    while ( nfc4_rfal_is_transceive_in_tx ( ctx ) && ( NFC4_RFAL_ERR_BUSY == error_flag ) );
    
    if ( nfc4_rfal_is_transceive_in_rx ( ctx ) )
    {
        return NFC4_RFAL_ERR_NONE;
    }
    return error_flag;
}

static err_t nfc4_rfal_transceive_blocking_tx( nfc4_t *ctx, uint8_t* tx_buf, uint16_t tx_buf_len, uint8_t* rx_buf, 
                                               uint16_t rx_buf_len, uint16_t* act_len, uint32_t flags, uint32_t fwt )
{
    err_t                          error_flag;
    nfc4_rfal_transceive_context_t ctx_tx;
    
    NFC4_RFAL_CREATE_BYTE_FLAGS_TX_RX_CONTEXT( ctx_tx, tx_buf, tx_buf_len, rx_buf, rx_buf_len, act_len, flags, fwt );
    EXIT_ON_ERR( error_flag, nfc4_rfal_start_transceive( ctx, &ctx_tx ) );
    
    return nfc4_rfal_transceive_run_blocking_tx( ctx );
}

static err_t nfc4_rfal_transceive_blocking_rx( nfc4_t *ctx )
{
    err_t error_flag;
    do
    {
        error_flag = nfc4_rfal_worker( ctx );
    }
    while ( nfc4_rfal_is_transceive_in_rx ( ctx ) && ( NFC4_RFAL_ERR_BUSY == error_flag ) );    
        
    return error_flag;
}

static err_t nfc4_rfal_transceive_blocking_tx_rx( nfc4_t *ctx, uint8_t* tx_buf, uint16_t tx_buf_len, uint8_t* rx_buf, 
                                                  uint16_t rx_buf_len, uint16_t* act_len, uint32_t flags, uint32_t fwt )
{
    err_t error_flag;
    
    EXIT_ON_ERR( error_flag, nfc4_rfal_transceive_blocking_tx( ctx, tx_buf, tx_buf_len, rx_buf, rx_buf_len, act_len, flags, fwt ) );
    error_flag = nfc4_rfal_transceive_blocking_rx( ctx );
    
    /* Convert received bits to bytes */
    if ( NULL != act_len )
    {
        *act_len = NFC4_RFAL_CONV_BITS_TO_BYTES( *act_len );
    }
    return error_flag;
}

static err_t nfc4_rfal_worker( nfc4_t *ctx )
{
    /* Run Tx or Rx state machines */
    if ( nfc4_rfal_is_transceive_in_tx ( ctx ) )
    {
        nfc4_rfal_transceive_tx( ctx );
    }
    if ( nfc4_rfal_is_transceive_in_rx ( ctx ) )
    {
        nfc4_rfal_transceive_rx( ctx );
    }
    
    return ( ( NFC4_TXRX_STATE_IDLE == ctx->rfal.tx_rx.state ) ? ctx->rfal.tx_rx.status : NFC4_RFAL_ERR_BUSY );
}

static void nfc4_rfal_nfc_worker( nfc4_t *ctx )
{
    err_t error_flag;
   
    nfc4_rfal_worker( ctx ); /* Execute RFAL process  */

    switch ( ctx->nfc_dev.state )
    {   
        case NFC4_NFC_STATE_START_DISCOVERY:
        {
            /* Initialize context for discovery cycle. */
            ctx->nfc_dev.dev_cnt      = 0;
            ctx->nfc_dev.sel_dev_idx  = 0;
            ctx->nfc_dev.state        = NFC4_NFC_STATE_POLL_COLAVOIDANCE;
            break;
        }    
        case NFC4_NFC_STATE_POLL_COLAVOIDANCE:                 
        {   
            /* Resolve any eventual collision. */
            error_flag = nfc4_rfal_nfc_poll_coll_resolution( ctx );                       
            /* Wait until all technologies are performed. */
            if ( NFC4_RFAL_ERR_BUSY != error_flag )                                                     
            {
                /* Check if any error occurred or no devices were found. */
                if ( ( NFC4_RFAL_ERR_NONE != error_flag ) || ( 0U == ctx->nfc_dev.dev_cnt ) )                     
                {
                    /* Unable to retrieve any device, restart loop. */
                    ctx->nfc_dev.state = NFC4_NFC_STATE_START_DISCOVERY;
                    break;                                                            
                }
                
                /* If only one device or no callback has been set, activate the first device found. */
                ctx->nfc_dev.sel_dev_idx = 0U;
                ctx->nfc_dev.state = NFC4_NFC_STATE_POLL_ACTIVATION;
            }
            break;
        }
        case NFC4_NFC_STATE_POLL_ACTIVATION:
        {
            error_flag = nfc4_rfal_nfc_poll_activation( ctx, ctx->nfc_dev.sel_dev_idx );
            if ( NFC4_RFAL_ERR_BUSY != error_flag )                   /* Wait until all Activation is complete */
            {
                if ( NFC4_RFAL_ERR_NONE != error_flag )               /* Activation failed selected device */
                {
                    ctx->nfc_dev.state = NFC4_NFC_STATE_DEACTIVATION; /* If Activation failed, restart loop */
                    break;
                }

                ctx->nfc_dev.state = NFC4_NFC_STATE_ACTIVATED;        /* Device has been properly activated */
            }
            break;
        }    
        default:
        {
            return;
        }
    }
}

static void nfc4_initialize_analog_config( nfc4_t *ctx, const uint8_t *an_cfg_settings )
{
    ctx->an_cfg_mgmt.analog_config_table      = an_cfg_settings;
    ctx->an_cfg_mgmt.analog_config_table_size = sizeof ( an_cfg_settings );
    ctx->an_cfg_mgmt.ready = true;
} 

static err_t nfc4_set_analog_config( nfc4_t *ctx, uint16_t config_id )
{
    err_t error_flag = 0;
    uint16_t config_offset = 0;
    uint8_t num_config_set;
    nfc4_analog_config_reg_addr_mask_val_t *config_table;

    if ( true != ctx->an_cfg_mgmt.ready )
    {
        return NFC4_ERROR;
    }
    
    /* Search LUT for the specific Configuration ID. */
    for ( ; ; )
    {
        num_config_set = nfc4_analog_config_search ( ctx, config_id, &config_offset );
        if ( NFC4_ANALOG_CONFIG_LUT_NOT_FOUND == num_config_set )
        {
            break;
        }
        
        config_table = ( nfc4_analog_config_reg_addr_mask_val_t * )( ( uint32_t ) ctx->an_cfg_mgmt.analog_config_table + 
                                                                     ( uint32_t ) config_offset ); 
        /* Increment the offset to the next index to search from. */
        config_offset += ( uint16_t )( num_config_set * sizeof ( nfc4_analog_config_reg_addr_mask_val_t ) ); 
        
        if ( ( ctx->an_cfg_mgmt.analog_config_table_size + 1 ) < config_offset )
        {   
            /* Error check make sure that the we do not access outside the configuration Table Size */
            return NFC4_ERROR;
        }
        
        for ( uint8_t cnt = 0; cnt < num_config_set; cnt++ )
        {
            if ( GETU16 ( config_table[ cnt ].addr ) & NFC4_TEST_REG_INDICATOR )
            {
                error_flag |= nfc4_modify_test_register_bits( ctx, GETU16 ( config_table[ cnt ].addr ) & ~NFC4_TEST_REG_INDICATOR, 
                                                                   config_table[cnt].mask, 
                                                                   config_table[cnt].val);
            }
            else
            {
                error_flag |= nfc4_modify_register_bits( ctx, GETU16 ( config_table[ cnt ].addr ), 
                                                              config_table[ cnt ].mask, 
                                                              config_table[ cnt ].mask & config_table[ cnt ].val );
            }
        }
    } /* while -> found Analog Config Id */
    
    return error_flag;
}

static uint8_t nfc4_analog_config_search ( nfc4_t *ctx, uint16_t config_id, uint16_t *config_offset )
{
    const uint8_t *config_table;
    const uint8_t *current_config_table;
    
    current_config_table = ctx->an_cfg_mgmt.analog_config_table;
    
    for ( uint16_t cnt = *config_offset; cnt < ctx->an_cfg_mgmt.analog_config_table_size; )
    {
        config_table = &current_config_table[ cnt ];
        if ( config_id == GETU16 ( config_table ) )
        {
            *config_offset = ( uint16_t )( cnt + 3 );
            return config_table[ 2 ];
        }
        
        /* If Config Id does not match, increment to next Configuration Id */
        cnt += ( uint16_t )( 3 + ( config_table[ 2 ] * sizeof ( nfc4_analog_config_reg_addr_mask_val_t ) ) );
    }
    
    return NFC4_ANALOG_CONFIG_LUT_NOT_FOUND;
}

static err_t nfc4_i2c_write ( nfc4_t *ctx, uint8_t reg, uint8_t *data_in, uint16_t len ) 
{
    uint8_t tx_buf[ NFC4_FIFO_DEPTH + 1 ] = { 0 };

    if ( NFC4_CMD_TEST_ACCESS == reg )
    {
        tx_buf[ 0 ] = reg;
        
        for ( uint16_t cnt = 0; cnt < len; cnt++ ) 
        {
            tx_buf[ cnt + 1 ] = data_in[ cnt ];
        }
        return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
    }
    else if ( NFC4_MODE_DIRECT_COMMAND == ( reg & NFC4_MODE_DIRECT_COMMAND ) )
    {
        tx_buf[ 0 ] = reg | NFC4_MODE_DIRECT_COMMAND;
        return i2c_master_write( &ctx->i2c, tx_buf, 1 );
    }
    else if ( reg & NFC4_REG_SPACE_B_MASK )
    {
        tx_buf[ 0 ] = NFC4_CMD_SPACE_B_ACCESS;
        tx_buf[ 1 ] = reg & ~NFC4_REG_SPACE_B_MASK;
        
        for ( uint16_t cnt = 0; cnt < len; cnt++ ) 
        {
            tx_buf[ cnt + 2 ] = data_in[ cnt ];
        }
        return i2c_master_write( &ctx->i2c, tx_buf, len + 2 );
    }
    else
    {
        tx_buf[ 0 ] = reg;
        
        for ( uint16_t cnt = 0; cnt < len; cnt++ ) 
        {
            tx_buf[ cnt + 1 ] = data_in[ cnt ];
        }
        return i2c_master_write( &ctx->i2c, tx_buf, len + 1 );
    }
}

static err_t nfc4_i2c_read ( nfc4_t *ctx, uint8_t reg, uint8_t *data_out, uint16_t len ) 
{
    uint8_t tx_buf[ 2 ] = { 0 };
    
    if ( NFC4_CMD_TEST_ACCESS == reg )
    {
        tx_buf[ 0 ] = reg;
        tx_buf[ 1 ] = data_out[ 0 ] | NFC4_MODE_REG_READ;
        return i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, data_out, len );
    }
    else if ( reg & NFC4_REG_SPACE_B_MASK )
    {
        tx_buf[ 0 ] = NFC4_CMD_SPACE_B_ACCESS;
        tx_buf[ 1 ] = ( reg & ~NFC4_REG_SPACE_B_MASK ) | NFC4_MODE_REG_READ;
        return i2c_master_write_then_read( &ctx->i2c, tx_buf, 2, data_out, len );
    }
    else if ( ( NFC4_MODE_PT_MEM_READ != reg ) && 
              ( NFC4_MODE_FIFO_READ != reg ) )
    {
        tx_buf[ 0 ] = reg | NFC4_MODE_REG_READ;
        return i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, data_out, len );
    }
    else
    {
        tx_buf[ 0 ] = reg;
        return i2c_master_write_then_read( &ctx->i2c, tx_buf, 1, data_out, len );
    }
}

static err_t nfc4_spi_write ( nfc4_t *ctx, uint8_t reg, uint8_t *data_in, uint16_t len ) 
{
    uint8_t tx_buf[ NFC4_FIFO_DEPTH + 1 ] = { 0 };
    err_t error_flag = NFC4_ERROR;

    spi_master_select_device( ctx->chip_select );
    
    if ( NFC4_CMD_TEST_ACCESS == reg )
    {
        tx_buf[ 0 ] = reg;
        
        for ( uint16_t cnt = 0; cnt < len; cnt++ ) 
        {
            tx_buf[ cnt + 1 ] = data_in[ cnt ];
        }
        error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    }
    else if ( NFC4_MODE_DIRECT_COMMAND == ( reg & NFC4_MODE_DIRECT_COMMAND ) )
    {
        tx_buf[ 0 ] = reg | NFC4_MODE_DIRECT_COMMAND;
        
        error_flag = spi_master_write( &ctx->spi, tx_buf, 1 );
    }
    else if ( reg & NFC4_REG_SPACE_B_MASK )
    {
        tx_buf[ 0 ] = NFC4_CMD_SPACE_B_ACCESS;
        tx_buf[ 1 ] = reg & ~NFC4_REG_SPACE_B_MASK;
        
        for ( uint16_t cnt = 0; cnt < len; cnt++ ) 
        {
            tx_buf[ cnt + 2 ] = data_in[ cnt ];
        }
        error_flag = spi_master_write( &ctx->spi, tx_buf, len + 2 );
    }
    else
    {
        tx_buf[ 0 ] = reg;
        
        for ( uint16_t cnt = 0; cnt < len; cnt++ ) 
        {
            tx_buf[ cnt + 1 ] = data_in[ cnt ];
        }
        error_flag = spi_master_write( &ctx->spi, tx_buf, len + 1 );
    }
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

static err_t nfc4_spi_read ( nfc4_t *ctx, uint8_t reg, uint8_t *data_out, uint16_t len ) 
{
    uint8_t tx_buf[ 2 ] = { 0 };
    err_t error_flag = NFC4_ERROR;
    
    spi_master_select_device( ctx->chip_select );
    
    if ( NFC4_CMD_TEST_ACCESS == reg )
    {
        tx_buf[ 0 ] = reg;
        tx_buf[ 1 ] = data_out[ 0 ] | NFC4_MODE_REG_READ;
        error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 2, data_out, len );
    }
    else if ( reg & NFC4_REG_SPACE_B_MASK )
    {
        tx_buf[ 0 ] = NFC4_CMD_SPACE_B_ACCESS;
        tx_buf[ 1 ] = ( reg & ~NFC4_REG_SPACE_B_MASK ) | NFC4_MODE_REG_READ;
        error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 2, data_out, len );
    }
    else if ( ( NFC4_MODE_PT_MEM_READ != reg ) && 
              ( NFC4_MODE_FIFO_READ != reg ) )
    {
        tx_buf[ 0 ] = reg | NFC4_MODE_REG_READ;
        error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_out, len );
    }
    else
    {
        tx_buf[ 0 ] = reg;
        error_flag = spi_master_write_then_read( &ctx->spi, tx_buf, 1, data_out, len );
    }
    spi_master_deselect_device( ctx->chip_select );

    return error_flag;
}

// ------------------------------------------------------------------------ END
