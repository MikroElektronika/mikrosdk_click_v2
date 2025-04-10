/*!
 * @file main.c
 * @brief Micro Pump Click Example.
 *
 * # Description
 * This example demonstrates the use of the Micro Pump Click board. It initializes the Click module, 
 * calibrates the offset for accurate current measurements, and then controls the motor in different states 
 * while measuring and logging the output current in milliamps (mA).
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the Micro Pump Click driver and performs offset calibration.
 *
 * ## Application Task
 * Alternates the motor's operational states between COAST and FORWARD. For each state, it logs the motor's 
 * current consumption.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "micropump.h"

static micropump_t micropump;   /**< Micro Pump Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    micropump_cfg_t micropump_cfg;  /**< Click config object. */

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
    micropump_cfg_setup( &micropump_cfg );
    MICROPUMP_MAP_MIKROBUS( micropump_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == micropump_init( &micropump, &micropump_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MICROPUMP_ERROR == micropump_calib_offset ( &micropump ) )
    {
        log_error( &logger, " Offset calibration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float current = 0;
    log_printf( &logger, " Motor state : COAST\r\n" );
    micropump_drive_motor ( &micropump, MICROPUMP_MOTOR_COAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( MICROPUMP_OK == micropump_get_out_current ( &micropump, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }

    log_printf( &logger, " Motor state : FORWARD\r\n" );
    micropump_drive_motor ( &micropump, MICROPUMP_MOTOR_FORWARD );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( MICROPUMP_OK == micropump_get_out_current ( &micropump, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
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
