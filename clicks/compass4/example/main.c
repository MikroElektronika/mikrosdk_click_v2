/*!
 * \file 
 * \brief Compass4 Click example
 * 
 * # Description
 * This demo application measures magnetic flux data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and resets the module, then checks
 * the communication with the module and sets the module default configuration.
 * 
 * ## Application Task  
 * Reads magnetic flux data and displays the values of X, Y, and Z axis to 
 * the USB UART each second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "compass4.h"

// ------------------------------------------------------------------ VARIABLES

static compass4_t compass4;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    compass4_cfg_t cfg;

    uint8_t device;

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

    compass4_cfg_setup( &cfg );
    COMPASS4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    compass4_init( &compass4, &cfg );

    compass4_hardware_reset( &compass4 );
    Delay_ms ( 500 );
    
    device = compass4_check_device( &compass4 );
    if ( device == 0 )
    {
        log_printf( &logger, ">> Device communication [ OK ] \r\n" );
    }
    else
    {
        log_printf( &logger, ">> Device communication [ ERROR ] \r\n" );
        for ( ; ; );
    }
    
    compass4_configuration ( &compass4, COMPASS4_CTRL1_WM_STEPS_5 | 
                                        COMPASS4_CTRL1_NOISE_ENABLE,
                                        COMPASS4_CTRL2_MODE_CONT_1 | 
                                        COMPASS4_CTRL2_SDR_LOW_NOISE |
                                        COMPASS4_CTRL2_FIFO_ENABLE );
                             
    log_printf( &logger, ">> Start measurement  \r\n" );
}

void application_task ( void )
{
    compass4_flux_t flux;
    uint8_t err;
    
    err = compass4_get_magnetic_flux( &compass4, &flux );
    if ( err != 0 )
    {
        log_printf( &logger, ">> Measurement error  \r\n" );
    }
    else
    {
        log_printf( &logger, ">> Magnetic flux data << \r\n" );
        log_printf( &logger, ">> X: %.2f \r\n", flux.x );
        log_printf( &logger, ">> Y: %.2f \r\n", flux.y );
        log_printf( &logger, ">> Z: %.2f \r\n", flux.z );
    }
    log_printf( &logger, "-----------------------------\r\n" );
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
