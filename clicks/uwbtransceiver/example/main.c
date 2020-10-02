/*!
 * \file 
 * \brief UwbTransceiver Click example
 * 
 * # Description
 * UWB Transceiver Click send and recieve data, depending on the selected device mode.
 * Click is communicating via standard SPI protocol.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Mapping GPIO and SPI module, setting device working mode
 * setting device ID and default configuration for selected mode.
 * 
 * ## Application Task  
 * Checks if interrupt occured for previous set mode.
 *      TX mode: Transmit data and then set delay for 2 seconds.
 *      RX mode: Receive data and logs it.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "uwbtransceiver.h"

// ------------------------------------------------------------------ VARIABLES

static uwbtransceiver_t uwbtransceiver;
static log_t logger;

// Device mode setter
static uint8_t dev_mode;

// Transmit buffer
static char data_tx[ 7 ] = "MikroE";

// Transmit length read var
static uint16_t temp_len;

// Recieved data buffer
static char transmit_data[ 512 ];

// Dev_status var
static uint8_t dev_status;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uwbtransceiver_cfg_t cfg;

    uint16_t tag_data;
    uint8_t id_raw[ 4 ];

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    uwbtransceiver_cfg_setup( &cfg );
    UWBTRANSCEIVER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uwbtransceiver_init( &uwbtransceiver, &cfg );

    Delay_ms( 100 );
    uwb_dev_reset( &uwbtransceiver );

    uwbtransceiver.offset = UWB_SUB_NO;                               
    uwb_generic_read( &uwbtransceiver, UWB_REG_DEV_ID, &id_raw[ 0 ], 4 );
                                 
    tag_data = ( id_raw[ 3 ] << 8 ) | id_raw[ 2 ];
    
    if ( UWB_TAG != tag_data )
    {
        log_printf( &logger, " ***** ERROR ***** \r\n" );
        for ( ; ; );
    }
    
    uwb_set_mode( &uwbtransceiver, UWB_MODE_IDLE );
    
    // Chose module working mode RX(receiver)/TX(transmiter)
    dev_mode = UWB_MODE_TX;
    //-----------------------------------------------------
    
    // Setting device mode and interrupt for that mode as well as clearing dev_status reg.
    uwb_set_mode( &uwbtransceiver, dev_mode );
    uwb_int_mask_set( &uwbtransceiver );
    uwb_clear_status( &uwbtransceiver );

    // Setting device address and network ID
    log_printf( &logger, " ******************** \r\n" );
    if ( UWB_MODE_RX == dev_mode )
    {
        uwb_set_dev_adr_n_network_id( &uwbtransceiver, 6, 10 );
        log_printf( &logger, " ***** RECEIVER ***** \r\n" );
    }
    else if ( UWB_MODE_TX == dev_mode )
    {
        uwb_set_dev_adr_n_network_id( &uwbtransceiver, 5, 10 );
        log_printf( &logger, " **** TRANSMITER **** \r\n" );
    }
    log_printf( &logger, " ******************** \r\n" );
    
    Delay_ms( 100 );

    // Setting default configuartion and tuning device for that configuration
    uwb_use_smart_power( &uwbtransceiver, UWB_LOW );
    uwb_frame_check( UWB_LOW );
    uwb_frame_filter( &uwbtransceiver, UWB_LOW );
    uwb_set_transmit_type( &uwbtransceiver, &UWB_TMODE_LONGDATA_RANGE_LOWPOWER[ 0 ] );
    uwb_set_channel( &uwbtransceiver, UWB_CHANNEL_5 );
    uwb_tune_config( &uwbtransceiver );

    Delay_ms( 100 );
    
    if ( UWB_MODE_RX == dev_mode )
    {
        // Setup for first receive
        uwb_set_mode( &uwbtransceiver, UWB_MODE_IDLE );
        uwb_set_bit ( &uwbtransceiver, UWB_REG_SYS_CFG, 29, UWB_HIGH );
        uwb_set_bit ( &uwbtransceiver, UWB_REG_SYS_CFG, 30, UWB_HIGH );
        uwb_set_bit ( &uwbtransceiver, UWB_REG_SYS_CFG, 31, UWB_HIGH );
        uwb_set_mode( &uwbtransceiver, UWB_MODE_RX );
        uwb_clear_status( &uwbtransceiver );
        uwb_start_transceiver( &uwbtransceiver );
    }
    else if ( UWB_MODE_TX == dev_mode )
    {
        // Setup for first transmit
        uwb_set_mode( &uwbtransceiver, UWB_MODE_IDLE );
        uwb_clear_status( &uwbtransceiver );
        uwb_set_transmit( &uwbtransceiver, &data_tx[ 0 ], 6 );
        uwb_set_mode( &uwbtransceiver, UWB_MODE_TX );
        uwb_start_transceiver( &uwbtransceiver );
    }

    log_printf( &logger, " ***** APP TASK ***** \r\n" );
    Delay_ms( 500 );
}

void application_task ( void )
{
    dev_status = uwb_get_qint_pin_status( &uwbtransceiver );

    if ( UWB_MODE_RX == dev_mode )
    {
        if ( dev_status )
        {
            // Reading transtimed data logs it and reseting to receive mode
            uwb_set_mode( &uwbtransceiver, UWB_MODE_IDLE );
            uwb_clear_status( &uwbtransceiver );
            temp_len = uwb_get_transmit_len( &uwbtransceiver );
            uwb_get_transmit( &uwbtransceiver, &transmit_data[ 0 ], temp_len );
            log_printf( &logger, "Received data: %s\r\n", transmit_data );
            log_printf( &logger, " - Receive done - \r\n" );
            uwb_set_mode( &uwbtransceiver, UWB_MODE_RX );
            uwb_start_transceiver( &uwbtransceiver );
        }
    }
    else if ( UWB_MODE_TX == dev_mode )
    {
        if ( dev_status )
        {
            // Transmits data reseting to transmit mode and setts 2sec delay
            log_printf( &logger, " - Transmit done - \r\n" );
            uwb_set_mode( &uwbtransceiver, UWB_MODE_IDLE );
            uwb_clear_status( &uwbtransceiver );
            uwb_set_transmit( &uwbtransceiver, &data_tx[ 0 ], 6 );
            uwb_set_mode( &uwbtransceiver, UWB_MODE_TX );
            uwb_start_transceiver( &uwbtransceiver );
            Delay_ms( 2000 );
        }
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
