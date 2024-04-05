/*!
 * @file main.c
 * @brief GSM/GNSS 2 Click Example.
 *
 * # Description
 * This example reads and processes data from GSM/GNSS 2 clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and powers up the module, then sets default configuration 
 * for connecting the device to network.
 *
 * ## Application Task
 * Waits for the device to connect to network, then waits for the GNSS position fix. Once it get a fix, 
 * it sends an SMS with GNSS info to the selected phone number approximately every 40 seconds.
 *
 * ## Additional Function
 * - static void gsmgnss2_clear_app_buf ( void )
 * - static void gsmgnss2_error_check( err_t error_flag )
 * - static void gsmgnss2_log_app_buf ( void )
 * - static void gsmgnss2_check_connection( void )
 * - static err_t gsmgnss2_rsp_check ( void )
 * - static err_t gsmgnss2_process ( void )
 * - static void gnss_parser_application ( void )
 *
 * @note
 * A passive GPS antenna is required for the GNSS to receive the position fix. It may take several minutes
 * for the module to receive the fix.
 * In order for the example to work, user needs to set the phone number to which he wants 
 * to send an SMS, and also will need to set an APN and SMSC (required for PDU mode only) of entered SIM card.
 * Enter valid data for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
 * Example. 
    SIM_APN "vipmobile"
    SIM_SMSC "+381610401"
    PHONE_NUMBER_TO_MESSAGE "+381659999999"
 *
 * @author Mikroe Team
 *
 */
// ------------------------------------------------------------------- INCLUDES 

#include "board.h"
#include "log.h"
#include "gsmgnss2.h"
#include "string.h"

#define APP_OK                              0
#define APP_ERROR_DRIVER                    -1
#define APP_ERROR_OVERFLOW                  -2
#define APP_ERROR_TIMEOUT                   -3

#define RSP_OK                              "OK"
#define RSP_ERROR                           "ERROR"

#define SIM_APN                             ""  // Set valid SIM APN
#define SIM_SMSC                            ""  // Set valid SMS Service Center Address - only in PDU mode
#define PHONE_NUMBER_TO_MESSAGE             ""  // Set Phone number to message

#define PROCESS_BUFFER_SIZE                 256

#define WAIT_FOR_CONNECTION                 0
#define CONNECTED_TO_NETWORK                1

static gsmgnss2_t gsmgnss2;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

static uint8_t app_connection_status        = WAIT_FOR_CONNECTION;

static err_t app_error_flag;
static uint8_t gnss_parser_flag = 0;
static uint8_t gnss_info_message[ 200 ] = { 0 }; 

/**
 * @brief GSM/GNSS 2 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @note None.
 */
static void gsmgnss2_clear_app_buf ( void );

/**
 * @brief GSM/GNSS 2 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gsmgnss2_process ( void );

/**
 * @brief GSM/GNSS 2 check for errors.
 * @details This function checks for different types of errors and logs them on UART.
 * @note None.
 */
static void gsmgnss2_error_check( err_t error_flag );

/**
 * @brief GSM/GNSS 2 logs application buffer.
 * @details This function logs data from application buffer.
 * @note None.
 */
static void gsmgnss2_log_app_buf ( void );

/**
 * @brief GSM/GNSS 2 response check.
 * @details This function checks for response and returns the status of response.
 * @return application status.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gsmgnss2_rsp_check ( void );

/**
 * @brief GSM/GNSS 2 check connection.
 * @details This function checks connection to the network and logs that status to UART.
 * @note None.
 */
static void gsmgnss2_check_connection( void );

/**
 * @brief GNSS parser application.
 * @details This function logs GNSS data on the USB UART and stores data in gnss_info_message buffer.
 * @param rsp Response buffer.
 * @note None.
 */
static void gnss_parser_application ( char *rsp );

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gsmgnss2_cfg_t gsmgnss2_cfg;  /**< Click config object. */

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
    gsmgnss2_cfg_setup( &gsmgnss2_cfg );
    GSMGNSS2_MAP_MIKROBUS( gsmgnss2_cfg, MIKROBUS_1 );
    gsmgnss2_init( &gsmgnss2, &gsmgnss2_cfg );

    gsmgnss2_module_power( &gsmgnss2, GSMGNSS2_MODULE_POWER_ON );
    
    // dummy read
    gsmgnss2_process( );
    gsmgnss2_clear_app_buf( );
    
    // AT
    gsmgnss2_send_cmd( &gsmgnss2, GSMGNSS2_CMD_AT );
    app_error_flag = gsmgnss2_rsp_check( );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // ATI - product information
    gsmgnss2_send_cmd( &gsmgnss2, GSMGNSS2_CMD_ATI );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGMR - firmware version
    gsmgnss2_send_cmd( &gsmgnss2, GSMGNSS2_CMD_CGMR );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CMEE - Report Mobile Equipment Error
    gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_CMEE, "2" );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - deregister from network
    gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_COPS, "2" );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGDCONT - set sim apn
    gsmgnss2_set_sim_apn( &gsmgnss2, SIM_APN );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CFUN - full funtionality
    gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_CFUN, "1" );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - automatic mode
    gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_COPS, "0" );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // CREG - network registration status
    gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_CREG, "1" );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // SMS message format - PDU mode
    gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_CMGF, "0" );      
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // QGNSSC - power ON GNSS
    gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_CGNSPWR, "1" );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
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
        // CREG - network registration status
        gsmgnss2_send_cmd_check( &gsmgnss2, GSMGNSS2_CMD_CREG );
        app_error_flag = gsmgnss2_rsp_check(  );
        gsmgnss2_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CSQ - signal quality
        gsmgnss2_send_cmd( &gsmgnss2, GSMGNSS2_CMD_CSQ );
        app_error_flag = gsmgnss2_rsp_check(  );
        gsmgnss2_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        for ( ; ; )
        {
            // Get GNSS info
            gnss_parser_flag = 1;
            gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_CGNSTST, "1" );
            
            for ( ; ; )
            {
                if ( GSMGNSS2_OK == gsmgnss2_process( ) )
                {                    
                    gnss_parser_application( app_buf );
                            
                    if ( gnss_parser_flag == 2 ) 
                    {
                        gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_CGNSTST, "0" ); 
                        app_error_flag = gsmgnss2_rsp_check(  );
                        gsmgnss2_error_check( app_error_flag );                      
                        log_printf( &logger, "> Sending message to phone number...\r\n" );
                        gsmgnss2_send_sms_pdu ( &gsmgnss2, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, gnss_info_message );      
                        app_error_flag = gsmgnss2_rsp_check(  );
                        gsmgnss2_error_check( app_error_flag );
                        // 30 seconds delay
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
                    if ( gnss_parser_flag != 1 ) 
                    {
                        break;
                    }
                }
            }            
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

