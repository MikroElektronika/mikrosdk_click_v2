/*!
 * @file main.c
 * @brief Skywire Click Example.
 *
 * # Description
 * Application example shows device capability of connecting to the network and sending
 * TCP/UDP messages, SMS messages, performing a voice call or reading the GNSS position
 * using standard "AT" commands.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Application task is split in few stages:
 *  - SKYWIRE_POWER_UP:
 * Powers up the device and reads the device identification.
 *
 *  - SKYWIRE_CONFIG_CONNECTION:
 * Sets configuration to device to be able to connect to the network.
 *
 *  - SKYWIRE_CHECK_CONNECTION:
 * Waits for the network registration indicated via CREG command and then checks the signal quality report.
 *
 *  - SKYWIRE_CONFIG_EXAMPLE:
 * Configures device for the selected example.
 *
 *  - SKYWIRE_EXAMPLE:
 * Depending on the selected demo example, it sends a TCP/UDP message, an SMS message,
 * performs a voice call or reads the GNSS position.
 *
 * By default, the TCP/UDP example is selected.
 *
 * ## Additional Function
 * - static void skywire_clear_app_buf ( void )
 * - static void skywire_log_app_buf ( void )
 * - static err_t skywire_process ( skywire_t *ctx )
 * - static err_t skywire_read_response ( skywire_t *ctx, uint8_t *rsp, uint32_t max_rsp_time )
 * - static err_t skywire_power_up ( skywire_t *ctx )
 * - static err_t skywire_config_connection ( skywire_t *ctx )
 * - static err_t skywire_check_connection ( skywire_t *ctx )
 * - static err_t skywire_config_example ( skywire_t *ctx )
 * - static err_t skywire_socket_echo ( skywire_t *ctx, uint8_t *protocol )
 * - static err_t skywire_example ( skywire_t *ctx )
 *
 * @note
 * The example is tested with the NL-SW-HSPA (Telit HE910) Skywire modem and the power on pulse duration
 * and the AT#GPIO, AT#SLED, AT#DIALMODE, socket and GPS commands are specific for this modem.
 * In order for the examples to work, user needs to set the APN of the entered SIM card,
 * as well as the phone number to which he wants to send an SMS or to call.
 * Enter valid values for the following macros: SIM_APN, SIM_APN_USER, SIM_APN_PASSWORD and PHONE_NUMBER.
 * Example:
    SIM_APN "internet"
    PHONE_NUMBER "+381659999999"
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "conversions.h"
#include "skywire.h"

#ifndef MIKROBUS_POSITION_SKYWIRE
    #define MIKROBUS_POSITION_SKYWIRE MIKROBUS_1
#endif

// Example selection macros
#define EXAMPLE_TCP_UDP                     0               // Example of sending messages to a TCP/UDP echo server
#define EXAMPLE_SMS                         1               // Example of sending SMS to a phone number
#define EXAMPLE_VOICE_CALL                  2               // Example of calling a phone number
#define EXAMPLE_GNSS                        3               // Example of reading the GNSS position
#define DEMO_EXAMPLE                        EXAMPLE_TCP_UDP // Example selection macro

// SIM config
#define SIM_APN                             ""              // Set valid SIM APN
#define SIM_APN_USER                        ""              // Set valid SIM APN user name
#define SIM_APN_PASSWORD                    ""              // Set valid SIM APN password
#define SIM_PIN                             ""              // Set valid SIM PIN, leave empty if not used

// SMS and voice call example parameters
#define PHONE_NUMBER                        ""              // Set phone number to message or to call
#define CALL_STATUS_CHECKS                  4               // Call status checks 5 seconds apart before hanging up

// TCP/UDP example parameters
#define REMOTE_IP                           "54.187.244.144"// TCP/UDP echo server IP address
#define REMOTE_PORT                         "51111"         // TCP/UDP echo server port
#define SOCKET_LOCAL_PORT                   "5000"          // UDP local port, has no effect for TCP
#define SOCKET_CONN_ID                      "1"             // Socket connection identifier
#define SOCKET_PROTOCOL_TCP                 "0"             // TCP socket transmission protocol
#define SOCKET_PROTOCOL_UDP                 "1"             // UDP socket transmission protocol

// GNSS example parameters
#define GPS_POWER_UP                        "1"             // GPS controller powered up
#define GPS_FIX_2D                          '2'             // <fix> field value for 2D fix
#define GPS_FIX_3D                          '3'             // <fix> field value for 3D fix
#define GPS_FIX_FIELD_POS                   5               // Number of commas before the <fix> field

// Message content
#define MESSAGE_CONTENT                     "Skywire Click board - demo example."

// Configuration values
#define CMEE_VERBOSE_FORMAT                 "2"             // +CME ERROR reports in verbose format
#define GPIO1_STAT_LED_NOT_SAVED            "1,0,2,0"       // GPIO1 as status LED, not saved in NVM
#define STAT_LED_MODULE_HANDLED             "2"             // Status LED handled by the module software
#define SMS_FORMAT_TEXT                     "1"             // SMS text mode
#define AUTOMATIC_REGISTRATION              "0"             // Automatic network registration
#define CONTEXT_DEACTIVATE                  "1,0"           // PDP context 1 deactivation
#define REG_STATUS_HOME                     '1'             // <stat> field value for the home network
#define REG_STATUS_ROAMING                  '5'             // <stat> field value for roaming

// Number of AT command attempts while waiting for the modem to boot
#define BOOT_CHECK_ATTEMPTS                 5

// Example repeat delay in seconds
#define EXAMPLE_REPEAT_DELAY_SEC            5
#define SMS_REPEAT_DELAY_SEC                30

// Application buffer size
#define APP_BUFFER_SIZE                     500
#define PROCESS_BUFFER_SIZE                 200
#define CMD_PARAM_BUFFER_SIZE               64
#define MSG_LEN_BUFFER_SIZE                 6

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    SKYWIRE_POWER_UP = 1,
    SKYWIRE_CONFIG_CONNECTION,
    SKYWIRE_CHECK_CONNECTION,
    SKYWIRE_CONFIG_EXAMPLE,
    SKYWIRE_EXAMPLE

} skywire_app_state_t;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static uint8_t app_buf[ APP_BUFFER_SIZE + 1 ] = { 0 };
static int32_t app_buf_len = 0;
static skywire_app_state_t app_state = SKYWIRE_POWER_UP;

static skywire_t skywire;
static log_t logger;

/**
 * @brief Skywire clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @return Nothing.
 * @note None.
 */
