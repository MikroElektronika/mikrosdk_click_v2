/*!
 * @file main.c
 * @brief Buck 18 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Buck 18 Click board by changing the output voltage.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * The demo application changes the output voltage and displays the current voltage output value.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "buck18.h"

static buck18_t buck18;   /**< Buck 18 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck18_cfg_t buck18_cfg;  /**< Click config object. */

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
    buck18_cfg_setup( &buck18_cfg );
    BUCK18_MAP_MIKROBUS( buck18_cfg, MIKROBUS_1 );
    err_t init_flag = buck18_init( &buck18, &buck18_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCK18_ERROR == buck18_default_cfg ( &buck18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    for ( buck18_vout_t vout = BUCK18_VOUT_3V3; vout <= BUCK18_VOUT_0V9; vout++ )
    {
        if ( BUCK18_OK == buck18_set_vout( &buck18, vout ) )
        {
            float voltage = 0;
            if ( BUCK18_OK == buck18_read_voltage( &buck18, &voltage ) ) 
            {
                log_printf( &logger, " Voltage : %.3f[V]\r\n\n", voltage );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
                Delay_ms ( 1000 );
            }
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
