/*!
 * \file 
 * \brief LR3 Click example
 * 
 * # Description
 * This example reads and processes data from LR 3 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, enables the click board and configures it for the selected mode.
 * 
 * ## Application Task  
 * Depending on the selected mode, it reads all the received data or sends a desired message
 * every 3 seconds. All data is being displayed on the USB UART.
 * 
 * ## Additional Function
 * - indication_handler - Logs results on USB UART when device gets indication status.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lr3.h"
#include "string.h"

// ------------------------------------------------------------------ VARIABLES

#define MASTER
// #define END_NODE

#define TEXT_TO_SEND "MikroE"

static lr3_t lr3;
static lr3_tx_msg_t lr3_tx_msg;
static log_t logger;

static lr3_message_t tmp_msg;

// -------------------------------------------------------- ADDITIONAL FUNCTIONS

static void indication_handler( uint8_t *cmd, uint8_t *pl_size, uint8_t *pl_buffer )
{
    if ( *cmd == LR3_INDICATES_RX_MSG )
    {
        if ( pl_buffer[ 0 ] == 0x00 )
        {
            log_printf( &logger, "Message received!\r\n" );
            int16_t rssi = ( pl_buffer[ 2 ] << 8 ) | pl_buffer[ 1 ];
            log_printf( &logger, "RSSI in dBm: %d\r\n", rssi );
            log_printf( &logger, "Signal-to-Noise Ratio: %u\r\n", ( uint16_t ) pl_buffer[ 3 ] );
            log_printf( &logger, "Source ID: 0x%.2X%.2X%.2X%.2X\r\n", ( uint16_t ) pl_buffer[ 7 ],
                                                                      ( uint16_t ) pl_buffer[ 6 ],
                                                                      ( uint16_t ) pl_buffer[ 5 ],
                                                                      ( uint16_t ) pl_buffer[ 4 ] );
            log_printf( &logger, "Message content: " );
            for ( uint8_t cnt = 8; cnt < *pl_size; cnt++ )
            {
                log_printf( &logger, "%c", ( uint16_t ) pl_buffer[ cnt ] );
            }
            log_printf( &logger, "\r\nChecksum: %u", ( uint16_t ) pl_buffer[ *pl_size ] );
            log_printf( &logger, "\r\n------------------------\r\n" );
        }
        else
        {
            log_printf( &logger, "Error!\r\n" );
        }
    }
    else
    {
        log_printf( &logger, "IND TYPE: 0x%.2X\r\n", ( uint16_t ) *cmd );
        log_printf( &logger, "PAYLOAD : " );
        
        for ( uint8_t cnt = 0; cnt <= *pl_size; cnt++ )
        {
            log_printf( &logger, "0x%.2X ", ( uint16_t ) pl_buffer[ cnt ] );
        }
        log_printf( &logger, "\r\n------------------------\r\n" );
    }
        
}

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    lr3_cfg_t cfg;

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

    lr3_cfg_setup( &cfg );
    LR3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lr3_init( &lr3, &cfg );

    Delay_ms( 100 );
    lr3_set_ind_handler( &lr3, indication_handler );
    lr3_hard_reset( &lr3 );
    lr3_factory_reset( &lr3 );
    Delay_ms( 1000 );
    
#ifdef MASTER
    // Set device as MASTER
    tmp_msg.payload[ 0 ] = 0;

    if( lr3_write_eeprom( &lr3, 0x00, 1, &tmp_msg.payload[ 0 ] ) )
    {
        log_error( &logger, "Setting device as MASTER!\r\n" );
        for( ; ; );
    }
    
    log_printf( &logger, "Device configured as MASTER!\r\n" );
    Delay_ms( 1000 );
    
    // Delete all network table
    if( lr3_delete_all_network_table( &lr3 ) )
    {
        log_error( &logger, "Deleting all paired devices!\r\n" );
        for( ; ; );
    }
    log_printf( &logger, "All paired devices deleted!\r\n" );
    Delay_ms( 1000 );
    
    // Enable pairing
    if( lr3_enable_pairing( &lr3, 1 ) )
    {
        log_error( &logger, "Pairing not enabled!\r\n" );
        for( ; ; );
    }
    log_printf( &logger, "Pairing enabled!\r\n" );
    Delay_ms( 1000 );
#endif

#ifdef END_NODE
    // Set device as END_NODE
    tmp_msg.payload[ 0 ] = 1;
    
    if( lr3_write_eeprom( &lr3, 0x00, 1, &tmp_msg.payload[ 0 ] ) )
    {
        log_error( &logger, "Setting device as END_NODE!\r\n" );
        for( ; ; );
    }
    
    log_printf( &logger, "Device configured as END_NODE!\r\n" );
    Delay_ms( 1000 );
    
    // Send pairing request and displays MASTER ID
    uint8_t master_id[ 4 ] = { 0 };
    do
    {
        lr3_get_pairing_request( &lr3 );
        Delay_ms( 1000 );
    }
    while ( lr3_get_activation_status( &lr3, master_id ) != 1 );
    log_printf( &logger, "Paired to a network!\r\n" );
    log_printf( &logger, "Master ID: 0x%.2X%.2X%.2X%.2X\r\n", ( uint16_t ) master_id[ 3 ],
                                                              ( uint16_t ) master_id[ 2 ],
                                                              ( uint16_t ) master_id[ 1 ],
                                                              ( uint16_t ) master_id[ 0 ] );
    
#endif
}

void application_task ( void )
{
#ifdef END_NODE
    strcpy( tmp_msg.payload, TEXT_TO_SEND );
   
    lr3_tx_msg.data_in = &tmp_msg.payload[ 0 ];
    lr3_tx_msg.n_bytes = strlen( TEXT_TO_SEND );
    lr3_tx_msg.destination_id = LR3_BROADCAST_MESSAGE;
    lr3_tx_msg.option = LR3_UNCONFIRMED_DATA_TX;
    if ( lr3_tx_message( &lr3, &lr3_tx_msg ) == 0 )
    {
        log_printf( &logger, "Message: \"%s\" sent to MASTER...\r\n", ( uint8_t * ) TEXT_TO_SEND );
        log_printf( &logger, "------------------------\r\n" );
    }
    
    Delay_ms( 3000 );
#endif
#ifdef MASTER
    lr3_read_message_process( &lr3 );
#endif
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
