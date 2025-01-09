/*!
 * @file main.c
 * @brief NFC 7 I2C Click example
 *
 * # Description
 * This example demonstrates the use of NFC 7 I2C Click board by handling the detection
 * and processing of various NFC technologies and protocols, and ensuring the application
 * can respond to different NFC card types (A,B,F,V).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, performs the Click default configuration and
 * reads the device firmware version.
 *
 * ## Application Task
 * Waits for an NFC device to be discovered, checks if it supports a known NFC technology, 
 * and then handles the device based on its protocol. The application continues processing
 * the device (reading and writing information) and waits until the card is removed.
 * Once the card is removed, the discovery process is restarted to detect a new NFC device.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nfc7i2c.h"

static nfc7i2c_t nfc7i2c;
static log_t logger;

/**
 * @brief NFC 7 I2C handle ISO14443-3A function.
 * @details This function handles discovered ISO14443-3A / Type 2 Tag (T2T) card by performing
 * read/write data to memory block 32.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void nfc7i2c_handle_iso14443_3a ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C handle ISO14443-4 function.
 * @details This function handles discovered ISO14443-4 (ISO-DEP) card by selecting the PPSE
 * (Paypass Payment System Environment) application.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void nfc7i2c_handle_iso14443_4 ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C handle ISO15693 function.
 * @details This function handles discovered ISO15693 card by performing read/write data
 * to memory block 32.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void nfc7i2c_handle_iso15693 ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C handle mifare function.
 * @details This function handles discovered MIFARE card by performing read/write data
 * to memory block 32.
 * @param[in] ctx : Click context object.
 * See #nfc7i2c_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void nfc7i2c_handle_mifare ( nfc7i2c_t *ctx );

/**
 * @brief NFC 7 I2C display card info function.
 * @details This function parses and displays the discovered card info on the USB UART.
 * @param[in] rf_intf : Discovered NFC remote device properties.
 * @return None.
 * @note None.
 */
