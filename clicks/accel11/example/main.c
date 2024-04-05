/*!
 * \file 
 * \brief Accel11 Click example
 * 
 * # Description
 * This demo application reads X / Y / Z axis acceleration data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device.
 * 
 * ## Application Task  
 * Reads X / Y / Z axis acceleration data and it logs to USBUART every 1500ms.
 * 
 * \author MikroE Team
 *
 */

// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "accel11.h"

// ------------------------------------------------------------------ VARIABLES

static accel11_t accel11;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    uint8_t tmp;
    log_cfg_t log_cfg;
    accel11_cfg_t cfg;

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

    accel11_cfg_setup( &cfg );
    ACCEL11_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel11_init( &accel11, &cfg );

    tmp = accel11_test_comunication( &accel11 );
    if ( tmp == ACCEL11_TEST_COMUNICATION_OK )
    {
        log_printf( &logger, " Comunication OK !!!\r\n" );
    }
    else
    {
        log_printf( &logger, " Comunication ERROR !!!\r\n" );
        for ( ; ; );
    }
    accel11_default_cfg( &accel11 );
}

void application_task ( void )
{
    int16_t x_axis;
    int16_t y_axis;
    int16_t z_axis;

    x_axis = accel11_get_axis_data( &accel11, ACCEL11_ACCEL_X_AXIS );
    log_printf( &logger, " X axis : %d\r\n", x_axis );

    y_axis = accel11_get_axis_data( &accel11, ACCEL11_ACCEL_Y_AXIS );
    log_printf( &logger, " Y axis : %d\r\n", y_axis );

    z_axis = accel11_get_axis_data( &accel11, ACCEL11_ACCEL_Z_AXIS );
    log_printf( &logger, " Z axis : %d\r\n", z_axis );

    log_printf( &logger, "---------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 500 );
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
