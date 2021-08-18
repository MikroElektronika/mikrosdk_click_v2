/*!
 * @file main.c
 * @brief Inclinometer Click example
 *
 * # Description
 * This example showcases ability of device to configure it for 
 * resolution and read Axis/Angle/Temperature data.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of the Host communication modules(UART, SPI). 
 * Sets default configuration where powe-up sequence is done with 
 * selecting MODE1 and enabling output on Angle channels. 
 * Read status and checks WhoAmI register. In the end example type
 * is selected( for reading Axes, Angles or Temperature data ).
 *
 * ## Application Task
 * Depending on the example type selected task is reading different data.
 * If EXAMPLE_AXIS selected it reads 3 axes values in range of -1<->1g. 
 * If EXAMPLE_ANGLE is slected it reads 3 angle values in range of 
 * -90<->90deg. EXAMPLE_TEMP reads temperature data from device in degC.
 *
 * @note
 * For Click board to work on ARM boards you need to pull-up MISO line.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "inclinometer.h"

/**
 * @brief Example selector values.
 * @details Enum for selecting example type.
 */
typedef enum
{
    EXAMPLE_AXIS = 1,
    EXAMPLE_ANGLE,
    EXAMPLE_TEMP

} inclinometer_example_t;

static inclinometer_t inclinometer;
static log_t logger;
static inclinometer_example_t example_type;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    inclinometer_cfg_t inclinometer_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.
    inclinometer_cfg_setup( &inclinometer_cfg );
    INCLINOMETER_MAP_MIKROBUS( inclinometer_cfg, MIKROBUS_1 );
    err_t init_flag  = inclinometer_init( &inclinometer, &inclinometer_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    //Powerup
    init_flag = inclinometer_default_cfg ( &inclinometer );
    if ( INCLINOMETER_ERROR == init_flag )
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    example_type = EXAMPLE_AXIS;
    Delay_ms( 1000 );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    switch ( example_type )
    {
        case EXAMPLE_AXIS:
        {
            inclinometer_accel_t axes_data;
            inclinometer_get_axes( &inclinometer, &axes_data );
            log_printf( &logger, "> ACCEL X[g]: %.2f\r\n", axes_data.x );
            log_printf( &logger, "> ACCEL Y[g]: %.2f\r\n", axes_data.y );
            log_printf( &logger, "> ACCEL Z[g]: %.2f\r\n", axes_data.z );
            break;
        }
        case EXAMPLE_ANGLE:
        {
            inclinometer_accel_t angle_data;
            inclinometer_get_angle( &inclinometer, &angle_data );
            log_printf( &logger, "> ANGLE X[deg]: %.2f\r\n", angle_data.x );
            log_printf( &logger, "> ANGLE Y[deg]: %.2f\r\n", angle_data.y );
            log_printf( &logger, "> ANGLE Z[deg]: %.2f\r\n", angle_data.z );
            break;
        }
        case EXAMPLE_TEMP:
        {
            float temp_data = 0;
            inclinometer_get_temperature( &inclinometer, &temp_data );
            log_printf( &logger, "> Temperature[degC]: %.2f\r\n", temp_data );
            break;
        }
        default:
        {
            log_error( &logger, " Example type." );
            break;
        }
    }
    log_printf( &logger, "*************************************\r\n" );
    Delay_ms( 100 );
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
