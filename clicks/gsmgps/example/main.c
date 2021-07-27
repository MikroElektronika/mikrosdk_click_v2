/*!
 * \file 
 * \brief Gsmgps Click example
 * 
 * # Description
 * This example reads and processes data from GSM-GPS click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and powers up the module, then sets default configuration 
 * for connecting the device to network.
 * 
 * ## Application Task  
 * Waits for the device to connect to network, then waits for the GPS position fix. Once it get a fix, 
 * it sends an SMS with GPS info to the selected phone number approximately every 40 seconds.
 * 
 * ## Additional Function
 * - static void gsmgps_clear_app_buf ( void )
 * - static void gsmgps_error_check( err_t error_flag )
 * - static void gsmgps_log_app_buf ( void )
 * - static void gsmgps_check_connection( void )
 * - static err_t gsmgps_rsp_check ( void )
 * - static err_t gsmgps_process ( void )
 * - static void gps_parser_application ( void )
 * 
 * @note 
 * In order for the example to work, user needs to set the phone number to which he wants 
 * to send an SMS, and also will need to set an APN and SMSC (required for PDU mode only) of entered SIM card.
 * Enter valid data for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
 * E.g. 
    SIM_APN "vipmobile"
    SIM_SMSC "+381610401"
    PHONE_NUMBER_TO_MESSAGE "+381659999999"
 * 
 * @author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "gsmgps.h"
#include "string.h"

#define APP_OK                              0
#define APP_ERROR_DRIVER                    -1
#define APP_ERROR_OVERFLOW                  -2
#define APP_ERROR_TIMEOUT                   -3

#define RSP_OK                              "OK"
#define RSP_ERROR                           "ERROR"

#define SIM_APN                             ""  // Set valid SIM APN
#define SIM_SMSC                            ""  // Set valid SMS Service Center Address - only in PDU mode
#define PHONE_NUMBER_TO_MESSAGE             "" // Set Phone number to message

#define PROCESS_BUFFER_SIZE                 256

#define WAIT_FOR_CONNECTION                 0
#define CONNECTED_TO_NETWORK                1

static gsmgps_t gsmgps;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ]  = { 0 };
static int32_t app_buf_len                  = 0;
static int32_t app_buf_cnt                  = 0;

static uint8_t app_connection_status        = WAIT_FOR_CONNECTION;

static err_t app_error_flag;
static uint8_t gps_parser_flag = 0;
static uint8_t gps_info_message[ 200 ] = { 0 };

/**
 * @brief GSM-GPS clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @note None.
 */
static void gsmgps_clear_app_buf ( void );

/**
 * @brief GSM-GPS data reading function.
 * @details This function reads data from device and concats data to application buffer.
 * 
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gsmgps_process ( void );

/**
 * @brief GSM-GPS check for errors.
 * @details This function checks for different types of errors and logs them on UART.
 * @note None.
 */
static void gsmgps_error_check( err_t error_flag );

/**
 * @brief GSM-GPS logs application buffer.
 * @details This function logs data from application buffer.
 * @note None.
 */
static void gsmgps_log_app_buf ( void );

/**
 * @brief GSM-GPS response check.
 * @details This function checks for response and returns the status of response.
 * 
 * @return application status.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t gsmgps_rsp_check ( void );

/**
 * @brief GSM-GPS check connection.
 * @details This function checks connection to the network and 
 *          logs that status to UART.
 * 
 * @note None.
 */
static void gsmgps_check_connection( void );

/**
 * @brief GPS parser application.
 * @param rsp Response buffer.
 * @details This function logs GPS data on the USB UART and stores data in gps_info_message buffer.
 * 
 * @note None.
 */
static void gps_parser_application ( char *rsp );

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    gsmgps_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    gsmgps_cfg_setup( &cfg );
    GSMGPS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gsmgps_init( &gsmgps, &cfg );

    gsmgps_module_power( &gsmgps, GSMGPS_MODULE_POWER_ON );
    
    // dummy read
    gsmgps_process( );
    gsmgps_clear_app_buf( );
    // AT
    gsmgps_send_cmd( &gsmgps, GSMGPS_CMD_AT );
    app_error_flag = gsmgps_rsp_check( );
    gsmgps_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // ATI - product information
    gsmgps_send_cmd( &gsmgps, GSMGPS_CMD_ATI );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGMR - firmware version
    gsmgps_send_cmd( &gsmgps, GSMGPS_CMD_CGMR );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - deregister from network
    gsmgps_send_cmd_with_parameter( &gsmgps, GSMGPS_CMD_COPS, "2" );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGDCONT - set sim apn
    gsmgps_set_sim_apn( &gsmgps, SIM_APN );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms( 500 );
     
    // CFUN - full funtionality
    gsmgps_send_cmd_with_parameter( &gsmgps, GSMGPS_CMD_CFUN, "1" );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - automatic mode
    gsmgps_send_cmd_with_parameter( &gsmgps, GSMGPS_CMD_COPS, "0" );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms( 2000 );
    
    // CREG - network registration status
    gsmgps_send_cmd_with_parameter( &gsmgps, GSMGPS_CMD_CREG, "2" );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CIMI - request IMSI
    gsmgps_send_cmd( &gsmgps, GSMGPS_CMD_CIMI );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGNSPWR - power ON GPS
    gsmgps_send_cmd_with_parameter( &gsmgps, GSMGPS_CMD_CGNSPWR, "1" );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task " );
    Delay_ms( 5000 );
}

