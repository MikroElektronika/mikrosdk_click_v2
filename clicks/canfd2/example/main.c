/*!
 * \file 
 * \brief CanFd2 Click example
 * 
 * # Description
 * This example reads and processes data from CAN FD 2 clicks.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and configures the Click board for the selected mode.
 * 
 * ## Application Task  
 * Depending on the selected mode, it reads all the received data or sends the desired message
 * every 2 seconds.
 * 
 * ## Additional Function
 * - static void canfd2_clear_app_buf ( void )
 * - static err_t canfd2_process ( canfd2_t *ctx )
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "canfd2.h"
#include "string.h"

// Comment out the line below in order to switch the application mode to receiver
#define DEMO_APP_TRANSMITTER

// Text message to send in the transmitter application mode
#define DEMO_TEXT_MESSAGE           "MIKROE - CAN FD 2 Click board\r\n\0"

#define PROCESS_BUFFER_SIZE 200

static canfd2_t canfd2;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief CAN FD 2 clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void canfd2_clear_app_buf ( void );

/**
 * @brief CAN FD 2 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #canfd2_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t canfd2_process ( canfd2_t *ctx );

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    canfd2_cfg_t cfg;

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

    canfd2_cfg_setup( &cfg );
    CANFD2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    canfd2_init( &canfd2, &cfg );
    
    CANFD2_SET_DATA_SAMPLE_EDGE;
    Delay_ms ( 100 );
    
#ifdef DEMO_APP_TRANSMITTER
    canfd2_set_mode( &canfd2, CANFD2_OP_MODE_NORMAL );
    if ( CANFD2_OP_MODE_NORMAL == canfd2_get_mode ( &canfd2 ) )
    {
        log_info( &logger, "--- TRANSMITTER MODE ---" );
    }
    else
    {
        log_info( &logger, "--- ERROR ---" );
        log_printf( &logger, "Please restart your system.\r\n" );
        for ( ; ; );
    }
#else
    canfd2_set_mode( &canfd2, CANFD2_OP_MODE_RECEIVE_ONLY );
    if ( CANFD2_OP_MODE_RECEIVE_ONLY == canfd2_get_mode ( &canfd2 ) )
    {
        log_info( &logger, "--- RECEIVER MODE ---" );
    }
    else
    {
        log_info( &logger, "--- ERROR ---" );
        log_printf( &logger, "Please restart your system.\r\n" );
        for ( ; ; );
    }
#endif
    Delay_ms ( 100 );
}

void application_task ( void )
{
#ifdef DEMO_APP_TRANSMITTER
    canfd2_generic_write( &canfd2, DEMO_TEXT_MESSAGE, strlen ( DEMO_TEXT_MESSAGE ) );
    log_info( &logger, "--- The message is sent ---" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    canfd2_process( &canfd2 );
    if ( app_buf_len > 0 ) 
    {
        Delay_ms ( 100 );
        canfd2_process ( &canfd2 );
        log_printf( &logger, "Received data: %s", app_buf );
        canfd2_clear_app_buf( );
    }
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

static void canfd2_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static err_t canfd2_process ( canfd2_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t rx_size = 0;
    rx_size = canfd2_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return CANFD2_OK;
    }
    return CANFD2_ERROR;
}

// ------------------------------------------------------------------------ END
