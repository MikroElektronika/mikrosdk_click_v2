/*!
 * @file main.c
 * @brief NB IoT 5 Click Example.
 *
 * # Description
 * This example reads and processes data from NB IoT 5 clicks. 
 * It configures device for connection to network, and checks 
 * if device is connected, and signal quality. After it connects, 
 * it sends SMS message to phone number set in application.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module, and sets default 
 * configuration for connection.
 * 
 * ## Application Task  
 * Checks if device is connected to network, when device connects 
 * to network device is sending SMS message to selected phone number.
 * 
 * ## Additional Function
 * - static void nbiot5_clear_app_buf ( void )
 * - static void nbiot5_error_check( err_t error_flag )
 * - static void nbiot5_log_app_buf ( void )
 * - static void nbiot5_check_connection( void )
 * - static err_t nbiot5_rsp_check ( void )
 * - static err_t nbiot5_process ( void )
 * 
 * *note:* 
 * In order for the example to work, 
   user needs to set the phone number to which he wants to 
   send an SMS and correct sim apn of its SIM card.
 * Enter valid data for the following macros: SIM_APN and PHONE_NUMBER_TO_MESSAGE.
 * E.g. 
    SIM_APN "vip.iot"
    PHONE_NUMBER_TO_MESSAGE "999999999"
 *
 *          *You need to have USB connected to device in the beggining of 
 *           the application for additional power on startup.*
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "nbiot5.h"

#define APP_OK                              0
#define APP_ERROR_DRIVER                    -1
#define APP_ERROR_OVERFLOW                  -2
#define APP_ERROR_TIMEOUT                   -3

#define RSP_OK                              "OK"
#define RSP_ERROR                           "ERROR"

#define SIM_APN                             "" // Set valid SIM APN
#define PHONE_NUMBER_TO_MESSAGE             "" // Set Phone number to message
#define MESSAGE_CONTENT                     "NB IoT 5 Click" // Messege content 

#define PROCESS_BUFFER_SIZE                 200

#define WAIT_FOR_CONNECTION                 0
#define CONNECTED_TO_NETWORK                1

static nbiot5_t nbiot5;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ]  = { 0 };
static int32_t app_buf_len                  = 0;
static int32_t app_buf_cnt                  = 0;

static uint8_t app_connection_status        = WAIT_FOR_CONNECTION;

static err_t app_error_flag;

/**
 * @brief NB IoT 5 clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void nbiot5_clear_app_buf ( void );

/**
 * @brief NB IoT 5 data reading function.
 * @details This function reads data from device and concats data to application buffer.
 * 
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot5_process ( void );

/**
 * @brief NB IoT 5 check for errors.
 * @details This function checks for different types of errors and logs them on UART.
 * @note None.
 */
static void nbiot5_error_check( err_t error_flag );

/**
 * @brief NB IoT 5 logs application buffer.
 * @details This function logs data from application buffer.
 * @note None.
 */
static void nbiot5_log_app_buf ( void );

/**
 * @brief NB IoT 5 response check.
 * @details This function checks for response and returns the status of response.
 * 
 * @return application status.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot5_rsp_check ( void );

/**
 * @brief LTE IoT 6 chek connection.
 * @details This function checks connection to the network and 
 *          logs that status to UART.
 * 
 * @note None.
 */
static void nbiot5_check_connection( void );


