/*!
 * @file main.c
 * @brief BT122-A Click Example.
 *
 * # Description
 * This example demonstrates the use of BT122-A Click board by processing data
 * from a connected BT device.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the Click board.
 *
 * ## Application Task
 * Handles most of the events required for this example, the packages of events not 
 * supported in this example will just be displayed on the USB UART.
 * The event handler will display all messages received from the remote device on
 * the USB UART and echo the same message to the connected device.
 *
 * ## Additional Function
 * - static void bt122a_check_response ( err_t error_flag )
 * - static void bt122a_event_handler ( bt122a_t *ctx )
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test. 
 * A smartphone and the Click board must be paired in order to exchange messages with each other.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "bt122a.h"

// Local device name.
#define DEVICE_NAME     "BT122-A Click"

static bt122a_t bt122a;
static log_t logger;
err_t error_flag = BT122A_OK;

/**
 * @brief BT122A check response function.
 * @details This function checks the error flag and logs OK or FAIL message on USB UART.
 * @param[in] error_flag : Function error flag.
 * @return None.
 * @note None.
 */
static void bt122a_check_response ( err_t error_flag );

/**
 * @brief BT122A event handler function.
 * @details This function handles most of the events required for this example.
 * @param[in] ctx : Click context object.
 * See #bt122a_t object definition for detailed explanation.
 * @return None.
 * @note The Click board must be configured and the remote device must be connected to it.
 */
