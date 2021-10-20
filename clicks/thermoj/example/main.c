/*!
 * \file 
 * \brief ThermoJ Click example
 * 
 * # Description
 * This app measured temperature.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization device.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of Thermo J Click board.
 * Measured temperature data from the MCP9600 sensor on Thermo J click board.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermoj.h"

// ------------------------------------------------------------------ VARIABLES

static thermoj_t thermoj;
static log_t logger;
static uint8_t check_data_ready;
static float temperature;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermoj_cfg_t cfg;

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

    thermoj_cfg_setup( &cfg );
    THERMOJ_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermoj_init( &thermoj, &cfg );

    log_printf( &logger, "---------------------------\r\n" );
    log_printf( &logger, "      Thermo J  Click      \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    
    log_printf( &logger, " Set thermocouple type:  J \r\n" );

    thermoj_set_thermocouple_type( &thermoj, THERMOJ_THERMOCOUPLE_TYPE_J );
    Delay_ms( 1000 );

    log_printf( &logger, "---------------------------\r\n" );
}

void application_task ( void )
{
    check_data_ready =  thermoj_check_data_ready( &thermoj );

    if ( check_data_ready )
    {
        temperature = thermoj_get_temperature( &thermoj );

        log_printf( &logger, " Temperature : %.2f Celsius\r\n", temperature );
        log_printf( &logger, "---------------------------\r\n" );

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
