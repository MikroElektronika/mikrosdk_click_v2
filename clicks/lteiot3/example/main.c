/*!
 * @file main.c
 * @brief LTE IoT 3 Click Example.
 *
 * # Description
 * This example reads and processes data from LTE IoT 3 clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and wake-up module and checks communication and device version.
 *
 * ## Application Task
 * Application taks is split in few stages:
 *  - CONFIGURATION_FOR_NETWORK : Sets configuration to device to 
 *                                be able to connect to newtork.
 * 
 *  - CHECK_NETWORK_CONNECTION  : Checks device connection status 
 *                                till device is connected to network.
 * 
 *  - SENDING_SMS               : Sends SMS message to desired number in text mode.
 * 
 *  - CONFIGURATION_FOR_GNSS    : Sets configuration to device to enable GNSS data.
 * 
 *  - GNSS_DATA                 : Reads and parses data from device to 
 *                                get latitude, longitude and altitude from device
 *
 * ## Additional Function
 * - lteiot3_clear_app_buf      : Function clears memory of app_buf.
 * 
 * - lteiot3_process            : Function collects data from module and 
 *                                concat that data to app_buf.
 * 
 * - lteiot3_error_check        : Function checks for different types of
 *                                errors and logs them on UART.
 *
 * - lteiot3_log_app_buf        : Function logs data from application buffer.
 * 
 * - lteiot3_rsp_check          : Function checks for response and returns 
 *                                the status of response.
 * 
 * - lteiot3_check_connection   : Function checks connection to the network and 
 *                                logs that status to UART.
 * 
 * - lteiot3_cmd_parser         : Function searches application buffer for command
 *                                and logs data of that command.
 * 
 * - lteiot3_element_parser     : Function searches application buffer for command and its 
 *                                element and copies data to element_data buffer.
 * 
 * - lteiot3_power_up_wait      : Function loops process function untill device respond with 
 *                                "^SYSSTART" that device sends on power up/restart.
 * 
 * - lteiot3_config_device_for_network  : Function sends commands for enableing network.
 * 
 * - lteiot3_check_connection_to_network : Function sends commands for checking connection to network.
 * 
 * - lteiot3_send_sms           : Function sends SMS via network in text mode.
 * 
 * - lteiot3_config_device_for_gnss : Function sends commands for enableing GNSS.
 * 
 * - lteiot3_gnss_data          : Function reads data from device and parses data 
 *                                to find latitude, longitude and altitude.
 * 
 * @note
 * In order for the example to work, 
 * user needs to set the phone number and sim apn to which he wants to send an SMS
 * Enter valid data for the following macros: SIM_APN and PHONE_NUMBER_TO_MESSAGE.
 * E.g. 
 *  SIM_APN "vipmobile"
 *  PHONE_NUMBER_TO_MESSAGE "+381659999999"
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "lteiot3.h"


#define SIM_APN                             ""  // Set valid SIM APN
#define PHONE_NUMBER_TO_MESSAGE             ""  // Set Phone number to message
#define MESSAGE_CONTENT                     "LTE IoT 3 Click"   // Messege content 

#define PROCESS_BUFFER_SIZE                 550

#define CONFIGURATION_FOR_NETWORK           0
#define CHECK_NETWORK_CONNECTION            1
#define SENDING_SMS                         2
#define CONFIGURATION_FOR_GNSS              3
#define GNSS_DATA                           4

static lteiot3_t lteiot3;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ]  = { 0 };
static int32_t app_buf_len                  = 0;
static int32_t app_buf_cnt                  = 0;

static uint8_t app_connection_status        = CHECK_NETWORK_CONNECTION;

static char latitude_data[ 30 ]             = { 0 };
static char longitude_data[ 30 ]            = { 0 };
static char altitude_data[ 30 ]             = { 0 };

static err_t app_error_flag;
static err_t last_error_flag;

/**
 * @brief LTE IoT 3 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length and counter.
 */
