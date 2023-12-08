/*!
 * \file 
 * \brief GmrAngle Click example
 * 
 * # Description
 * This is an example which demonstrates the use of GMR Angle Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes GPIO pins, SPI and LOG modules.
 * 
 * ## Application Task  
 * Display angle value in degrees.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB uart changes for every 300 msec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gmrangle.h"

// ------------------------------------------------------------------ VARIABLES

static gmrangle_t gmrangle;
static log_t logger;
static float angle;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gmrangle_cfg_t cfg;

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
    gmrangle_cfg_setup( &cfg );
    GMRANGLE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gmrangle_init( &gmrangle, &cfg );
    
    GMRANGLE_SET_DATA_SAMPLE_EDGE; 
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "   GMR Angle Click\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "        Start\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    angle = gmrangle_calculate_angle( &gmrangle );
    log_printf( &logger, " Angle is %.1f\r\n", angle );
    Delay_ms( 300 );
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
