/*!
 * @file main.c
 * @brief Smart Card 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of Smart Card 2 click board by checking
 * the SIM card presence and activating the card on insert. The card should respond
 * with an ATR (Answer to Reset) message.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the device.
 *
 * ## Application Task
 * Reads and parses all CCID messages received from the device. Checks the SIM card presence
 * and activates it if it's inserted. The card should respond with an ATR (Answer to Reset) message.
 * All data is being logged on the USB UART where you can track their changes.
 * 
 * @note
 * This example doesn't parse ATR messages.
 * There are some online ATR parsers which could be used for decoding those messages.
 * For example: https://smartcard-atr.apdu.fr/
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "smartcard2.h"

static smartcard2_t smartcard2;
static log_t logger;
static uint8_t icc_status = SMARTCARD2_ICC_ABSENT;

/**
 * @brief Smart Card 2 display ccid message function.
 * @details This function parses the CCID message and updates the icc_status in the end.
 * The results will be displayed on the USB UART.
 * @param[in] ccid : CCID message to be parsed.
 * See #smartcard2_ccid_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
static void smartcard2_display_ccid_message ( smartcard2_ccid_t ccid );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartcard2_cfg_t smartcard2_cfg;  /**< Click config object. */

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
    smartcard2_cfg_setup( &smartcard2_cfg );
    SMARTCARD2_MAP_MIKROBUS( smartcard2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == smartcard2_init( &smartcard2, &smartcard2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    smartcard2_ccid_t ccid = { 0 };
    if ( SMARTCARD2_OK == smartcard2_read_ccid ( &smartcard2, &ccid ) )
    {
        smartcard2_display_ccid_message ( ccid );
    }
    if ( SMARTCARD2_ICC_PRESENT == icc_status )
    {
        log_printf( &logger, " Activating card... \r\n" );
        smartcard2_icc_power_on ( &smartcard2, SMARTCARD2_POWER_SEL_3V );
        Delay_ms ( 100 );
    }
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void smartcard2_display_ccid_message ( smartcard2_ccid_t ccid )
{
    log_printf( &logger, "---------------------------------\r\n" );
    switch ( ccid.type )
    {
        case SMARTCARD2_EVT_NOTIFY_SLOT_CHANGE:
        {
            log_printf( &logger, " Message type: Slot change\r\n" );
            if ( SMARTCARD2_CARD_ABSENT == ccid.payload[ 0 ] )
            {
                icc_status = SMARTCARD2_ICC_ABSENT;
            }
            else if ( SMARTCARD2_CARD_PRESENT == ccid.payload[ 0 ] )
            {
                icc_status = SMARTCARD2_ICC_PRESENT;
            }
            break;
        }
        case SMARTCARD2_CTRL_NACK:
        {
            log_printf( &logger, " Message type: NACK\r\n" );
            log_printf( &logger, " Command not acknowledged\r\n" );
            break;
        }
        case SMARTCARD2_RSP_SLOT_STATUS:
        {
            log_printf( &logger, " Message type: Slot status\r\n" );
            log_printf( &logger, " Slot number: 0x%.2X\r\n", ( uint16_t ) ccid.slot_num );
            log_printf( &logger, " Seq number: 0x%.2X\r\n", ( uint16_t ) ccid.seq_num );
            log_printf( &logger, " Status: 0x%.2X\r\n", ( uint16_t ) ccid.spec_bytes[ 0 ] );
            icc_status = ccid.spec_bytes[ 0 ] & SMARTCARD2_ICC_STATUS_MASK;
            log_printf( &logger, " Error: 0x%.2X\r\n", ( uint16_t ) ccid.spec_bytes[ 1 ] );
            log_printf( &logger, " Clock status: " );
            switch ( ccid.spec_bytes[ 2 ] )
            {
                case SMARTCARD2_CLK_STATUS_RUNNING:
                {
                    log_printf( &logger, "Running\r\n" );
                    break;
                }
                case SMARTCARD2_CLK_STATUS_STATE_L:
                {
                    log_printf( &logger, "Stoped in state L\r\n" );
                    break;
                }
                case SMARTCARD2_CLK_STATUS_STATE_H:
                {
                    log_printf( &logger, "Stoped in state H\r\n" );
                    break;
                }
                default:
                {
                    log_printf( &logger, "Unknown\r\n" );
                    break;
                }
            }
            break;
        }
        case SMARTCARD2_RSP_DATA_BLOCK:
        {
            log_printf( &logger, " Message type: Data Block\r\n" );
            log_printf( &logger, " Payload size: %lu\r\n", ccid.payload_size );
            log_printf( &logger, " Slot number: 0x%.2X\r\n", ( uint16_t ) ccid.slot_num );
            log_printf( &logger, " Seq number: 0x%.2X\r\n", ( uint16_t ) ccid.seq_num );
            log_printf( &logger, " Status: 0x%.2X\r\n", ( uint16_t ) ccid.spec_bytes[ 0 ] );
            icc_status = ccid.spec_bytes[ 0 ] & SMARTCARD2_ICC_STATUS_MASK;
            log_printf( &logger, " Error: 0x%.2X\r\n", ( uint16_t ) ccid.spec_bytes[ 1 ] );
            log_printf( &logger, " Chain parameter: 0x%.2X\r\n", ( uint16_t ) ccid.spec_bytes[ 2 ] );
            if ( ccid.payload_size )
            {
                log_printf( &logger, " Payload (ATR data as response to power on):\r\n" );
                for ( uint32_t cnt = 0; cnt < ccid.payload_size; cnt++ )
                {
                    log_printf( &logger, " %.2X", ( uint16_t ) ccid.payload[ cnt ] );
                }
                log_printf( &logger, "\r\n" );
            }
            break;
        }
        default:
        {
            log_printf( &logger, " Message type: 0x%.2X\r\n", ( uint16_t ) ccid.type );
            log_printf( &logger, " Payload size: %lu\r\n", ccid.payload_size );
            log_printf( &logger, " Slot number: 0x%.2X\r\n", ( uint16_t ) ccid.slot_num );
            log_printf( &logger, " Seq number: 0x%.2X\r\n", ( uint16_t ) ccid.seq_num );
            log_printf( &logger, " Spec bytes: 0x%.2X, 0x%.2X, 0x%.2X\r\n", ( uint16_t ) ccid.spec_bytes[ 0 ], 
                                                                            ( uint16_t ) ccid.spec_bytes[ 1 ], 
                                                                            ( uint16_t ) ccid.spec_bytes[ 2 ] );
            if ( ccid.payload_size )
            {
                log_printf( &logger, " Payload:\r\n" );
                for ( uint32_t cnt = 0; cnt < ccid.payload_size; cnt++ )
                {
                    log_printf( &logger, " 0x%.2X", ( uint16_t ) ccid.payload[ cnt ] );
                    if ( 7 == cnt % 8 )
                    {
                        log_printf( &logger, "\r\n" );
                    }
                }
                log_printf( &logger, "\r\n" );
            }
            break;
        }
    }
    if ( SMARTCARD2_ICC_ABSENT == icc_status )
    {
        log_printf( &logger, " ICC status: ABSENT\r\n" );
    }
    else if ( SMARTCARD2_ICC_PRESENT == icc_status )
    {
        log_printf( &logger, " ICC status: PRESENT\r\n" );
    }
    else if ( SMARTCARD2_ICC_ACTIVE == icc_status )
    {
        log_printf( &logger, " ICC status: ACTIVE\r\n" );
    }
    log_printf( &logger, "---------------------------------\r\n\n" );
}

// ------------------------------------------------------------------------ END
