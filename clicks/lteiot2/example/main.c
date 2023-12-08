/*!
 * \file 
 * \brief LteIot2 Click example
 * 
 * # Description
 * This example reads and processes data from LTE IoT 2 click.
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
 * - static void lteiot2_clear_app_buf ( void )
 * - static void lteiot2_error_check( err_t error_flag )
 * - static void lteiot2_log_app_buf ( void )
 * - static void lteiot2_check_connection( void )
 * - static err_t lteiot2_rsp_check ( void )
 * - static err_t lteiot2_process ( void )
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
#include "lteiot2.h"
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

#define PROCESS_BUFFER_SIZE                 280

#define WAIT_FOR_CONNECTION                 0
#define CONNECTED_TO_NETWORK                1

static lteiot2_t lteiot2;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ]  = { 0 };
static int32_t app_buf_len                  = 0;
static int32_t app_buf_cnt                  = 0;

static uint8_t app_connection_status        = WAIT_FOR_CONNECTION;

static err_t app_error_flag;
static uint8_t gps_parser_flag = 0;
static uint8_t gps_info_message[ 200 ] = { 0 };

/**
 * @brief LTE IoT 2 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 * @note None.
 */
static void lteiot2_clear_app_buf ( void );

/**
 * @brief LTE IoT 2 data reading function.
 * @details This function reads data from device and concats data to application buffer.
 * 
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot2_process ( void );

/**
 * @brief LTE IoT 2 check for errors.
 * @details This function checks for different types of errors and logs them on UART.
 * @note None.
 */
static void lteiot2_error_check( err_t error_flag );

/**
 * @brief LTE IoT 2 logs application buffer.
 * @details This function logs data from application buffer.
 * @note None.
 */
static void lteiot2_log_app_buf ( void );

/**
 * @brief LTE IoT 2 response check.
 * @details This function checks for response and returns the status of response.
 * 
 * @return application status.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lteiot2_rsp_check ( void );

/**
 * @brief LTE IoT 2 check connection.
 * @details This function checks connection to the network and 
 *          logs that status to UART.
 * 
 * @note None.
 */
static void lteiot2_check_connection( void );

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
    lteiot2_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lteiot2_cfg_setup( &cfg );
    LTEIOT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lteiot2_init( &lteiot2, &cfg );

    lteiot2_module_power( &lteiot2, LTEIOT2_MODULE_POWER_ON );
    
    // dummy read
    lteiot2_process( );
    lteiot2_clear_app_buf( );
    // AT
    lteiot2_send_cmd( &lteiot2, LTEIOT2_CMD_AT );
    app_error_flag = lteiot2_rsp_check( );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // ATI - product information
    lteiot2_send_cmd( &lteiot2, LTEIOT2_CMD_ATI );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGMR - firmware version
    lteiot2_send_cmd( &lteiot2, LTEIOT2_CMD_CGMR );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - deregister from network
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_COPS, "2" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGDCONT - set sim apn
    lteiot2_set_sim_apn( &lteiot2, SIM_APN );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
     
    // CFUN - full funtionality
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_CFUN, "1" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - automatic mode
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_COPS, "0" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 2000 );
    
    // CREG - network registration status
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_CREG, "2" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CIMI - request IMSI
    lteiot2_send_cmd( &lteiot2, LTEIOT2_CMD_CIMI );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // QGPSCFG - Set <nmeasrc> to 1 to enable acquisition of NMEA sentences via AT+QGPSGNMEA
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_QGPSCFG, "\"nmeasrc\",1" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // QGPS - Set to 1 to turn ON GNSS
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_QGPS, "1" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
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
        lteiot2_send_cmd_check( &lteiot2, LTEIOT2_CMD_CGATT );
        app_error_flag = lteiot2_rsp_check(  );
        lteiot2_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CREG - network registration status
        lteiot2_send_cmd_check( &lteiot2, LTEIOT2_CMD_CREG );
        app_error_flag = lteiot2_rsp_check(  );
        lteiot2_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CSQ - signal quality
        lteiot2_send_cmd( &lteiot2, LTEIOT2_CMD_CSQ );
        app_error_flag = lteiot2_rsp_check(  );
        lteiot2_error_check( app_error_flag );
        Delay_ms( 5000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        // SMS message format - PDU mode
        lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_CMGF, "0" );
        app_error_flag = lteiot2_rsp_check(  );
        lteiot2_error_check( app_error_flag );
        Delay_ms( 3000 );
        
        for( ; ; )
        {   
            // Get GPS info
            gps_parser_flag = 1;
            lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_QGPSGNMEA, "\"GGA\"" );
            app_error_flag = lteiot2_rsp_check(  );
            lteiot2_error_check( app_error_flag );
            Delay_ms( 3000 );
            
            if ( gps_parser_flag == 0 )
            {
                log_printf( &logger, "> Sending message to phone number...\r\n" );
                lteiot2_send_sms_pdu ( &lteiot2, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, gps_info_message );
                app_error_flag = lteiot2_rsp_check(  );
                lteiot2_error_check( app_error_flag );
                Delay_ms( 10000 );
                Delay_ms( 10000 );
                Delay_ms( 10000 );
            }
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

