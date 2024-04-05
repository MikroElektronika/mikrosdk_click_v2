/*!
 * @file main.c
 * @brief CAN Isolator 3 Click Example.
 *
 * # Description
 * This example writes and reads and processes data from CAN Isolator 3 Click.
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
 * - static err_t canisolator3_process ( canisolator3_t *ctx )
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "canisolator3.h"

#define PROCESS_BUFFER_SIZE 200
#define TX_MESSAGE "CAN Isolator 3 Click \r\n"

// Comment out the line below in order to switch the application mode to receiver.
#define DEMO_APP_TRANSMITTER

static canisolator3_t canisolator3;
static log_t logger;

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief CAN Isolator 3 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #canisolator3_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t canisolator3_process ( canisolator3_t *ctx );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    canisolator3_cfg_t canisolator3_cfg;  /**< Click config object. */

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
    canisolator3_cfg_setup( &canisolator3_cfg );
    CANISOLATOR3_MAP_MIKROBUS( canisolator3_cfg, MIKROBUS_1 );
    if ( UART_ERROR == canisolator3_init( &canisolator3, &canisolator3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    canisolator3_default_cfg ( &canisolator3 );
    
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
    canisolator3_generic_write( &canisolator3, TX_MESSAGE, strlen( TX_MESSAGE ) );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    canisolator3_process( &canisolator3 );
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

static err_t canisolator3_process ( canisolator3_t *ctx ) 
{
    uint32_t rx_size;
    char rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    rx_size = canisolator3_generic_read( &canisolator3, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        log_printf( &logger, "%s", rx_buf );
        return CANISOLATOR3_OK;
    }
    return CANISOLATOR3_ERROR;
}

// ------------------------------------------------------------------------ END
