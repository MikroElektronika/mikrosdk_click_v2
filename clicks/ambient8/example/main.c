/*!
 * \file 
 * \brief Ambient8 Click example
 * 
 * # Description
 * This application collects data from the sensor, calculates the light intensity 
 * to a diggital format, and then logs it.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes device and I2C driver
 * 
 * ## Application Task  
 * Performs Lux calculation based on window and IR factor and log results.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "ambient8.h"

// ------------------------------------------------------------------ VARIABLES

static ambient8_t ambient8;
static log_t logger;

static uint8_t status_flag;
static float lux_level;
static float window_factor;
static float IR_factor;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient8_cfg_t cfg;

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

    ambient8_cfg_setup( &cfg );
    AMBIENT8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient8_init( &ambient8, &cfg );

    window_factor = 1;
    IR_factor = 0;
}

void application_task ( void )
{
    status_flag = ambient8_get_lux_level( &ambient8, &lux_level, window_factor,
                                          IR_factor );

    if ( status_flag == 0 )
    {
        log_printf( &logger, "Lux level : %.2f lx\r\n", lux_level );
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
