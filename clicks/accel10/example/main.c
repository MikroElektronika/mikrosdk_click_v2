/*!
 * \file 
 * \brief Accel10 Click example
 * 
 * # Description
 * This example demonstrates the use of Accel 10 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and checks the communication by reading the device ID.
 * After that, performs the click default configuration.
 * 
 * ## Application Task  
 * Reads the accel values for X, Y, and Z axis and also reads the temperature in Celsius
 * and displays the results on the USB UART each second.
 * 
 * \author Nenad Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "accel10.h"

// ------------------------------------------------------------------ VARIABLES

static accel10_t accel10;
static log_t logger;

static accel10_data_t accel_data;
static int8_t temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel10_cfg_t cfg;

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

    accel10_cfg_setup( &cfg );
    ACCEL10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel10_init( &accel10, &cfg );
    Delay_ms( 500 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "    Accel 10 Click\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    
    // Checking communication
    if ( accel10_check_id( &accel10 ) == ACCEL10_SUCCESS )
    {
        log_printf( &logger, "  Communication  OK\r\n" );
        log_printf( &logger, "---------------------\r\n" );
        Delay_ms( 100 );
    }
    else
    {
        log_printf( &logger, "  Communication ERROR\r\n" );
        log_printf( &logger, "  Reset the device\r\n" );
        log_printf( &logger, "---------------------\r\n" );
        for ( ; ; );
    }
    
    accel10_default_cfg ( &accel10 );
    log_printf( &logger, "  Default config.\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    if ( accel10_check_data_ready( &accel10 ) == ACCEL10_STATUS_DATA_READY )
    {
        accel10_get_data ( &accel10, &accel_data );
        Delay_ms( 10 );
        
        log_printf( &logger, "  Accel X :  %d\r\n", accel_data.x );
        log_printf( &logger, "  Accel Y :  %d\r\n", accel_data.y );
        log_printf( &logger, "  Accel Z :  %d\r\n", accel_data.z );
    
        temperature = accel10_read_temperature( &accel10 );
        Delay_ms( 10 );

        log_printf( &logger, " Temperature :  %d C\r\n", ( int16_t ) temperature );
        log_printf( &logger, "---------------------\r\n" );
        Delay_ms( 1000 );
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
