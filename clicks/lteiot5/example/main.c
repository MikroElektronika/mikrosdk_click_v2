/*!
 * @file 
 * @brief LTEIoT6 Click example
 * 
 * # Description
 * This example reads and processes data from LTE IoT 5 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module and sets default configuration for connecting device to network.
 * 
 * ## Application Task  
 * Waits for device to connect to network and then sends SMS to selected phone number.
 * 
 * ## Additional Function
 * - static void lteiot5_clear_app_buf ( void )
 * - static void lteiot5_error_check( err_t error_flag )
 * - static void lteiot5_log_app_buf ( void )
 * - static void lteiot5_check_connection( void )
 * - static err_t lteiot5_rsp_check ( void )
 * - static err_t lteiot5_process ( void )
 * 
 * *note:* 
 * In order for the example to work, 
   user needs to set the phone number and sim apn to which he wants to send an SMS
 * Enter valid data for the following macros: SIM_APN and PHONE_NUMBER_TO_MESSAGE.
 * E.g. 
    SIM_APN "vip.mobile"
    PHONE_NUMBER_TO_MESSAGE "999999999"
 * 
 * @author Luka Filipovic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "lteiot5.h"

#define APP_OK                              0
#define APP_ERROR_DRIVER                    -1
#define APP_ERROR_OVERFLOW                  -2
#define APP_ERROR_TIMEOUT                   -3

#define RSP_OK                              "OK"
#define RSP_ERROR                           "ERROR"

#define SIM_APN                             ""  // Set valid SIM APN
#define PHONE_NUMBER_TO_MESSAGE             ""  // Set Phone number to message
#define MESSAGE_CONTENT                     "LTE IoT 5 Click"   // Messege content 

#define PROCESS_BUFFER_SIZE                 500

#define WAIT_FOR_CONNECTION                 0
#define CONNECTED_TO_NETWORK                1

static lteiot5_t lteiot5;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ]  = { 0 };
static int32_t app_buf_len                  = 0;
static int32_t app_buf_cnt                  = 0;

static uint8_t app_connection_status        = WAIT_FOR_CONNECTION;

static err_t app_error_flag;

/**
 * @brief LTE IoT 5 clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void lteiot5_clear_app_buf ( void );

/**
 * @brief LTE IoT 5 data reading function.
 * @details This function reads data from device and concats data to application buffer.
 * 
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot5_process ( void );

/**
 * @brief LTE IoT 5 check for errors.
 * @details This function checks for different types of errors and logs them on UART.
 * @note None.
 */
static void lteiot5_error_check( err_t error_flag );

/**
 * @brief LTE IoT 5 logs application buffer.
 * @details This function logs data from application buffer.
 * @note None.
 */
static void lteiot5_log_app_buf ( void );

/**
 * @brief LTE IoT 5 response check.
 * @details This function checks for response and returns the status of response.
 * 
 * @return application status.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot5_rsp_check ( void );

/**
 * @brief LTE IoT 5 chek connection.
 * @details This function checks connection to the network and 
 *          logs that status to UART.
 * 
 * @note None.
 */
static void lteiot5_check_connection( void );