static void lteiot2_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t lteiot2_process ( void )
{
    err_t return_flag = APP_ERROR_DRIVER;
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };
    
    rx_size = lteiot2_generic_read( &lteiot2, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    { 
        int32_t buf_cnt = 0;
        return_flag = APP_OK;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE )
        {
            lteiot2_clear_app_buf(  );
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

static err_t lteiot2_rsp_check ( void )
{
    uint16_t timeout_cnt = 0;
    uint16_t timeout = 10000;
    
    err_t error_flag = lteiot2_process(  );
    
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        return error_flag;
    }
    
    while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
    {
        error_flag = lteiot2_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
        {
            return error_flag;
        }
        
        timeout_cnt++;
        if ( timeout_cnt > timeout )
        {
            while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) )
            {
                lteiot2_send_cmd( &lteiot2, LTEIOT2_CMD_AT );
                lteiot2_process(  );
                Delay_ms( 100 );
            }
            lteiot2_clear_app_buf(  );
            return APP_ERROR_TIMEOUT;
        }
        
        Delay_ms( 1 );
    }
    
    lteiot2_check_connection();
    
    lteiot2_log_app_buf();
    
    return APP_OK;
}

static void lteiot2_error_check( err_t error_flag )
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

static void lteiot2_log_app_buf ( void )
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
    
    lteiot2_clear_app_buf(  );
}

static void lteiot2_check_connection( void )
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
    lteiot2_generic_parser( rsp, LTEIOT2_NMEA_GPGGA, LTEIOT2_GPGGA_LATITUDE, element_buf );
    if ( strlen( element_buf ) > 0 )
    {
        strcpy( gps_info_message, "LTE IoT 2 click - GPS info\n" );
        strcat( gps_info_message, "Latitude: " );
        strncat( gps_info_message, element_buf, 2 );
        strcat( gps_info_message, " deg, " );
        strcat( gps_info_message, &element_buf[ 2 ] );
        strcat( gps_info_message, "'" );
        log_printf( &logger, "Latitude:  %.2s deg, %s'\r\n", element_buf, &element_buf[ 2 ] );
        lteiot2_generic_parser( rsp, LTEIOT2_NMEA_GPGGA, LTEIOT2_GPGGA_LONGITUDE, element_buf );
        strcat( gps_info_message, "\nLongitude: " );
        strncat( gps_info_message, element_buf, 3 );
        strcat( gps_info_message, " deg, " );
        strcat( gps_info_message, &element_buf[ 3 ] );
        strcat( gps_info_message, "'" );
        log_printf( &logger, "Longitude:  %.3s deg, %s'\r\n", element_buf, &element_buf[ 3 ] );
        memset( element_buf, 0, sizeof( element_buf ) );
        lteiot2_generic_parser( rsp, LTEIOT2_NMEA_GPGGA, LTEIOT2_GPGGA_ALTITUDE, element_buf );
        strcat( gps_info_message, "\nAltitude: " );
        strcat( gps_info_message, element_buf );
        strcat( gps_info_message, " m" );
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
