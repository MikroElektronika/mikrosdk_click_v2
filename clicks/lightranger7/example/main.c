/*!
 * @file main.c
 * @brief LightRanger 7 Click Example.
 *
 * # Description
 * This example demonstrates the use of LightRanger 7 Click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads and processes all incoming data and displays them on the USB UART.
 * 
 * @note 
 * By default, the Click board is programmed with the AFBR_S50_Example_RA4M2 firmware.
 * At the beginning this FW returns API version, chip ID, and module version. After that
 * it starts the measurements and prints the recent measurement results that consists of:
 *  1. Time stamp in seconds since the last MCU reset.
 *  2. Range in mm (converting the Q9.22 value to mm).
 *  3. Amplitude in LSB (converting the UQ12.4 value to LSB).
 *  4. Signal Quality in % (100% = good signal).
 *  5. Status (0: OK; < 0: Error; > 0: Warning.
 * For more information refer to the AFBR-S50 GitHub repository: 
 * https://github.com/Broadcom/AFBR-S50-API
 *
 * ## Additional Function
 * - static void lightranger7_clear_app_buf ( void )
 * - static err_t lightranger7_process ( lightranger7_t *ctx )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "lightranger7.h"

#define PROCESS_BUFFER_SIZE 200

static lightranger7_t lightranger7;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief LightRanger 7 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void lightranger7_clear_app_buf ( void );

/**
 * @brief LightRanger 7 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #lightranger7_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t lightranger7_process ( lightranger7_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lightranger7_cfg_t lightranger7_cfg;  /**< Click config object. */

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
    lightranger7_cfg_setup( &lightranger7_cfg );
    LIGHTRANGER7_MAP_MIKROBUS( lightranger7_cfg, MIKROBUS_1 );
    if ( UART_ERROR == lightranger7_init( &lightranger7, &lightranger7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    log_printf( &logger, " Reset device\r\n" );
    lightranger7_reset_device ( &lightranger7 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    lightranger7_process( &lightranger7 );
    if ( app_buf_len > 0 ) 
    {
        log_printf( &logger, "%s", app_buf );
        lightranger7_clear_app_buf( );
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

static void lightranger7_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t lightranger7_process ( lightranger7_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    rx_size = lightranger7_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = app_buf_len;
        if ( ( ( app_buf_len + rx_size ) > PROCESS_BUFFER_SIZE ) && ( app_buf_len > 0 ) ) 
        {
            buf_cnt = PROCESS_BUFFER_SIZE - ( ( app_buf_len + rx_size ) - PROCESS_BUFFER_SIZE );
            memmove ( app_buf, &app_buf[ PROCESS_BUFFER_SIZE - buf_cnt ], buf_cnt );
        }
        for ( int32_t rx_cnt = 0; rx_cnt < rx_size; rx_cnt++ ) 
        {
            if ( rx_buf[ rx_cnt ] ) 
            {
                app_buf[ buf_cnt++ ] = rx_buf[ rx_cnt ];
                if ( app_buf_len < PROCESS_BUFFER_SIZE )
                {
                    app_buf_len++;
                }
            }
        }
        return LIGHTRANGER7_OK;
    }
    return LIGHTRANGER7_ERROR;
}

// ------------------------------------------------------------------------ END
