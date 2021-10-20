/*!
 * @file main.c
 * @brief NB IoT 4 Click Example.
 *
 * # Description
 * Application example shows device capability to connect 
 * network and send SMS messages using standard "AT" commands.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes UART communication modules and additional pins 
 * wait for powerup or restarts device. Test communication and 
 * read information from device.
 *
 * ## Application Task
 * First it confiures device for connection to network(sets 
 * extern sim, selected apn). It waits until device gets 
 * information that is connected to home network. Then 
 * checks connection parameters. After that it configures 
 * device for one type of sending message TEXT or PDU mode. 
 * In the end it sends SMS message to selected number.
 *
 * ## Additional Function
 * - static void nbiot4_clear_app_buf ( void )
 * - static err_t nbiot4_process ( void )
 * - static void nbiot4_log_app_buf ( void )
 * - static err_t nbiot4_rsp_check ( void )
 * - static err_t nbiot4_configure_for_connection( void )
 * - static err_t nbiot4_check_connection( void )
 * - static err_t nbiot4_wait_to_connect( void )
 * - static err_t nbiot4_configure_for_sms( void )
 * - static err_t nbiot4_send_meesage( void )
 * - static void nbiot4_restart_device( uint16_t start_timeout )
 *
 * @note
 * In order for the example to work, user needs to set the phone number to which he wants 
 * to send an SMS, and also will need to set an APN and SMSC of entered SIM card.
 * Enter valid data for the following macros: SIM_APN, SMSC_ADDRESS and PHONE_NUMBER_TO_MESSAGE.
 * E.g. 
 * SIM_APN                      "vip.iot"
 * SMSC_ADDRESS                 "+381610401"
 * PHONE_NUMBER_TO_MESSAGE      "+381659999999"
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nbiot4.h"

//Set valid SIM APN
#define SIM_APN                     "sim_apn"
//Set Phone number to message
#define PHONE_NUMBER_TO_MESSAGE     "+381659999999"
//Messege content 
#define MESSAGE_CONTENT             "NB IoT 4 Click"
//Set valid SMSC fro SIM
#define SMSC_ADDRESS                "+381999999"

#define PROCESS_BUFFER_SIZE         600

/**
 * Select message type
 */
#define PDU_MESSAGE 
// #define TEXT_MESSAGE

/**
 * @brief Example states.
 * @details Predefined enum values for application example state.
 */
typedef enum
{
    NBIOT4_CONFIGURE_FOR_CONNECTION = 1,
    NBIOT4_WAIT_FOR_CONNECTION,
    NBIOT4_CHECK_CONNECTION,
    NBIOT4_CONFIGURE_FOR_SMS,
    NBIOT4_MESSAGES

} nbiot4_example_state_t;

static nbiot4_t nbiot4;
static log_t logger;

/**
 * @brief Application example variables.
 * @details Variables used in application example.
 */
static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;
static err_t error_flag;
static nbiot4_example_state_t example_state;


/**
 * @brief Clearing application buffer.
 * @details This function clears memory of application 
 * buffer and reset it's length and counter.
 * @return Nothing
 */
static void nbiot4_clear_app_buf ( void );

/**
 * @brief Data reading function.
 * @details This function reads data from device and 
 * appends data to application buffer.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t nbiot4_process ( void );

/**
 * @brief Logs application buffer.
 * @details This function logs data from application buffer.
 * @return Nothing
 */
static void nbiot4_log_app_buf ( void );

/**
 * @brief Response check.
 * @details This function checks for response and 
 * returns the status of response.
 * @return Application status.
 * See #err_t definition for detailed explanation.
 */
static err_t nbiot4_rsp_check ( void );

/**
 * @brief Configure device for connection to the network.
 * @details Sends commands to configure and enable 
 * connection to the specified network.
 * @return Application status.
 * See #err_t definition for detailed explanation.
 */
static err_t nbiot4_configure_for_connection( void );

/**
 * @brief Check connection signal.
 * @details Check for connection signal from CREG command.
 * @return Application status.
 * See #err_t definition for detailed explanation.
 */
static err_t nbiot4_check_connection( void );

/**
 * @brief Whait for connection signal.
 * @details Wait for connection signal from CEREG command.
 */
static void nbiot4_wait_to_connect( void );

/**
 * @brief Configure device for connection to the network.
 * @details Sends commands to configure and enable 
 * connection to the secifide network.
 * @return Application status.
 * See #err_t definition for detailed explanation.
 */
static err_t nbiot4_configure_for_sms( void );

/**
 * @brief Sending text message.
 * @details This function sends text messages to predefined number.
 * @return Application status.
 * See #err_t definition for detailed explanation.
 */
static err_t nbiot4_send_meesage( void );

/**
 * @brief Wait for powerup response.
 * @details Wait for powerup response if not received send restart command.
 * @param[in] start_timeout : Time to wait for rsp before sending reset command.
 * @return Nothing
 */
