/*!
 * \file 
 * \brief Uwb Click example
 * 
 * # Description
 * UWB Click sends and receive data, depending on the selected device mode.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures the click board for the selected mode.
 * 
 * ## Application Task  
 * Depending on the selected mode, it reads all the received data or sends the desired message
 * every 2 seconds.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "uwb.h"

// ------------------------------------------------------------------ VARIABLES

static uwb_t uwb;
static log_t logger;

// Device mode setter - selects the module working mode RX(receiver)/TX(transmitter)
static uint8_t dev_mode = UWB_MODE_TX;

// Transmit buffers
static uint8_t data_tx_1[ 7 ] = "MikroE";
static uint8_t data_tx_2[ 10 ] = "UWB click";

// Transmit length read var
static uint16_t temp_len = 0;

// Recieved data buffer
static uint8_t transmit_data[ 256 ] = { 0 };

// Dev_status var
static uint8_t dev_status = { 0 };

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    uwb_cfg_t cfg;

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

    // Click initialization.
    uwb_cfg_setup( &cfg );
    UWB_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    uwb_init( &uwb, &cfg );
    Delay_ms( 100 );
    
    uwb_enable ( &uwb );
    Delay_ms( 100 );
    
    uint8_t id_raw[ 4 ] = { 0 };
    uwb.offset = UWB_SUB_NO;                               
    uwb_generic_read( &uwb, UWB_REG_DEV_ID, &id_raw[ 0 ], 4 );
                                 
    uint16_t tag_data = ( ( uint16_t ) id_raw[ 3 ] << 8 ) | id_raw[ 2 ];
    
    if ( UWB_TAG != tag_data )
    {
        log_printf( &logger, " ***** ERROR ***** \r\n" );
        for ( ; ; );
    }
    
    uwb_set_mode( &uwb, UWB_MODE_IDLE );
    
    //-----------------------------------------------------
    
    // Setting device mode and interrupt for that mode as well as clearing dev_status reg.
    uwb_set_mode( &uwb, dev_mode );
    uwb_int_mask_set( &uwb );
    uwb_clear_status( &uwb );

    // Setting device address and network ID
    log_printf( &logger, " ******************** \r\n" );
    if ( UWB_MODE_RX == dev_mode )
    {
        uwb_set_dev_adr_n_network_id( &uwb, 6, 10 );
        log_printf( &logger, " ***** RECEIVER ***** \r\n" );
    }
    else if ( UWB_MODE_TX == dev_mode )
    {
        uwb_set_dev_adr_n_network_id( &uwb, 5, 10 );
        log_printf( &logger, " **** TRANSMITER **** \r\n" );
    }
    log_printf( &logger, " ******************** \r\n" );
    
    Delay_ms( 100 );

    // Setting default configuartion and tuning device for that configuration
    uwb_use_smart_power( &uwb, UWB_LOW );
    uwb_frame_check( UWB_LOW );
    uwb_frame_filter( &uwb, UWB_LOW );
    uwb_set_transmit_type( &uwb, &UWB_TMODE_LONGDATA_RANGE_LOWPOWER[ 0 ] );
    uwb_set_channel( &uwb, UWB_CHANNEL_5 );
    uwb_tune_config( &uwb );

    Delay_ms( 100 );
    
    if ( UWB_MODE_RX == dev_mode )
    {
        // Setup for first receive
        uwb_set_mode( &uwb, UWB_MODE_IDLE );
        uwb_set_bit ( &uwb, UWB_REG_SYS_CFG, 29, UWB_HIGH );
        uwb_set_bit ( &uwb, UWB_REG_SYS_CFG, 30, UWB_HIGH );
        uwb_set_bit ( &uwb, UWB_REG_SYS_CFG, 31, UWB_HIGH );
        uwb_set_mode( &uwb, UWB_MODE_RX );
        uwb_clear_status( &uwb );
        uwb_start_transceiver( &uwb );
    }
    else if ( UWB_MODE_TX == dev_mode )
    {
        // Setup for first transmit
        uwb_set_mode( &uwb, UWB_MODE_IDLE );
        uwb_clear_status( &uwb );
        uwb_set_transmit( &uwb, &data_tx_1[ 0 ], 6 );
        uwb_set_mode( &uwb, UWB_MODE_TX );
        uwb_start_transceiver( &uwb );
        log_printf( &logger, " - Transmit 1 done - \r\n" );
    }

    log_printf( &logger, " ***** APP TASK ***** \r\n" );
    Delay_ms( 2000 );
}

void application_task ( void )
{
    dev_status = uwb_get_qint_pin_status( &uwb );

    if ( UWB_MODE_RX == dev_mode )
    {
        if ( dev_status )
        {
            // Reading transmitted data, logs it and resetting to receive mode
            uwb_set_mode( &uwb, UWB_MODE_IDLE );
            uwb_clear_status( &uwb );
            temp_len = uwb_get_transmit_len( &uwb );
            uwb_get_transmit( &uwb, &transmit_data[ 0 ], temp_len );
            log_printf( &logger, "Received data: %s\r\n", transmit_data );
            log_printf( &logger, " - Receive done - \r\n" );
            uwb_set_mode( &uwb, UWB_MODE_RX );
            uwb_start_transceiver( &uwb );
        }
    }
    else if ( UWB_MODE_TX == dev_mode )
    {
        if ( dev_status )
        {
            // Transmits data, resetting to transmit mode and sets 2sec delay
            uwb_set_mode( &uwb, UWB_MODE_IDLE );
            uwb_clear_status( &uwb );
            uwb_set_transmit( &uwb, &data_tx_2[ 0 ], 9 );
            uwb_set_mode( &uwb, UWB_MODE_TX );
            uwb_start_transceiver( &uwb );
            log_printf( &logger, " - Transmit 2 done - \r\n" );
            Delay_ms( 2000 );
            uwb_set_mode( &uwb, UWB_MODE_IDLE );
            uwb_clear_status( &uwb );
            uwb_set_transmit( &uwb, &data_tx_1[ 0 ], 6 );
            uwb_set_mode( &uwb, UWB_MODE_TX );
            uwb_start_transceiver( &uwb );
            log_printf( &logger, " - Transmit 1 done - \r\n" );
            Delay_ms( 2000 );
        }
    }
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
