/*!
 * \file 
 * \brief NbIot Click example
 * 
* # Description
 * This example reads and processes data from NB IoT clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes driver, wake-up module and sets default configuration 
 * for connecting device to network.
 * 
 * ## Application Task  
 * Waits for device to connect to network and then checks the signal quality 
 * every 5 seconds. All data is being logged on USB UART where you can track their changes.
 * 
 * ## Additional Function
 * - static void nbiot_clear_app_buf ( void )
 * - static void nbiot_error_check( err_t error_flag )
 * - static void nbiot_log_app_buf ( void )
 * - static void nbiot_check_connection( void )
 * - static err_t nbiot_rsp_check ( void )
 * - static err_t nbiot_process ( void )
 * 
 * @note 
 * In order for the example to work, a valid SIM card needs to be entered.
 * 
 * @author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "nbiot.h"

#define APP_OK                              0
#define APP_ERROR_DRIVER                    -1
#define APP_ERROR_OVERFLOW                  -2
#define APP_ERROR_TIMEOUT                   -3

#define RSP_OK                              "OK"
#define RSP_ERROR                           "ERROR"

#define PROCESS_BUFFER_SIZE                 500

#define WAIT_FOR_CONNECTION                 0
#define CONNECTED_TO_NETWORK                1

static nbiot_t nbiot;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ]  = { 0 };
static int32_t app_buf_len                  = 0;
static int32_t app_buf_cnt                  = 0;

static uint8_t app_connection_status        = WAIT_FOR_CONNECTION;

static err_t app_error_flag;

/**
 * @brief NB IoT clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @note None.
 */
static void nbiot_clear_app_buf ( void );

/**
 * @brief NB IoT data reading function.
 * @details This function reads data from device and concats data to application buffer.
 * 
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot_process ( void );

/**
 * @brief NB IoT check for errors.
 * @details This function checks for different types of errors and logs them on UART.
 * @note None.
 */
static void nbiot_error_check( err_t error_flag );

/**
 * @brief NB IoT logs application buffer.
 * @details This function logs data from application buffer.
 * @note None.
 */
static void nbiot_log_app_buf ( void );

/**
 * @brief NB IoT response check.
 * @details This function checks for response and returns the status of response.
 * 
 * @return application status.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t nbiot_rsp_check ( void );

/**
 * @brief NB IoT chek connection.
 * @details This function checks connection to the network and 
 *          logs that status to UART.
 * 
 * @note None.
 */
static void nbiot_check_connection( void );

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nbiot_cfg_t nbiot_cfg;  /**< Click config object. */

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
    nbiot_cfg_setup( &nbiot_cfg );
    NBIOT_MAP_MIKROBUS( nbiot_cfg, MIKROBUS_1 );
    err_t init_flag  = nbiot_init( &nbiot, &nbiot_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Power on device... " );
    nbiot_power_on( &nbiot );
    // dummy read
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    
    // AT
    nbiot_send_cmd( &nbiot, NBIOT_CMD_AT );
    app_error_flag = nbiot_rsp_check( );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // ATI - product information
    nbiot_send_cmd( &nbiot, NBIOT_CMD_ATI );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGMR - firmware version
    nbiot_send_cmd( &nbiot, NBIOT_CMD_CGMR );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 1000 );
    
    // COPS - deregister from network
    nbiot_send_cmd_with_parameter( &nbiot, NBIOT_CMD_COPS, "2" );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 1000 );
     
    // CFUN - full funtionality
    nbiot_send_cmd_with_parameter( &nbiot, NBIOT_CMD_CFUN, "1" );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - automatic mode
    nbiot_send_cmd_with_parameter( &nbiot, NBIOT_CMD_COPS, "0" );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // CEREG - network registration status
    nbiot_send_cmd_with_parameter( &nbiot, NBIOT_CMD_CEREG, "2" );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CIMI - request IMSI
    nbiot_send_cmd( &nbiot, NBIOT_CMD_CIMI );
    app_error_flag = nbiot_rsp_check(  );
    nbiot_error_check( app_error_flag );
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
        // CGATT - request IMSI
        nbiot_send_cmd_check( &nbiot, NBIOT_CMD_CGATT );
        app_error_flag = nbiot_rsp_check(  );
        nbiot_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CEREG - network registration status
        nbiot_send_cmd_check( &nbiot, NBIOT_CMD_CEREG );
        app_error_flag = nbiot_rsp_check(  );
        nbiot_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CSQ - signal quality
        nbiot_send_cmd( &nbiot, NBIOT_CMD_CSQ );
        app_error_flag = nbiot_rsp_check(  );
        nbiot_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        log_info( &logger, "CHECKING SIGNAL QUALITY" );
        nbiot_send_cmd( &nbiot, NBIOT_CMD_CSQ );
        app_error_flag = nbiot_rsp_check(  );
        nbiot_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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

static void nbiot_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t nbiot_process ( void )
{
    err_t return_flag = APP_ERROR_DRIVER;
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };
    
    rx_size = nbiot_generic_read( &nbiot, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    { 
        int32_t buf_cnt = 0;
        return_flag = APP_OK;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE )
        {
            nbiot_clear_app_buf(  );
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

static err_t nbiot_rsp_check ( void )
{
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 20000;
    
    err_t error_flag = nbiot_process(  );
    
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        return error_flag;
    }
    
    while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
    {
        error_flag = nbiot_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
        {
            return error_flag;
        }
        
        timeout_cnt++;
        if ( timeout_cnt > timeout )
        {
            while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
            {
                nbiot_send_cmd( &nbiot, NBIOT_CMD_AT );
                nbiot_process(  );
                Delay_ms ( 100 );
            }
            nbiot_clear_app_buf(  );
            return APP_ERROR_TIMEOUT;
        }
        
        Delay_ms ( 1 );
    }
    
    nbiot_check_connection();
    
    nbiot_log_app_buf();
    
    log_printf( &logger, "-----------------------------------\r\n" );
    
    return APP_OK;
}

static void nbiot_error_check( err_t error_flag )
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

static void nbiot_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    log_printf( &logger, "\r\n" );
    nbiot_clear_app_buf(  );
}

static void nbiot_check_connection( void )
{
    #define CONNECTED "+CGATT:1"
    
    if ( strstr( app_buf, CONNECTED ) != 0 )
    {
        app_connection_status = CONNECTED_TO_NETWORK;
    }
}

// ------------------------------------------------------------------------ END