static void skywire_clear_app_buf ( void );

/**
 * @brief Skywire log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @return Nothing.
 * @note None.
 */
static void skywire_log_app_buf ( void );

/**
 * @brief Skywire data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @param[in] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t skywire_process ( skywire_t *ctx );

/**
 * @brief Skywire read response function.
 * @details This function waits for a response message, reads and displays it on the USB UART.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @param[in] rsp : Expected response.
 * @param[in] max_rsp_time : Maximum response time in milliseconds.
 * @return @li @c  0 - OK response,
 *         @li @c -2 - Timeout error,
 *         @li @c -3 - Command error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t skywire_read_response ( skywire_t *ctx, uint8_t *rsp, uint32_t max_rsp_time );

/**
 * @brief Skywire power up function.
 * @details This function powers up the device and reads the device identification.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @return @li @c    0 - OK,
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t skywire_power_up ( skywire_t *ctx );

/**
 * @brief Skywire config connection function.
 * @details This function configures and enables connection to the specified network.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @return @li @c    0 - OK,
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note The example is stopped if the SIM PIN is required but not set or wrong.
 */
static err_t skywire_config_connection ( skywire_t *ctx );

/**
 * @brief Skywire check connection function.
 * @details This function checks the connection to network.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @return @li @c    0 - OK,
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t skywire_check_connection ( skywire_t *ctx );

/**
 * @brief Skywire config example function.
 * @details This function configures device for the selected example.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @return @li @c    0 - OK,
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t skywire_config_example ( skywire_t *ctx );

/**
 * @brief Skywire socket echo function.
 * @details This function opens a socket to the echo server, sends a message, reads the echoed
 * message and closes the socket.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @param[in] protocol : Socket transmission protocol ("0" - TCP, "1" - UDP).
 * @return @li @c    0 - OK,
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note The PDP context must be activated before calling this function.
 */
static err_t skywire_socket_echo ( skywire_t *ctx, uint8_t *protocol );

