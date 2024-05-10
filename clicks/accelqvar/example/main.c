/*!
 * @file main.c
 * @brief AccelQvar Click example
 *
 * # Description
 * This library contains API for the AccelQvar Click driver. 
 * The library initializes and defines the I2C and SPI drivers to write and read data 
 * from registers and the default configuration for reading the accelerator data 
 * and Qvar electrostatic sensor measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C and SPI module and log UART.
 * After driver initialization, the app sets the default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the AccelQvar Click board.
 * Measures and displays acceleration data for the X-axis, Y-axis, and Z-axis [mg] 
 * and detects and displays a touch position and the strength of a touch.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accelqvar.h"

// Qvar sensing - the threshold for touch detection, position and sensitivity
#define ACCELQVAR_THOLD_DETECT_TOUCH    1.0
#define ACCELQVAR_TOUCH_ZERO            0.0
#define ACCELQVAR_THOLD_SENS            1.3

static accelqvar_t accelqvar;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accelqvar_cfg_t accelqvar_cfg;  /**< Click config object. */

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
    accelqvar_cfg_setup( &accelqvar_cfg );
    ACCELQVAR_MAP_MIKROBUS( accelqvar_cfg, MIKROBUS_1 );
    err_t init_flag = accelqvar_init( &accelqvar, &accelqvar_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms ( 100 );

    if ( ACCELQVAR_ERROR == accelqvar_default_cfg ( &accelqvar ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );

    log_info( &logger, " Application Task " );
    log_printf( &logger, "_________________\r\n" );
}

void application_task ( void )
{
    accelqvar_axes_t acc_axis;
    if ( ACCELQVAR_OK == accelqvar_get_axes_data( &accelqvar, &acc_axis ) )
    {
        log_printf( &logger, " Accel X: %.2f mg\r\n", acc_axis.x );
        log_printf( &logger, " Accel Y: %.2f mg\r\n", acc_axis.y );
        log_printf( &logger, " Accel Z: %.2f mg\r\n", acc_axis.z );
        log_printf( &logger, "_________________\r\n" );
    }

    float qvar = 0;
    if ( ACCELQVAR_OK == accelqvar_get_qvar_data( &accelqvar, &qvar ) )
    {
        if ( abs( qvar ) > ACCELQVAR_THOLD_DETECT_TOUCH )
        {
            uint8_t touch_strength = ( uint8_t ) ( abs( qvar ) / ACCELQVAR_THOLD_SENS );
            log_printf( &logger, " Touch position: " );
            if ( qvar < ACCELQVAR_TOUCH_ZERO )
            {
                log_printf( &logger, " Left\r\n" );
            }
            else
            {
                log_printf( &logger, " Right\r\n " );
            }
            log_printf( &logger, " Strength: " );
            while ( touch_strength )
            {
                log_printf( &logger, "|" );
                touch_strength--;
            }
            log_printf( &logger, "\r\n_________________\r\n" );
        }
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
