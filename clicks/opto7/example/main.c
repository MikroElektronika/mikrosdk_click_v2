/*!
 * @file main.c
 * @brief Opto 7 Click Example.
 *
 * # Description
 * This example demonstrates the use of Opto 7 click board by processing
 * the incoming data and displaying them on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of UART LOG and GPIO pin, and UART drivers.
 *
 * ## Application Task
 * This example is made of two parts:
 * GPIO Example - The output pin is toggled every 5 seconds and input pin state is being tracked.
 * UART Example - Device assigned as transmitter is sending message and receiver is reading it and displaying it on USB UART.
 * 
 * ## Additional Function
 * - static void opto7_clear_app_buf ( void )
 * - static void opto7_log_app_buf ( void )
 * - static err_t opto7_process ( opto7_t *ctx )
 * 
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "opto7.h"

// Example selection macros
#define EXAMPLE_GPIO                1               // Example of using GPIO
#define EXAMPLE_UART                2               // Example of using UART
#define DEMO_EXAMPLE                EXAMPLE_GPIO    // Example selection macro

// Macros for UART example
#define TRANSMITTER                 // Comment out this line to place device into receiver mode
#define TX_MESSAGE                  "Opto 7 Click Example \r\n"

// Application buffer size
#define APP_BUFFER_SIZE             500
#define PROCESS_BUFFER_SIZE         200

static opto7_t opto7;
static log_t logger;


static uint8_t app_buf[ APP_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief Test clearing application buffer.
 * @details This function clears memory of application buffer and reset its length.
 * @note None.
 */
static void opto7_clear_app_buf ( void );

/**
 * @brief Test log application buffer.
 * @details This function logs data from application buffer to USB UART.
 * @note None.
 */
static void opto7_log_app_buf ( void );

/**
 * @brief Test data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #opto7_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t opto7_process ( opto7_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    opto7_cfg_t opto7_cfg;  /**< Click config object. */

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
    opto7_cfg_setup( &opto7_cfg );
    OPTO7_MAP_MIKROBUS( opto7_cfg, MIKROBUS_1 );
    
#if ( DEMO_EXAMPLE == EXAMPLE_GPIO )
    opto7_drv_interface_selection( &opto7_cfg, OPTO7_DRV_SEL_GPIO );
#else
    opto7_drv_interface_selection( &opto7_cfg, OPTO7_DRV_SEL_UART );
#endif
    
    if ( UART_ERROR == opto7_init( &opto7, &opto7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#if ( DEMO_EXAMPLE == EXAMPLE_GPIO )
    log_printf( &logger, " GP1 pin state HIGH \r\n" );
    opto7_set_gp1_pin( &opto7, OPTO7_PIN_STATE_HIGH );
     if ( OPTO7_PIN_STATE_HIGH == opto7_get_gp2_pin( &opto7 ) )
    {
        log_printf( &logger, " GP2 pin state HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " GP2 pin state LOW \r\n" );
    }
    log_printf( &logger, "- - - - - - - - - - - -\r\n" );
    Delay_ms( 5000 );
    
    log_printf( &logger, " GP1 pin state LOW \r\n" );
    opto7_set_gp1_pin( &opto7, OPTO7_PIN_STATE_LOW );
    if ( OPTO7_PIN_STATE_HIGH == opto7_get_gp2_pin( &opto7 ) )
    {
        log_printf( &logger, " GP2 pin state HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " GP2 pin state LOW \r\n" );
    }
    log_printf( &logger, "- - - - - - - - - - - -\r\n" );
    Delay_ms( 5000 );
#else
#if defined TRANSMITTER
    log_printf( &logger, " Message sent! \r\n" );
    opto7_generic_write( &opto7, TX_MESSAGE, strlen( TX_MESSAGE ) );
    Delay_ms( 2000 );
#else
    if ( OPTO7_OK == opto7_process( &opto7 ) ) 
    {
        opto7_log_app_buf( );
        opto7_clear_app_buf( );
    }
#endif

#endif
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

static void opto7_clear_app_buf ( void ) 
{
    memset( app_buf, 0, app_buf_len );
    app_buf_len = 0;
}

static void opto7_log_app_buf ( void )
{
    for ( int32_t buf_cnt = 0; buf_cnt < app_buf_len; buf_cnt++ )
    {
        log_printf( &logger, "%c", app_buf[ buf_cnt ] );
    }
}

static err_t opto7_process ( opto7_t *ctx ) 
{
    uint8_t rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    int32_t overflow_bytes = 0;
    int32_t rx_cnt = 0;
    int32_t rx_size = opto7_generic_read( ctx, rx_buf, PROCESS_BUFFER_SIZE );
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
        return OPTO7_OK;
    }
    return OPTO7_ERROR;
}

// ------------------------------------------------------------------------ END