/**
 * @brief Skywire example function.
 * @details This function executes the TCP/UDP, SMS, voice call or GNSS example depending on
 * the DEMO_EXAMPLE macro.
 * @param[out] ctx : Click context object.
 * See #skywire_t object definition for detailed explanation.
 * @return @li @c    0 - OK,
 *         @li @c != 0 - Read response error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t skywire_example ( skywire_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    skywire_cfg_t skywire_cfg;  /**< Click config object. */

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
    skywire_cfg_setup( &skywire_cfg );
    SKYWIRE_MAP_MIKROBUS( skywire_cfg, MIKROBUS_POSITION_SKYWIRE );
    if ( UART_ERROR == skywire_init( &skywire, &skywire_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );

    app_state = SKYWIRE_POWER_UP;
    log_printf( &logger, ">>> APP STATE - POWER UP <<<\r\n\n" );
}

void application_task ( void ) 
{
    switch ( app_state )
    {
        case SKYWIRE_POWER_UP:
        {
            if ( SKYWIRE_OK == skywire_power_up( &skywire ) )
            {
                app_state = SKYWIRE_CONFIG_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CONFIG CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case SKYWIRE_CONFIG_CONNECTION:
        {
            if ( SKYWIRE_OK == skywire_config_connection( &skywire ) )
            {
                app_state = SKYWIRE_CHECK_CONNECTION;
                log_printf( &logger, ">>> APP STATE - CHECK CONNECTION <<<\r\n\n" );
            }
            break;
        }
        case SKYWIRE_CHECK_CONNECTION:
        {
            if ( SKYWIRE_OK == skywire_check_connection( &skywire ) )
            {
                app_state = SKYWIRE_CONFIG_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - CONFIG EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case SKYWIRE_CONFIG_EXAMPLE:
        {
            if ( SKYWIRE_OK == skywire_config_example( &skywire ) )
            {
                app_state = SKYWIRE_EXAMPLE;
                log_printf( &logger, ">>> APP STATE - EXAMPLE <<<\r\n\n" );
            }
            break;
        }
        case SKYWIRE_EXAMPLE:
        {
            skywire_example( &skywire );
            break;
        }
        default:
        {
            log_error( &logger, " APP STATE." );
            break;
        }
    }
}

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit( );
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

static void skywire_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void skywire_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t skywire_process ( skywire_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = skywire_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( ( 0 < rx_size ) && ( APP_BUFFER_SIZE >= rx_size ) ) 
    {
        if ( APP_BUFFER_SIZE < ( app_buf_len + rx_size ) ) 
        {
            overflow_bytes = ( app_buf_len + rx_size ) - APP_BUFFER_SIZE;
            app_buf_len = APP_BUFFER_SIZE - rx_size;
            for ( int32_t buf_cnt = 0; buf_cnt < overflow_bytes; buf_cnt++ )
            {
                log_printf( &logger, "%c", app_buf[ buf_cnt ] );
            }
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
        return SKYWIRE_OK;
    }
    return SKYWIRE_ERROR;
}

static err_t skywire_read_response ( skywire_t *ctx, uint8_t *rsp, uint32_t max_rsp_time )
{
    uint32_t timeout_cnt = max_rsp_time;

    skywire_clear_app_buf( );

    /* Read until either the expected response or "ERROR" is received, or the timeout expires */
    while ( ( 0 == strstr( app_buf, rsp ) ) && ( 0 == strstr( app_buf, SKYWIRE_RSP_ERROR ) ) &&
            ( timeout_cnt ) )
    {
        skywire_process( ctx );
        Delay_1ms( );
        timeout_cnt--;
    }

    /* The expected response or "ERROR" does not imply the end of the message, wait for the rest of it */
    Delay_ms( 200 );
    skywire_process( ctx );
    skywire_log_app_buf( );

    if ( strstr( app_buf, rsp ) ) 
    {
        log_printf( &logger, "--------------------------------\r\n" );
        return SKYWIRE_OK;
    }
    if ( strstr( app_buf, SKYWIRE_RSP_ERROR ) )
    {
        log_printf( &logger, "--------------------------------\r\n" );
        log_error( &logger, " CMD!" );
        return SKYWIRE_ERROR_CMD;
    }
    log_error( &logger, " Timeout!" );

    return SKYWIRE_ERROR_TIMEOUT;
}

static err_t skywire_power_up ( skywire_t *ctx )
{
    err_t error_flag = SKYWIRE_OK;
    uint8_t attempt_cnt = BOOT_CHECK_ATTEMPTS;

    log_printf( &logger, ">>> Check if the modem is already powered up.\r\n" );
    skywire_cmd_run( ctx, SKYWIRE_CMD_AT );
    if ( SKYWIRE_OK != skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT ) )
    {
        /* Modem is recovered with the hardware shutdown before the power on pulse */
        log_printf( &logger, ">>> Perform hardware shutdown before power up.\r\n" );
        skywire_hw_shutdown( ctx );
        Delay_ms( 1000 );

        log_printf( &logger, ">>> Power up the modem.\r\n" );
        skywire_power_on( ctx );

        /* The modem is ready to accept AT commands 2 seconds after the ON_OFF release */
        Delay_ms( 1000 );
        Delay_ms( 1000 );

        log_printf( &logger, ">>> Wait for the modem to respond.\r\n" );
        while ( attempt_cnt )
        {
            skywire_cmd_run( ctx, SKYWIRE_CMD_AT );
            if ( SKYWIRE_OK == skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT ) )
            {
                break;
            }
            attempt_cnt--;
        }

        if ( 0 == attempt_cnt )
        {
            log_error( &logger, " Modem does not respond." );
            return SKYWIRE_ERROR;
        }
    }

    log_printf( &logger, ">>> Get manufacturer identification.\r\n" );
    skywire_cmd_run( ctx, SKYWIRE_CMD_GET_MANUFACTURER_ID );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );

    log_printf( &logger, ">>> Get model identification.\r\n" );
    skywire_cmd_run( ctx, SKYWIRE_CMD_GET_MODEL_ID );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );

    log_printf( &logger, ">>> Get software revision identification.\r\n" );
    skywire_cmd_run( ctx, SKYWIRE_CMD_GET_SW_REVISION );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );

    log_printf( &logger, ">>> Enable verbose error reports.\r\n" );
    skywire_cmd_set( ctx, SKYWIRE_CMD_REPORT_ME_ERROR, CMEE_VERBOSE_FORMAT );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );

    return error_flag;
}

