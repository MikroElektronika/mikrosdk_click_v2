/*!
 * @file main.c
 * @brief M-BUS RF 2 Click Example.
 *
 * # Description
 * This example demonstrates the use of M-BUS RF 2 Click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click configuration depending on selected DEMO_EXAMPLE macro.
 *
 * ## Application Task
 * This example contains two examples depending on selected DEMO_EXAMPLE macro:
 * EXAMPLE_TRANSMIT - Device is sending MESSAGE data to be read by receiver.
 * EXAMPLE_RECEIVER - Device is reading transmitted message, and display it on USB UART terminal.
 *
 * ## Additional Function
 * - static void mbusrf2_clear_app_buf ( void )
 * - static void mbusrf2_log_app_buf ( void )
 * - static err_t mbusrf2_process ( mbusrf2_t *ctx )
 * - static err_t mbusrf2_rsp_check ( uint8_t cmd )
 * - static void mbusrf2_error_check ( err_t error_flag )
 * - static void mbusrf2_configure_for_example ( void )
 * - static void mbusrf2_example ( void )
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "mbusrf2.h"

// Example selection macros
#define EXAMPLE_TRANSMIT                    0                // Transmit example
#define EXAMPLE_RECEIVER                    1                // Reciver example
#define DEMO_EXAMPLE                        EXAMPLE_RECEIVER // Example selection macro

// Mode selection macros
#define WM_BUS_MODE_S                       0
#define WM_BUS_MODE_T                       1
#define WM_BUS_MODE                         WM_BUS_MODE_S

// Message to be sent
#define MESSAGE                             "M-BUS RF 2 Click"

// Application buffer size
#define APP_BUFFER_SIZE                     500
#define PROCESS_BUFFER_SIZE                 200

static mbusrf2_t mbusrf2;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static err_t error_flag;

/**
 * @brief M-BUS RF 2 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void mbusrf2_clear_app_buf ( void );

/**
 * @brief M-BUS RF 2 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void mbusrf2_log_app_buf ( void );

/**
 * @brief M-BUS RF 2 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #mbusrf2_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t mbusrf2_process ( void );

/**
 * @brief Response check.
 * @details This function checks for response and
 * returns the status of response.
 * @param[in] rsp  Expected response.
 * @return @li @c  0 - OK response.
 *         @li @c -1 - Error response.
 *         @li @c -2 - Timeout error.
  * See #err_t definition for detailed explanation.
 */
static err_t mbusrf2_rsp_check ( uint8_t cmd );

/**
 * @brief Check for errors.
 * @details This function checks for different types of
 * errors and logs them on UART or logs the response if no errors occured.
 * @param[in] error_flag  Error flag to check.
 */
static void mbusrf2_error_check ( err_t error_flag );

/**
 * @brief M-BUS RF 2 configure for example function.
 * @details This function is used to configure device for example.
 */
static void mbusrf2_configure_for_example ( void );

/**
 * @brief M-BUS RF 2 execute example function.
 * @details This function executes transmitter or receiver example depending on the DEMO_EXAMPLE macro.
 */
static void mbusrf2_example ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mbusrf2_cfg_t mbusrf2_cfg;  /**< Click config object. */

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
    mbusrf2_cfg_setup( &mbusrf2_cfg );
    MBUSRF2_MAP_MIKROBUS( mbusrf2_cfg, MIKROBUS_1 );
    if ( UART_ERROR == mbusrf2_init( &mbusrf2, &mbusrf2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    mbusrf2_process( );
    mbusrf2_clear_app_buf( );
    Delay_ms ( 500 );
   
    mbusrf2_configure_for_example( );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    mbusrf2_example( );
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

static void mbusrf2_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void mbusrf2_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t mbusrf2_process ( void ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = mbusrf2_generic_read( &mbusrf2, rx_buf, PROCESS_BUFFER_SIZE );
    if ( ( rx_size > 0 ) && ( rx_size <= APP_BUFFER_SIZE ) ) 
    {
        if ( ( app_buf_len + rx_size ) > APP_BUFFER_SIZE ) 
        {
            overflow_bytes = ( app_buf_len + rx_size ) - APP_BUFFER_SIZE;
            app_buf_len = APP_BUFFER_SIZE - rx_size;
            memmove ( app_buf, &app_buf[ overflow_bytes ], app_buf_len );
            memset ( &app_buf[ app_buf_len ], 0, overflow_bytes );
        }
        for ( rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ app_buf_len++ ] = rx_buf[ rx_cnt ];
            }
        }
        return MBUSRF2_OK;
    }
    return MBUSRF2_ERROR;
}