static void nfc7i2c_display_card_info ( nfc7i2c_rf_intf_t rf_intf );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfc7i2c_cfg_t nfc7i2c_cfg;  /**< Click config object. */

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    nfc7i2c_cfg_setup( &nfc7i2c_cfg );
    NFC7I2C_MAP_MIKROBUS( nfc7i2c_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == nfc7i2c_init( &nfc7i2c, &nfc7i2c_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( NFC7I2C_ERROR == nfc7i2c_default_cfg ( &nfc7i2c ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    log_printf( &logger, " FW version: %.2X.%.2X.%.2X\r\n", 
                ( uint16_t ) nfc7i2c.fw_version[ 0 ], 
                ( uint16_t ) nfc7i2c.fw_version[ 1 ], 
                ( uint16_t ) nfc7i2c.fw_version[ 2 ] );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    nfc7i2c_rf_intf_t rf_intf;
    log_printf( &logger, " WAITING FOR DEVICE DISCOVERY\r\n\n" );
    if ( NFC7I2C_OK == nfc7i2c_wait_discovery ( &nfc7i2c, &rf_intf ) )
    {
        if ( ( NFC7I2C_NCI_RF_TECH_PASSIVE_POLL_NFC_A == rf_intf.mode_tech ) || 
             ( NFC7I2C_NCI_RF_TECH_PASSIVE_POLL_NFC_B == rf_intf.mode_tech ) || 
             ( NFC7I2C_NCI_RF_TECH_PASSIVE_POLL_NFC_F == rf_intf.mode_tech ) || 
             ( NFC7I2C_NCI_RF_TECH_PASSIVE_POLL_15693 == rf_intf.mode_tech ) )
        {
            for ( ; ; )
            {
                nfc7i2c_display_card_info ( rf_intf );

                switch ( rf_intf.protocol )
                {
                    case NFC7I2C_NCI_RF_PROT_T2T:
                    {
                        nfc7i2c_handle_iso14443_3a ( &nfc7i2c );
                        break;
                    }
                    case NFC7I2C_NCI_RF_PROT_ISODEP:
                    {
                        nfc7i2c_handle_iso14443_4 ( &nfc7i2c );
                        break;
                    }
                    case NFC7I2C_NCI_RF_PROT_T5T:
                    {
                        nfc7i2c_handle_iso15693 ( &nfc7i2c );
                        break;
                    }
                    case NFC7I2C_NCI_RF_PROT_MIFARE:
                    {
                        nfc7i2c_handle_mifare ( &nfc7i2c );
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                if ( !rf_intf.more_tags )
                {
                    break;
                }
                nfc7i2c_reader_act_next ( &nfc7i2c, &rf_intf );
            }
            
            nfc7i2c_presence_check ( &nfc7i2c, &rf_intf );
            log_printf ( &logger, " - CARD REMOVED\r\n\n" );

            nfc7i2c_stop_discovery ( &nfc7i2c );
            while ( NFC7I2C_OK != nfc7i2c_start_discovery ( &nfc7i2c ) );
        }
        else
        {
            log_printf ( &logger, " - WRONG DISCOVERY\r\n\n" );
        }
    }
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void nfc7i2c_handle_iso14443_3a ( nfc7i2c_t *ctx )
{
    #define BLK_NB_ISO14443_3A      32
    #define DATA_WRITE_ISO14443_3A  0x11, 0x22, 0x33, 0x44
    uint8_t rd_block[ ] = { NFC7I2C_T2T_CMD_READ, BLK_NB_ISO14443_3A };
    uint8_t wr_block[ ] = { NFC7I2C_T2T_CMD_WRITE, BLK_NB_ISO14443_3A, DATA_WRITE_ISO14443_3A };
    err_t error_flag = NFC7I2C_OK;

    // Read block
    ctx->pkt_data.payload_len = sizeof ( rd_block );
    memcpy ( ctx->pkt_data.payload, rd_block, ctx->pkt_data.payload_len );
    error_flag = nfc7i2c_reader_tag_cmd ( ctx, &ctx->pkt_data );
    if ( ( NFC7I2C_OK != error_flag ) || 
         ( NFC7I2C_NCI_STAT_OK != ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] ) )
    {
        log_printf ( &logger, " Read block %u failed with error %.2X\r\n", 
                     ( uint16_t ) rd_block[ 1 ], 
                     ( uint16_t ) ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] );
        return;
    }
    log_printf ( &logger, " Read block %u: ", ( uint16_t ) rd_block[ 1 ] );
    for ( uint8_t cnt = 0; cnt < 4; cnt++ )
    {
        log_printf( &logger, "%.2X ", ( uint16_t ) ctx->pkt_data.payload[ cnt ] );
    }
    log_printf( &logger, "\r\n" );

    // Write block
    ctx->pkt_data.payload_len = sizeof ( wr_block );
    memcpy ( ctx->pkt_data.payload, wr_block, ctx->pkt_data.payload_len );
    error_flag = nfc7i2c_reader_tag_cmd ( ctx, &ctx->pkt_data );
    if ( ( NFC7I2C_OK != error_flag ) || ( NFC7I2C_T2T_ACK != ctx->pkt_data.payload[ 0 ] ) )
    {
        log_printf ( &logger, " Write block %u failed with error %.2X\r\n", 
                     ( uint16_t ) wr_block[ 1 ], 
                     ( uint16_t ) ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] );
        return;
    }
    log_printf ( &logger, " Block %u written\r\n", ( uint16_t ) wr_block[ 1 ] );
    
    // Read back block
    ctx->pkt_data.payload_len = sizeof ( rd_block );
    memcpy ( ctx->pkt_data.payload, rd_block, ctx->pkt_data.payload_len );
    error_flag = nfc7i2c_reader_tag_cmd ( ctx, &ctx->pkt_data );
    if ( ( NFC7I2C_OK != error_flag ) || 
         ( NFC7I2C_NCI_STAT_OK != ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] ) )
    {
        log_printf ( &logger, " Read block %u failed with error %.2X\r\n", 
                     ( uint16_t ) rd_block[ 1 ], 
                     ( uint16_t ) ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] );
        return;
    }
    log_printf ( &logger, " Read block %u: ", ( uint16_t ) rd_block[ 1 ] );
    for ( uint8_t cnt = 0; cnt < 4; cnt++ )
    {
        log_printf( &logger, "%.2X ", ( uint16_t ) ctx->pkt_data.payload[ cnt ] );
    }
    log_printf( &logger, "\r\n" );
}

static void nfc7i2c_handle_iso14443_4 ( nfc7i2c_t *ctx )
{
    err_t error_flag = NFC7I2C_OK;

    ctx->pkt_data.payload_len = strlen ( NFC7I2C_T4T_PPSE_APDU ) + 6;
    ctx->pkt_data.payload[ 0 ] = NFC7I2C_T4T_CLA_NO_SECURE;
    ctx->pkt_data.payload[ 1 ] = NFC7I2C_T4T_INS_SELECT;
    ctx->pkt_data.payload[ 2 ] = NFC7I2C_T4T_P1_SELECT_BY_NAME;
    ctx->pkt_data.payload[ 3 ] = NFC7I2C_T4T_P2_ONLY_OCCURANCE;
    ctx->pkt_data.payload[ 4 ] = strlen ( NFC7I2C_T4T_PPSE_APDU );
    memcpy ( &ctx->pkt_data.payload[ 5 ], NFC7I2C_T4T_PPSE_APDU, strlen ( NFC7I2C_T4T_PPSE_APDU ) );
    ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] = NFC7I2C_T4T_LE_RSP_MAY_PRESENT;
    error_flag = nfc7i2c_reader_tag_cmd ( ctx, &ctx->pkt_data );
    if ( ( NFC7I2C_OK != error_flag ) || 
         ( NFC7I2C_T4T_RSP_COMPLETE_1 != ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 2 ] ) || 
         ( NFC7I2C_T4T_RSP_COMPLETE_2 != ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] ) )
    {
        log_printf ( &logger, " Select PPSE failed with error %.2X %.2X\r\n", 
                     ( uint16_t ) ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 2 ], 
                     ( uint16_t ) ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] );
        return;
    }
    log_printf ( &logger, " Select PPSE Application succeed\r\n" );
}