static err_t skywire_config_connection ( skywire_t *ctx )
{
    err_t error_flag = SKYWIRE_OK;
#if ( ( EXAMPLE_TCP_UDP == DEMO_EXAMPLE ) || ( EXAMPLE_SMS == DEMO_EXAMPLE ) || \
      ( EXAMPLE_VOICE_CALL == DEMO_EXAMPLE ) )
    log_printf( &logger, ">>> Set GPIO1 as status LED output.\r\n" );
    skywire_cmd_set( ctx, SKYWIRE_CMD_GPIO_CONTROL, GPIO1_STAT_LED_NOT_SAVED );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );

    log_printf( &logger, ">>> Set status LED handled by the module software.\r\n" );
    skywire_cmd_set( ctx, SKYWIRE_CMD_STAT_LED_SETTING, STAT_LED_MODULE_HANDLED );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );

    log_printf( &logger, ">>> Check SIM card status.\r\n" );
    skywire_cmd_get( ctx, SKYWIRE_CMD_ENTER_PIN );
    if ( SKYWIRE_OK != skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_SIM_STATUS ) )
    {
        log_error( &logger, " SIM card is not inserted or not ready." );
        return SKYWIRE_ERROR;
    }

    if ( strstr( app_buf, SKYWIRE_RSP_SIM_PIN ) )
    {
        if ( 0 == strlen( SIM_PIN ) )
        {
            log_error( &logger, " SIM PIN is required, set it with the SIM_PIN macro." );
            for ( ; ; );
        }

        log_printf( &logger, ">>> Enter SIM PIN.\r\n" );
        skywire_cmd_set( ctx, SKYWIRE_CMD_ENTER_PIN, SIM_PIN );
        if ( SKYWIRE_OK != skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_SIM_STATUS ) )
        {
            log_error( &logger, " Wrong SIM PIN, the example is stopped to avoid blocking the SIM card." );
            for ( ; ; );
        }
    }

    log_printf( &logger, ">>> Set SIM APN.\r\n" );
    skywire_set_sim_apn( ctx, SIM_APN );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );

    log_printf( &logger, ">>> Set automatic registration.\r\n" );
    skywire_cmd_set( ctx, SKYWIRE_CMD_OPERATOR_SELECTION, AUTOMATIC_REGISTRATION );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_CONTEXT_ACTIVATION );
