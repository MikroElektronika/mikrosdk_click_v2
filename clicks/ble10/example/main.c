/*!
 * @file main.c
 * @brief BLE 10 Click Example.
 *
 * # Description
 * This example reads and processes data from BLE 10 clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, then performs a factory reset and sets the local device name.
 *
 * ## Application Task
 * Logs all the received events/responses on the USB UART.
 * Then checks if there's a specific command string (defined by the GET_TEMP_COMMAND macro)
 * received from the GATT Server, and if so, it executes temperature reading command and logs the results.
 *
 * ## Additional Function
 * - static void ble10_clear_app_buf ( void )
 * - static err_t ble10_process ( void )
 * - static err_t bluetooth2_display_rsp ( char *rsp_end )
 *
 * @note
 * We have used the nRF Connect smartphone application for the test.
 * Make sure to configure the GATT Server properly in the nRF Connect application, then you
 * will be able to send a desired command from it, once you connect to the click board.
 * You can use the Sample configuration for GATT Server which comes with the application installation
 * and then send a command via Test Service from the Server.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ble10.h"
#include "conversions.h"
#include "generic_pointer.h"

#define PROCESS_BUFFER_SIZE 200

// Response and Events macros.
#define RSP_TIMEOUT         20000
#define RSP_OK              "OK"
#define RSP_ERROR           "ERROR"
#define EVT_DONE            "DONE"
#define EVT_RESET           "RESET"
#define EVT_GATT_VAL        "GATT_VAL"

// Local device name.
#define DEVICE_NAME         "BLE 10 Click"

// The command string that will execute temperature reading, which is expected to be received
// from the GATT Server of the connected device.
#define GET_TEMP_COMMAND    "get temp"

static ble10_t ble10;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;
static uint8_t connection_flag = 0;
static uint16_t send_cnt = 0;

/**
 * @brief BLE 10 clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void ble10_clear_app_buf ( void );

/**
 * @brief BLE 10 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ble10_process ( void );

/**
 * @brief BLE 10 display response function.
 * @details This function reads data from device until sends @a rsp_end or ERROR message or until
 * it exceeds the timeout value.
 * @param[in] rsp_end : Response/Event ending string [OK, DONE, RESET, GATT_VAL].
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ble10_display_rsp ( char *rsp_end );

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    ble10_cfg_t ble10_cfg;  /**< Click config object. */

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

    ble10_cfg_setup( &ble10_cfg );
    BLE10_MAP_MIKROBUS( ble10_cfg, MIKROBUS_1 );
    err_t init_flag  = ble10_init( &ble10, &ble10_cfg );
    if ( UART_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    ble10_default_cfg ( &ble10 );
    ble10_process( );
    ble10_clear_app_buf( );

    app_buf_len = 0;
    app_buf_cnt = 0;
    log_printf( &logger, " - Factory Reset -\r\n" );
    ble10_factory_reset ( &ble10 );
    ble10_display_rsp ( EVT_RESET );

    log_printf( &logger, " - Set Device Name -\r\n" );
    ble10_set_device_name ( &ble10, DEVICE_NAME );
    ble10_display_rsp ( RSP_OK );

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    ble10_process( );
    if ( app_buf_len > 0 )
    {
        Delay_ms( 100 );
        ble10_process( );
        for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
        {
            log_printf( &logger, "%c", app_buf[ buf_cnt ] );
        }
        if ( strstr( app_buf, EVT_GATT_VAL ) )
        {
            char get_temp_cmd[ ] = GET_TEMP_COMMAND;
            const char * __generic_ptr msg_ptr = strrchr ( app_buf, ',' ) + 1;
            uint8_t msg_len = *( msg_ptr - 2 ) - 48;

            if ( msg_len == strlen ( get_temp_cmd ) )
            {
                char get_temp_hex[ 64 ] = { 0 };
                uint8_t get_temp_hex_chr[ 3 ] = { 0 };
                uint8_t cnt = 0;
                for ( cnt = 0; cnt < strlen ( get_temp_cmd ); cnt++ )
                {
                    uint8_to_hex ( get_temp_cmd[ cnt ], get_temp_hex_chr );
                    strcat ( get_temp_hex, get_temp_hex_chr );
                }

                if ( 0 == memcmp ( get_temp_hex, msg_ptr, strlen ( get_temp_hex ) ) )
                {
                    ble10_clear_app_buf( );
                    log_printf( &logger, " - Get Temperature -\r\n" );
                    ble10_get_temperature ( &ble10 );
                    ble10_display_rsp ( RSP_OK );
                }
            }
        }
        ble10_clear_app_buf( );
    }
    Delay_ms( 1 );
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

static void ble10_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t ble10_process ( void )
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = ble10_generic_read( &ble10, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE )
        {
            ble10_clear_app_buf( );
            return BLE10_ERROR;
        }
        else
        {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }

        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ )
        {
            if ( rx_buff[ rx_cnt ] != 0 )
            {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buff[ rx_cnt ];
            }
            else
            {
                app_buf_len--;
                buf_cnt--;
            }
        }
        return BLE10_OK;
    }
    return BLE10_ERROR;
}

static err_t ble10_display_rsp ( char *rsp_end )
{
    uint32_t timeout = RSP_TIMEOUT;
    while ( timeout-- )
    {
        ble10_process( );
        if ( app_buf_len > 0 )
        {
            for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
            {
                log_printf( &logger, "%c", app_buf[ buf_cnt ] );
            }
            if ( strstr( app_buf, rsp_end ) )
            {
                ble10_clear_app_buf( );
                Delay_ms( 100 );
                ble10_process( );
                for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
                {
                    log_printf( &logger, "%c", app_buf[ buf_cnt ] );
                }
                ble10_clear_app_buf( );
                log_printf( &logger, "--------------------------------\r\n" );
                return BLE10_OK;
            }
            ble10_clear_app_buf( );
        }
        Delay_ms ( 1 );
    }
    return BLE10_ERROR;
}

// ------------------------------------------------------------------------ END