static void bt122a_event_handler ( bt122a_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bt122a_cfg_t bt122a_cfg;  /**< Click config object. */

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
    bt122a_cfg_setup( &bt122a_cfg );
    BT122A_MAP_MIKROBUS( bt122a_cfg, MIKROBUS_1 );
    if ( UART_ERROR == bt122a_init( &bt122a, &bt122a_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    log_printf( &logger, ">>> Set Local Name to \"%s\"\r\n", ( char * ) DEVICE_NAME );
    error_flag = bt122a_set_local_name ( &bt122a, DEVICE_NAME );
    bt122a_check_response ( error_flag );
    
    log_printf( &logger, ">>> Delete Bondings\r\n" );
    error_flag = bt122a_delete_bondings ( &bt122a );
    bt122a_check_response ( error_flag );
    
    log_printf( &logger, ">>> Set Bondable Mode\r\n" );
    error_flag = bt122a_set_bondable_mode ( &bt122a, BT122A_SM_SET_BONDABLE_ALLOWED );
    bt122a_check_response ( error_flag );
    
    log_printf( &logger, ">>> Set GAP Mode\r\n" );
    error_flag = bt122a_set_gap_mode ( &bt122a, BT122A_GAP_MODE_CONNECTABLE, 
                                                BT122A_GAP_MODE_DISCOVERABLE, 
                                                BT122A_GAP_MODE_NOT_LIMITED );
    bt122a_check_response ( error_flag );
    
    log_printf( &logger, ">>> RFCOMM Start Server\r\n" );
    error_flag = bt122a_rfcomm_start_server ( &bt122a, BT122A_RFCOMM_SERVER_DEF_SDP_ID, 
                                                       BT122A_RFCOMM_SERVER_DEF_STREAM_DEST );
    bt122a_check_response ( error_flag );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    bt122a_event_handler( &bt122a );
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

static void bt122a_check_response ( err_t error_flag )
{
    log_printf( &logger, "<<< %s\r\n\n", ( char * ) 
                ( ( BT122A_OK == error_flag ) ? "OK" : "FAIL" ) );
}

static void bt122a_event_handler ( bt122a_t *ctx )
{
    bt122a_package_t pkg;
    uint8_t byte_cnt = 0;
    
    if ( BT122A_OK != bt122a_read_package ( ctx, &pkg ) ) 
    {
        return;
    }

    if ( BT122A_MSG_TYPE_EVENT != pkg.msg_type )
    {
        log_printf( &logger, "<<< Unknown Message Type: 0x%.2X\r\n\n", ( uint16_t ) pkg.msg_type );
        return;
    }

    switch ( pkg.msg_class )
    {
        case BT122A_MSG_CLASS_ENDPOINT:
        {
            if ( BT122A_MSG_ID_EVT_ENDPOINT_DATA == pkg.msg_id )
            {
                log_printf( &logger, "<<< The endpoint 0x%.2X received data: ", 
                            ( uint16_t ) pkg.payload[ 0 ] );
                for ( byte_cnt = 0; byte_cnt < pkg.payload[ 1 ]; byte_cnt++ )
                {
                    log_printf( &logger, "%c", pkg.payload[ byte_cnt + 2 ] );
                }
                pkg.payload[ pkg.payload[ 1 ] + 2 ] = 0;
                log_printf( &logger, "\r\n>>> Echo back the received message\r\n" );
                error_flag = bt122a_endpoint_send_data ( &bt122a, &pkg.payload[ 0 ], &pkg.payload[ 2 ] );
                bt122a_check_response ( error_flag );
            }
            break;
        }
        case BT122A_MSG_CLASS_CONNECTION:
        {
            if ( BT122A_MSG_ID_EVT_CONNECTION_OPENED == pkg.msg_id )
            {
                log_printf( &logger, "<<< Connection 0x%.2X: OPENED\r\n", ( uint16_t ) pkg.payload[ 7 ]  );
                log_printf( &logger, "    Address of remote device: " );
                log_printf( &logger, "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n", ( uint16_t ) pkg.payload[ 5 ],
                                                                          ( uint16_t ) pkg.payload[ 4 ], 
                                                                          ( uint16_t ) pkg.payload[ 3 ],
                                                                          ( uint16_t ) pkg.payload[ 2 ],
                                                                          ( uint16_t ) pkg.payload[ 1 ],
                                                                          ( uint16_t ) pkg.payload[ 0 ] );
                log_printf( &logger, "    Role of the local device : %s\r\n", ( char * )
                            ( 0 == pkg.payload[ 6 ] ? "Peripheral" : "Central" ) );
                
                log_printf( &logger, "    Bonded : %s\r\n\n", 
                            ( 0xFF == pkg.payload[ 8 ] ) ? "NO" : "YES" );
            }
            else if ( BT122A_MSG_ID_EVT_CONNECTION_CLOSED == pkg.msg_id )
            {
                log_printf( &logger, "<<< Connection 0x%.2X: CLOSED\r\n\n", ( uint16_t ) pkg.payload[ 2 ] );
            }
            break;
        }
        case BT122A_MSG_CLASS_SM:
        {
            if ( BT122A_MSG_ID_EVT_SM_BONDED == pkg.msg_id )
            {
                log_printf( &logger, "<<< Connection 0x%.2X: %s\r\n\n", 
                            ( uint16_t ) pkg.payload[ 0 ], ( char * )
                            ( 0xFF != pkg.payload[ 1 ] ? "BONDED" : "NOT BONDED" ) );
            }
            break;
        }
        case BT122A_MSG_CLASS_RFCOMM:
        {
            if ( BT122A_MSG_ID_EVT_RFCOMM_OPENED == pkg.msg_id )
            {
                log_printf( &logger, "<<< RFCOMM connection 0x%.2X: OPENED\r\n", ( uint16_t ) pkg.payload[ 0 ] );
                log_printf( &logger, "    Address of remote device: " );
                log_printf( &logger, "%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\r\n\n", ( uint16_t ) pkg.payload[ 6 ],
                                                                            ( uint16_t ) pkg.payload[ 5 ], 
                                                                            ( uint16_t ) pkg.payload[ 4 ],
                                                                            ( uint16_t ) pkg.payload[ 3 ],
                                                                            ( uint16_t ) pkg.payload[ 2 ],
                                                                            ( uint16_t ) pkg.payload[ 1 ] );
            }
            else if ( BT122A_MSG_ID_EVT_RFCOMM_MODEM_STATUS == pkg.msg_id )
            {
                log_printf( &logger, "<<< RFCOMM connection 0x%.2X status: 0x%.2X\r\n\n", 
                            ( uint16_t ) pkg.payload[ 0 ], 
                            ( uint16_t ) pkg.payload[ 1 ] );
            }
            break;
        }
        default:
        {
            log_printf( &logger, "<<< Message Type: 0x%.2X\r\n", ( uint16_t ) pkg.msg_type );
            log_printf( &logger, "    Payload len: 0x%.2X\r\n", ( uint16_t ) pkg.payload_len );
            log_printf( &logger, "    Message Class: 0x%.2X\r\n", ( uint16_t ) pkg.msg_class );
            log_printf( &logger, "    Message ID: 0x%.2X\r\n", ( uint16_t ) pkg.msg_id );
            
            if ( pkg.payload_len > 0 )
            {
                log_printf( &logger, "   Payload: " );
                for ( uint8_t cnt = 0; cnt < pkg.payload_len; cnt++ )
                {
                    log_printf( &logger, " 0x%.2X ", ( uint16_t ) pkg.payload[ cnt ] );
                }
                log_printf( &logger, "\r\n\n" );
            }
            break;
        }
    }
}

// ------------------------------------------------------------------------ END