#endif
    return error_flag;
}

static err_t skywire_check_connection ( skywire_t *ctx )
{
    err_t error_flag = SKYWIRE_OK;
#if ( ( EXAMPLE_TCP_UDP == DEMO_EXAMPLE ) || ( EXAMPLE_SMS == DEMO_EXAMPLE ) || \
      ( EXAMPLE_VOICE_CALL == DEMO_EXAMPLE ) )
    uint8_t * __generic_ptr creg_ptr = 0;

    log_printf( &logger, ">>> Check network registration.\r\n" );
    skywire_cmd_get( ctx, SKYWIRE_CMD_NETWORK_REGISTRATION );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );

    /* Response format: +CREG: <mode>,<stat>[,<Lac>,<Ci>[,<AcT>]], <stat> follows the first comma */
    creg_ptr = strstr( app_buf, SKYWIRE_RSP_NETWORK_REGISTRATION );
    if ( creg_ptr )
    {
        creg_ptr = strstr( creg_ptr, "," );
    }

    if ( ( creg_ptr ) && ( ( REG_STATUS_HOME == creg_ptr[ 1 ] ) || ( REG_STATUS_ROAMING == creg_ptr[ 1 ] ) ) )
    {
        log_printf( &logger, ">>> Check signal quality.\r\n" );
        skywire_cmd_run( ctx, SKYWIRE_CMD_SIGNAL_QUALITY );
        error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );
    }
    else
    {
        error_flag = SKYWIRE_ERROR;
        Delay_ms( 1000 );
        Delay_ms( 1000 );
    }
#endif
    return error_flag;
}

static err_t skywire_config_example ( skywire_t *ctx )
{
    err_t error_flag = SKYWIRE_OK;
#if ( EXAMPLE_TCP_UDP == DEMO_EXAMPLE )
    uint8_t cmd_param[ CMD_PARAM_BUFFER_SIZE ] = { 0 };

    /* Firstly deactivate the context in case it is still active from the previous run */
    log_printf( &logger, ">>> Deactivate PDP context.\r\n" );
    skywire_cmd_set( ctx, SKYWIRE_CMD_CONTEXT_ACTIVATION, CONTEXT_DEACTIVATE );
    skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_CONTEXT_ACTIVATION );

    /* Context activation format: AT#SGACT=<cid>,1,"<user>","<password>", the response contains the IP address */
    log_printf( &logger, ">>> Activate PDP context.\r\n" );
    strcpy( cmd_param, SKYWIRE_PDP_CONTEXT_ID );
    strcat( cmd_param, ",1,\"" );
    strcat( cmd_param, SIM_APN_USER );
    strcat( cmd_param, "\",\"" );
    strcat( cmd_param, SIM_APN_PASSWORD );
    strcat( cmd_param, "\"" );
    skywire_cmd_set( ctx, SKYWIRE_CMD_CONTEXT_ACTIVATION, cmd_param );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_CONTEXT_ACTIVATION );
#elif ( EXAMPLE_SMS == DEMO_EXAMPLE )
    log_printf( &logger, ">>> Set SMS text mode.\r\n" );
    skywire_cmd_set( ctx, SKYWIRE_CMD_MESSAGE_FORMAT, SMS_FORMAT_TEXT );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );

    /* The service center address is mandatory for sending SMS, it is normally stored on the SIM card */
    log_printf( &logger, ">>> Check SMS service center address.\r\n" );
    skywire_cmd_get( ctx, SKYWIRE_CMD_SERVICE_CENTER_ADDRESS );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_SIM_STATUS );
#elif ( EXAMPLE_VOICE_CALL == DEMO_EXAMPLE )
    /* Dialing mode defines when the OK result code is received for a voice call */
    log_printf( &logger, ">>> Get dialing mode.\r\n" );
    skywire_cmd_get( ctx, SKYWIRE_CMD_DIALING_MODE );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );
