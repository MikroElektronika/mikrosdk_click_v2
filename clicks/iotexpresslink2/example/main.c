/*!
 * @file main.c
 * @brief IoT ExpressLink 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of IoT ExpressLink 2 click board by connecting
 * to the selected AWS account's data endpoint and showcasing the messaging topic model
 * through sending and receiving messages to/from AWS IoT console.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger, powers up the device, reads and displays
 * the vendor model, thing name, and the PEM certificate of the device. It then sets
 * the SIM APN and device endpoint, and attempts to connect to AWS network.
 * Finally, it configures the topic name and number and subscribes to it.
 *
 * ## Application Task
 * Sends a desired message on the configured topic and retrieves the next two pending
 * messages from the same topic approximately every 10 seconds. The sent message is also
 * added to the receive queue because the same topic is used for both sending and receiving.
 * 
 * ## Additional Function
 * - static void iotexpresslink2_clear_app_buf ( void )
 * - static err_t iotexpresslink2_process ( iotexpresslink2_t *ctx )
 * - static err_t iotexpresslink2_read_response ( iotexpresslink2_t *ctx, uint32_t timeout )
 *
 * @note
 * Steps for the very first connection attempt:
 *  1. During the initial connection attempt, the device responds with: "ERR14 UNABLE TO CONNECT
 * Certificate generation completed. Proceed to register device with AWS cloud and then try
 * to connect again". 
 *  2. At this point, you should restart the system and proceed with registering the device
 * with the AWS Cloud using device's thing name and PEM certificate displayed in the logger.
 * Detailed steps for registering device are described in the module's application development guide. 
 *  3. After registering the device with your AWS account, restart the system, and it should
 * now successfully connect to the cloud.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "iotexpresslink2.h"

// Enter valid APN below for inserted SIM card
#define SIM_APN                 "internet"

// Enter the device data endpoint below for your AWS account in form:
// xxxxxxxxxxxxxx-ats.iot.us-east-1.amazonaws.com
#define DEVICE_ENDPOINT         ""

// Device topic and text message
#define TOPIC_NUM               "1"
#define TOPIC_NAME              "IoT_ExpressLink_2"
#define TEXT_MESSAGE            "IoT ExpressLink 2 click board - demo message"

// Application buffer size
#define APP_BUFFER_SIZE         900
#define PROCESS_BUFFER_SIZE     100

static iotexpresslink2_t iotexpresslink2;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief IoT ExpressLink 2 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void iotexpresslink2_clear_app_buf ( void );

/**
 * @brief IoT ExpressLink 2 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #iotexpresslink2_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t iotexpresslink2_process ( iotexpresslink2_t *ctx );

/**
 * @brief IoT ExpressLink read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[in] ctx : Click context object.
 * See #iotexpresslink_t object definition for detailed explanation.
 * @param[in] timeout : Timeout for command response in milliseconds.
 * @return @li @c  0 - OK response.
 *         @li @c -1 - Unknown error.
 *         @li @c -2 - Timeout error.
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t iotexpresslink2_read_response ( iotexpresslink2_t *ctx, uint32_t timeout );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    iotexpresslink2_cfg_t iotexpresslink2_cfg;  /**< Click config object. */

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
    iotexpresslink2_cfg_setup( &iotexpresslink2_cfg );
    IOTEXPRESSLINK2_MAP_MIKROBUS( iotexpresslink2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == iotexpresslink2_init( &iotexpresslink2, &iotexpresslink2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_printf( &logger, "Power up device\r\n\n" );
    iotexpresslink2_power_on ( &iotexpresslink2 );

    log_printf( &logger, "Get vendor model\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_CONF_CHECK );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK2_CONF_KEY_ABOUT );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    
    log_printf( &logger, "Get thing name\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_CONF_CHECK );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK2_CONF_KEY_THING_NAME );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    
    log_printf( &logger, "Get certificate pem\r\n" );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_CONF_CHECK );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK2_CONF_KEY_CERTIFICATE_PEM );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    
    log_printf( &logger, "Set SIM APN to: %s\r\n", ( char * ) SIM_APN );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_CONF );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK2_CONF_KEY_APN );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SIGN_EQUAL );
    strcat ( app_buf, SIM_APN );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    
    log_printf( &logger, "Set device endpoint to: %s\r\n", ( char * ) DEVICE_ENDPOINT );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_CONF );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK2_CONF_KEY_ENDPOINT );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SIGN_EQUAL );
    strcat ( app_buf, DEVICE_ENDPOINT );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    
    log_printf( &logger, "Trying to connect...\r\n" );
    log_printf( &logger, "This may take up to 15min for the initial connect.\r\n" );
    iotexpresslink2_send_cmd ( &iotexpresslink2, IOTEXPRESSLINK2_CMD_CONNECT );
    if ( IOTEXPRESSLINK2_OK != 
         iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_CONNECT_TIMEOUT ) )
    {
        log_printf( &logger, "\r\nUNABLE TO CONNECT\r\n" );
        log_printf( &logger, "Make sure that the SIM card is inserted in the board, \r\n" ); 
        log_printf( &logger, "an antenna is connected, and the module is within range \r\n" );
        log_printf( &logger, "of a cellular network that provides LTE-M coverage.\r\n" );
        log_printf( &logger, "Double check that the device registration procedure have been \r\n" );
        log_printf( &logger, "correctly followed. If CONNECT worked in the past for this \r\n" );
        log_printf( &logger, "device, it may be that the cellular network has decided \r\n" );
        log_printf( &logger, "to refuse service for a \"guard time\" (e.g. 1 hour) because \r\n" );
        log_printf( &logger, "the device has connected and disconnected more than a handful \r\n" );
        log_printf( &logger, "of times in quick succession. The only way to avoid this is \r\n" );
        log_printf( &logger, "avoiding many connections/disconnections. \r\n" );
        for ( ; ; );
    }
    
    log_printf( &logger, "Set topic %s to: %s\r\n", ( char * ) TOPIC_NUM, ( char * ) TOPIC_NAME );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_CONF );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SEPARATOR );
    strcat ( app_buf, IOTEXPRESSLINK2_CONF_KEY_TOPIC );
    strcat ( app_buf, TOPIC_NUM );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SIGN_EQUAL );
    strcat ( app_buf, TOPIC_NAME );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    
    log_printf( &logger, "Subscribe to topic %s\r\n", ( char * ) TOPIC_NUM );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_SUBSCRIBE );
    strcat ( app_buf, TOPIC_NUM );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    // Send message on topic
    log_printf( &logger, "Send message on topic: %s\r\n", ( char * ) TOPIC_NAME );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_SEND );
    strcat ( app_buf, TOPIC_NUM );
    strcat ( app_buf, IOTEXPRESSLINK2_CMD_SEPARATOR );
    strcat ( app_buf, TEXT_MESSAGE );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    Delay_ms ( 1000 );
    
    // Retrieve the next message received on topic in the order of arrival.
    log_printf( &logger, "Request next message pending on topic: %s\r\n", ( char * ) TOPIC_NAME );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_GET );
    strcat ( app_buf, TOPIC_NUM );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    Delay_ms ( 1000 );
    
    // Retrieve the next message received on topic in the order of arrival.
    log_printf( &logger, "Request next message pending on topic: %s\r\n", ( char * ) TOPIC_NAME );
    strcpy ( app_buf, IOTEXPRESSLINK2_CMD_GET );
    strcat ( app_buf, TOPIC_NUM );
    iotexpresslink2_send_cmd ( &iotexpresslink2, app_buf );
    iotexpresslink2_read_response ( &iotexpresslink2, IOTEXPRESSLINK2_NORMAL_TIMEOUT );
    // 8 seconds delay
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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

