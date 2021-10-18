/*!
 * @file main.c
 * @brief LTE IoT 6 Click Example.
 *
 * # Description
 * Application example shows device capability to connect 
 * network and send SMS messages using standard "AT" commands.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and wake-up module and test communication.
 *
 * ## Application Task
 * Application taks is split in few stages:
 *  - LTEIOT6_CONFIGURE_FOR_CONNECTION: 
 * Sets configuration to device to be able to connect to newtork.
 * 
 *  - LTEIOT6_WAIT_FOR_CONNECTION: 
 * Checks device response untill device sends information 
 * that it is connected to network.
 * 
 *  - LTEIOT6_CHECK_CONNECTION:
 * Checks device connection status parameters.
 * 
 *  - LTEIOT6_CONFIGURE_FOR_MESSAGES:
 * Sets configuration to device to send SMS messages.
 * 
 *  - LTEIOT6_MESSAGES:
 * Sends message in selected mode (PDU/TXT).
 *
 *
 * ## Additional Function
 * - static void lteiot6_clear_app_buf ( void )
 * - static err_t lteiot6_process ( void )
 * - static void lteiot6_error_check( err_t error_flag )
 * - static void lteiot6_log_app_buf ( void )
 * - static err_t lteiot6_rsp_check ( void )
 * - static err_t lteiot6_configure_for_connection( void )
 * - static err_t lteiot6_check_connection( void )
 * - static err_t lteiot6_check_connection_parameters( void )
 * - static err_t lteiot6_configure_for_meesages( void )
 * - static err_t lteiot6_send_meesage( void )
 * - 
 *
 * @note
 * In order for the example to work, user needs to set the phone number to which he wants 
 * to send an SMS, and also will need to set an APN and SMSC of entered SIM card.
 * Enter valid data for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
 * E.g. 
 * SIM_APN                     "vip.iot"
 * SMSC_ADDRESS_CSCA           "\"+381999999\",145"
 * SMSC_ADDRESS_PDU            "+381999999\" 
 * PHONE_NUMBER_TO_MESSAGE     "+381659999999"
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lteiot6.h"

//Set valid SIM APN
#define SIM_APN                     ""
//Set Phone number to message
#define PHONE_NUMBER_TO_MESSAGE     "+381659999999"
//Messege content 
#define MESSAGE_CONTENT             "LTE IoT 6 Click"
//Set valid SMSC fro SIM
#define SMSC_ADDRESS_CSCA           "\"+381999999\",145" 
#define SMSC_ADDRESS_PDU            "+381999999" 

#define PROCESS_BUFFER_SIZE         300

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
   LTEIOT6_CONFIGURE_FOR_CONNECTION = 1,
   LTEIOT6_WAIT_FOR_CONNECTION,
   LTEIOT6_CHECK_CONNECTION,
   LTEIOT6_CONFIGURE_FOR_MESSAGES,
   LTEIOT6_MESSAGES

} lteiot6_example_state_t;

static lteiot6_t lteiot6;
static log_t logger;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;
static err_t error_flag;
static lteiot6_example_state_t example_state;


/**
 * @brief Clearing application buffer.
 * @details This function clears memory of application 
 * buffer and reset it's length and counter.
 */
static void lteiot6_clear_app_buf ( void );

/**
 * @brief Data reading function.
 * @details This function reads data from device and 
 * appends data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t lteiot6_process ( void );

/**
 * @brief Check for errors.
 * @details This function checks for different types of 
 * errors and logs them on UART or logs the response if no errors occured.
 */
static void lteiot6_error_check( err_t error_flag );

/**
 * @brief Logs application buffer.
 * @details This function logs data from application buffer.
 */
static void lteiot6_log_app_buf ( void );

/**
 * @brief Response check.
 * @details This function checks for response and 
 * returns the status of response.
 * 
 * @return application status.
 * See #err_t definition for detailed explanation.
 */
static err_t lteiot6_rsp_check ( void );

/**
 * @brief Configure device for connection to the network.
 * @details Sends commands to configure and enable 
 * connection to the secifide network.
 */
static err_t lteiot6_configure_for_connection( void );

/**
 * @brief Whait for connection signal.
 * @details Wait for connection signal from CREG command.
 */
static err_t lteiot6_check_connection( void );

/**
 * @brief Check connection parameters.
 * @details This function checks connection parameters.
 */
static err_t lteiot6_check_connection_parameters( void );

/**
 * @brief Configure device for sending messages.
 * @details Configure device to send txt mode 
 * messages and SMSC of the SIM card.
 */
static err_t lteiot6_configure_for_meesages( void );

/**
 * @brief Sending text message.
 * @details This function sends text messages to predefined number.
 */