static void nfc7i2c_handle_iso15693 ( nfc7i2c_t *ctx )
{
    #define BLK_NB_ISO15693     32
    #define DATA_WRITE_ISO15693 0x11, 0x22, 0x33, 0x44
    uint8_t rd_block[ ] = { NFC7I2C_ISO15693_FLAG_DR_HIGH, NFC7I2C_ISO15693_CMD_READ_SINGLE, BLK_NB_ISO15693 };
    uint8_t wr_block[ ] = { NFC7I2C_ISO15693_FLAG_DR_HIGH, NFC7I2C_ISO15693_CMD_WRITE_SINGLE, 
                            BLK_NB_ISO15693, DATA_WRITE_ISO15693 };
    err_t error_flag = NFC7I2C_OK;

    // Read
    ctx->pkt_data.payload_len = sizeof ( rd_block );
    memcpy ( ctx->pkt_data.payload, rd_block, ctx->pkt_data.payload_len );
    error_flag = nfc7i2c_reader_tag_cmd ( ctx, &ctx->pkt_data );
    if ( ( NFC7I2C_OK != error_flag ) || 
         ( NFC7I2C_ISO15693_RSP_OK != ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] ) )
    {
        log_printf ( &logger, " Read block %u failed with error %.2X\r\n", 
                     ( uint16_t ) rd_block[ 2 ], 
                     ( uint16_t ) ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] );
        return;
    }
    log_printf ( &logger, " Read block %u: ", ( uint16_t ) rd_block[ 2 ] );
    for ( uint8_t cnt = 0; cnt < ( ctx->pkt_data.payload_len - 2 ); cnt++ )
    {
        log_printf( &logger, "%.2X ", ( uint16_t ) ctx->pkt_data.payload[ cnt + 1 ] );
    }
    log_printf( &logger, "\r\n" );

    // Write
    ctx->pkt_data.payload_len = sizeof ( wr_block );
    memcpy ( ctx->pkt_data.payload, wr_block, ctx->pkt_data.payload_len );
    error_flag = nfc7i2c_reader_tag_cmd ( ctx, &ctx->pkt_data );
    if ( ( NFC7I2C_OK != error_flag ) || 
         ( NFC7I2C_ISO15693_RSP_OK != ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] ) )
    {
        log_printf ( &logger, " Write block %u failed with error %.2X\r\n", 
                     ( uint16_t ) wr_block[ 2 ], 
                     ( uint16_t ) ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] );
        return;
    }
    log_printf ( &logger, " Block %u written\r\n", ( uint16_t ) wr_block[ 2 ] );
    
    // Read back
    ctx->pkt_data.payload_len = sizeof ( rd_block );
    memcpy ( ctx->pkt_data.payload, rd_block, ctx->pkt_data.payload_len );
    error_flag = nfc7i2c_reader_tag_cmd ( ctx, &ctx->pkt_data );
    if ( ( NFC7I2C_OK != error_flag ) || 
         ( NFC7I2C_ISO15693_RSP_OK != ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] ) )
    {
        log_printf ( &logger, " Read block %u failed with error %.2X\r\n", 
                     ( uint16_t ) rd_block[ 2 ], 
                     ( uint16_t ) ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] );
        return;
    }
    log_printf ( &logger, " Read block %u: ", ( uint16_t ) rd_block[ 2 ] );
    for ( uint8_t cnt = 0; cnt < ( ctx->pkt_data.payload_len - 2 ); cnt++ )
    {
        log_printf( &logger, "%.2X ", ( uint16_t ) ctx->pkt_data.payload[ cnt + 1 ] );
    }
    log_printf( &logger, "\r\n" );
}