static void iotexpresslink2_clear_app_buf ( void ) 
{
    memset( app_buf, 0, APP_BUFFER_SIZE );
    app_buf_len = 0;
}

static void iotexpresslink2_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t iotexpresslink2_process ( iotexpresslink2_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = iotexpresslink2_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( ( rx_size > 0 ) && ( rx_size <= APP_BUFFER_SIZE ) ) 
    {
        if ( ( app_buf_len + rx_size ) > APP_BUFFER_SIZE ) 
        {
            overflow_bytes = ( app_buf_len + rx_size ) - APP_BUFFER_SIZE;
            app_buf_len = APP_BUFFER_SIZE - rx_size;
            memmove ( app_buf, &app_buf[ overflow_bytes ], app_buf_len );
            memset ( &app_buf[ app_buf_len ], 0, overflow_bytes );
        }
        for ( rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ app_buf_len++ ] = rx_buf[ rx_cnt ];
            }
        }
        return IOTEXPRESSLINK2_OK;
    }
    return IOTEXPRESSLINK2_ERROR;
}

static err_t iotexpresslink2_read_response ( iotexpresslink2_t *ctx, uint32_t timeout ) 
{
    uint32_t timeout_cnt = 0;
    iotexpresslink2_clear_app_buf ( );
    iotexpresslink2_process( ctx );
    while ( ( 0 == strstr( app_buf, IOTEXPRESSLINK2_RSP_OK ) ) &&
            ( 0 == strstr( app_buf, IOTEXPRESSLINK2_RSP_ERR ) ) )
    {
        iotexpresslink2_process( ctx );
        if ( timeout_cnt++ > timeout )
        {
            iotexpresslink2_clear_app_buf( );
            return IOTEXPRESSLINK2_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    Delay_ms ( 100 );
    while ( IOTEXPRESSLINK2_OK == iotexpresslink2_process( ctx ) )
    {
        Delay_ms ( 100 );
    }
    if ( app_buf_len > 0 ) 
    {
        log_printf( &logger, "%s\r\n", app_buf );
    }
    Delay_ms ( 100 );
    if ( strstr( app_buf, IOTEXPRESSLINK2_RSP_OK ) )
    {
        iotexpresslink2_clear_app_buf( );
        return IOTEXPRESSLINK2_OK;
    }
    else if ( strstr( app_buf, IOTEXPRESSLINK2_RSP_ERR ) )
    {
        iotexpresslink2_clear_app_buf( );
        return IOTEXPRESSLINK2_ERROR_CMD;
    }
    iotexpresslink2_clear_app_buf( );
    return IOTEXPRESSLINK2_ERROR;
}

// ------------------------------------------------------------------------ END