void application_task ( void )
{
    if ( app_connection_status == WAIT_FOR_CONNECTION )
    {
        // CGATT - request IMSI
        gsmgps_send_cmd_check( &gsmgps, GSMGPS_CMD_CGATT );
        app_error_flag = gsmgps_rsp_check(  );
        gsmgps_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CREG - network registration status
        gsmgps_send_cmd_check( &gsmgps, GSMGPS_CMD_CREG );
        app_error_flag = gsmgps_rsp_check(  );
        gsmgps_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CSQ - signal quality
        gsmgps_send_cmd( &gsmgps, GSMGPS_CMD_CSQ );
        app_error_flag = gsmgps_rsp_check(  );
        gsmgps_error_check( app_error_flag );
        Delay_ms( 5000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        // SMS message format - PDU mode
        gsmgps_send_cmd_with_parameter( &gsmgps, GSMGPS_CMD_CMGF, "0" );
        app_error_flag = gsmgps_rsp_check(  );
        gsmgps_error_check( app_error_flag );
        Delay_ms( 3000 );
        
        for( ; ; )
        {   
            // Get GPS info
            gps_parser_flag = 1;
            gsmgps_send_cmd_with_parameter( &gsmgps, GSMGPS_CMD_CGPSINF, "2" );
            app_error_flag = gsmgps_rsp_check(  );
            gsmgps_error_check( app_error_flag );
            Delay_ms( 3000 );
            
            if ( gps_parser_flag == 0 )
            {
                log_printf( &logger, "> Sending message to phone number...\r\n" );
                gsmgps_send_sms_pdu ( &gsmgps, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, gps_info_message );
                app_error_flag = gsmgps_rsp_check(  );
                gsmgps_error_check( app_error_flag );
                Delay_ms( 10000 );
                Delay_ms( 10000 );
                Delay_ms( 10000 );
            }
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

static void gsmgps_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t gsmgps_process ( void )
{
    err_t return_flag = APP_ERROR_DRIVER;
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };
    
    rx_size = gsmgps_generic_read( &gsmgps, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    { 
        int32_t buf_cnt = 0;
        return_flag = APP_OK;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE )
        {
            gsmgps_clear_app_buf(  );
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

static err_t gsmgps_rsp_check ( void )
{
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 10000;
    
    err_t error_flag = gsmgps_process(  );
    
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        return error_flag;
    }
    
    while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
    {
        error_flag = gsmgps_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
        {
            return error_flag;
        }
        
        timeout_cnt++;
        if ( timeout_cnt > timeout )
        {
            while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
            {
                gsmgps_send_cmd( &gsmgps, GSMGPS_CMD_AT );
                gsmgps_process(  );
                Delay_ms( 100 );
            }
            gsmgps_clear_app_buf(  );
            return APP_ERROR_TIMEOUT;
        }
        
        Delay_ms( 1 );
    }
    
    gsmgps_check_connection();
    
    gsmgps_log_app_buf();
    
    return APP_OK;
}

static void gsmgps_error_check( err_t error_flag )
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

static void gsmgps_log_app_buf ( void )
{
    if ( gps_parser_flag == 1 )
    {
        gps_parser_application( app_buf );
        
    }
    else
    {
        for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
        {
            log_printf( &logger, "%c", app_buf[ buf_cnt ] );
        }
        log_printf( &logger, "\r\n-----------------------------------\r\n" );
    }
    
    gsmgps_clear_app_buf(  );
}

static void gsmgps_check_connection( void )
{
    #define CONNECTED "+CGATT: 1"
    
    if ( strstr( app_buf, CONNECTED ) != 0 )
    {
        app_connection_status = CONNECTED_TO_NETWORK;
    }
}

static void gps_parser_application ( char *rsp )
{
    char element_buf[ 200 ] = { 0 };
    memset( gps_info_message, 0, 200 ); 
    gsmgps_generic_parser( rsp, GSMGPS_NEMA_GPGGA, GSMGPS_GPGGA_LATITUDE, element_buf );
    if ( strcmp( element_buf, "0000.0000" ) != 0 )
    {
        strcpy( gps_info_message, "GSM-GPS click - GPS info\n" );
        strcat( gps_info_message, "Latitude: " );
        strcat( gps_info_message, element_buf );
        log_printf( &logger, "Latitude:  %s\r\n", element_buf );
        gsmgps_generic_parser( rsp, GSMGPS_NEMA_GPGGA, GSMGPS_GPGGA_LONGITUDE, element_buf );
        strcat( gps_info_message, "\nLongitude: " );
        strcat( gps_info_message, element_buf );
        log_printf( &logger, "Longitude:  %s\r\n", element_buf );
        memset( element_buf, 0, sizeof( element_buf ) );
        gsmgps_generic_parser( rsp, GSMGPS_NEMA_GPGGA, GSMGPS_GPGGA_ALTITUDE, element_buf );
        strcat( gps_info_message, "\nAltitude: " );
        strcat( gps_info_message, element_buf );
        log_printf( &logger, "Altitude: %s m\r\n", element_buf );  
        gps_parser_flag = 0;
    }
    else
    {
        log_printf( &logger, "Waiting for the position fix..." );
    }
    log_printf( &logger, "\r\n-----------------------------------\r\n" );
}

// ------------------------------------------------------------------------ END
