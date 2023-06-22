/*!
 * @file 
 * @brief Thermostat4 Click example
 * 
 * # Description
 * Thermostat 4 Click reads alert on the warm and hot channel, using standard SPI communication.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes Driver init, Relay test and
 * sets hysteresis on the WARM channel ( channel B ), after that starts uploading new data.
 * 
 * ## Application Task  
 * Reads Alert on the WARM and HOT channel.
 * 
 * @note
 * The user has the option of adjusting the hysteresis for channel B via the SPI module 
 * while for channel A it is adjusted via the potentiometer.
 * 
 * @author MikroE Team
 *
 */

#include "board.h"
#include "log.h"
#include "thermostat4.h"

static thermostat4_t thermostat4;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;
    thermostat4_cfg_t thermostat4_cfg;

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
    log_info( &logger, " Application Init " );

    // Click initialization.
    thermostat4_cfg_setup( &thermostat4_cfg );
    THERMOSTAT4_MAP_MIKROBUS( thermostat4_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == thermostat4_init( &thermostat4, &thermostat4_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }

    log_printf( &logger, " RELAY ON\r\n" );
    thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_ON );
    Delay_ms( 1000 );
    log_printf( &logger, " RELAY OFF\r\n" );
    thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_OFF );
    Delay_ms( 500 );
    
    thermostat4_set_warm_hysteresis( &thermostat4, 0 );
    thermostat4_new_cfg_upload( &thermostat4 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    if ( THERMOSTAT4_HOT_ALERT == thermostat4_hot_alert_state( &thermostat4 ) ) 
    {
        log_printf( &logger, " HOT ALERT\r\n" );
        thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_ON );
    } 
    else if ( THERMOSTAT4_WARM_ALERT == thermostat4_warm_alert_state( &thermostat4 ) ) 
    {
        log_printf( &logger, " WARM ALERT\r\n" );
        thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_ON );
    } 
    else 
    { 
        log_printf( &logger, " TEMPERATURE OK\r\n" );
        thermostat4_relay_ctrl( &thermostat4, THERMOSTAT4_RELAY_OFF );
    }  
    Delay_ms( 2000 );
}

void main ( void )
{
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
