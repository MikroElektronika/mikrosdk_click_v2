/*!
 * @file main.c
 * @brief BLE 9 Click example
 *
 * # Description
 * This example demonstrates the use of BLE 9 click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads and processes all incoming data and displays them on the USB UART.
 *
 * ## Additional Function
 * - static void ble9_clear_app_buf ( void )
 * - static err_t ble9_process ( ble9_t *ctx )
 * 
 * <pre>
 * For more information on the chip itself and the firmware on it,
 * please visit the following page:
 *     [1] https://docs.silabs.com/bluetooth/3.1
 *         - Take into condideration that the library itself
 *           is designed to work with GSDK version 3.1.0
 *           If you wish to use a different version of firmware,
 *           take into consideration that some functions might not work.
 * </pre>
 *
 * @author MikroE Team
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "ble9.h"
#include "log.h"

#define PROCESS_BUFFER_SIZE 200

static ble9_t ble9;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief BLE 9 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void ble9_clear_app_buf ( void );

/**
 * @brief BLE 9 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #ble9_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ble9_process ( ble9_t *ctx );

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    ble9_cfg_t cfg;

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
    Delay_ms( 100 );

    //  Click initialization.
    ble9_cfg_setup( &cfg );
    BLE9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ble9_init( &ble9, &cfg );
    Delay_ms( 1000 );

    log_printf( &logger, "Creating advertising point...\n" );
    Delay_ms( 100 );
    ble9_adv_create_id ( &ble9 );

    log_printf( &logger, "Starting module advertising...\n" );
    Delay_ms( 100 );
    ble9_adv_start ( &ble9, BLE9_ADVERTISER_MODE_DISCOVERABLE_GENERAL, 
                     BLE9_ADVERTISER_MODE_CONNECTABLE_SCANNABLE );

    log_printf( &logger, "The module has been configured.\n" );
    Delay_ms( 100 );
}

void application_task ( void )
{
    ble9_process ( &ble9 );
    if ( app_buf_len > 0 ) 
    {
        for ( uint16_t cnt = 0; cnt < app_buf_len; cnt++ )
        {
            log_printf( &logger, "%.2X ", ( uint16_t ) app_buf[ cnt ] );
        }
        ble9_clear_app_buf( );
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

static void ble9_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t ble9_process ( ble9_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    rx_size = ble9_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = app_buf_len;
        if ( ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE ) && ( app_buf_len > 0 ) ) 
        {
            buf_cnt = PROCESS_BUFFER_SIZE - ( ( app_buf_len + rx_size ) - PROCESS_BUFFER_SIZE );
            memmove ( app_buf, &app_buf[ PROCESS_BUFFER_SIZE - buf_cnt ], buf_cnt );
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ buf_cnt++ ] = rx_buf[ rx_cnt ];
                if ( app_buf_len < PROCESS_BUFFER_SIZE )
                {
                    app_buf_len++;
                }
            }
        }
        return BLE9_OK;
    }
    return BLE9_ERROR;
}

// ------------------------------------------------------------------------ END
