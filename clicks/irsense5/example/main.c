/*!
 * @file main.c
 * @brief IR Sense 5 Click Example.
 *
 * # Description
 * This library contains API for the IR Sense 5 Click driver 
 * for measuring ambient and object temperature.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of the I2C and ADC module and log UART.
 *
 * ## Application Task
 * The demo application measures ambient and object temperature in degrees Celsius.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "irsense5.h"

static irsense5_t irsense5;   /**< IR Sense 5 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irsense5_cfg_t irsense5_cfg;  /**< Click config object. */

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
    irsense5_cfg_setup( &irsense5_cfg );
    IRSENSE5_MAP_MIKROBUS( irsense5_cfg, MIKROBUS_1 );
    err_t init_flag = irsense5_init( &irsense5, &irsense5_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature = 0;
    if ( IRSENSE5_OK == irsense5_get_amb_temp ( &irsense5, &temperature ) )
    {
        log_printf( &logger, " Ambient Temperature: %.2f [degC]\r\n", temperature );
        Delay_ms ( 1000 );
    }

    if ( IRSENSE5_OK == irsense5_get_obj_temp ( &irsense5, &temperature ) )
    {
        log_printf( &logger, " Object Temperature:  %.2f [degC]\r\n\n", temperature );
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
