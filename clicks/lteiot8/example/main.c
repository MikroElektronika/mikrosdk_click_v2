/*!
 * @file main.c
 * @brief LTE IoT 8 Click Example.
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
 *  - LTEIOT8_CONFIGURE_FOR_CONNECTION: 
 * Sets configuration to device to be able to connect to newtork.
 * 
 *  - LTEIOT8_WAIT_FOR_CONNECTION: 
 * Checks device response untill device sends information 
 * that it is connected to network.
 * 
 *  - LTEIOT8_CHECK_CONNECTION:
 * Checks device connection status parameters.
 * 
 *  - LTEIOT8_CONFIGURE_FOR_MESSAGES:
 * Sets configuration to device to send SMS messages.
 * 
 *  - LTEIOT8_MESSAGES:
 * Sends message in selected mode (PDU/TXT).
 *
 *
 * ## Additional Function
 * - static void lteiot8_clear_app_buf ( void )
 * - static err_t lteiot8_process ( void )
 * - static void lteiot8_error_check( err_t error_flag )
 * - static void lteiot8_log_app_buf ( void )
 * - static err_t lteiot8_rsp_check ( void )
 * - static err_t lteiot8_configure_for_connection( void )
 * - static err_t lteiot8_check_connection( void )
 * - static err_t lteiot8_check_connection_parameters( void )
 * - static err_t lteiot8_configure_for_meesages( void )
 * - static err_t lteiot8_send_meesage( void )
 * - 
 *
 * @note
 *  * In order for the example to work, user needs to set the phone number to which he wants 
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
#include "lteiot8.h"

//Set valid SIM APN
#define SIM_APN                     ""
//Set Phone number to message
#define PHONE_NUMBER_TO_MESSAGE     "+381659999999"
//Messege content 
#define MESSAGE_CONTENT             "LTE IoT 8 Click"
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
   LTEIOT8_CONFIGURE_FOR_CONNECTION = 1,
   LTEIOT8_WAIT_FOR_CONNECTION,
   LTEIOT8_CHECK_CONNECTION,
   LTEIOT8_CONFIGURE_FOR_MESSAGES,
   LTEIOT8_MESSAGES

} lteiot8_example_state_t;

static lteiot8_t lteiot8;
static log_t logger;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;
static err_t error_flag;
static lteiot8_example_state_t example_state;


/**
 * @brief Clearing application buffer.
 * @details This function clears memory of application 
 * buffer and reset it's length and counter.
 */
static void lteiot8_clear_app_buf ( void );

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
static err_t lteiot8_process ( void );

/**
 * @brief Check for errors.
 * @details This function checks for different types of 
 * errors and logs them on UART or logs the response if no errors occured.
 */
static void lteiot8_error_check( err_t error_flag );

/**
 * @brief Logs application buffer.
 * @details This function logs data from application buffer.
 */
static void lteiot8_log_app_buf ( void );

/**
 * @brief Response check.
 * @details This function checks for response and 
 * returns the status of response.
 * 
 * @return application status.
 * See #err_t definition for detailed explanation.
 */
static err_t lteiot8_rsp_check ( void );

/**
 * @brief Configure device for connection to the network.
 * @details Sends commands to configure and enable 
 * connection to the secifide network.
 */
static err_t lteiot8_configure_for_connection( void );

/**
 * @brief Whait for connection signal.
 * @details Wait for connection signal from CREG command.
 */
static err_t lteiot8_check_connection( void );

/**
 * @brief Check connection parameters.
 * @details This function checks connection parameters.
 */
static err_t lteiot8_check_connection_parameters( void );

/**
 * @brief Configure device for sending messages.
 * @details Configure device to send txt mode 
 * messages and SMSC of the SIM card.
 */
static err_t lteiot8_configure_for_meesages( void );

/**
 * @brief Sending text message.
 * @details This function sends text messages to predefined number.
 */