static void gsmgnss2_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t gsmgnss2_process ( void ) 
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = gsmgnss2_generic_read( &gsmgnss2, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size > PROCESS_BUFFER_SIZE )
        {
            rx_size = PROCESS_BUFFER_SIZE - app_buf_len;
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
        return GSMGNSS2_OK; 
    }
    return GSMGNSS2_ERROR;
}

static err_t gsmgnss2_rsp_check ( void )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 100000;
    
    err_t error_flag = gsmgnss2_process(  );
    
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        return error_flag;
    }
    
    while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
    {
        error_flag = gsmgnss2_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
        {
            return error_flag;
        }
        
        timeout_cnt++;
        if ( timeout_cnt > timeout )
        {
            while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
            {
                gsmgnss2_send_cmd( &gsmgnss2, GSMGNSS2_CMD_AT );
                gsmgnss2_process(  );
                Delay_ms ( 100 );
            }
            gsmgnss2_clear_app_buf(  );
            return APP_ERROR_TIMEOUT;
        }
        
        Delay_ms ( 1 );
    }
    
    gsmgnss2_check_connection();
    
    gsmgnss2_log_app_buf();
    
    return APP_OK;
}

static void gsmgnss2_error_check( err_t error_flag )
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

static void gsmgnss2_log_app_buf ( void )
{
    if ( gnss_parser_flag == 0 ) 
    {
        for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
        {
            log_printf( &logger, "%c", app_buf[ buf_cnt ] );
        }
        log_printf( &logger, "\r\n-----------------------------------\r\n" );
    }
    gsmgnss2_clear_app_buf(  );
}

static void gsmgnss2_check_connection( void )
{
    #define CONNECTED "+CREG: 1,1"
    
    if ( strstr( app_buf, CONNECTED ) != 0 )
    {
        app_connection_status = CONNECTED_TO_NETWORK;
    }
}

static void gnss_parser_application ( char *rsp ) 
{
    char element_buf[ 100 ] = { 0 };
    if ( GSMGNSS2_OK == gsmgnss2_parse_gngga( rsp, GSMGNSS2_GNGGA_LATITUDE, element_buf ) )
    {        
        memset( gnss_info_message, 0, 200 ); 
        if ( strlen( element_buf ) > 0 )
        {
            strcpy( gnss_info_message, "GNSS info\n" );
            strcat( gnss_info_message, "Latitude: " );
            strncat( gnss_info_message, element_buf, 2 );
            strcat( gnss_info_message, " deg, " );
            strcat( gnss_info_message, &element_buf[ 2 ] );
            strcat( gnss_info_message, " min" );
            gsmgnss2_parse_gngga( rsp, GSMGNSS2_GNGGA_LONGITUDE, element_buf );
            strcat( gnss_info_message, "\nLongitude: " );
            strncat( gnss_info_message, element_buf, 3 );
            strcat( gnss_info_message, " deg, " );
            strcat( gnss_info_message, &element_buf[ 3 ] );
            strcat( gnss_info_message, " min" );
            memset( element_buf, 0, sizeof( element_buf ) );
            gsmgnss2_parse_gngga( rsp, GSMGNSS2_GNGGA_ALTITUDE, element_buf );
            strcat( gnss_info_message, "\nAltitude: " );
            strcat( gnss_info_message, element_buf );
            strcat( gnss_info_message, " m" );
            log_printf( &logger, "%s\r\n", gnss_info_message );
            gnss_parser_flag = 2;
        }
        else
        {
            log_printf( &logger, " Waiting for the position fix...\r\n" );
            gnss_parser_flag = 3;
        }
        log_printf( &logger, "\r\n-----------------------------------\r\n" );
        gsmgnss2_clear_app_buf();
        
        // Clear RX buffer //
        for ( uint8_t buf_cnt = 0; buf_cnt < 20; buf_cnt++ )
        {
            Delay_ms ( 1 );
            gsmgnss2_process( );
            gsmgnss2_clear_app_buf();
        }
    }
}

// ------------------------------------------------------------------------ END