static void nbiot4_restart_device( uint16_t start_timeout );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nbiot4_cfg_t nbiot4_cfg;  /**< Click config object. */

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
    Delay_ms( 500 );
    // Click initialization.

    nbiot4_cfg_setup( &nbiot4_cfg );
    NBIOT4_MAP_MIKROBUS( nbiot4_cfg, MIKROBUS_1 );
    err_t init_flag  = nbiot4_init( &nbiot4, &nbiot4_cfg );
    if ( UART_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    nbiot4_default_cfg( &nbiot4 );
    nbiot4_process( );
    nbiot4_clear_app_buf(  );
    
    log_info( &logger, "Power up" );
    nbiot4_restart_device( 5000 );
    
    //Check communication
    nbiot4_send_cmd( &nbiot4, NBIOT4_CMD_AT );
    error_flag = nbiot4_rsp_check();
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );
    
    //Check revision
    nbiot4_send_cmd( &nbiot4, NBIOT4_CMD_ATI );
    error_flag = nbiot4_rsp_check();
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );
    
    log_info( &logger, " Application Task " );
    example_state = NBIOT4_CONFIGURE_FOR_CONNECTION;
}

void application_task ( void ) 
{
    switch ( example_state )
    {
        case NBIOT4_CONFIGURE_FOR_CONNECTION:
        {
            if ( !nbiot4_configure_for_connection() )
                example_state++;
            break;
        }
        case NBIOT4_WAIT_FOR_CONNECTION:
        {
            nbiot4_wait_to_connect( );
            example_state++;
            break;
        }
        case NBIOT4_CHECK_CONNECTION:
        {
            if ( !nbiot4_check_connection() )
                example_state++;
            break;
        }
        case NBIOT4_CONFIGURE_FOR_SMS:
        {
            if ( !nbiot4_configure_for_sms() )
                example_state++;
            break;
        }
        case NBIOT4_MESSAGES:
        {
            nbiot4_send_meesage();
            break;
        }
        default:
        {
            log_error( &logger, " Unknown example state." );
            Delay_ms( 500 );
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

static void nbiot4_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t nbiot4_process ( void ) 
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = nbiot4_generic_read( &nbiot4, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE ) 
        {
           nbiot4_clear_app_buf(  );
            return NBIOT4_ERROR;
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
        return NBIOT4_OK;
    }
    return NBIOT4_ERROR;
}

static err_t nbiot4_rsp_check ( void )
{
    nbiot4_process(  );
    
    while ( ( 0 == strstr( app_buf, NBIOT4_RSP_OK ) ) && 
            ( 0 == strstr( app_buf, NBIOT4_RSP_ERROR ) ) && 
            ( 0 == strstr( app_buf, NBIOT4_RSP_NO_RSP ) && 
            ( 0 == strstr( app_buf, NBIOT4_RSP_CMD_NO_RSP ) ) ) )
    {
        error_flag = nbiot4_process(  );
        nbiot4_log_app_buf( );
        Delay_ms( 1 );
    }
    
    Delay_ms( 500 );
    nbiot4_process(  );
    
    if ( 0 != strstr( app_buf, NBIOT4_RSP_OK ) )
    {
        error_flag = NBIOT4_OK;
    }
    else if ( 0 != strstr( app_buf, NBIOT4_RSP_ERROR ) )
    {
        error_flag = NBIOT4_ERROR_CMD;
    }
    else
    {
        error_flag = NBIOT4_ERROR_UNKNOWN;
    }
    
    return error_flag;
}

static void nbiot4_log_app_buf ( void )
{
    for ( ; app_buf_cnt < app_buf_len; app_buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ app_buf_cnt ] );
    }
}

static err_t nbiot4_configure_for_connection( void )
{
    err_t func_error = NBIOT4_OK; 
    
    //Check is extern SIM is being used
    #define EXTERN_SIM "^SIMSWAP: 1"
    nbiot4_send_cmd_check( &nbiot4, NBIOT4_CMD_SIMSWAP );
    error_flag = nbiot4_rsp_check();
    if ( strstr( app_buf, EXTERN_SIM ) == 0 )
    {
        //Set extern SIM
        #define SET_EXTERN_SIM "1"
        nbiot4_send_cmd_with_parameter( &nbiot4, NBIOT4_CMD_SIMSWAP, SET_EXTERN_SIM );
        error_flag = nbiot4_rsp_check();
        nbiot4_log_app_buf( );
        nbiot4_clear_app_buf(  );
        //Reset device to apply setttings
        nbiot4_restart_device( 0 );
    }
    
    //Check SIM ID
    nbiot4_send_cmd( &nbiot4, NBIOT4_CMD_CIMI );
    error_flag = nbiot4_rsp_check();
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );
    
    //Enable full functionality
    #define EN_FUNCTIONALITY "1"
    nbiot4_send_cmd_with_parameter( &nbiot4, NBIOT4_CMD_CFUN, EN_FUNCTIONALITY );
    error_flag = nbiot4_rsp_check();
    func_error |= error_flag;
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );
    
    //Set SIM APN
    nbiot4_set_sim_apn( &nbiot4, SIM_APN );
    error_flag = nbiot4_rsp_check();
    func_error |= error_flag;
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );
    
    //Enable network registartion
    #define ENABLE_REG "2"
    nbiot4_send_cmd_with_parameter( &nbiot4, NBIOT4_CMD_CEREG, ENABLE_REG );
    error_flag = nbiot4_rsp_check();
    func_error |= error_flag;
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );
    nbiot4_send_cmd_with_parameter( &nbiot4, NBIOT4_CMD_CREG, ENABLE_REG );
    error_flag = nbiot4_rsp_check();
    func_error |= error_flag;
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );
    
    return func_error;
}