static err_t mbusrf2_rsp_check ( uint8_t cmd )
{
    err_t error_flag = MBUSRF2_OK;
    uint32_t timeout_cnt = 0;
    uint32_t timeout = 120000;
    Delay_ms ( 100 );
    mbusrf2_clear_app_buf( );
    error_flag |= mbusrf2_process( );
    while ( MBUSRF2_OK != error_flag )
    {
        error_flag |= mbusrf2_process( );
        if ( timeout_cnt++ > timeout )
        {
            mbusrf2_clear_app_buf( );
            return MBUSRF2_ERROR_TIMEOUT;
        }
        Delay_ms ( 1 );
    }
    mbusrf2_process( );
    Delay_ms ( 100 );
    if ( ( cmd | MBUSRF2_CMD_RESPONSE ) == app_buf[ 1 ] )
    {
        return MBUSRF2_OK;
    }
    else
    {
        return MBUSRF2_ERROR;
    }
}

static void mbusrf2_error_check ( err_t error_flag )
{
    switch ( error_flag )
    {
        case MBUSRF2_OK:
        {
            log_printf( &logger, " OK \r\n" );

            break;
        }
        case MBUSRF2_ERROR:
        {
            log_error( &logger, " ERROR!" );
            break;
        }
        case MBUSRF2_ERROR_TIMEOUT:
        {
            log_error( &logger, " Timeout!" );
            break;
        }
    }
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    Delay_ms ( 500 );
}

