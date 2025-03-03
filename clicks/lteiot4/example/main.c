/*!
 * @file main.c
 * @brief LTE IoT 4 Click Example.
 *
 * # Description
 * This example reads and processes data from LTE IoT 4 Clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver and wake-up module.
 * 
 * ## Application Task  
 * Reads the received data and parses it.
 * 
 * ## Additional Function
 * - static void lteiot4_clear_app_buf ( void )
 * - static void lteiot4_error_check( err_t error_flag )
 * - static void lteiot4_log_app_buf ( void )
 * - static void lteiot4_check_connection( void )
 * - static err_t lteiot4_rsp_check ( void )
 * - static err_t lteiot4_process ( void )
 * 
 * *note:* 
 * In order for the example to work, 
   user needs to set the phone number and sim apn to which he wants to send an SMS
 * Enter valid data for the following macros: SIM_APN.
 * E.g. 
    SIM_APN "vip.mobile"
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lteiot4.h"

#define APP_OK                              0
#define APP_ERROR_DRIVER                    -1
#define APP_ERROR_OVERFLOW                  -2
#define APP_ERROR_TIMEOUT                   -3

#define RSP_OK                              "OK"
#define RSP_ERROR                           "ERROR"

#define SIM_APN                             "" // Set valid SIM APN

#define PROCESS_BUFFER_SIZE                 500

#define WAIT_FOR_CONNECTION                 0
#define CONNECTED_TO_NETWORK                1

static lteiot4_t lteiot4;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ]  = { 0 };
static int32_t app_buf_len                  = 0;
static int32_t app_buf_cnt                  = 0;

static uint8_t app_connection_status        = WAIT_FOR_CONNECTION;

static err_t app_error_flag;

/**
 * @brief LTE IoT 4 clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void lteiot4_clear_app_buf ( void );

/**
 * @brief LTE IoT 4 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * 
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot4_process ( void );

/**
 * @brief LTE IoT 4 check for errors.
 * @details This function checks for different types of errors and logs them on UART.
 * @note None.
 */
static void lteiot4_error_check( err_t error_flag );

/**
 * @brief LTE IoT 4 logs application buffer.
 * @details This function logs data from application buffer.
 * @note None.
 */
static void lteiot4_log_app_buf ( void );

/**
 * @brief LTE IoT 4 response check.
 * @details This function checks for response and returns the status of response.
 * 
 * @return application status.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot4_rsp_check ( void );

/**
 * @brief LTE IoT 4 check connection.
 * @details This function checks connection to the network and 
 *          logs that status to UART.
 * 
 * @note None.
 */
static void lteiot4_check_connection( void );

void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    lteiot4_cfg_t lteiot4_cfg;    /**< Click config object. */

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
    lteiot4_cfg_setup( &lteiot4_cfg );
    LTEIOT4_MAP_MIKROBUS( lteiot4_cfg, MIKROBUS_1 );
    err_t init_flag  = lteiot4_init( &lteiot4, &lteiot4_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Power up device... " );
    lteiot4_default_cfg ( &lteiot4 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    lteiot4_process(  );
    lteiot4_process(  );
    lteiot4_process(  );
    lteiot4_clear_app_buf(  );
    
    //AT
    log_info( &logger, " Communication test " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_AT );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CGMM
    log_info( &logger, " Module version " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_MODULE_VERSION );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CGMR
    log_info( &logger, " FW version " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_FW_VERSION );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CFUN
    log_info( &logger, " Flight mode " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_FLIGHT_MODE );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //XSYSTEMMODE
    log_info( &logger, " Enable NB network " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_NBIOT_MODE );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CIND
    log_info( &logger, " Enable service and messages " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_ENABLE_NET_SMS );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CFUN
    log_info( &logger, " Full functionalty mode " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_FULL_FUNCTION );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CGDCONT
    log_info( &logger, " Set APN " );
    lteiot4_set_sim_apn( &lteiot4, SIM_APN );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //COPS
    log_info( &logger, " Set automatic network search " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_AUTO_NET_SRC );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CEREG
    log_info( &logger, " Activate search for network  " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_SEARCH_NET );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CIMI
    log_info( &logger, " SIM test " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_SIM_TEST );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task\r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    if ( app_connection_status == WAIT_FOR_CONNECTION )
    {
        //CEREG
        log_info( &logger, " Check connection  " );
        lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_CHECK_CONNECTION );
        app_error_flag = lteiot4_rsp_check();
        lteiot4_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        //CEREG
        log_info( &logger, " Check network status  " );
        lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_CHECK_REGISTARTION );
        app_error_flag = lteiot4_rsp_check();
        lteiot4_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        //CEREG
        log_info( &logger, " Check signal quality  " );
        lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_SIGNAL_QUALITY );
        app_error_flag = lteiot4_rsp_check();
        lteiot4_error_check( app_error_flag );
        log_printf( &logger, "-------------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK\r\n" );
        log_printf( &logger, "-------------------------------\r\n" );
        //CCLK
        log_info( &logger, " Set Time " );
        lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_SET_DUMMY_CLOCK );
        app_error_flag = lteiot4_rsp_check();
        lteiot4_error_check( app_error_flag );
        log_printf( &logger, "-------------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        
        for(;;)
        {
            //XTEMP
            log_info( &logger, " Check Temperature " );
            lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_CHECK_TEMPERATURE );
            app_error_flag = lteiot4_rsp_check();
            lteiot4_error_check( app_error_flag );
            Delay_ms ( 500 );
            //CCLK
            log_info( &logger, " Check Time " );
            lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_CHECK_CLOCK );
            app_error_flag = lteiot4_rsp_check();
            lteiot4_error_check( app_error_flag );
            log_printf( &logger, "-------------------------------\r\n" );
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

static void lteiot4_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t lteiot4_process ( void )
{
    err_t return_flag = APP_ERROR_DRIVER;
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };
    
    rx_size = lteiot4_generic_read( &lteiot4, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    { 
        int32_t buf_cnt = 0;
        return_flag = APP_OK;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE )
        {
            lteiot4_clear_app_buf(  );
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

static err_t lteiot4_rsp_check ( void )
{
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 5000;
    
    err_t error_flag = lteiot4_process(  );
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        return error_flag;
    }
    
    while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
    {
        error_flag = lteiot4_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
        {
            return error_flag;
        }
        
        timeout_cnt++;
        if ( timeout_cnt > timeout )
        {
            lteiot4_clear_app_buf(  );
            return APP_ERROR_TIMEOUT;
        }
        
        Delay_ms ( 1 );
    }
    
    lteiot4_check_connection();
    
    lteiot4_log_app_buf();
    
    return APP_OK;
}

static void lteiot4_error_check( err_t error_flag )
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

static void lteiot4_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    log_printf( &logger, "\r\n" );
    lteiot4_clear_app_buf(  );
}

static void lteiot4_check_connection( void )
{
    #define CONNECTED "+CGATT: 1"
    
    if ( strstr( app_buf, CONNECTED ) != 0 )
    {
        app_connection_status = CONNECTED_TO_NETWORK;
    }
}


// ------------------------------------------------------------------------ END
