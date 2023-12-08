/*!
 * \file main.c
 * \brief Oximeter2 Click example
 * 
 * # Description
 * This application collects data from the sensor, calculates it and then logs
 * the result.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and performs the device configuration which puts Time Slot A
 * and Time Slot B modes to active state.
 * Before the device configuration, the SW reset will be performed, which puts
 * the registers in their initial state.
 * 
 * ## Application Task  
 * Application measures value of oxygen level in human's blood.
 *
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "oximeter2.h"

// ------------------------------------------------------------------ VARIABLES

// Oximeter 2 context instance declaration.
static oximeter2_t oximeter2;

// Logger context instance declaration.
static log_t logger;

// Result storage.
static uint32_t res_slot[ 100 ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void oximeter2_write_res ( uint32_t data_write )
{
    log_printf( &logger, "%u\r\n", data_write );
}

void oximeter2_logs_results( void )
{
    uint8_t final_result;
    
    oximeter2_read_data( &oximeter2, &res_slot[ 0 ] );

    log_printf( &logger, "Average result per photodiode is: \r\n" );
    
    switch ( oximeter2.enabled_channel )
    {
        case OXIMETER2_CH3_CH4_SELECTED:
        {
            log_printf( &logger, "PD3: " );
            oximeter2_write_res( res_slot[ 2 ] );
            log_printf( &logger, "PD4: " );
            oximeter2_write_res( res_slot[ 3 ] );

            final_result = ( res_slot[ 2 ] + res_slot[ 3 ] ) / 1000;
            break;
        }
        case OXIMETER2_ALL_CHANNELS_SELECTED:
        {
            log_printf( &logger, "PD1: " );
            oximeter2_write_res( res_slot[ 0 ] );
            log_printf( &logger, "PD2: " );
            oximeter2_write_res( res_slot[ 1 ] );
            log_printf( &logger, "PD3: " );
            oximeter2_write_res( res_slot[ 2 ] );
            log_printf( &logger, "PD4: " );
            oximeter2_write_res( res_slot[ 3 ]);

            final_result = ( res_slot[ 0 ] + res_slot [ 1 ] + res_slot[ 2 ] + res_slot[ 3 ] ) / 1000;
            break;
        }
        default:
        {
            break;
        }
    }
    
    if (final_result > 100)
    {
        final_result = 100;
    }
    log_printf( &logger, "Average result, in percentage: %u\r\n", ( uint16_t )final_result );
    log_printf( &logger, "-------------------------\r\n" );

    Delay_ms( 300 );
}

void application_init ( void )
{
    log_cfg_t log_cfg;
    oximeter2_cfg_t cfg;
    
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
    oximeter2_cfg_setup( &cfg );
    OXIMETER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    oximeter2_init( &oximeter2, &cfg );
    oximeter2_default_cfg( &oximeter2 );
}

void application_task ( void )
{
    oximeter2_logs_results();
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