#elif ( EXAMPLE_GNSS == DEMO_EXAMPLE )
    /* The power up command is not allowed while the GPS controller is already powered up */
    log_printf( &logger, ">>> Get GNSS receiver power state.\r\n" );
    skywire_cmd_get( ctx, SKYWIRE_CMD_GPS_POWER );
    if ( SKYWIRE_OK == skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT ) )
    {
        if ( 0 == strstr( app_buf, SKYWIRE_RSP_GPS_POWERED_UP ) )
        {
            log_printf( &logger, ">>> Power up GNSS receiver.\r\n" );
            skywire_cmd_set( ctx, SKYWIRE_CMD_GPS_POWER, GPS_POWER_UP );
            error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );
        }
    }
#endif
    return error_flag;
}

static err_t skywire_socket_echo ( skywire_t *ctx, uint8_t *protocol )
{
    err_t error_flag = SKYWIRE_OK;
    uint8_t cmd_param[ CMD_PARAM_BUFFER_SIZE ] = { 0 };
    uint8_t msg_len_buf[ MSG_LEN_BUFFER_SIZE ] = { 0 };
    uint16_t msg_len = strlen( MESSAGE_CONTENT );

    uint16_to_str( msg_len, msg_len_buf );
    l_trim( msg_len_buf );
    r_trim( msg_len_buf );

    /* Socket dial format: AT#SD=<connId>,<txProt>,<rPort>,"<IPaddr>",<closureType>,<lPort>,<connMode>. */
    log_printf( &logger, ">>> Open socket.\r\n" );
    strcpy( cmd_param, SOCKET_CONN_ID );
    strcat( cmd_param, "," );
    strcat( cmd_param, protocol );
    strcat( cmd_param, "," );
    strcat( cmd_param, REMOTE_PORT );
    strcat( cmd_param, ",\"" );
    strcat( cmd_param, REMOTE_IP );
    strcat( cmd_param, "\",0," );
    strcat( cmd_param, SOCKET_LOCAL_PORT );
    strcat( cmd_param, ",1" );
    skywire_cmd_set( ctx, SKYWIRE_CMD_SOCKET_DIAL, cmd_param );
    if ( SKYWIRE_OK != skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_SOCKET_OPEN ) )
    {
        log_error( &logger, " Failed to open socket." );
        return SKYWIRE_ERROR;
    }

    /* Send data format: AT#SSENDEXT=<connId>,<bytestosend>, the data is sent after the "> " prompt */
    log_printf( &logger, ">>> Write message to socket.\r\n" );
    strcpy( cmd_param, SOCKET_CONN_ID );
    strcat( cmd_param, "," );
    strcat( cmd_param, msg_len_buf );
    skywire_cmd_set( ctx, SKYWIRE_CMD_SOCKET_SEND, cmd_param );
    if ( SKYWIRE_OK == skywire_read_response( ctx, SKYWIRE_RSP_DATA_PROMPT, SKYWIRE_MAX_AT_DEFAULT ) )
    {
        skywire_generic_write( ctx, MESSAGE_CONTENT, msg_len );
        error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_SOCKET_DATA );
    }
    else
    {
        error_flag = SKYWIRE_ERROR;
    }

    if ( SKYWIRE_OK == error_flag )
    {
        if ( 0 == strstr( app_buf, SKYWIRE_URC_SOCKET_RING ) )
        {
            skywire_read_response( ctx, SKYWIRE_URC_SOCKET_RING, SKYWIRE_MAX_SOCKET_DATA );
        }

        if ( strstr( app_buf, SKYWIRE_URC_SOCKET_RING ) )
        {
            /* Read data format: AT#SRECV=<connId>,<maxByte>, the parameters are the same as for sending */
            log_printf( &logger, ">>> Read echo message.\r\n" );
            skywire_cmd_set( ctx, SKYWIRE_CMD_SOCKET_RECEIVE, cmd_param );
            error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );
        }
        else
        {
            log_error( &logger, " Echo message is not received." );
            error_flag = SKYWIRE_ERROR;
        }
    }

    /* Socket shutdown format: AT#SH=<connId> */
    log_printf( &logger, ">>> Close socket.\r\n" );
    skywire_cmd_set( ctx, SKYWIRE_CMD_SOCKET_SHUTDOWN, SOCKET_CONN_ID );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );

    return error_flag;
}

