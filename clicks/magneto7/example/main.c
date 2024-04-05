/*!
 * \file 
 * \brief Magneto7 Click example
 * 
 * # Description
 * This demo application reads position of a magnet above the sensor.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device.
 * 
 * ## Application Task  
 * Waits for INT pin to go LOW, gets raw data, converts it to uT and logs results.
 *  
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "magneto7.h"

// ------------------------------------------------------------------ VARIABLES

static magneto7_t magneto7;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto7_cfg_t cfg;
    uint8_t init_status;

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

    magneto7_cfg_setup( &cfg );
    MAGNETO7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto7_init( &magneto7, &cfg );
    Delay_ms ( 300 );

    init_status = magneto7_default_cfg( &magneto7 );
    if ( init_status == 0)
    {
        log_printf( &logger, "> app init done\r\n" );
    }
    else if ( init_status == 1 )
    {
        log_printf( &logger, "> app init fail\r\n" );
        for ( ; ; );
    }
}

void application_task ( void )
{
    uint8_t int_status;
    float converted_data;

    int16_t data_x;
    int16_t data_y;
    int16_t data_z;

    int_status = magneto7_int_get( &magneto7 );
    
    if ( int_status == 0 )
    {
        magneto7_get_data( &magneto7, &data_x, &data_y, &data_z );
        
        converted_data = magneto7_convert_to_ut( &magneto7, data_x, MAGNETO7_SENSOR_RES_14_BIT );
        log_printf( &logger, "> X Axis : %f [uT]\r\n", converted_data );
        
        converted_data = magneto7_convert_to_ut( &magneto7, data_y, MAGNETO7_SENSOR_RES_14_BIT );
        log_printf( &logger, "> Y Axis : %f [uT]\r\n", converted_data );

        converted_data = magneto7_convert_to_ut( &magneto7, data_z, MAGNETO7_SENSOR_RES_14_BIT );
        log_printf( &logger, "> Z Axis : %f [uT]\r\n", converted_data );

        log_printf( &logger, "\r\n" );
        
        Delay_ms ( 300 );
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
