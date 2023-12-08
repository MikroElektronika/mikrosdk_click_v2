/*!
 * \file 
 * \brief Geomagnetic Click example
 * 
 * # Description
 * This example showcases how to initialize and configure the logger and click modules and
 * measure and display the data later on.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the logger and click modules.
 * 
 * ## Application Task  
 * This function first checks whether the device is ready to start measuring and after that
 * collects and displays data from all three axes every half a second.
 * 
 * *note:* 
 * The Geomagnetic Click needs to initialize the SPI communication module first, because the
 * communication interface selection ( on the click ) is locked on to SPI and we need to write
 * some data to the registers in order to configure the click module.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "geomagnetic.h"

// ------------------------------------------------------------------ VARIABLES

static geomagnetic_t geomagnetic;
static log_t logger;
static geomagnetic_axis_t geomag_axis;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    geomagnetic_cfg_t cfg;

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

    geomagnetic_cfg_setup( &cfg );
    GEOMAGNETIC_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    geomagnetic_init( &geomagnetic, &cfg );
    geomagnetic_default_cfg( &geomagnetic );
}

void application_task ( )
{
    GEOMAGNETIC_RETVAL ready_check;
    uint16_t resolution_hall;

    ready_check = geomagnetic_check_ready( &geomagnetic );

    while ( ready_check != GEOMAG_DATA_READY )
    {
        ready_check = geomagnetic_check_ready( &geomagnetic );
    }

    geomagnetic_read_axis_data( &geomagnetic, &geomag_axis, &resolution_hall );

    log_printf( &logger, "X axis: %d\r\n", geomag_axis.x_axis );
    log_printf( &logger, "Y axis: %d\r\n", geomag_axis.y_axis );
    log_printf( &logger, "Z axis: %d\r\n", geomag_axis.z_axis );
    log_printf( &logger, "---------------------------------\r\n" );

    Delay_ms( 500 );
}

int main ( void ) 
{
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

// ------------------------------------------------------------------------ END