void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot5_cfg_t lteiot5_cfg;  /**< Click config object. */

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
    Delay_ms ( 1000 );
    
    // Click initialization.
    lteiot5_cfg_setup( &lteiot5_cfg );
    LTEIOT5_MAP_MIKROBUS( lteiot5_cfg, MIKROBUS_1 );
    err_t init_flag  = lteiot5_init( &lteiot5, &lteiot5_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Power on device... " );
    lteiot5_reset( &lteiot5 );
    lteiot5_power_on( &lteiot5 );
    
    lteiot5_send_cmd( &lteiot5, LTEIOT5_CMD_AT );
    Delay_ms ( 500 );
    lteiot5_process(  );
    lteiot5_clear_app_buf(  );
    
    //AT
    lteiot5_send_cmd( &lteiot5, LTEIOT5_CMD_AT );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //ATI
    lteiot5_send_cmd( &lteiot5, LTEIOT5_CMD_ATI );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //ATI
    lteiot5_send_cmd( &lteiot5, LTEIOT5_CMD_CGMR );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CFUN
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_CFUN, "0" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //COPS
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_COPS, "2" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CGDCONT
    lteiot5_set_sim_apn( &lteiot5, SIM_APN );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //URAT
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_URAT, "7" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //UBANDMASK,
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_UBANDMASK, "0,185473183" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CFUN
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_CFUN, "1" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms ( 1000 );
    
    //CFUN
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_CFUN, "16" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    lteiot5_send_cmd_check( &lteiot5, LTEIOT5_CMD_CFUN );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //COPS
    lteiot5_send_cmd_check( &lteiot5, LTEIOT5_CMD_COPS );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //UANTR
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_UANTR, "0" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CEREG
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_CEREG, "2" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CIMI
    lteiot5_send_cmd( &lteiot5, LTEIOT5_CMD_CIMI );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

void application_task ( void )
{  
    if ( app_connection_status == WAIT_FOR_CONNECTION )
    {
        lteiot5_send_cmd_check( &lteiot5, LTEIOT5_CMD_CGATT );
        app_error_flag = lteiot5_rsp_check();
        lteiot5_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        lteiot5_send_cmd_check( &lteiot5, LTEIOT5_CMD_CEREG );
        app_error_flag = lteiot5_rsp_check();
        lteiot5_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        lteiot5_send_cmd( &lteiot5, LTEIOT5_CMD_CSQ );
        app_error_flag = lteiot5_rsp_check();
        lteiot5_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        lteiot5_send_cmd_with_parameter( &lteiot5, "AT+CMGF", "1" );
        app_error_flag = lteiot5_rsp_check();
        lteiot5_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        
        for( ; ; )
        {   
            log_printf( &logger, "> Sending message to phone number...\r\n" );
            lteiot5_send_text_message( &lteiot5, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
            app_error_flag = lteiot5_rsp_check();
            lteiot5_error_check( app_error_flag );
            // 10 seconds delay
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
        }
    }
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

static void lteiot5_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t lteiot5_process ( void )
{
    err_t return_flag = APP_ERROR_DRIVER;
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };
    
    rx_size = lteiot5_generic_read( &lteiot5, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    { 
        int32_t buf_cnt = 0;
        return_flag = APP_OK;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE )
        {
            lteiot5_clear_app_buf(  );
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
            }
        }
    } 

    return return_flag;
}

static err_t lteiot5_rsp_check ( void )
{
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 10000;
    
    err_t error_flag = lteiot5_process(  );
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        return error_flag;
    }
    
    while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
    {
        error_flag = lteiot5_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
        {
            return error_flag;
        }
        
        timeout_cnt++;
        if ( timeout_cnt > timeout )
        {
            while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
            {
                lteiot5_send_cmd( &lteiot5, LTEIOT5_CMD_AT );
                lteiot5_process(  );
                Delay_ms ( 100 );
            }
            lteiot5_clear_app_buf(  );
            return APP_ERROR_TIMEOUT;
        }
        
        Delay_ms ( 1 );
    }
    
    lteiot5_check_connection();
    
    lteiot5_log_app_buf();
    
    log_printf( &logger, "-----------------------------------\r\n" );
    
    return APP_OK;
}

static void lteiot5_error_check( err_t error_flag )
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

static void lteiot5_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    log_printf( &logger, "\r\n" );
    lteiot5_clear_app_buf(  );
}

static void lteiot5_check_connection( void )
{
    #define CONNECTED "+CGATT: 1"
    
    if ( strstr( app_buf, CONNECTED ) != 0 )
    {
        app_connection_status = CONNECTED_TO_NETWORK;
    }
}

// ------------------------------------------------------------------------ END