void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    nbiot5_cfg_t nbiot5_cfg;    /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );
    Delay_ms( 1000 );
    
    // Click initialization.
    nbiot5_cfg_setup( &nbiot5_cfg );
    NBIOT5_MAP_MIKROBUS( nbiot5_cfg, MIKROBUS_1 );
    err_t init_flag  = nbiot5_init( &nbiot5, &nbiot5_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Power up device... " );
    nbiot5_default_cfg ( &nbiot5 );
    
    nbiot5_send_cmd( &nbiot5, NBIOT5_CMD_ATI );
    nbiot5_process(  );
    nbiot5_clear_app_buf(  );
    
    //ATI
    nbiot5_send_cmd( &nbiot5, NBIOT5_CMD_ATI );
    app_error_flag = nbiot5_rsp_check();
    nbiot5_error_check( app_error_flag );
    Delay_ms( 1000 );
    
    //CFUN
    nbiot5_send_cmd( &nbiot5, NBIOT5_SET_CFUN );
    app_error_flag = nbiot5_rsp_check();
    nbiot5_error_check( app_error_flag );
    Delay_ms( 1000 );
    
    //CEREG
    nbiot5_send_cmd( &nbiot5, NBIOT5_SET_CREG );
    app_error_flag = nbiot5_rsp_check();
    nbiot5_error_check( app_error_flag );
    Delay_ms( 1000 );
    
    //CGDCONT
    nbiot5_set_sim_apn( &nbiot5, SIM_APN );
    app_error_flag = nbiot5_rsp_check();
    nbiot5_error_check( app_error_flag );
    Delay_ms( 1000 );
    
    //COPS
    nbiot5_send_cmd( &nbiot5, NBIOT5_SET_COPS );
    app_error_flag = nbiot5_rsp_check();
    nbiot5_error_check( app_error_flag );
    Delay_ms( 1000 );
    
    //CIMI
    nbiot5_send_cmd( &nbiot5, NBIOT5_CMD_CIMI );
    app_error_flag = nbiot5_rsp_check();
    nbiot5_error_check( app_error_flag );
    Delay_ms( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task " );
    Delay_ms( 2000 );
}

void application_task ( void )
{
    
    if ( app_connection_status == WAIT_FOR_CONNECTION )
    {
        nbiot5_send_cmd( &nbiot5, NBIOT5_CHECK_CGATT );
        app_error_flag = nbiot5_rsp_check();
        nbiot5_error_check( app_error_flag );
        Delay_ms( 2000 );
        
        nbiot5_send_cmd( &nbiot5, NBIOT5_CHECK_CREG );
        app_error_flag = nbiot5_rsp_check();
        nbiot5_error_check( app_error_flag );
        Delay_ms( 2000 );
        
        nbiot5_send_cmd( &nbiot5, NBIOT5_CMD_CSQ );
        app_error_flag = nbiot5_rsp_check();
        nbiot5_error_check( app_error_flag );
        Delay_ms( 2000 );
    }
    else
    {
        //Setting SMS mode
        
        nbiot5_send_cmd( &nbiot5, NBIOT5_SET_CMGF );
        app_error_flag = nbiot5_rsp_check();
        nbiot5_error_check( app_error_flag );
        Delay_ms( 3000 );
        
        for( ; ; )
        {  
            log_printf( &logger, "> Sending message to phone number...\r\n" );
            nbiot5_send_text_message( &nbiot5, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
            app_error_flag = nbiot5_rsp_check();
            nbiot5_error_check( app_error_flag );
            Delay_ms( 10000 );
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

static void nbiot5_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t nbiot5_process ( void )
{
    err_t return_flag = APP_ERROR_DRIVER;
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };
    
    rx_size = nbiot5_generic_read( &nbiot5, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    { 
        int32_t buf_cnt = 0;
        return_flag = APP_OK;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE )
        {
            nbiot5_clear_app_buf(  );
            return_flag = APP_ERROR_OVERFLOW;
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
    } 

    return return_flag;
}

static err_t nbiot5_rsp_check ( void )
{
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 10000;
    
    err_t error_flag = nbiot5_process(  );
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        return error_flag;
    }
    
    while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
    {
        error_flag = nbiot5_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
        {
            return error_flag;
        }
        
        timeout_cnt++;
        if ( timeout_cnt > timeout )
        {
            nbiot5_clear_app_buf(  );
            return APP_ERROR_TIMEOUT;
        }
        
        Delay_ms( 1 );
    }
    
    nbiot5_check_connection();
    
    nbiot5_log_app_buf();
    
    return APP_OK;
}

static void nbiot5_error_check( err_t error_flag )
{
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        switch ( error_flag )
        {
            case -2:
                log_error( &logger, " Overflow!" );
                break;
            case -3:
                log_error( &logger, " Timeout!" );
                break;
            default:
                break;
        }
    }
}

static void nbiot5_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    log_printf( &logger, "\r\n" );
    nbiot5_clear_app_buf(  );
}

static void nbiot5_check_connection( void )
{
    #define CHECK_CONNECTION    "AT+CGATT?"
    #define CONNECTED           "+CGATT: 1"
    #define NOT_CONNECTED       "+CGATT: 0"
    
    if ( strstr( app_buf, CHECK_CONNECTION ) != 0 )
    {
        if ( strstr( app_buf, CONNECTED ) != 0 )
        {
            log_info( &logger, "CONNECTED TO NETWORK" );
            app_connection_status = CONNECTED_TO_NETWORK;
        }
        else if ( strstr( app_buf, NOT_CONNECTED ) != 0 )
        {
            log_info( &logger, "NOT CONNECTED TO NETWORK" );
        }
    }
}

// ------------------------------------------------------------------------ END
