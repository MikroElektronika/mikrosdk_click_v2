/*!
 * @file main.c
 * @brief RFID Click example
 *
 * # Description
 * This example demonstrates the use of RFID Click board 
 * by reading MIFARE ISO/IEC 14443 type A tag UID.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, selects the communication interface and performs
 * the click default configuration.
 *
 * ## Application Task
 * If there's a tag detected, it reads its UID and displays it on USB UART.
 *
 * @note
 * It is recommended to tie SSI_0, SSI_1 to VCC/GND at power-up, depending on 
 * the communication interface selection by A and B on-board jumpers. 
 * SSI_0 - UART: 0 SPI: 1
 * SSI_1 - UART: 0 SPI: 0
 * 
 * Only tags with 4-byte or 7-byte UIDs are compatible with this example.
 * We recommend MIKROE-1475 - an RFiD tag 13.56MHz compliant with ISO14443-A standard.
 * 
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "rfid.h"

static rfid_t rfid;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rfid_cfg_t rfid_cfg;  /**< Click config object. */

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
    Delay_ms( 100 );

    // Click initialization.

    rfid_cfg_setup( &rfid_cfg );
    RFID_MAP_MIKROBUS( rfid_cfg, MIKROBUS_1 );
    err_t error_flag = rfid_init( &rfid, &rfid_cfg );
    if ( error_flag != RFID_OK ) 
    {
        log_error( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_printf( &logger, " Selecting communication interface... \r\n" );
    error_flag = rfid_select_communication_interface ( &rfid, RFID_SPI );
    if ( error_flag != RFID_OK ) 
    {
        log_error( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_printf( &logger, " Configuring the device... \r\n" );
    error_flag = rfid_default_cfg ( &rfid );
    if ( error_flag != RFID_OK ) 
    {
        log_error( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    
    log_printf( &logger, " The device has been configured! \r\n" );
}

void application_task ( void ) 
{
    uint8_t tag_uid[ 20 ] = { 0 };
    uint8_t tag_len = rfid_get_tag_uid( &rfid, RFID_ISO_14443A, tag_uid );
    if ( tag_len > 0 )
    {
        log_printf( &logger, " TAG UID: " );
        for ( uint8_t cnt = 0; cnt < tag_len; cnt++ )
        {
            log_printf( &logger, "0x%.2X ", ( uint16_t ) tag_uid[ cnt ] );
        }
        log_printf( &logger, "\r\n----------------------------------\r\n" );
        Delay_ms( 1000 );
    }
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