static err_t skywire_example ( skywire_t *ctx )
{
    err_t error_flag = SKYWIRE_OK;

#if ( EXAMPLE_SMS == DEMO_EXAMPLE )
    uint8_t delay_cnt = SMS_REPEAT_DELAY_SEC;
#else
    uint8_t delay_cnt = EXAMPLE_REPEAT_DELAY_SEC;
#endif

#if ( EXAMPLE_TCP_UDP == DEMO_EXAMPLE )
    log_printf( &logger, ">>> TCP echo example.\r\n\n" );
    error_flag |= skywire_socket_echo( ctx, SOCKET_PROTOCOL_TCP );

    log_printf( &logger, ">>> UDP echo example.\r\n\n" );
    error_flag |= skywire_socket_echo( ctx, SOCKET_PROTOCOL_UDP );
#elif ( EXAMPLE_SMS == DEMO_EXAMPLE )
    log_printf( &logger, ">>> Send SMS in text mode.\r\n" );
    skywire_send_sms_text( ctx, PHONE_NUMBER, MESSAGE_CONTENT );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_SMS_SENT, SKYWIRE_MAX_SMS_SEND );
#elif ( EXAMPLE_VOICE_CALL == DEMO_EXAMPLE )
    uint8_t call_cmd[ CMD_PARAM_BUFFER_SIZE ] = { 0 };
    uint8_t check_cnt = CALL_STATUS_CHECKS;

    /*
     * With the factory default dialing mode the OK result code is received when the called
     * phone starts ringing. Any character sent before that aborts the call setup, so no
     * other command is sent until the response is received.
     */
    log_printf( &logger, ">>> Start voice call.\r\n" );
    strcpy( call_cmd, SKYWIRE_CMD_DIAL );
    strcat( call_cmd, PHONE_NUMBER );
    strcat( call_cmd, ";" );
    skywire_cmd_run( ctx, call_cmd );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_CALL_SETUP );

    /* Display the call status while the called phone is ringing */
    while ( ( SKYWIRE_OK == error_flag ) && ( check_cnt ) )
    {
        Delay_ms( 1000 );
        Delay_ms( 1000 );
        Delay_ms( 1000 );

        log_printf( &logger, ">>> Get current call status.\r\n" );
        skywire_cmd_run( ctx, SKYWIRE_CMD_LIST_CURRENT_CALLS );
        skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );
        check_cnt--;
    }

    log_printf( &logger, ">>> Hang up the call.\r\n" );
    skywire_cmd_run( ctx, SKYWIRE_CMD_HANG_UP_CALL );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );
#elif ( EXAMPLE_GNSS == DEMO_EXAMPLE )
    uint8_t * __generic_ptr gps_ptr = 0;
    uint8_t field_cnt = GPS_FIX_FIELD_POS;

    log_printf( &logger, ">>> Get GNSS position.\r\n" );
    skywire_cmd_run( ctx, SKYWIRE_CMD_GPS_ACQUIRED_POSITION );
    error_flag |= skywire_read_response( ctx, SKYWIRE_RSP_OK, SKYWIRE_MAX_AT_DEFAULT );

    /*
     * Response format: $GPSACP: <UTC>,<latitude>,<longitude>,<hdop>,<altitude>,<fix>,...
     * The <fix> field follows the fifth comma, 2 - 2D fix, 3 - 3D fix, other values - invalid fix.
     */
    gps_ptr = strstr( app_buf, SKYWIRE_RSP_GPS_POSITION );
    while ( ( gps_ptr ) && ( field_cnt ) )
    {
        gps_ptr = strstr( gps_ptr + 1, "," );
        field_cnt--;
    }

    if ( ( gps_ptr ) && ( ( GPS_FIX_2D == gps_ptr[ 1 ] ) || ( GPS_FIX_3D == gps_ptr[ 1 ] ) ) )
    {
        log_printf( &logger, ">>> GNSS position is fixed.\r\n\n" );
    }
    else
    {
        log_printf( &logger, ">>> GNSS position is not fixed yet.\r\n\n" );
    }
#endif
    while ( delay_cnt )
    {
        Delay_ms( 1000 );
        delay_cnt--;
    }

    return error_flag;
}

// ------------------------------------------------------------------------ END