static void lteiot3_clear_app_buf ( void );

/**
 * @brief LTE IoT 3 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 * 
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t lteiot3_process ( void );

/**
 * @brief LTE IoT 3 check for errors.
 * @details This function checks for different types of errors and logs them on UART.
 */
static void lteiot3_error_check( err_t error_flag );

/**
 * @brief LTE IoT 3 logs application buffer.
 * @details This function logs data from application buffer.
 */
static void lteiot3_log_app_buf ( void );

/**
 * @brief LTE IoT 3 response check.
 * @details This function checks for response and returns the status of response.
 * 
 * @return application status.
 * See #err_t definition for detailed explanation.
 */
static err_t lteiot3_rsp_check ( void );

/**
 * @brief LTE IoT 3 chek connection.
 * @details This function checks connection to the network and 
 *          logs that status to UART.
 */
static void lteiot3_check_connection( void );

/**
 * @brief IRNSS command data parser.
 * @details This function searches @b app_buf for @b cmd and logs data of that command.
 *
 * @param[in] cmd : Command to parese.
 * 
 * @return @li @c  0 - Parsed data succes.
 *         @li @c -1 - No @b cmd in application buffer.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t lteiot3_cmd_parser ( char *cmd );

/**
 * @brief IRNSS element of command data parser.
 * @details This function searches @b app_buf for @b cmd and it's 
 *          @b element and copies data to @b element_data buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - No @b cmd in application buffer.
 *         @li @c -2 - No data for @b element in @b cmd.
 *         @li @c -3 - Data buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 */
static err_t lteiot3_element_parser ( char *cmd, uint8_t element, char *element_data );

/**
 * @brief LTE IoT 3 waits device to respond with @b LTEIOT3_SYSSTART.
 * @details This function loops process function untill device respond with 
 *          @b LTEIOT3_SYSSTART that device sends on power up/restart.
 */
static void lteiot3_power_up_wait ( void );

/**
 * @brief LTE IoT 3 set up device for network.
 * @details This function sends commands for enableing network.
 */
static void lteiot3_config_device_for_network( void );

/**
 * @brief LTE IoT 3 check connection commands.
 * @details This function sends commands for checking connection to network.
 */
static void lteiot3_check_connection_to_network( void );

/**
 * @brief LTE IoT 3 sends SMS via network.
 * @details This function sends SMS via network in text mode.
 */
static void lteiot3_send_sms( void );

/**
 * @brief LTE IoT 3 set up device for GNSS.
 * @details This function sends commands for enableing GNSS.
 */
static void lteiot3_config_device_for_gnss( void );

/**
 * @brief LTE IoT 3 reads data from device and parses that data.
 * @details This function reads data from device and parses data 
 *          to find latitude, longitude and altitude.
 */
