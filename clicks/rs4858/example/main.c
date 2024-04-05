/*!
 * @file main.c
 * @brief RS485 8 Click Example.
 *
 * # Description
 * This example reads and processes data from RS485 8 clicks.
 * The library also includes a function for enabling/disabling 
 * the receiver or driver and data writing or reading.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the RS485 8 Click board.
 * The app sends a "MikroE" message, reads the received data and parses it.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * ## Additional Function
 * - static err_t rs4858_process ( void )
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "rs4858.h"

#define PROCESS_BUFFER_SIZE 200

// Comment out the line below in order to switch the application mode to receiver.
#define DEMO_APP_TRANSMITTER

static rs4858_t rs4858;
static log_t logger;

uint8_t data_buf[ 8 ] = { 'M', 'i', 'k', 'r', 'o', 'E', '\r', '\n' };

static uint8_t app_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
static int32_t app_buf_len = 0;

/**
 * @brief RS485 8 data reading function.
 * @details This function reads data from device and concatenates data to application buffer. 
 * @param[in] ctx : Click context object.
 * See #rs4858_t object definition for detailed explanation.
 * @return @li @c  0 - Read some data.
 *         @li @c -1 - Nothing is read.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
static err_t rs4858_process ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rs4858_cfg_t rs4858_cfg;  /**< Click config object. */

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
    rs4858_cfg_setup( &rs4858_cfg );
    RS4858_MAP_MIKROBUS( rs4858_cfg, MIKROBUS_2 );
    if ( UART_ERROR == rs4858_init( &rs4858, &rs4858_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    rs4858_default_cfg ( &rs4858 );
    
#ifdef DEMO_APP_TRANSMITTER
    log_info( &logger, "---- Transmitter mode ----" );
#else
    log_info( &logger, "---- Receiver mode ----" );
#endif 
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
#ifdef DEMO_APP_TRANSMITTER
    rs4858_generic_write( &rs4858, data_buf, strlen( data_buf ) );
    log_info( &logger, "---- Data sent ----" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
#else
    rs4858_process( );
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

static err_t rs4858_process ( void ) 
{
    int32_t rx_size;
    char rx_buf[ PROCESS_BUFFER_SIZE ] = { 0 };
    rx_size = rs4858_generic_read( &rs4858, rx_buf, PROCESS_BUFFER_SIZE );
    if ( rx_size > 0 ) 
    {
        log_printf( &logger, "%s", rx_buf );
        return RS4858_OK;
    }
    return RS4858_ERROR;
}

// ------------------------------------------------------------------------ END
