/*!
 * \file 
 * \brief Buck14 Click example
 * 
 * # Description
 * This app enables usage of high-efficiency step-down converter.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Configure device.
 * 
 * ## Application Task  
 * Sends 4 different commands for VOUT in span of 8sec
 * 
 * *note:* 
 * When you send data you should send LSB first.
 * Device input V should be beetween 4.5 - 14 V.
 * Device output V could be from 0.5 - 5 V deepending from limits you set currently it is set to 1V.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "buck14.h"

// ------------------------------------------------------------------ VARIABLES

static buck14_t buck14;
static log_t logger;

// ------------------------------------------------------- ADDITIONAL FUNCTIONS

void error_handler ( uint8_t stat_data )
{
    if ( stat_data == BUCK14_ERROR )
    {
        log_printf( &logger, "ERROR! \r\n " );
        for ( ; ; );
    }
    else if ( stat_data == BUCK14_ID_ERROR )
    {
        log_printf( &logger, "ID ERROR! \r\n " );
        for ( ; ; );
    }
    else if ( stat_data == BUCK14_CMD_ERROR )
    {
        log_printf( &logger, "CMD ERROR! \r\n " );
    }
}

void read_vout_data ( buck14_t *ctx )
{
    uint16_t temp_data;

    temp_data = buc14_read_vout( &buck14 );
    log_printf( &logger, "VOUT ~ %u mV \r\n", temp_data );
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    buck14_cfg_t cfg;
    uint8_t write_data;
    uint8_t status_data;

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

    buck14_cfg_setup( &cfg );
    BUCK14_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    buck14_init( &buck14, &cfg );

    buck14_reset( &buck14 );

    write_data  = BUCK14_CTRL_ENABLE_NO_MARGIN;
    buck14_generic_write( &buck14, BUCK14_CMD_OPERATION, &write_data , 1 );
    Delay_ms( 300 );

    status_data = buck14_check_mfr_id(  &buck14 );
    error_handler( status_data );
    log_printf( &logger, "-Device ID OK!\r\n" );
    
    buck14_power_ctrl( &buck14, BUCK14_PIN_STATE_HIGH );

    buck14_default_cfg( &buck14 );
    log_printf( &logger, " ***** App init ***** \r\n" );
    log_printf( &logger, "----------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    uint8_t status_data;
    float vout_value;

    vout_value = 1.2;
    status_data = buc14_write_vout( &buck14, vout_value );
    error_handler( status_data );

    if ( status_data == BUCK14_SUCCESSFUL )
    {
        read_vout_data(  &buck14 );
    }
    Delay_ms( 8000 );

    vout_value = 3.7;
    status_data = buc14_write_vout( &buck14, vout_value );
    error_handler( status_data );

    if ( status_data == BUCK14_SUCCESSFUL )
    {
        read_vout_data( &buck14 );
    }

    Delay_ms( 8000 );

    vout_value = 2.5;
    status_data = buc14_write_vout( &buck14, vout_value );
    error_handler( status_data );

    if ( status_data == BUCK14_SUCCESSFUL )
    {
        read_vout_data(  &buck14 );
    }
    
    Delay_ms( 8000 );

    vout_value = 4.5;
    status_data = buc14_write_vout(  &buck14, vout_value );
    error_handler( status_data );

    if ( status_data == BUCK14_SUCCESSFUL )
    {
        read_vout_data(  &buck14 );
    }
    
    Delay_ms( 4000 );
    log_printf( &logger, "```````````````\r\n" );
    Delay_ms( 4000 );
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
