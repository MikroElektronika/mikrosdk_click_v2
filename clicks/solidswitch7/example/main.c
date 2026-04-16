/*!
 * @file main.c
 * @brief SolidSwitch 7 Click Example.
 *
 * # Description
 * This example demonstrates the use of the SolidSwitch 7 Click board by 
 * periodically enabling and disabling the output channel while monitoring 
 * and logging the load current.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the logger and the Click board, enables analog diagnostics 
 * and automatic restart features.
 *
 * ## Application Task
 * Alternately enables and disables the output every few seconds, and logs the 
 * measured current in each state using the USB UART.
 *
 * @note
 * Ensure proper load and supply are connected to observe current change 
 * during output toggling.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "solidswitch7.h"

#ifndef MIKROBUS_POSITION_SOLIDSWITCH7
    #define MIKROBUS_POSITION_SOLIDSWITCH7 MIKROBUS_1
#endif

static solidswitch7_t solidswitch7;   /**< SolidSwitch 7 Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch7_cfg_t solidswitch7_cfg;  /**< Click config object. */

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
    solidswitch7_cfg_setup( &solidswitch7_cfg );
    SOLIDSWITCH7_MAP_MIKROBUS( solidswitch7_cfg, MIKROBUS_POSITION_SOLIDSWITCH7 );
    err_t init_flag = solidswitch7_init( &solidswitch7, &solidswitch7_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    solidswitch7_an_diag_enable ( &solidswitch7 );
    solidswitch7_auto_rst_enable ( &solidswitch7 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float current = 0;
    log_printf( &logger, " Enable VOUT\r\n" );
    solidswitch7_output_enable ( &solidswitch7 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( SOLIDSWITCH7_OK == solidswitch7_read_current ( &solidswitch7, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f A\r\n\n", current );
    }
    Delay_ms ( 1000 );
    log_printf( &logger, " Disable VOUT\r\n" );
    solidswitch7_output_disable ( &solidswitch7 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( SOLIDSWITCH7_OK == solidswitch7_read_current ( &solidswitch7, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f A\r\n\n", current );
    }
    Delay_ms ( 1000 );
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
