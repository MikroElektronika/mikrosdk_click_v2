/*!
 * @file main.c
 * @brief 3G-AA Click Example.
 *
 * # Description
 * This example reads and processes data from 3G-AA click.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and powers up the module, then sets default configuration 
 * for connecting the device to network.
 * 
 * ## Application Task  
 * Waits for device to connect to network and then sends a desired SMS to the selected phone number
 * approximately every 30 seconds.
 * 
 * ## Additional Function
 * - static void c3gaa_clear_app_buf ( void )
 * - static void c3gaa_error_check( err_t error_flag )
 * - static void c3gaa_log_app_buf ( void )
 * - static void c3gaa_check_connection( void )
 * - static err_t c3gaa_rsp_check ( void )
 * - static err_t c3gaa_process ( void )
 * 
 * @note 
 * In order for the example to work, user needs to set the phone number to which he wants 
 * to send an SMS, and also will need to set an APN and SMSC (required for PDU mode only) of entered SIM card.
 * Enter valid data for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
 * E.g. 
    SIM_APN "vipmobile"
    SIM_SMSC "+381610401"
    PHONE_NUMBER_TO_MESSAGE "+38169999999"
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "c3gaa.h"
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
#define MESSAGE_CONTENT                     "3G-AA click board - demo example."   // Message content 

#define PROCESS_BUFFER_SIZE                 256

#define WAIT_FOR_CONNECTION                 0
#define CONNECTED_TO_NETWORK                1

static c3gaa_t c3gaa;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

static uint8_t app_connection_status        = WAIT_FOR_CONNECTION;

static err_t app_error_flag;

/**
 * @brief 3G-AA clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void c3gaa_clear_app_buf ( void );

/**
 * @brief 3G-AA data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c3gaa_process ( void );

/**
 * @brief 3G-AA check for errors.
 * @details This function checks for different types of errors and logs them on UART.
 * @note None.
 */
static void c3gaa_error_check( err_t error_flag );

/**
 * @brief 3G-AA logs application buffer.
 * @details This function logs data from application buffer.
 * @note None.
 */
static void c3gaa_log_app_buf ( void );

/**
 * @brief 3G-AA response check.
 * @details This function checks for response and returns the status of response.
 * 
 * @return application status.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c3gaa_rsp_check ( void );

/**
 * @brief 3G-AA check connection.
 * @details This function checks connection to the network and 
 *          logs that status to UART.
 * 
 * @note None.
 */
static void c3gaa_check_connection( void );

// ------------------------------------------------------ APPLICATION FUNCTIONS


void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3gaa_cfg_t c3gaa_cfg;  /**< Click config object. */

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

    c3gaa_cfg_setup( &c3gaa_cfg );
    C3GAA_MAP_MIKROBUS( c3gaa_cfg, MIKROBUS_1 );
    c3gaa_init( &c3gaa, &c3gaa_cfg );

    c3gaa_module_power( &c3gaa, C3GAA_MODULE_POWER_ON );
    
    // dummy read
    c3gaa_process( );
    c3gaa_clear_app_buf( );
    
    // AT
    c3gaa_send_cmd( &c3gaa, C3GAA_CMD_AT );
    app_error_flag = c3gaa_rsp_check( );
    c3gaa_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // ATI - product information
    c3gaa_send_cmd( &c3gaa, C3GAA_CMD_ATI );
    app_error_flag = c3gaa_rsp_check(  );
    c3gaa_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGMR - firmware version
    c3gaa_send_cmd( &c3gaa, C3GAA_CMD_CGMR );
    app_error_flag = c3gaa_rsp_check(  );
    c3gaa_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CMEE - Report Mobile Equipment Error
    c3gaa_send_cmd_with_parameter( &c3gaa, C3GAA_CMD_CMEE, "2" );
    app_error_flag = c3gaa_rsp_check(  );
    c3gaa_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - deregister from network
    c3gaa_send_cmd_with_parameter( &c3gaa, C3GAA_CMD_COPS, "2" );
    Delay_ms( 4000 );
    app_error_flag = c3gaa_rsp_check(  );
    c3gaa_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGDCONT - set sim apn
    c3gaa_set_sim_apn( &c3gaa, SIM_APN );
    app_error_flag = c3gaa_rsp_check(  );
    c3gaa_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CFUN - full funtionality
    c3gaa_send_cmd_with_parameter( &c3gaa, C3GAA_CMD_CFUN, "1" );
    app_error_flag = c3gaa_rsp_check(  );
    c3gaa_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - automatic mode
    c3gaa_send_cmd_with_parameter( &c3gaa, C3GAA_CMD_COPS, "0" );
    Delay_ms( 4000 );
    app_error_flag = c3gaa_rsp_check(  );
    c3gaa_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CREG - network registration status
    c3gaa_send_cmd_with_parameter( &c3gaa, C3GAA_CMD_CREG, "1" );
    app_error_flag = c3gaa_rsp_check(  );
    c3gaa_error_check( app_error_flag );
    Delay_ms( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task " );
    Delay_ms( 5000 );
}

