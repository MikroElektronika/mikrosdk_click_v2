/*!
 * \file 
 * \brief Thermo17 Click example
 * 
 * # Description
 * This demo-app shows local and remote temperature measurement procedure using Thermo 17 click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization of the device and checks ID
 * 
 * ## Application Task  
 * Appliction measures temp value every 1000ms and logs it
 * 
 * \author Luka Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "thermo17.h"

// ------------------------------------------------------------------ VARIABLES

static thermo17_t thermo17;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo17_cfg_t cfg;
    uint8_t id_data;

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

    thermo17_cfg_setup( &cfg );
    THERMO17_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo17_init( &thermo17, &cfg );

    id_data = thermo17_generic_read( &thermo17 ,THERMO17_REG_R_ID );
    
    if ( id_data == THERMO17_DEV_ID )
    {
        log_info( &logger, " - Correct device ID" );
    }
    else
    {
        log_info( &logger, " - Device ID ERROR" );
        for ( ; ; );
    }

    log_info( &logger, " Starting measurement " );
}

void application_task ( void )
{
    float read_data;

    read_data = thermo17_read_temp( &thermo17 ,THERMO17_TEMPERATURE_LOCAL );
    log_printf( &logger, " - LOCAL: : %.2f C\r\n", read_data );

    Delay_ms( 100 );

    read_data = thermo17_read_temp( &thermo17 ,THERMO17_TEMPERATURE_REMOTE );
    log_printf( &logger, " - REMOTE: : %.2f C\r\n", read_data );
    
    Delay_ms( 100 );
    log_printf( &logger, " ******************** \r\n" );
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
