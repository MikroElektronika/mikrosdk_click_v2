/*!
 * @file main.c
 * @brief DC Motor 28 FNG Click Example.
 *
 * # Description
 * This example demonstrates the use of the DC Motor 28 FNG Click board. It initializes the Click driver, 
 * calibrates the offset for accurate current measurements, and then controls the motor in different states 
 * while measuring and logging the output current in milliamps (mA).
 *
 * The demo application is composed of two sections:
 *
 * ## Application Init
 * Initializes the logger and the DC Motor 28 FNG Click driver and performs offset calibration for current
 * measurements.
 *
 * ## Application Task
 * Controls the motor in a sequence of states: FORWARD, BRAKE, REVERSE, and COAST. In each state, the output 
 * current is measured and logged, providing insights into the motor's performance and consumption.
 *
 * @note
 * Ensure the PMODE switch is set to position 1 (HIGH), the motor is properly connected to the board
 * OUT1 and OUT2 terminals, and the proper power supply is connected to the input terminal.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dcmotor28fng.h"

static dcmotor28fng_t dcmotor28fng;   /**< DC Motor 28 FNG Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dcmotor28fng_cfg_t dcmotor28fng_cfg;  /**< Click config object. */

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
    dcmotor28fng_cfg_setup( &dcmotor28fng_cfg );
    DCMOTOR28FNG_MAP_MIKROBUS( dcmotor28fng_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == dcmotor28fng_init( &dcmotor28fng, &dcmotor28fng_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DCMOTOR28FNG_ERROR == dcmotor28fng_calib_offset ( &dcmotor28fng ) )
    {
        log_error( &logger, " Offset calibration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float current = 0;

    log_printf( &logger, " Motor state : FORWARD\r\n" );
    dcmotor28fng_drive_motor ( &dcmotor28fng, DCMOTOR28FNG_MOTOR_FORWARD );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( DCMOTOR28FNG_OK == dcmotor28fng_get_out_current ( &dcmotor28fng, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }

    log_printf( &logger, " Motor state : BRAKE\r\n" );
    dcmotor28fng_drive_motor ( &dcmotor28fng, DCMOTOR28FNG_MOTOR_BRAKE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( DCMOTOR28FNG_OK == dcmotor28fng_get_out_current ( &dcmotor28fng, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }

    log_printf( &logger, " Motor state : REVERSE\r\n" );
    dcmotor28fng_drive_motor ( &dcmotor28fng, DCMOTOR28FNG_MOTOR_REVERSE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( DCMOTOR28FNG_OK == dcmotor28fng_get_out_current ( &dcmotor28fng, &current ) ) 
    {
        log_printf( &logger, " Current : %.3f mA\r\n\n", current );
    }

    log_printf( &logger, " Motor state : COAST\r\n" );
    dcmotor28fng_drive_motor ( &dcmotor28fng, DCMOTOR28FNG_MOTOR_COAST );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    if ( DCMOTOR28FNG_OK == dcmotor28fng_get_out_current ( &dcmotor28fng, &current ) ) 
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
