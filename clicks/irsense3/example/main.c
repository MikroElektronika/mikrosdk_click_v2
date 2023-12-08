/*!
 * \file 
 * \brief IrSense3 Click example
 * 
 * # Description
 * Demo application shows detection of human and reading of 
 * other parameters such as IR current ..
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configuring clicks and log objects.
 * Software reset and settings the click in the default configuration.
 * 
 * ## Application Task  
 * Reads temperature data, outputs current of IR Sensor and checks for human approach.
 * 
 * \author Katarina Perendic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "irsense3.h"

// ------------------------------------------------------------------ VARIABLES

static irsense3_t irsense3;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    irsense3_cfg_t cfg;

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

    irsense3_cfg_setup( &cfg );
    IRSENSE3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    irsense3_init( &irsense3, &cfg );

    // Software reset

    log_info( &logger, "---- Software reset ----" );
    irsense3_software_reset( &irsense3 );
    Delay_ms( 1000 );

    // Configuration

    log_info( &logger, "---- Default config ----" );
    irsense3_default_cfg( &irsense3 );
}

void application_task ( void )
{
    float temperature;
    float ir_current_data;
    uint8_t f_detect;

    // Detection Object

    f_detect = irsense3_human_approach_detect( &irsense3 );
    if ( f_detect != 0 )
    {
       log_printf( &logger, ">> Human Approach detected !!!\r\n" );
       Delay_ms( 1000 );
    }

    // Output current of IR sensor

    ir_current_data = irsense3_get_ir_sensor_data( &irsense3 );
    log_printf( &logger, ">> IR current data: %.2f pA.\r\n", ir_current_data );

    // Temperature

    temperature = irsense3_get_temperature_data( &irsense3 );
    log_printf( &logger, ">> Temperature: %.2f C.\r\n", temperature );

    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms( 1000 );
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
