/*!
 * \file 
 * \brief Current3 Click example
 * 
 * # Description
 * Current 3 Click can be used to measure current ranging up to 8000mA, and display temperature, 
 * voltage and current data - using I2C comunication.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C,
 * check communication and set sense sampling configuration, also write log.
 * 
 * ## Application Task  
 * This is an example which demonstrates the use of Current 3  Click board.
 * Current 3 Click board can be used to measure current ranging
 * up to 8000mA, and display temperature, voltage and current data.
 * All data logs write on USB uart changes for every 2 sec.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "current3.h"

// ------------------------------------------------------------------ VARIABLES

static current3_t current3;
static log_t logger;
static current3_sense_cfg_data_t sense_cfg_data;

static float temperature;
static float voltage;
static float current;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    current3_cfg_t cfg;
    uint8_t read_data;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 115200;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    current3_cfg_setup( &cfg );
    CURRENT3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    current3_init( &current3, &cfg );

    Delay_ms( 100 );
    log_printf( &logger, "     Driver init. done     \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
    
    current3_generic_read( &current3, CURRENT3_REG_PRODUCT_ID, &read_data, 1 );
    if ( read_data == CURRENT3_DEV_ID )
    {
        log_printf( &logger, "     Communication OK      \r\n" );
        log_printf( &logger, "---------------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "    Communication ERROR    \r\n" );
        log_printf( &logger, "     Reset the device      \r\n" );
        log_printf( &logger, "---------------------------\r\n" );
        for ( ; ; );
    }
    
    current3_default_cfg( &current3, sense_cfg_data );
}

void application_task ( void )
{
    temperature = current3_get_temperature( &current3, CURRENT3_TEMP_INTERNAL_DIODE );
    log_printf( &logger, " Temperature = %.2f C\r\n", temperature );

    voltage = current3_get_source_voltage( &current3 );
    log_printf( &logger, " Voltage     = %.2f V\r\n", voltage );

    current = current3_get_current( &current3 );
    log_printf( &logger, " Current     = %.2f mA\r\n", current );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 2000 );
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
