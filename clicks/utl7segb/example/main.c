/*!
 * @file main.c
 * @brief UT-L 7-SEG B Click example
 *
 * # Description
 * This example demonstrates the use of the UT-L 7-SEG B Click board™ 
 * by writing and displaying the desired numbers on the screen.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * The demo application draws numbers, in hexadecimal format, from 0h to FFh on the display.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "utl7segb.h"

static utl7segb_t utl7segb;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    utl7segb_cfg_t utl7segb_cfg;  /**< Click config object. */

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
    utl7segb_cfg_setup( &utl7segb_cfg );
    UTL7SEGB_MAP_MIKROBUS( utl7segb_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == utl7segb_init( &utl7segb, &utl7segb_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UTL7SEGB_ERROR == utl7segb_default_cfg ( &utl7segb ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    for ( uint8_t hex_num = 0x00; hex_num < 0xFF; hex_num++ ) 
    {
        if ( UTL7SEGB_OK == utl7segb_display_number( &utl7segb, 
                                                     UTL7SEGB_BASE_NUM_SYS_HEXADECIMAL, 
                                                     hex_num, 
                                                     UTL7SEGB_NO_DOT ) )
        {
            log_printf( &logger, " --- %.2X ---\r\n", ( uint16_t ) hex_num );
            Delay_ms ( 500 );
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

// ------------------------------------------------------------------------ END
