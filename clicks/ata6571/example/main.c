/*!
 * @file main.c
 * @brief ATA6571 Click Example.
 *
 * # Description
 * This example reads and processes data from ATA6571 Clicks.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and sets the device operating mode.
 *
 * ## Application Task
 * Depending on the selected demo application mode, it reads all the received data or 
 * sends the desired message every 2 seconds.
 *
 * ## Additional Function
 * - static void ata6571_clear_app_buf ( void )
 * - static err_t ata6571_process ( void )
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ata6571.h"

#define PROCESS_BUFFER_SIZE 200

/*** Demo application mode selection, only one mode should be selected at the same time ***/
#define DEMO_APP_RECEIVER
// #define DEMO_APP_TRANSMITTER

#define TEXT_TO_SEND           "MikroE - ATA6571 Click board\r\n"

static ata6571_t ata6571;
static log_t logger;

static char app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;
static int32_t app_buf_cnt = 0;

/**
 * @brief ATA6571 clearing application buffer.
 * @details This function clears memory of application buffer and reset it's length and counter.
 * @note None.
 */
static void ata6571_clear_app_buf ( void );

/**
 * @brief ATA6571 data reading function.
 * @details This function reads data from device and concatenates data to application buffer.
 *
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 *         @li @c -2 - Application buffer overflow.
 *
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t ata6571_process ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    ata6571_cfg_t ata6571_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    ata6571_cfg_setup( &ata6571_cfg );
    ATA6571_MAP_MIKROBUS( ata6571_cfg, MIKROBUS_1 );
    err_t init_flag = ata6571_init( &ata6571, &ata6571_cfg );
    if ( UART_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    
#ifdef DEMO_APP_RECEIVER
    log_printf( &logger, "---- RECEIVER MODE ----\r\n" );
#endif 
#ifdef DEMO_APP_TRANSMITTER
    log_printf( &logger, "---- TRANSMITTER MODE ----\r\n" );
#endif 
    
    ata6571_set_operating_mode ( &ata6571, ATA6571_OPERATING_MODE_NORMAL );
    app_buf_len = 0;
    app_buf_cnt = 0;

    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
#ifdef DEMO_APP_RECEIVER
    ata6571_process();

    if ( app_buf_len > 0 ) 
    {
        Delay_ms ( 100 );
        ata6571_process();
        
        log_printf( &logger, "%s", app_buf );
        log_printf( &logger, "-------------------------------------\r\n" );
        ata6571_clear_app_buf(  );
    }
#endif  

#ifdef DEMO_APP_TRANSMITTER 
    ata6571_generic_write( &ata6571, TEXT_TO_SEND, strlen( TEXT_TO_SEND ) );
    log_printf( &logger, "---- The message has been sent ----\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#endif
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

static void ata6571_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
    app_buf_cnt = 0;
}

static err_t ata6571_process ( void ) 
{
    int32_t rx_size;
    char rx_buff[ PROCESS_BUFFER_SIZE ] = { 0 };

    rx_size = ata6571_generic_read( &ata6571, rx_buff, PROCESS_BUFFER_SIZE );

    if ( rx_size > 0 ) 
    {
        int32_t buf_cnt = 0;

        if ( app_buf_len + rx_size >= PROCESS_BUFFER_SIZE ) 
        {
            ata6571_clear_app_buf(  );
            return ATA6571_ERROR;
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
        return ATA6571_OK;
    }
    return ATA6571_ERROR;
}

// ------------------------------------------------------------------------ END
