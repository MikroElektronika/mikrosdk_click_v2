/*!
 * @file main.c
 * @brief Pressure 19 Click Example.
 *
 * # Description
 * This example demonstrates the use of Pressure 19 click board by reading and 
 * displaying the absolute pressure value in mBar.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads and displays the absolute pressure value [mBar] on the USB UART approximately 
 * once per seconds.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "pressure19.h"

static pressure19_t pressure19;         /**< Pressure 19 Click driver object. */
static log_t logger;                    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    pressure19_cfg_t pressure19_cfg;    /**< Click config object. */

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
    pressure19_cfg_setup( &pressure19_cfg );
    PRESSURE19_MAP_MIKROBUS( pressure19_cfg, MIKROBUS_1 );
    err_t init_flag = pressure19_init( &pressure19, &pressure19_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t pressure;
    if ( PRESSURE19_OK == pressure19_get_pressure ( &pressure19, &pressure ) ) 
    {
        log_printf( &logger, " Pressure : %u mBar\r\n\n", pressure );
        Delay_ms ( 1000 );
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
