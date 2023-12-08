/*!
 * @file main.c
 * @brief Heart Rate 9 Click Example.
 *
 * # Description
 * This example reads and processes data from Heart Rate 9 clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes driver and wake-up module.
 *
 * ## Application Task
 * Reads the received data and logs it.
 *
 * ## Additional Function
 * - static void heartrate9_clear_app_buf ( void ) - Function clears memory of app_buf.
 * - static err_t heartrate9_process ( void ) - The general process of collecting data the module sends.
 *
 * @note
 * Data structure is:
 *  > AA;BB;CC;DD;EE; <
 * 
 *  > AA -> Data header.
 *  > BB -> Red diode.
 *  > CC -> IR diode.
 *  > DD -> Green diode.
 *  > EE -> BPM.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "heartrate9.h"

#define PROCESS_BUFFER_SIZE 200

static heartrate9_t heartrate9;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

/**
 * @brief Heart Rate 9 clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void heartrate9_clear_app_buf ( void );

/**
 * @brief Heart Rate 9 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t heartrate9_process ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate9_cfg_t heartrate9_cfg;  /**< Click config object. */

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

    // Click initialization.
    heartrate9_cfg_setup( &heartrate9_cfg );
    HEARTRATE9_MAP_MIKROBUS( heartrate9_cfg, MIKROBUS_1 );
    err_t init_flag  = heartrate9_init( &heartrate9, &heartrate9_cfg );
    if ( init_flag == UART_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    app_buf_len = 0;
    app_buf_cnt = 0;
}

void application_task ( void )
{
   heartrate9_process();

    if ( app_buf_len > 0 )
    {
        log_printf( &logger, "%s", app_buf );
        heartrate9_clear_app_buf(  );
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

static void heartrate9_clear_app_buf ( void )
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t heartrate9_process ( void )
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = heartrate9_generic_read( &heartrate9, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 )
    {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE )
        {
           heartrate9_clear_app_buf(  );
            return -2;
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
        return 0;
    }
    return -1;
}

// ------------------------------------------------------------------------ END
