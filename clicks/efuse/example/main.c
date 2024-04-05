/*!
 * @file main.c
 * @brief eFuse Click Example.
 *
 * # Description
 * This library contains API for the eFuse Click driver.
 * This demo application shows use of a eFuse Click board™.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of GPIO module and log UART.
 * After driver initialization the app set default settings.
 *
 * ## Application Task
 * This is an example that shows the use of an eFuse Click board™.
 * The Electronic Fuse is an electrical safety device that operates to 
 * provide overcurrent protection of an electrical circuit.
 * The intervention threshold is programmed by the Rs resistor.
 * The device disconnects the load if the power overcomes the pre-set threshold, 
 * for example if Vset = 3.9 kOhm, Vin = 12 V, 
 * the intervention threshold is set approximately to 875 mA.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "efuse.h"

static efuse_t efuse;   /**< eFuse Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void ) 
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    efuse_cfg_t efuse_cfg;  /**< Click config object. */

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

    efuse_cfg_setup( &efuse_cfg );
    EFUSE_MAP_MIKROBUS( efuse_cfg, MIKROBUS_1 );
    if ( efuse_init( &efuse, &efuse_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    efuse_default_cfg ( &efuse );
    Delay_ms ( 100 );
    
    log_printf( &logger, " Disable PWM \r\n" );
    efuse_disable_pwm( &efuse );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "\t Active \r\n" );
    efuse_enable_device( &efuse );
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "\tInactive \r\n" );
    efuse_disable_device( &efuse );
    // 10 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