static void lteiot3_gnss_data( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot3_cfg_t lteiot3_cfg;  /**< Click config object. */

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
    Delay_ms( 1000 );

    // Click initialization.

    lteiot3_cfg_setup( &lteiot3_cfg );
    LTEIOT3_MAP_MIKROBUS( lteiot3_cfg, MIKROBUS_1 );
    err_t init_flag  = lteiot3_init( &lteiot3, &lteiot3_cfg );
    if ( UART_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Power on device... " );
    lteiot3_default_cfg ( &lteiot3 );
    lteiot3_process( );
    lteiot3_clear_app_buf( );
    
    lteiot3_send_cmd_with_parameter( &lteiot3, LTEIOT3_CMD_CFUN, "1,1" );
    lteiot3_power_up_wait();    
    app_buf_len = 0;
    app_buf_cnt = 0;
    
    //AT
    lteiot3_send_cmd( &lteiot3, LTEIOT3_CMD_AT );
    app_error_flag = lteiot3_rsp_check();
    lteiot3_error_check( app_error_flag );
    Delay_ms( 500 );
    //ATI
    lteiot3_send_cmd( &lteiot3, LTEIOT3_CMD_ATI );
    app_error_flag = lteiot3_rsp_check();
    lteiot3_error_check( app_error_flag );
    Delay_ms( 500 );

    app_connection_status = CONFIGURATION_FOR_NETWORK;
    log_info( &logger, " Application Task " );
    Delay_ms( 2000 );
}

void application_task ( void ) 
{    
    switch( app_connection_status )
    {
        case CONFIGURATION_FOR_NETWORK:
        {
            lteiot3_config_device_for_network( );
            break;
        }
        case CHECK_NETWORK_CONNECTION:
        {
            lteiot3_check_connection_to_network( );
            break;
        }
        case SENDING_SMS:
        {
            lteiot3_send_sms( );
            break;
        }
        case CONFIGURATION_FOR_GNSS:
        {
            lteiot3_config_device_for_gnss( );
            break;
        }
        case GNSS_DATA:
        {
            lteiot3_gnss_data();

            break;
        }
        default:
        {
            log_error( &logger, "Application status error!" );
            app_connection_status = CHECK_NETWORK_CONNECTION;
            Delay_ms( 1000 );
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

static void lteiot3_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t lteiot3_process ( void )
{
    err_t return_flag = LTEIOT3_ERROR;
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };
    
    rx_size = lteiot3_generic_read( &lteiot3, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    { 
        int32_t buf_cnt = 0;
        return_flag = LTEIOT3_OK;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE )
        {
            lteiot3_clear_app_buf(  );
            return_flag = LTEIOT3_ERROR_OVERFLOW;
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

static err_t lteiot3_rsp_check ( void )
{
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 1000000;
    
    volatile err_t error_flag = lteiot3_process(  );
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        return error_flag;
    }
    
    while ( ( strstr( app_buf, LTEIOT3_RSP_OK ) == 0 ) && 
            ( strstr( app_buf, LTEIOT3_RSP_ERROR ) == 0 ) )
    {
        error_flag = lteiot3_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
        {
            return error_flag;
        }
        
        timeout_cnt++;
        if ( timeout_cnt > timeout )
        {
            while ( ( strstr( app_buf, LTEIOT3_RSP_OK ) == 0 ) && 
                    ( strstr( app_buf, LTEIOT3_RSP_ERROR ) == 0 ) )
            {
                lteiot3_send_cmd( &lteiot3, LTEIOT3_CMD_AT );
                Delay_ms( 100 );
                lteiot3_process(  );
                Delay_ms( 100 );
            }
            lteiot3_clear_app_buf(  );
            return LTEIOT3_ERROR_TIMEOUT;
        }
        
        Delay_ms( 1 );
    }
    
    lteiot3_check_connection();
    
    error_flag = LTEIOT3_OK;
    
    if ( strstr( app_buf, LTEIOT3_RSP_ERROR ) != 0 )
    {
        error_flag = LTEIOT3_ERROR;
    }
    
    lteiot3_log_app_buf();
    
    log_printf( &logger, "-----------------------------------\r\n" );
    
    return error_flag;
}

static void lteiot3_error_check( err_t error_flag )
{
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) )
    {
        switch ( error_flag )
        {
            case -2:
            {
                log_error( &logger, " Overflow!" );
                break;
            }
            case -3:
            {
                log_error( &logger, " Timeout!" );
                break;
            }
            default:
            {
                break;
            }
        }
    }
}

static void lteiot3_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    log_printf( &logger, "\r\n" );
    lteiot3_clear_app_buf(  );
}

static void lteiot3_check_connection( void )
{
    #define CONNECTED "+CGATT: 1"
    
    if ( strstr( app_buf, CONNECTED ) != 0 )
    {
        app_connection_status = SENDING_SMS;
    }
}

static err_t lteiot3_cmd_parser ( char *cmd )
{
    err_t ret_flag = 0;
    
    if ( strstr( app_buf, cmd ) != 0 )
    {
        char * __generic gngga_ptr;
        
        gngga_ptr = strstr( app_buf, cmd );
        
        while (strchr( gngga_ptr, LTEIOT3_GNSS_START ) == 0)
        {
            lteiot3_process();
        }
        
        for ( ; ; )
        {
            log_printf( &logger, "%c", *gngga_ptr );
            gngga_ptr++;
            
            if ( ( *gngga_ptr == LTEIOT3_GNSS_START ) )
            {
                break;
            }
        }
    }
    else
    {
        ret_flag = -1;
    }
    
    return ret_flag;
}

static err_t lteiot3_element_parser ( char *cmd, uint8_t element, char *element_data )
{
    err_t ret_flag = 0;
    
    
    if ( strstr( app_buf, cmd ) != 0 )
    {
        uint8_t element_cnt = 0;
        char data_buf[ 30 ] = { 0 };
        uint8_t data_cnt = 0;
        char * __generic gngga_ptr;
        
        gngga_ptr = strstr( app_buf, cmd );
        
        while (strchr( gngga_ptr, LTEIOT3_GNSS_START ) == 0)
        {
            lteiot3_process();
        }
        
        for ( ; ; )
        {
            if ( ( *gngga_ptr == LTEIOT3_GNSS_START ) )
            {
                ret_flag = -2;
                break;
            }
            
            if ( *gngga_ptr == LTEIOT3_GNSS_SEPARATOR )
            {
                if (element_cnt == element)
                {
                    if ( data_cnt == 0 )
                    {
                        ret_flag = -2;
                    }
                    strcpy( element_data, data_buf );
                    break;
                }
                
                element_cnt++;
            }
            
            if ( ( element == element_cnt ) && ( *gngga_ptr != LTEIOT3_GNSS_SEPARATOR ) )
            {
                data_buf[ data_cnt ] = *gngga_ptr;
                data_cnt++;
                
                if ( data_cnt >= 30 )
                {
                    ret_flag = -3;
                    break;
                }
            }
            
            gngga_ptr++;
        }
    }
    else
    {
        ret_flag = -1;
    }
    
    return ret_flag;
}

static void lteiot3_power_up_wait ( void )
{
    do
    {
        lteiot3_process();
        Delay_ms( 10 );
    } while( 0 == strstr( app_buf, LTEIOT3_SYSSTART ) );
    
    lteiot3_log_app_buf();
}

static void lteiot3_config_device_for_network( void )
{   
    //CIMI
    lteiot3_send_cmd( &lteiot3, LTEIOT3_CMD_CIMI );
    app_error_flag = lteiot3_rsp_check();
    lteiot3_error_check( app_error_flag );
    Delay_ms( 2000 );
    
    //CGDCONT
    lteiot3_set_sim_apn( &lteiot3, SIM_APN );
    app_error_flag = lteiot3_rsp_check();
    lteiot3_error_check( app_error_flag );
    Delay_ms( 500 );

    //CEREG
    lteiot3_send_cmd_with_parameter( &lteiot3, LTEIOT3_CMD_CREG, "2" );
    app_error_flag = lteiot3_rsp_check();
    lteiot3_error_check( app_error_flag );
    Delay_ms( 500 );
    
    app_connection_status = CHECK_NETWORK_CONNECTION;
}

static void lteiot3_check_connection_to_network( void )
{
    lteiot3_send_cmd_check( &lteiot3, LTEIOT3_CMD_CGATT );
    app_error_flag = lteiot3_rsp_check();
    lteiot3_error_check( app_error_flag );
    Delay_ms( 500 );
    
    lteiot3_send_cmd_check( &lteiot3, LTEIOT3_CMD_CEREG );
    app_error_flag = lteiot3_rsp_check();
    lteiot3_error_check( app_error_flag );
    Delay_ms( 500 );
    
    lteiot3_send_cmd( &lteiot3, LTEIOT3_CMD_CSQ );
    app_error_flag = lteiot3_rsp_check();
    lteiot3_error_check( app_error_flag );
    Delay_ms( 2000 );
        
    if ( CHECK_NETWORK_CONNECTION != app_connection_status )
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
    }
}

static void lteiot3_send_sms( void )
{
    lteiot3_send_cmd_with_parameter( &lteiot3, LTEIOT3_CMD_CMGF, "1" );
    app_error_flag = lteiot3_rsp_check();
    lteiot3_error_check( app_error_flag );
    Delay_ms( 2000 );
    
    log_printf( &logger, "> Sending message to phone number...\r\n" );
    lteiot3_send_text_message( &lteiot3, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
    app_error_flag = lteiot3_rsp_check();
    lteiot3_error_check( app_error_flag );
    if ( LTEIOT3_OK == app_error_flag )
    {
        log_printf( &logger, "> Message sent...\r\n" );
        app_connection_status = CONFIGURATION_FOR_GNSS;
    }
    Delay_ms( 2000 );
}

static void lteiot3_config_device_for_gnss( void )
{
    #define GNNS_START_MODE_EN  "AT^SGPSC=\"Engine/StartMode\",0"
    #define GNNS_START_GPS      "AT^SGPSC=\"Nmea/GPS\",\"on\""
    #define GNSS_POWER_UP       "AT^SGPSC=\"Engine\",3"
    
    lteiot3_send_cmd( &lteiot3, GNNS_START_GPS );
    app_error_flag = lteiot3_rsp_check();
    lteiot3_error_check( app_error_flag );
    Delay_ms( 500 );
    
    lteiot3_send_cmd( &lteiot3, GNNS_START_MODE_EN );
    app_error_flag = lteiot3_rsp_check();
    lteiot3_error_check( app_error_flag );
    Delay_ms( 500 );
        
    lteiot3_send_cmd_with_parameter( &lteiot3, LTEIOT3_CMD_CFUN, "1,1" );
    lteiot3_power_up_wait();
    Delay_ms( 3000 );
    
    do {
        lteiot3_send_cmd( &lteiot3, GNSS_POWER_UP );
        app_error_flag = lteiot3_rsp_check();
        lteiot3_error_check( app_error_flag );
        
    } while ( app_error_flag < 0 );
    
    app_connection_status = GNSS_DATA;
    last_error_flag = 0;
    log_info( &logger, "GNSS APP" );
}

static void lteiot3_gnss_data( void )
{
    lteiot3_process();
    
    err_t error_flag = lteiot3_element_parser( LTEIOT3_GNSS_GPGGA, LTEIOT3_GPGGA_LATITUDE, 
                                            latitude_data );
    
    error_flag |= lteiot3_element_parser(  LTEIOT3_GNSS_GPGGA, LTEIOT3_GPGGA_LONGITUDE, 
                                        longitude_data );
    
    error_flag |= lteiot3_element_parser(  LTEIOT3_GNSS_GPGGA, LTEIOT3_GPGGA_ALTITUDE, 
                                        altitude_data );
    
    if ( error_flag == 0 )
    {
        if ( last_error_flag != 0)
        {
            log_printf( &logger, "\r\n" );
        }
        log_printf( &logger, ">Latitude:\r\n - deg: %.2s \r\n - min: %s\r\n", 
                    latitude_data, &latitude_data[ 2 ] );
        
        log_printf( &logger, ">Longitude:\r\n - deg: %.3s \r\n - min: %s\r\n", 
                    longitude_data, &longitude_data[ 3 ] );
        
        log_printf( &logger, ">Altitude:\r\n - %sm\r\n", 
                    altitude_data );
        
        log_printf( &logger, "----------------------------------------\r\n" );
    }
    else if ( error_flag < -1 )
    {
        if ( last_error_flag == 0 )
        {
            log_printf( &logger, "Waiting for data" );
        }
        log_printf( &logger, "." );
    }
    
    if ( error_flag != -1 )
    {
        last_error_flag = error_flag;
        lteiot3_clear_app_buf(  );
    }
}

// ------------------------------------------------------------------------ END