void application_task ( void ) {
     if ( app_connection_status == WAIT_FOR_CONNECTION ) {
        // CREG - network registration status
        c3gaa_send_cmd_check( &c3gaa, C3GAA_CMD_CREG );
        app_error_flag = c3gaa_rsp_check(  );
        c3gaa_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CSQ - signal quality
        c3gaa_send_cmd( &c3gaa, C3GAA_CMD_CSQ );
        app_error_flag = c3gaa_rsp_check(  );
        c3gaa_error_check( app_error_flag );
        Delay_ms( 3000 );
    } else {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        // SMS message format - PDU mode
        c3gaa_send_cmd_with_parameter( &c3gaa, C3GAA_CMD_CMGF, "0" );
        app_error_flag = c3gaa_rsp_check(  );
        c3gaa_error_check( app_error_flag );
        Delay_ms( 3000 );
        
        for( ; ; ) {   
            log_printf( &logger, "> Sending message to phone number...\r\n" );
            c3gaa_send_sms_pdu ( &c3gaa, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
            app_error_flag = c3gaa_rsp_check(  );
            c3gaa_error_check( app_error_flag );
            Delay_ms( 10000 );
            Delay_ms( 10000 );
            Delay_ms( 10000 );
        }
    }
}

void main ( void )  {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

static void c3gaa_clear_app_buf ( void ) {
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t c3gaa_process ( void ) {
    err_t return_flag = APP_ERROR_DRIVER;
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };
    
    rx_size = c3gaa_generic_read( &c3gaa, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 ) { 
        int32_t buf_cnt = 0;
        return_flag = APP_OK;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE ) {
            c3gaa_clear_app_buf(  );
            return_flag = APP_ERROR_OVERFLOW;
        } else {
            buf_cnt = app_buf_len;
            app_buf_len += rx_size;
        }

        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) {
            if ( rx_buff[ rx_cnt ] != 0 ) {
                app_buf[ ( buf_cnt + rx_cnt ) ] = rx_buff[ rx_cnt ];
            } else {
                app_buf_len--;
                buf_cnt--;
            }
        }
    } 

    return return_flag;
}

static err_t c3gaa_rsp_check ( void ) {
    uint16_t timeout_cnt = 0;
    uint32_t timeout = 100000;
    
    err_t error_flag = c3gaa_process(  );
    
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) ) {
        return error_flag;
    }
    
    while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) ) {
        error_flag = c3gaa_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) ) {
            return error_flag;
        }
        
        timeout_cnt++;
        if ( timeout_cnt > timeout ) {
            while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) ) {
                c3gaa_send_cmd( &c3gaa, C3GAA_CMD_AT );
                c3gaa_process(  );
                Delay_ms( 100 );
            }
            c3gaa_clear_app_buf(  );
            return APP_ERROR_TIMEOUT;
        }
        
        Delay_ms( 1 );
    }
    
    c3gaa_check_connection();
    
    c3gaa_log_app_buf();
    
    return APP_OK;
}

static void c3gaa_error_check( err_t error_flag ) {
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) ) {
        switch ( error_flag ) {
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

static void c3gaa_log_app_buf ( void ) {
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ ) {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    log_printf( &logger, "\r\n-----------------------------------\r\n" );
    
    c3gaa_clear_app_buf(  );
}

static void c3gaa_check_connection( void ) {
    #define CONNECTED "+CREG: 1,1"
    
    if ( strstr( app_buf, CONNECTED ) != 0 ) {
        app_connection_status = CONNECTED_TO_NETWORK;
    }
}

// ------------------------------------------------------------------------ END