static err_t lteiot8_send_meesage( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot8_cfg_t lteiot8_cfg;  /**< Click config object. */

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
    lteiot8_cfg_setup( &lteiot8_cfg );
    LTEIOT8_MAP_MIKROBUS( lteiot8_cfg, MIKROBUS_1 );
    err_t init_flag  = lteiot8_init( &lteiot8, &lteiot8_cfg );
    if ( init_flag == UART_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    lteiot8_process();
    lteiot8_clear_app_buf(); 
    app_buf_len = 0;
    app_buf_cnt = 0;
    
    lteiot8_default_cfg ( &lteiot8 );
    while ( 0 == strstr( app_buf, LTEIOT8_RSP_SYSTART ) )
    {
        lteiot8_process();
    }
    
    //Check communication
    lteiot8_send_cmd( &lteiot8, "AT" );
    error_flag = lteiot8_rsp_check();
    lteiot8_error_check( error_flag );
    
    log_info( &logger, " Application Task " );
    example_state = LTEIOT8_CONFIGURE_FOR_CONNECTION;
}

void application_task ( void ) 
{
    switch ( example_state )
    {
        case LTEIOT8_CONFIGURE_FOR_CONNECTION:
        {
            if ( LTEIOT8_OK == lteiot8_configure_for_connection( ) )
            {
                example_state = LTEIOT8_WAIT_FOR_CONNECTION;
            }
            Delay_ms( 5000 );
            break;
        }
        case LTEIOT8_WAIT_FOR_CONNECTION:
        {
            if ( LTEIOT8_OK == lteiot8_check_connection( ) )
            {
                example_state = LTEIOT8_CHECK_CONNECTION;
            }
            break;
        }
        case LTEIOT8_CHECK_CONNECTION:
        {
            if ( LTEIOT8_OK == lteiot8_check_connection_parameters( ) )
            {
                example_state = LTEIOT8_CONFIGURE_FOR_MESSAGES;
            }
            Delay_ms( 5000 );
            break;
        }
        case LTEIOT8_CONFIGURE_FOR_MESSAGES:
        {
            if ( LTEIOT8_OK == lteiot8_configure_for_meesages( ) )
            {
                example_state = LTEIOT8_MESSAGES;
            }
            Delay_ms( 5000 );
            break;
        }
        case LTEIOT8_MESSAGES:
        {
            lteiot8_send_meesage();
            Delay_ms( 10000 );
            break;
        }
        default:
        {
            log_error( &logger, " Example state." );
            break;
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

static void lteiot8_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t lteiot8_process ( void ) 
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = lteiot8_generic_read( &lteiot8, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE ) 
        {
           lteiot8_clear_app_buf(  );
            return LTEIOT8_ERROR;
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
        return LTEIOT8_OK;
    }
    return LTEIOT8_ERROR;
}

static err_t lteiot8_rsp_check ( void )
{
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 10000;
    
    err_t error_flag = lteiot8_process(  );
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        return error_flag;
    }
    
    while ( ( 0 == strstr( app_buf, LTEIOT8_RSP_OK ) ) && 
            ( 0 == strstr( app_buf, LTEIOT8_RSP_ERROR ) ) )
    {
        error_flag = lteiot8_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
        {
            return error_flag;
        }
        
        timeout_cnt++;
        if ( timeout_cnt > timeout )
        {
            lteiot8_clear_app_buf(  );
            return LTEIOT8_ERROR_TIMEOUT;
        }
        
        Delay_ms( 1 );
    }
    
    if ( 0 != strstr( app_buf, LTEIOT8_RSP_OK ) )
    {
        return LTEIOT8_OK;
    }
    else if ( 0 == strstr( app_buf, LTEIOT8_RSP_ERROR ) )
    {
        return LTEIOT8_ERROR_CMD;
    }
    else
    {
        return LTEIOT8_ERROR_UNKNOWN;
    }
}

static void lteiot8_error_check( err_t error_flag )
{
    switch ( error_flag )
    {
        case LTEIOT8_OK:
        {
            lteiot8_log_app_buf( );
            break;
        }
        case LTEIOT8_ERROR:
        {
            log_error( &logger, " Overflow!" );
            break;
        }
        case LTEIOT8_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );
            break;
        }
        case LTEIOT8_ERROR_CMD:
        {
            log_error( &logger, " CMD!" );
            break;
        }
        case LTEIOT8_ERROR_UNKNOWN:
        default:
        {
            log_error( &logger, " Unknown!" );
            break;
        }
    }
    lteiot8_clear_app_buf(  );
    Delay_ms( 500 );
}

