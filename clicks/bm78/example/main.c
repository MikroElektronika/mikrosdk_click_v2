/*!
 * @file main.c
 * @brief BM78 Click Example.
 *
 * # Description
 * This example demonstrates the use of BM78 click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration by writing it into the EEPROM.
 *
 * ## Application Task
 * Reads and processes all incoming data from the Serial Bluetooth Terminal smartphone application and displays them on the USB UART.
 *
 * ## Additional Function
 * - static void bm78_clear_app_buf ( void )
 * - static void bm78_log_app_buf ( void )
 * - static err_t bm78_process ( bm78_t *ctx )                  
 *
 * @note
 * We have used the Serial Bluetooth Terminal smartphone application for the test. 
 * A smartphone and the click board must be paired in order to exchange messages with each other.
 *
 * @author Stefan Ilic
 *
 */     
            
#include "board.h"
#include "log.h"            
#include "bm78.h"

// Application buffer size
#define APP_BUFFER_SIZE             500
#define PROCESS_BUFFER_SIZE         200

static bm78_t bm78;
static log_t logger;

static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief BM78 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void bm78_clear_app_buf ( void );

/**
 * @brief BM78 log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void bm78_log_app_buf ( void );

/**
 * @brief BM78 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #bm78_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t bm78_process ( bm78_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    bm78_cfg_t bm78_cfg;  /**< Click config object. */

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
    bm78_cfg_setup( &bm78_cfg );
    BM78_MAP_MIKROBUS( bm78_cfg, MIKROBUS_1 );
    if ( UART_ERROR == bm78_init( &bm78, &bm78_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    uint8_t tmp_data[ 16 ];
    bm78_generic_read( &bm78, &tmp_data, 1 );  
    Delay_ms ( 100 );

    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    log_printf( &logger, " Place Click into Write EEPROM mode \r\n" );
    log_printf( &logger, " By setting MODE SEL in the following configuration \r\n" );
    log_printf( &logger, "         | 1 | 2 | 3 |             \r\n" );
    log_printf( &logger, "         | H | L | L |             \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    log_printf( &logger, " Send YES once you placed Click into Write EEPROM mode \r\n" );
    #define WANTED_ANSWER "YES/r/n"
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    while ( 1 )
    {
        log_read( &logger, &tmp_data, 5 );
        
        if ( 0 == strstr ( WANTED_ANSWER, tmp_data ) )
        {
            break;
        }
        else
        {
            log_printf( &logger, " Send YES once you placed Click into Write EEPROM mode \r\n" );
        }
    }
    bm78_hw_reset( &bm78 );
    log_printf( &logger, " Writing into the EEPROM \r\n" );
    if ( BM78_ERROR == bm78_flash_eeprom ( &bm78 ) )
    {
        log_error( &logger, " EEPROM Flash failed. " );
        log_printf( &logger, " Check Selected Click mode. \r\n" );
        for ( ; ; );
    }

    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    log_printf( &logger, " Place Click into Application mode \r\n" );
    log_printf( &logger, " By setting MODE SEL in the following configuration \r\n" );
    log_printf( &logger, "         | 1 | 2 | 3 |             \r\n" );
    log_printf( &logger, "         | L | L | L |             \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    log_printf( &logger, " Send YES once you placed Click into Application mode \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    while ( 1 )
    {
        log_read( &logger, &tmp_data, 5 );
        
        if ( 0 == strstr ( WANTED_ANSWER, tmp_data ) )
        {
            break;
        }
        else
        {
            log_printf( &logger, " Send YES once you placed Click into Application mode \r\n" );
        }
    }
    bm78_hw_reset( &bm78 );

    log_info( &logger, " Application Task " );
    log_printf( &logger, " Connect to the device using the Serial Bluetooth Terminal App \r\n\r\n" );
}

void application_task ( void ) 
{
    if ( BM78_OK == bm78_process( &bm78 ) ) 
    {
        bm78_log_app_buf( );
        bm78_clear_app_buf( );
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

static void bm78_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void bm78_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t bm78_process ( bm78_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = bm78_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return BM78_OK;
    }
    return BM78_ERROR;
}

// ------------------------------------------------------------------------ END
