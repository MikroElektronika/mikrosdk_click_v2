/*!
 * \file 
 * \brief Proximity7 Click example
 * 
 * # Description
 * This application give us lux level and proximiti data.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes I2C driver and writes basic settings to device registers
 * 
 * ## Application Task  
 * Logs lux level and proximity data
 * 
 * *note:* 
 * - When setting LED drive strength please note that if "proximity drive level - PDL" bit in "configuration register" is set to 1, LED drive current values are reduced by 9.
 * - When setting wait time note that if "wait long - WLONG" bit is set to 1, time is 12x longer. Therefore if WLONG == 1 set time between 33ms and 8386.56ms.
 * - When setting ALS gain note that if "ALS gain level - AGL" bit is set to 1, ALS gains are scaled by 0.16, otherwise, they are scaled by 1.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "proximity7.h"

// ------------------------------------------------------------------ VARIABLES


static proximity7_t proximity7;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    proximity7_cfg_t cfg;

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

    proximity7_cfg_setup( &cfg );
    PROXIMITY7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    proximity7_init( &proximity7, &cfg );

    Delay_ms ( 100 );

    proximity7_default_cfg( &proximity7 );

    log_printf( &logger, "> > > Default configuration done < < <\r\n" );
}

void application_task ( void )
{
    uint8_t write_buffer[ 2 ];
    uint8_t read_buffer[ 1 ] ;
    float lux_level;
    uint16_t proximity;
    uint8_t als_valid;
    uint8_t proximity_valid;

    proximity7_generic_read( &proximity7, PROXIMITY7_STATUS | PROXIMITY7_REPEATED_BYTE, &read_buffer[ 0 ], 1 );
    
    als_valid = read_buffer[ 0 ] & PROXIMITY7_ALS_VALID_MASK;
    proximity_valid = read_buffer[ 0 ] & PROXIMITY7_PROXIMITY_VALID_MASK;
    
    if ( ( als_valid != 0 ) && ( proximity_valid != 0 ) )
    {
        log_printf( &logger, " " );

        lux_level = proximity7_get_lux_level( &proximity7 );
        log_printf( &logger, "> > > Lux level   : %f lx\r\n", lux_level );
    
        proximity = proximity7_get_proximity_data( &proximity7 );
        log_printf( &logger, "> > > Proximity   : %d\r\n", proximity );

        write_buffer[ 0 ] = PROXIMITY7_SPECIAL_FUNCTION | PROXIMITY7_PROXIMITY_AND_ALS_INT_PIN_CLEAR;
        proximity7_generic_write( &proximity7, PROXIMITY7_SPECIAL_FUNCTION | PROXIMITY7_PROXIMITY_AND_ALS_INT_PIN_CLEAR, &write_buffer[ 0 ], 1 );
    }
    
    Delay_ms ( 300 );
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