static void lteiot8_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t lteiot8_configure_for_connection( void )
{
    err_t func_error = LTEIOT8_OK;
    
    //Enable full functionality
    #define FULL_FUNCTIONALITY "1"
    lteiot8_send_cmd_with_parameter( &lteiot8, LTEIOT8_CMD_CFUN, FULL_FUNCTIONALITY );
    error_flag = lteiot8_rsp_check();
    func_error |= error_flag;
    lteiot8_error_check( error_flag );
    
    //Enable device LED
    #define GNSS_LEN "1"
    lteiot8_send_cmd_with_parameter( &lteiot8, LTEIOT8_CMD_SQNLED, GNSS_LEN );
    error_flag = lteiot8_rsp_check();
    func_error |= error_flag;
    lteiot8_error_check( error_flag );
    
    //Set SIM APN
    lteiot8_set_sim_apn( &lteiot8, SIM_APN );
    error_flag = lteiot8_rsp_check();
    func_error |= error_flag;
    lteiot8_error_check( error_flag );
    
    //Automatic configure cops
    #define AUTOMATIC "0"
    lteiot8_send_cmd_with_parameter( &lteiot8, LTEIOT8_CMD_COPS, AUTOMATIC );
    error_flag = lteiot8_rsp_check(); 
    func_error |= error_flag;
    lteiot8_error_check( error_flag );
    
    //Enable network registartion
    #define ENABLE_REG "2"
    lteiot8_send_cmd_with_parameter( &lteiot8, LTEIOT8_CMD_CEREG, ENABLE_REG );
    error_flag = lteiot8_rsp_check();
    func_error |= error_flag;
    lteiot8_error_check( error_flag );
    
    return func_error;
}

static err_t lteiot8_check_connection( void )
{
    #define CONNECTED "+CEREG: 1"
    lteiot8_process();
    if ( 0 != strstr(app_buf, CONNECTED ) )
    {
        Delay_ms( 100 );
        lteiot8_process();
        lteiot8_log_app_buf( );
        lteiot8_clear_app_buf(  );
        return LTEIOT8_OK;
    }
    
    return LTEIOT8_ERROR;
}

static err_t lteiot8_check_connection_parameters( void )
{
    err_t func_error = LTEIOT8_OK;
    
    //Check if connected
    lteiot8_send_cmd_check( &lteiot8, LTEIOT8_CMD_CGATT );
    error_flag = lteiot8_rsp_check();
    func_error |= error_flag;
    lteiot8_error_check( error_flag );
    
    //Check registration
    lteiot8_send_cmd_check( &lteiot8, LTEIOT8_CMD_CEREG );
    error_flag = lteiot8_rsp_check();
    func_error |= error_flag;
    lteiot8_error_check( error_flag );
    
    //Check signal quality
    lteiot8_send_cmd( &lteiot8, LTEIOT8_CMD_CSQ );
    error_flag = lteiot8_rsp_check();
    func_error |= error_flag;
    lteiot8_error_check( error_flag );
    
    return func_error;
}

static err_t lteiot8_configure_for_meesages( void )
{
    err_t func_error = LTEIOT8_OK;
    
    //Set message mode
    #define PDU_MESSAGE_MODE "0"
    #define TXT_MESSAGE_MODE "1"
    lteiot8_send_cmd_with_parameter( &lteiot8, LTEIOT8_CMD_CMGF, TXT_MESSAGE_MODE );
    error_flag = lteiot8_rsp_check();
    func_error |= error_flag;
    lteiot8_error_check( error_flag );
    
    //Set SMSC for SIM card
    lteiot8_send_cmd_with_parameter( &lteiot8, LTEIOT8_CMD_CSCA, SMSC_ADDRESS_CSCA );
    error_flag = lteiot8_rsp_check();
    func_error |= error_flag;
    lteiot8_error_check( error_flag );

    return func_error;
}

static err_t lteiot8_send_meesage( void )
{
    #define CMGF_PDU "+CMGF: 0"
    #define CMGF_TXT "+CMGF: 1"
    
    //Sendind message  
    lteiot8_send_cmd_check( &lteiot8, LTEIOT8_CMD_CMGF );
    error_flag = lteiot8_rsp_check();
    
    if ( 0 != strstr( app_buf, CMGF_PDU ) )
    {
        lteiot8_clear_app_buf(  );
        lteiot8_send_sms_pdu( &lteiot8, SMSC_ADDRESS_PDU, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
        error_flag = lteiot8_rsp_check();
        lteiot8_error_check( error_flag );
    }
    else if ( 0 != strstr( app_buf, CMGF_TXT ) )
    {
        lteiot8_clear_app_buf(  );
        lteiot8_send_text_message( &lteiot8, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
        error_flag = lteiot8_rsp_check();
        lteiot8_error_check( error_flag );
    }
    
    return error_flag;
}


// ------------------------------------------------------------------------ END