static void nfc7i2c_handle_mifare ( nfc7i2c_t *ctx )
{
    #define BLK_NB_MFC      32 // Do not use first 4 blocks and sector trailer blocks (7, 11, 15, etc)
    #define KEY_MFC         0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF
    #define DATA_WRITE_MFC  0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF
    uint8_t authenticate[ ] = { NFC7I2C_MFC_REQ_AUTHENTICATE, BLK_NB_MFC / 4, NFC7I2C_MFC_KEY_SELECTOR_A_EMB, KEY_MFC };
    uint8_t rd_block[ ] = { NFC7I2C_MFC_REQ_XCHG_DATA, NFC7I2C_MFC_CMD_READ, BLK_NB_MFC };
    uint8_t wr_part1[ ] = { NFC7I2C_MFC_REQ_XCHG_DATA, NFC7I2C_MFC_CMD_WRITE, BLK_NB_MFC };
    uint8_t wr_part2[ ] = { NFC7I2C_MFC_REQ_XCHG_DATA, DATA_WRITE_MFC };
    err_t error_flag = NFC7I2C_OK;

    if ( ( BLK_NB_MFC < 4 ) || ( 3 == ( BLK_NB_MFC % 4 ) ) )
    {
        log_printf ( &logger, " Block %u is a sector trailer block\r\n", ( uint16_t ) BLK_NB_MFC );
        return;
    }
    // Authenticate
    ctx->pkt_data.payload_len = sizeof ( authenticate );
    memcpy ( ctx->pkt_data.payload, authenticate, ctx->pkt_data.payload_len );
    error_flag = nfc7i2c_reader_tag_cmd ( ctx, &ctx->pkt_data );
    if ( ( NFC7I2C_OK != error_flag ) || 
         ( NFC7I2C_NCI_STAT_OK != ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] ) )
    {
        log_printf ( &logger, " Authenticate sector %u failed with error %.2X\r\n", 
                     ( uint16_t ) authenticate[ 1 ], 
                     ( uint16_t ) ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] );
        return;
    }
    log_printf ( &logger, " Authenticate sector %u succeed\r\n", ( uint16_t ) authenticate[ 1 ] );

    // Read block
    ctx->pkt_data.payload_len = sizeof ( rd_block );
    memcpy ( ctx->pkt_data.payload, rd_block, ctx->pkt_data.payload_len );
    error_flag = nfc7i2c_reader_tag_cmd ( ctx, &ctx->pkt_data );
    if ( ( NFC7I2C_OK != error_flag ) || 
         ( NFC7I2C_NCI_STAT_OK != ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] ) )
    {
        log_printf ( &logger, " Read block %u failed with error %.2X\r\n", 
                     ( uint16_t ) rd_block[ 2 ], 
                     ( uint16_t ) ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] );
        return;
    }
    log_printf ( &logger, " Read block %u: ", ( uint16_t ) rd_block[ 2 ] );
    for ( uint8_t cnt = 0; cnt < ( ctx->pkt_data.payload_len - 2 ); cnt++ )
    {
        log_printf( &logger, "%.2X ", ( uint16_t ) ctx->pkt_data.payload[ cnt + 1 ] );
    }
    log_printf( &logger, "\r\n" );

    // Write block
    ctx->pkt_data.payload_len = sizeof ( wr_part1 );
    memcpy ( ctx->pkt_data.payload, wr_part1, ctx->pkt_data.payload_len );
    error_flag = nfc7i2c_reader_tag_cmd ( ctx, &ctx->pkt_data );
    if ( ( NFC7I2C_OK != error_flag ) || ( NFC7I2C_MFC_ACK != ctx->pkt_data.payload[ 1 ] ) )
    {
        log_printf ( &logger, " Write block %u failed with error %.2X\r\n", 
                     ( uint16_t ) wr_part1[ 2 ], 
                     ( uint16_t ) ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] );
        return;
    }
    ctx->pkt_data.payload_len = sizeof ( wr_part2 );
    memcpy ( ctx->pkt_data.payload, wr_part2, ctx->pkt_data.payload_len );
    error_flag = nfc7i2c_reader_tag_cmd ( ctx, &ctx->pkt_data );
    if ( ( NFC7I2C_OK != error_flag ) || ( NFC7I2C_MFC_ACK != ctx->pkt_data.payload[ 1 ] ) )
    {
        log_printf ( &logger, " Write block %u failed with error %.2X\r\n", 
                     ( uint16_t ) wr_part1[ 2 ], 
                     ( uint16_t ) ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] );
        return;
    }
    log_printf ( &logger, " Block %u written\r\n", ( uint16_t ) wr_part1[ 2 ] );
    
    // Read back
    ctx->pkt_data.payload_len = sizeof ( rd_block );
    memcpy ( ctx->pkt_data.payload, rd_block, ctx->pkt_data.payload_len );
    error_flag = nfc7i2c_reader_tag_cmd ( ctx, &ctx->pkt_data );
    if ( ( NFC7I2C_OK != error_flag ) || 
         ( NFC7I2C_NCI_STAT_OK != ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] ) )
    {
        log_printf ( &logger, " Read block %u failed with error %.2X\r\n", 
                     ( uint16_t ) rd_block[ 2 ], 
                     ( uint16_t ) ctx->pkt_data.payload[ ctx->pkt_data.payload_len - 1 ] );
        return;
    }
    log_printf ( &logger, " Read block %u: ", ( uint16_t ) rd_block[ 2 ] );
    for ( uint8_t cnt = 0; cnt < ( ctx->pkt_data.payload_len - 2 ); cnt++ )
    {
        log_printf( &logger, "%.2X ", ( uint16_t ) ctx->pkt_data.payload[ cnt + 1 ] );
    }
    log_printf( &logger, "\r\n" );
}

