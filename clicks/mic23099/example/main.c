/*!
 * \file 
 * \brief MIC23099 Click example
 * 
 * # Description
 * MIC23099 click represent single AA/AAA cell step-down/step-up regulator 
 * with battery monitoring.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * This example demonstrates the use of MIC23099 Click board by checking 
 * the state of power good pin and sends note via UART Terminal 
 * if the state is low.
 * 
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "mic23099.h"

// ------------------------------------------------------------------ VARIABLES

static mic23099_t mic23099;
static log_t logger;

static uint8_t new_stat;
static uint8_t old_stat;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    mic23099_cfg_t cfg;

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
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Application  Init\r\n" );
    Delay_ms ( 1000 );

    //  Click initialization.

    mic23099_cfg_setup( &cfg );
    MIC23099_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    mic23099_init( &mic23099, &cfg );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " ---- MIC23099 Click ---- \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
    
    mic23099_default_cfg( &mic23099 );
    Delay_ms ( 1000 );
    
    new_stat = MIC23099_DISABLE;
    old_stat = MIC23099_ENABLE;
    
    log_printf( &logger, " -- Initialization done --\r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{  
    new_stat = mic23099_check_power_good( &mic23099 );

    if ( new_stat == MIC23099_ENABLE && old_stat == MIC23099_DISABLE )
    {
        old_stat = MIC23099_ENABLE;
    }

    if ( new_stat == MIC23099_DISABLE && old_stat == MIC23099_ENABLE )
    {
        log_printf( &logger, " Change  battery  and  reset. \r\n" );
        log_printf( &logger, "------------------------------\r\n" );
        old_stat = MIC23099_DISABLE;
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
