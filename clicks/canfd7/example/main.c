/*!
 * @file main.c
 * @brief CAN FD 7 Click Example.
 *
 * # Description
 * This example writes and reads and processes data from CAN FD 7 Click.
 * The library also includes a function for selection of the output polarity.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * This example contains Transmitter/Receiver task depending on uncommented code.
 * Receiver logs each received byte to the UART for data logging,
 * while the transmitter sends messages every 2 seconds.
 *
 * ## Additional Function
 * - static err_t canfd7_process ( canfd7_t *ctx )
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "canfd7.h"

#define PROCESS_BUFFER_SIZE 200
#define TX_MESSAGE "CAN FD 7 Click \r\n"

// Comment out the line below in order to switch the application mode to receiver.
#define DEMO_APP_TRANSMITTER

static canfd7_t canfd7;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief CAN FD 7 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #canfd7_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t canfd7_process ( canfd7_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    canfd7_cfg_t canfd7_cfg;  /**< Click config object. */

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
    canfd7_cfg_setup( &canfd7_cfg );
    CANFD7_MAP_MIKROBUS( canfd7_cfg, MIKROBUS_1 );
    if ( UART_ERROR == canfd7_init( &canfd7, &canfd7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    canfd7_default_cfg ( &canfd7 );
    
#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- Transmitter mode ----" );
#else
    log_info( &logger, "---- Receiver mode ----" );
#endif 
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    canfd7_generic_write( &canfd7, TX_MESSAGE, strlen( TX_MESSAGE ) );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms( 2000 );
#else
    canfd7_process( &canfd7 );
#endif
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

static err_t canfd7_process ( canfd7_t *ctx ) 
{
    uint32_t rx_size;
    char rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    rx_size = canfd7_generic_read( &canfd7, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        log_printf( &logger, "%s", rx_buf );
        return CANFD7_OK;
    }
    return CANFD7_ERROR;
}

// ------------------------------------------------------------------------ END