static err_t lteiot6_send_meesage( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot6_cfg_t lteiot6_cfg;  /**< Click config object. */

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
    Delay_ms( 1000 );
    log_info( &logger, " Application Init " );
    Delay_ms( 1000 );

    // Click initialization.
    lteiot6_cfg_setup( &lteiot6_cfg );
    LTEIOT6_MAP_MIKROBUS( lteiot6_cfg, MIKROBUS_1 );
    err_t init_flag  = lteiot6_init( &lteiot6, &lteiot6_cfg );
    if ( init_flag == UART_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    lteiot6_process();
    lteiot6_clear_app_buf(); 
    app_buf_len = 0;
    app_buf_cnt = 0;
    
    lteiot6_reset( &lteiot6 );
    lteiot6_power_on( &lteiot6 );
    
    //Check communication
    lteiot6_send_cmd( &lteiot6, LTEIOT6_CMD_AT );
    error_flag = lteiot6_rsp_check();
    lteiot6_error_check( error_flag );
    
    //Check fw version
    lteiot6_send_cmd( &lteiot6, LTEIOT6_CMD_ATI );
    error_flag = lteiot6_rsp_check();
    lteiot6_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = LTEIOT6_CONFIGURE_FOR_CONNECTION;
}

void application_task ( void ) 
{
    switch ( example_state )
    {
        case LTEIOT6_CONFIGURE_FOR_CONNECTION:
        {
            if ( LTEIOT6_OK == lteiot6_configure_for_connection( ) )
            {
                example_state = LTEIOT6_WAIT_FOR_CONNECTION;
            }
            break;
        }
        case LTEIOT6_WAIT_FOR_CONNECTION:
        {
            if ( LTEIOT6_OK == lteiot6_check_connection( ) )
            {
                example_state = LTEIOT6_CHECK_CONNECTION;
            }
            break;
        }
        case LTEIOT6_CHECK_CONNECTION:
        {
            Delay_ms( 1000 );
            if ( LTEIOT6_OK == lteiot6_check_connection_parameters( ) )
            {
                example_state = LTEIOT6_CONFIGURE_FOR_MESSAGES;
            }
            Delay_ms( 1000 );
            break;
        }
        case LTEIOT6_CONFIGURE_FOR_MESSAGES:
        {
            if ( LTEIOT6_OK == lteiot6_configure_for_meesages( ) )
            {
                example_state = LTEIOT6_MESSAGES;
            }
            Delay_ms( 1000 );
            break;
        }
        case LTEIOT6_MESSAGES:
        {
            lteiot6_send_meesage();
            Delay_ms( 1000 );
            break;
        }
        default:
        {
            log_error( &logger, " Example state." );
            break;
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

static void lteiot6_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t lteiot6_process ( void ) 
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = lteiot6_generic_read( &lteiot6, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE ) 
        {
           lteiot6_clear_app_buf(  );
            return LTEIOT6_ERROR;
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
        return LTEIOT6_OK;
    }
    return LTEIOT6_ERROR;
}

static err_t lteiot6_rsp_check ( void )
{
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 50000;
    
    err_t error_flag = lteiot6_process(  );
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        return error_flag;
    }
    
    while ( ( 0 == strstr( app_buf, LTEIOT6_RSP_OK ) ) && 
            ( 0 == strstr( app_buf, LTEIOT6_RSP_ERROR ) ) )
    {
        error_flag = lteiot6_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
        {
            return error_flag;
        }
        
        timeout_cnt++;
        if ( timeout_cnt > timeout )
        {
            lteiot6_clear_app_buf(  );
            return LTEIOT6_ERROR_TIMEOUT;
        }
        
        Delay_ms( 1 );
    }
    
    if ( 0 != strstr( app_buf, LTEIOT6_RSP_OK ) )
    {
        return LTEIOT6_OK;
    }
    else if ( 0 == strstr( app_buf, LTEIOT6_RSP_ERROR ) )
    {
        return LTEIOT6_ERROR_CMD;
    }
    else
    {
        return LTEIOT6_ERROR_UNKNOWN;
    }
}

static void lteiot6_error_check( err_t error_flag )
{
    switch ( error_flag )
    {
        case LTEIOT6_OK:
        {
            lteiot6_log_app_buf( );
            break;
        }
        case LTEIOT6_ERROR:
        {
            log_error( &logger, " Overflow!" );
            break;
        }
        case LTEIOT6_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );
            break;
        }
        case LTEIOT6_ERROR_CMD:
        {
            log_error( &logger, " CMD!" );
            break;
        }
        case LTEIOT6_ERROR_UNKNOWN:
        default:
        {
            log_error( &logger, " Unknown!" );
            break;
        }
    }
    lteiot6_clear_app_buf(  );
    Delay_ms( 500 );
}

