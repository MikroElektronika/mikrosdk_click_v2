/*!
 * \file 
 * \brief c6DofImu10 Click example
 * 
 * # Description
 * This app reads the accelerometer and magnetometer axis data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device and runs a communication test that reads 
 * device id (registry Who_I_AM).
 * 
 * ## Application Task  
 * Reads the accelerometer and magnetometer axis data.
 * And reads temperature values. All data logs on the USBUART.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c6dofimu10.h"

// ------------------------------------------------------------------ VARIABLES

static c6dofimu10_t c6dofimu10;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void app_display_axis_data ( c6dofimu10_axis_t *axis )
{
    log_printf( &logger, "* X: %d \r\n", axis->x );

    log_printf( &logger, "* Y: %d \r\n", axis->y );

    log_printf( &logger, "* Z: %d \r\n", axis->z );

    log_printf( &logger, "------------------------\r\n" );
}

void app_display_temp_data ( float temp )
{
    log_printf( &logger, "* Temperature:  %.2f C\r\n", temp );
    log_printf( &logger, "------------------------\r\n" );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu10_cfg_t cfg;
    uint8_t com_test;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c6dofimu10_cfg_setup( &cfg );
    c6DOFIMU10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu10_init( &c6dofimu10, &cfg );

    // TEST COMMUNICATION
    com_test = c6dofimu10_communication_test( &c6dofimu10 );
    if ( com_test != C6DOFIMU10_DEVICE_OK )
    {
        log_printf( &logger, "-- Device communication ERROR --\r\n" );
        for( ; ; );
    }
    log_printf( &logger, "-- Device communication OK --\r\n" );
    Delay_ms( 2000 );
    
    c6dofimu10_default_cfg ( &c6dofimu10 );
    log_printf( &logger, "-- Device configuration --\r\n" );
    Delay_ms( 500 );
}

void application_task ( void )
{
    c6dofimu10_axis_t accel_axis;
    c6dofimu10_axis_t mag_axis;
    float temperature;

    c6dofimu10_get_accel_axis ( &c6dofimu10, &accel_axis );
    c6dofimu10_get_mag_axis ( &c6dofimu10, &mag_axis );
    temperature = c6dofimu10_get_temperature( &c6dofimu10, C6DOFIMU10_TEMP_FORMAT_CELSIUS );

    log_printf( &logger, "-- Accelerometer axis --\r\n" );
    app_display_axis_data( &accel_axis );

    log_printf( &logger, "-- Magnetometer axis --\r\n" );
    app_display_axis_data( &mag_axis );

    log_printf( &logger, "-- Temperature data --\r\n" );
    app_display_temp_data( temperature );
    log_printf( &logger, "***************************************************************************************\r\n" );
    Delay_ms( 1000 );
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
