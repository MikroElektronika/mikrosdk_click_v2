/*!
 * @file main.c
 * @brief 4G LTE-ATT Click Example.
 *
 * # Description
 * This example reads and processes data from 4G LTE-ATT Click.
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
 * - static void c4glteatt_clear_app_buf ( void )
 * - static void c4glteatt_error_check( err_t error_flag )
 * - static void c4glteatt_log_app_buf ( void )
 * - static void c4glteatt_check_connection( void )
 * - static err_t c4glteatt_rsp_check ( void )
 * - static err_t c4glteatt_process ( void )
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
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "c4glteatt.h"
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
#define MESSAGE_CONTENT                     "4G LTE-ATT Click board - demo example."   // Message content 

#define PROCESS_BUFFER_SIZE                 256

#define WAIT_FOR_CONNECTION                 0
#define CONNECTED_TO_NETWORK                1

static c4glteatt_t c4glteatt;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

static uint8_t app_connection_status        = WAIT_FOR_CONNECTION;

static err_t app_error_flag;

/**
 * @brief 4G LTE-ATT clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void c4glteatt_clear_app_buf ( void );

/**
 * @brief 4G LTE-ATT data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c4glteatt_process ( void );

/**
 * @brief 4G LTE-ATT check for errors.
 * @details This function checks for different types of errors and logs them on UART.
 * @note None.
 */
static void c4glteatt_error_check( err_t error_flag );

/**
 * @brief 4G LTE-ATT logs application buffer.
 * @details This function logs data from application buffer.
 * @note None.
 */
static void c4glteatt_log_app_buf ( void );

/**
 * @brief 4G LTE-ATT response check.
 * @details This function checks for response and returns the status of response.
 * 
 * @return application status.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t c4glteatt_rsp_check ( void );

/**
 * @brief 4G LTE-ATT check connection.
 * @details This function checks connection to the network and 
 *          logs that status to UART.
 * 
 * @note None.
 */
static void c4glteatt_check_connection( void );

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    c4glteatt_cfg_t c4glteatt_cfg;  /**< Click config object. */

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

    c4glteatt_cfg_setup( &c4glteatt_cfg );
    C4GLTEATT_MAP_MIKROBUS( c4glteatt_cfg, MIKROBUS_1 );
    c4glteatt_init( &c4glteatt, &c4glteatt_cfg );
    
    c4glteatt_module_power_on( &c4glteatt );
    
    // dummy read
    c4glteatt_process( );
    c4glteatt_clear_app_buf( );
    
    // AT
    c4glteatt_send_cmd( &c4glteatt, C4GLTEATT_CMD_AT );
    app_error_flag = c4glteatt_rsp_check( );
    c4glteatt_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // ATI - product information
    c4glteatt_send_cmd( &c4glteatt, C4GLTEATT_CMD_ATI );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGMR - firmware version
    c4glteatt_send_cmd( &c4glteatt, C4GLTEATT_CMD_CGMR );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CMEE - Report Mobile Equipment Error
    c4glteatt_send_cmd_with_parameter( &c4glteatt, C4GLTEATT_CMD_CMEE, "2" );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - deregister from network
    c4glteatt_send_cmd_with_parameter( &c4glteatt, C4GLTEATT_CMD_COPS, "2" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGDCONT - set sim apn
    c4glteatt_set_sim_apn( &c4glteatt, SIM_APN );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CFUN - full funtionality
    c4glteatt_send_cmd_with_parameter( &c4glteatt, C4GLTEATT_CMD_CFUN, "1" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - automatic mode
    c4glteatt_send_cmd_with_parameter( &c4glteatt, C4GLTEATT_CMD_COPS, "0" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CREG - network registration status
    c4glteatt_send_cmd_with_parameter( &c4glteatt, C4GLTEATT_CMD_CREG, "1" );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
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

void application_task ( void ) {
    if ( app_connection_status == WAIT_FOR_CONNECTION ) {
        // CREG - network registration status
        c4glteatt_send_cmd_check( &c4glteatt, C4GLTEATT_CMD_CREG );
        app_error_flag = c4glteatt_rsp_check(  );
        c4glteatt_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CSQ - signal quality
        c4glteatt_send_cmd( &c4glteatt, C4GLTEATT_CMD_CSQ );
        app_error_flag = c4glteatt_rsp_check(  );
        c4glteatt_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    } else {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        // SMS message format - PDU mode
        c4glteatt_send_cmd_with_parameter( &c4glteatt, C4GLTEATT_CMD_CMGF, "0" );
        app_error_flag = c4glteatt_rsp_check(  );
        c4glteatt_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        
        for( ; ; ) {   
            log_printf( &logger, "> Sending message to phone number...\r\n" );
            c4glteatt_send_sms_pdu ( &c4glteatt, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
            app_error_flag = c4glteatt_rsp_check(  );
            c4glteatt_error_check( app_error_flag );
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

static void c4glteatt_clear_app_buf ( void ) {
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t c4glteatt_process ( void ) {
    err_t return_flag = APP_ERROR_DRIVER;
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };
    
    rx_size = c4glteatt_generic_read( &c4glteatt, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 ) { 
        int32_t buf_cnt = 0;
        return_flag = APP_OK;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE ) {
            c4glteatt_clear_app_buf(  );
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

static err_t c4glteatt_rsp_check ( void ) {
    uint16_t timeout_cnt = 0;
    uint32_t timeout = 100000;
    
    err_t error_flag = c4glteatt_process(  );
    
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) ) {
        return error_flag;
    }
    
    while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) ) {
        error_flag = c4glteatt_process(  );
        if ( ( error_flag != 0 ) && ( error_flag != -1 ) ) {
            return error_flag;
        }
        
        timeout_cnt++;
        if ( timeout_cnt > timeout ) {
            while ( ( strstr( app_buf, RSP_OK ) == 0 ) && ( strstr( app_buf, RSP_ERROR ) == 0 ) ) {
                c4glteatt_send_cmd( &c4glteatt, C4GLTEATT_CMD_AT );
                c4glteatt_process(  );
                Delay_ms ( 100 );
            }
            c4glteatt_clear_app_buf(  );
            return APP_ERROR_TIMEOUT;
        }
        
        Delay_ms ( 1 );
    }
    
    c4glteatt_check_connection();
    
    c4glteatt_log_app_buf();
    
    return APP_OK;
}

static void c4glteatt_error_check( err_t error_flag ) {
    if ( ( error_flag != 0 ) && ( error_flag != -1 ) ) {
        switch ( error_flag ) {
            case -2: {
                log_error( &logger, " Overflow!" );
                break;
            }
            case -3: {
                log_error( &logger, " Timeout!" );
                break;
            }
            default: {
                break;
            }
        }
    }
}

static void c4glteatt_log_app_buf ( void ) {
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ ) {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
    log_printf( &logger, "\r\n-----------------------------------\r\n" );
    
    c4glteatt_clear_app_buf(  );
}

static void c4glteatt_check_connection( void ) {
    #define CONNECTED "+CREG: 1,1"
    
    if ( strstr( app_buf, CONNECTED ) != 0 ) {
        app_connection_status = CONNECTED_TO_NETWORK;
    }
}


// ------------------------------------------------------------------------ END
