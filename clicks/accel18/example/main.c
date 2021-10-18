/*!
 * @file main.c
 * @brief Accel18 Click example
 *
 * # Description
 * This example application showcases ability of the device
 * to read axes values on detected interrupt, and check detected
 * motion.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of comunication modules(SPI/I2C, UART) and additional
 * two interrupt pins. Then configures device and sets 8g range and 25
 * data rate, with interrupt enabled.
 *
 * ## Application Task
 * Whenever interrupt is detected checks interrupt status for motion
 * detection, and then reads x, y, and z axes, calculates value and
 * logs result.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "accel18.h"

static accel18_t accel18;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    accel18_cfg_t accel18_cfg;  /**< Click config object. */

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
    accel18_cfg_setup( &accel18_cfg );
    ACCEL18_MAP_MIKROBUS( accel18_cfg, MIKROBUS_1 );
    err_t init_flag  = accel18_init( &accel18, &accel18_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    if ( accel18_default_cfg ( &accel18 ) )
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( !accel18_get_interrupt_1( &accel18 ) )
    {
        //Interrupt detected check
        uint8_t int_flag = 0;
        uint8_t interrupt_state = 0;
        accel18_byte_read( &accel18, ACCEL18_REG_INTERRUPT_STATUS, &interrupt_state );
        if ( interrupt_state & ACCEL18_INT_TILT_EN )
        {
            int_flag++;
            log_printf( &logger, ">Tilt<\t" );
        }
        if ( interrupt_state & ACCEL18_INT_FLIP_EN )
        {
            int_flag++;
            log_printf( &logger, ">Flip<\t" );
        }
        if ( interrupt_state & ACCEL18_INT_SHAKE_EN )
        {
            int_flag++;
            log_printf( &logger, ">Shake<\t" );
        }
        if ( int_flag )
        {
            log_printf( &logger, "\r\n" );
        }

        //Axis read
        accel18_axes_t axes_data;
        accel18_read_axes( &accel18, &axes_data );
        log_printf( &logger, " > X[g]: %.2f\r\n", axes_data.x );
        log_printf( &logger, " > Y[g]: %.2f\r\n", axes_data.y );
        log_printf( &logger, " > Z[g]: %.2f\r\n", axes_data.z );
        log_printf( &logger, "**************************\r\n" );
        Delay_ms( 300 );
    }
}

void main ( void )
{
    application_init( );

    for ( ; ; )
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
