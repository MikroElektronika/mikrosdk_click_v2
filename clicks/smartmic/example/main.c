/*!
 * @file main.c
 * @brief SmartMic Click example
 *
 * # Description
 * This example demonstrates the use of Smart Mic Click board by programming 
 * it with 4 different keywords, and then waiting for a keyword event, 
 * parsing it and displaying on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration 
 * which programs the device with system config, firmware, and 4 keywords 
 * ("Hello VoiceQ","Switch The Light","Next Song","Baidu Yixia") binaries.
 *
 * ## Application Task
 * Waits for a keyword event, parses it and displays on the USB UART 
 * an appropriate message for the detected keyword.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "smartmic.h"

static smartmic_t smartmic;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartmic_cfg_t smartmic_cfg;  /**< Click config object. */

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
    smartmic_cfg_setup( &smartmic_cfg );
    SMARTMIC_MAP_MIKROBUS( smartmic_cfg, MIKROBUS_1 );
    if ( SMARTMIC_OK != smartmic_init( &smartmic, &smartmic_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Configuring device... \r\n" );
    
    if ( SMARTMIC_OK != smartmic_default_cfg ( &smartmic ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    switch ( smartmic_wait_keyword ( &smartmic ) )
    {
        case SMARTMIC_OEM1_KWD_DETECTED:
        {
            log_printf ( &logger, " Hello VoiceQ keyword detected!\r\n" );
            break;
        }
        case SMARTMIC_OEM2_KWD_DETECTED:
        {
            log_printf ( &logger, " Switch The Light keyword detected!\r\n" );
            break;
        }
        case SMARTMIC_OEM3_KWD_DETECTED:
        {
            log_printf ( &logger, " Next Song keyword detected!\r\n" );
            break;
        }
        case SMARTMIC_OEM4_KWD_DETECTED:
        {
            log_printf ( &logger, " Baidu YiXia keyword detected!\r\n" );
            break;
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