static void mbusrf2_configure_for_example ( void )
{
    uint8_t tx_data[ 3 ] = { 0 };

#if ( EXAMPLE_TRANSMIT == DEMO_EXAMPLE )
    log_printf( &logger, "Factory reset \r\n" );
    mbusrf2_send_command( &mbusrf2, MBUSRF2_CMD_FACTORYRESET_REQ, 0, 0 );
    error_flag = mbusrf2_rsp_check( MBUSRF2_CMD_FACTORYRESET_REQ );
    mbusrf2_error_check( error_flag );

    log_printf( &logger, "Reset device \r\n" );
    mbusrf2_send_command( &mbusrf2, MBUSRF2_CMD_RESET_REQ, 0, 0 );
    error_flag = mbusrf2_rsp_check( MBUSRF2_CMD_RESET_REQ );
    mbusrf2_error_check( error_flag );

    #define MODE_MEMORY_INDEX       0x46
    #define SET_MODE_LENGTH         0x01
#if ( WM_BUS_MODE_S == WM_BUS_MODE )
    log_printf( &logger, "Set mode S1-m \r\n" );
    #define S1_METER_ROLE           0x02
    tx_data[ 0 ] = MODE_MEMORY_INDEX;
    tx_data[ 1 ] = SET_MODE_LENGTH;
    tx_data[ 2 ] = S1_METER_ROLE;
    mbusrf2_send_command( &mbusrf2, MBUSRF2_CMD_SET_REQ, tx_data, 3 );
    error_flag = mbusrf2_rsp_check( MBUSRF2_CMD_SET_REQ );
    mbusrf2_error_check( error_flag );

#elif ( WM_BUS_MODE_T == WM_BUS_MODE )
    log_printf( &logger, "Set mode T1-meter \r\n" );
    #define T1_METER_ROLE           0x05
    tx_data[ 0 ] = MODE_MEMORY_INDEX;
    tx_data[ 1 ] = SET_MODE_LENGTH;
    tx_data[ 2 ] = T1_METER_ROLE;
    mbusrf2_send_command( &mbusrf2, MBUSRF2_CMD_SET_REQ, tx_data, 3 );
    error_flag = mbusrf2_rsp_check( MBUSRF2_CMD_SET_REQ );
    mbusrf2_error_check( error_flag );

#endif
    log_printf( &logger, "Reset device \r\n" );
    mbusrf2_send_command( &mbusrf2, MBUSRF2_CMD_RESET_REQ, 0, 0 );
    error_flag = mbusrf2_rsp_check( MBUSRF2_CMD_RESET_REQ );
    mbusrf2_error_check( error_flag );

#elif ( EXAMPLE_RECEIVER == DEMO_EXAMPLE ) 
    log_printf( &logger, "Factory reset \r\n" );
    mbusrf2_send_command( &mbusrf2, MBUSRF2_CMD_FACTORYRESET_REQ, 0, 0 );
    error_flag = mbusrf2_rsp_check( MBUSRF2_CMD_FACTORYRESET_REQ );
    mbusrf2_error_check( error_flag );

    log_printf( &logger, "Reset device \r\n" );
    mbusrf2_send_command( &mbusrf2, MBUSRF2_CMD_RESET_REQ, 0, 0 );
    error_flag = mbusrf2_rsp_check( MBUSRF2_CMD_RESET_REQ );
    mbusrf2_error_check( error_flag );

    #define EN_CMD_OUT_MEM_INDEX    0x05
    #define EN_CMD_OUT_LENGTH       0x01
    #define EN_CMD_OUT              0x01

    tx_data[ 0 ] = EN_CMD_OUT_MEM_INDEX;
    tx_data[ 1 ] = EN_CMD_OUT_LENGTH;
    tx_data[ 2 ] = EN_CMD_OUT;
    log_printf( &logger, "Enable command output \r\n" );
    mbusrf2_send_command( &mbusrf2, MBUSRF2_CMD_SET_REQ, tx_data, 3 );
    error_flag = mbusrf2_rsp_check( MBUSRF2_CMD_SET_REQ );
    mbusrf2_error_check( error_flag );

    #define MODE_MEMORY_INDEX       0x46
    #define SET_MODE_LENGTH         0x01

#if ( WM_BUS_MODE_S == WM_BUS_MODE )
    log_printf( &logger, "Set mode S2 \r\n" );
    #define S2_ROLE                 0x03
    tx_data[ 0 ] = MODE_MEMORY_INDEX;
    tx_data[ 1 ] = SET_MODE_LENGTH;
    tx_data[ 2 ] = S2_ROLE;
    mbusrf2_send_command( &mbusrf2, MBUSRF2_CMD_SET_REQ, tx_data, 3 );
    error_flag = mbusrf2_rsp_check( MBUSRF2_CMD_SET_REQ );
    mbusrf2_error_check( error_flag );

#elif ( ( WM_BUS_MODE_C == WM_BUS_MODE ) || ( WM_BUS_MODE_T == WM_BUS_MODE ) )
    log_printf( &logger, "Set mode C2 T2 mode \r\n" );
    #define C2_T2_MODE              0x09
    tx_data[ 0 ] = MODE_MEMORY_INDEX;
    tx_data[ 1 ] = SET_MODE_LENGTH;
    tx_data[ 2 ] = C2_T2_MODE;
    mbusrf2_send_command( &mbusrf2, MBUSRF2_CMD_SET_REQ, tx_data, 3 );
    error_flag = mbusrf2_rsp_check( MBUSRF2_CMD_SET_REQ );
    mbusrf2_error_check( error_flag );

#endif
    log_printf( &logger, "Reset device \r\n" );
    mbusrf2_send_command( &mbusrf2, MBUSRF2_CMD_RESET_REQ, 0, 0 );
    error_flag = mbusrf2_rsp_check( MBUSRF2_CMD_RESET_REQ );

#else
    #error "No demo example selected"
#endif
}

static void mbusrf2_example ( void )
{
#if ( ( EXAMPLE_TRANSMIT == DEMO_EXAMPLE ) )
    log_printf( &logger, "Send message \r\n" );
    mbusrf2_send_data( &mbusrf2, MESSAGE, strlen( MESSAGE ) );
    error_flag = mbusrf2_rsp_check( MBUSRF2_CMD_DATA_REQ );
    mbusrf2_error_check( error_flag );
    Delay_ms ( 1000 );

#elif ( EXAMPLE_RECEIVER == DEMO_EXAMPLE ) 
    if ( MBUSRF2_OK == mbusrf2_process( ) ) 
    {
        Delay_ms ( 100 );
        for ( uint8_t buf_cnt = 0; buf_cnt < app_buf[ 2 ]; buf_cnt++ )
        {
            log_printf( &logger, "%c", app_buf[ buf_cnt + 2 ] );
        }
        log_printf( &logger, "\r\n" );
        mbusrf2_clear_app_buf( );
    }
    
#else
    #error "No demo example selected"
#endif
}

// ------------------------------------------------------------------------ END