static void nfc7i2c_display_card_info ( nfc7i2c_rf_intf_t rf_intf )
{
    switch ( rf_intf.protocol )
    {
        case NFC7I2C_NCI_RF_PROT_T1T:
        case NFC7I2C_NCI_RF_PROT_T2T:
        case NFC7I2C_NCI_RF_PROT_T3T:
        case NFC7I2C_NCI_RF_PROT_ISODEP:
        {
            log_printf( &logger, " - POLL MODE: Remote T%uT activated\r\n", ( uint16_t ) rf_intf.protocol );
            break;
        }
        case NFC7I2C_NCI_RF_PROT_T5T:
        {
            log_printf( &logger, " - POLL MODE: Remote ISO15693 card activated\r\n" );
            break;
        }
        case NFC7I2C_NCI_RF_PROT_MIFARE:
        {
            log_printf( &logger, " - POLL MODE: Remote MIFARE card activated\r\n" );
            break;
        }
        default:
        {
            log_printf( &logger, " - POLL MODE: Undetermined target\r\n" );
            return;
        }
    }

    switch ( rf_intf.mode_tech )
    {
        case NFC7I2C_NCI_RF_TECH_PASSIVE_POLL_NFC_A:
        {
            log_printf( &logger, "\tSENS_RES = %.2X %.2X\r\n", 
                        ( uint16_t ) rf_intf.info.nfc_app.sens_res[ 0 ], 
                        ( uint16_t ) rf_intf.info.nfc_app.sens_res[ 1 ] );
            log_printf( &logger, "\tNFCID = " );
            for ( uint8_t cnt = 0; cnt < rf_intf.info.nfc_app.nfc_id_len; cnt++ )
            {
                log_printf( &logger, "%.2X ", ( uint16_t ) rf_intf.info.nfc_app.nfc_id[ cnt ] );
            }
            log_printf( &logger, "\r\n" );
            if ( 0 != rf_intf.info.nfc_app.sel_res_len )
            {
                log_printf( &logger, "\tSEL_RES = %.2X\r\n", ( uint16_t ) rf_intf.info.nfc_app.sens_res[ 0 ] );
            }
            break;
        }
        case NFC7I2C_NCI_RF_TECH_PASSIVE_POLL_NFC_B:
        {
            if ( 0 != rf_intf.info.nfc_bpp.sens_res_len )
            {
                log_printf( &logger, "\tSENS_RES = " );
                for ( uint8_t cnt = 0; cnt < rf_intf.info.nfc_bpp.sens_res_len; cnt++ )
                {
                    log_printf( &logger, "%.2X ", ( uint16_t ) rf_intf.info.nfc_bpp.sens_res[ cnt ] );
                }
                log_printf( &logger, "\r\n" );
            }
            break;
        }
        case NFC7I2C_NCI_RF_TECH_PASSIVE_POLL_NFC_F:
        {
            log_printf( &logger, "\tBitrate = %s\r\n", ( char * ) 
                        ( ( 1 == rf_intf.info.nfc_fpp.bitrate ) ? "212" : "424" ) );
            if ( 0 != rf_intf.info.nfc_fpp.sens_res_len )
            {
                log_printf( &logger, "\tSENS_RES = " );
                for ( uint8_t cnt = 0; cnt < rf_intf.info.nfc_fpp.sens_res_len; cnt++ )
                {
                    log_printf( &logger, "%.2X ", ( uint16_t ) rf_intf.info.nfc_fpp.sens_res[ cnt ] );
                }
                log_printf( &logger, "\r\n" );
            }
            break;
        }
        case NFC7I2C_NCI_RF_TECH_PASSIVE_POLL_15693:
        {
            log_printf( &logger, "\tID = " );
            for ( uint8_t cnt = 0; cnt < sizeof ( rf_intf.info.nfc_vpp.id ); cnt++ )
            {
                log_printf( &logger, "%.2X ", ( uint16_t ) rf_intf.info.nfc_vpp.id[ cnt ] );
            }
            log_printf( &logger, "\r\n" );
            log_printf( &logger, "\tAFI = %.2X\r\n", ( uint16_t ) rf_intf.info.nfc_vpp.afi );
            log_printf( &logger, "\tDSFID = %.2X\r\n", ( uint16_t ) rf_intf.info.nfc_vpp.dsf_id );
            break;
        }
        default:
        {
            break;
        }
    }
}

// ------------------------------------------------------------------------ END