static void lteiot6_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t lteiot6_configure_for_connection( void )
{
    err_t func_error = LTEIOT6_OK;
    
    //Disconnect
    #define DISCONNECT "2"
    lteiot6_send_cmd_with_parameter( &lteiot6, LTEIOT6_CMD_COPS, DISCONNECT );
    error_flag = lteiot6_rsp_check(); 
    func_error |= error_flag;
    lteiot6_error_check( error_flag );
    
    //Airplane mode
    #define AIRPLANE_MODE "4"
    lteiot6_send_cmd_with_parameter( &lteiot6, LTEIOT6_CMD_CFUN, AIRPLANE_MODE );
    error_flag = lteiot6_rsp_check();
    func_error |= error_flag;
    lteiot6_error_check( error_flag );
    
    //Set SIM APN
    lteiot6_set_sim_apn( &lteiot6, SIM_APN );
    error_flag = lteiot6_rsp_check();
    func_error |= error_flag;
    lteiot6_error_check( error_flag );
    
    //Enable full functionality
    #define FULL_FUNCTIONALITY "1"
    lteiot6_send_cmd_with_parameter( &lteiot6, LTEIOT6_CMD_CFUN, FULL_FUNCTIONALITY );
    error_flag = lteiot6_rsp_check();
    func_error |= error_flag;
    lteiot6_error_check( error_flag );
    
    //Automatic configure cops
    #define AUTOMATIC "0"
    lteiot6_send_cmd_with_parameter( &lteiot6, LTEIOT6_CMD_COPS, AUTOMATIC );
    error_flag = lteiot6_rsp_check(); 
    func_error |= error_flag;
    lteiot6_error_check( error_flag );
    
    //Enable network registartion
    #define ENABLE_REG "2"
    lteiot6_send_cmd_with_parameter( &lteiot6, LTEIOT6_CMD_CREG, ENABLE_REG );
    error_flag = lteiot6_rsp_check();
    func_error |= error_flag;
    lteiot6_error_check( error_flag );
    
    return func_error;
}

static err_t lteiot6_check_connection( void )
{
    #define CONNECTED "+CREG: 1"
    lteiot6_process();
    if ( 0 != strstr(app_buf, CONNECTED ) )
    {
        Delay_ms( 100 );
        lteiot6_process();
        lteiot6_log_app_buf( );
        lteiot6_clear_app_buf(  );
        return LTEIOT6_OK;
    }
    
    return LTEIOT6_ERROR;
}

static err_t lteiot6_check_connection_parameters( void )
{
    err_t func_error = LTEIOT6_OK;
    
    //Check if connected
    lteiot6_send_cmd_check( &lteiot6, LTEIOT6_CMD_CGATT );
    error_flag = lteiot6_rsp_check();
    func_error |= error_flag;
    lteiot6_error_check( error_flag );
    
    //Check registration
    lteiot6_send_cmd_check( &lteiot6, LTEIOT6_CMD_CREG );
    error_flag = lteiot6_rsp_check();
    func_error |= error_flag;
    lteiot6_error_check( error_flag );
    
    //Check signal quality
    lteiot6_send_cmd( &lteiot6, LTEIOT6_CMD_CSQ );
    error_flag = lteiot6_rsp_check();
    func_error |= error_flag;
    lteiot6_error_check( error_flag );
    
    return func_error;
}

static err_t lteiot6_configure_for_meesages( void )
{
    err_t func_error = LTEIOT6_OK;
    
    //Set message mode
    #define PDU_MESSAGE_MODE "0"
    #define TXT_MESSAGE_MODE "1"
    lteiot6_send_cmd_with_parameter( &lteiot6, LTEIOT6_CMD_CMGF, PDU_MESSAGE_MODE );
    error_flag = lteiot6_rsp_check();
    func_error |= error_flag;
    lteiot6_error_check( error_flag );
    
    //Set SMSC for SIM card
    lteiot6_send_cmd_with_parameter( &lteiot6, LTEIOT6_CMD_CSCA, SMSC_ADDRESS_CSCA );
    error_flag = lteiot6_rsp_check();
    func_error |= error_flag;
    lteiot6_error_check( error_flag );

    return func_error;
}

static err_t lteiot6_send_meesage( void )
{
    #define CMGF_PDU "+CMGF: 0"
    #define CMGF_TXT "+CMGF: 1"
    
    //Sendind message  
    lteiot6_send_cmd_check( &lteiot6, LTEIOT6_CMD_CMGF );
    error_flag = lteiot6_rsp_check();
    
    if ( 0 != strstr( app_buf, CMGF_PDU ) )
    {
        lteiot6_clear_app_buf(  );
        lteiot6_send_sms_pdu( &lteiot6, SMSC_ADDRESS_PDU, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
        error_flag = lteiot6_rsp_check();
        lteiot6_error_check( error_flag );
    }
    else if ( 0 != strstr( app_buf, CMGF_TXT ) )
    {
        lteiot6_clear_app_buf(  );
        lteiot6_send_text_message( &lteiot6, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
        error_flag = lteiot6_rsp_check();
        lteiot6_error_check( error_flag );
    }
    
    return error_flag;
}


// ------------------------------------------------------------------------ END