static void nbiot4_wait_to_connect( void )
{
    //Check if connected to home network
    #define HOME_NETWORK_CONNECTED "+CEREG: 2,1"
    do
    {
        nbiot4_clear_app_buf(  );
        nbiot4_send_cmd_check( &nbiot4, NBIOT4_CMD_CEREG );
        nbiot4_rsp_check();
        Delay_ms( 100 );
    } while ( !error_flag && !strstr( app_buf, HOME_NETWORK_CONNECTED ) );
    
    Delay_ms( 100 );
    nbiot4_process(  );
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );

//     nbiot4_restart_device( 0 );
}

static err_t nbiot4_check_connection( void )
{
    err_t func_error = NBIOT4_OK;
    
    //Check if connected
    nbiot4_send_cmd_check( &nbiot4, NBIOT4_CMD_CGATT );
    error_flag = nbiot4_rsp_check();
    func_error |= error_flag;
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );
    
    //Check registration
    nbiot4_send_cmd_check( &nbiot4, NBIOT4_CMD_CEREG );
    error_flag = nbiot4_rsp_check();
    func_error |= error_flag;
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );
    
    //Check signal quality
    nbiot4_send_cmd( &nbiot4, NBIOT4_CMD_CSQ );
    error_flag = nbiot4_rsp_check();
    func_error |= error_flag;
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );
    
    Delay_ms( 5000 );
    
    return func_error;
}

static err_t nbiot4_configure_for_sms( void )
{
    err_t func_error = NBIOT4_OK;
    
    //Need to do this to be able to send SMS
    nbiot4_send_cmd_with_parameter( &nbiot4, NBIOT4_CMD_CGATT, "0" );
    nbiot4_rsp_check();
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );
    
    //Set message mode
    #ifdef TEXT_MESSAGE
    
    #define MESSAGE_MODE "1"
    
    #else 
    #ifdef PDU_MESSAGE
    
    #define MESSAGE_MODE "0"
    
    #else
    
    #define MESSAGE_MODE "0"
    
    #endif
    #endif
    
    nbiot4_send_cmd_with_parameter( &nbiot4, NBIOT4_CMD_CMGF, MESSAGE_MODE );
    error_flag = nbiot4_rsp_check();
    func_error |= error_flag;
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );
    
    //Set SMSC for SIM card
    nbiot4_send_cmd_with_parameter( &nbiot4, NBIOT4_CMD_CSCA, SMSC_ADDRESS );
    error_flag = nbiot4_rsp_check();
    func_error |= error_flag;
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );

    return func_error;
}

static err_t nbiot4_send_meesage( void )
{
    #define CMGF_PDU "+CMGF: 0"
    #define CMGF_TXT "+CMGF: 1"
    
    //Sending message  
    nbiot4_send_cmd_check( &nbiot4, NBIOT4_CMD_CMGF );
    error_flag = nbiot4_rsp_check();
    nbiot4_clear_app_buf(  );
    
    #ifdef TEXT_MESSAGE
    
    nbiot4_send_text_message( &nbiot4, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
    
    #else
    #ifdef PDU_MESSAGE
    
    nbiot4_send_sms_pdu( &nbiot4, SMSC_ADDRESS, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
    
    #endif
    #endif
    
    error_flag = nbiot4_rsp_check( );
    nbiot4_log_app_buf( );
    nbiot4_clear_app_buf(  );
    
    Delay_ms( 10000 );
    return error_flag;
}

static void nbiot4_restart_device( uint16_t start_timeout )
{
    uint16_t timeout_cnt = start_timeout;
    while ( ( strlen( app_buf ) < 20 ) && timeout_cnt )
    {
        nbiot4_process( );
        nbiot4_log_app_buf( );
        Delay_ms( 1 );
        timeout_cnt--;
    }
    
    if (!timeout_cnt)
    {
        nbiot4_send_cmd( &nbiot4, NBIOT4_CMD_RESTART );
    }
    
    timeout_cnt = 20000;
    while ( timeout_cnt )
    {
        nbiot4_process( );
        nbiot4_log_app_buf( );
        Delay_ms( 1 );
        timeout_cnt--;
        if ( strstr( app_buf, "+CREG" ) )
        {
            break;
        }
    }
}

// ------------------------------------------------------------------------ END
