/*!
 * @file main.c
 * @brief DIGI IN 2 Click example
 *
 * # Description
 * This example demonstrates the use of DIGI IN 2 Click board by reading and
 * displaying the state of the channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the click default configuration.
 *
 * ## Application Task
 * Reads and displays on the USB UART the channel state every second.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "digiin2.h"

static digiin2_t digiin2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digiin2_cfg_t digiin2_cfg;  /**< Click config object. */

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
    digiin2_cfg_setup( &digiin2_cfg );
    DIGIIN2_MAP_MIKROBUS( digiin2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == digiin2_init( &digiin2, &digiin2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIIN2_ERROR == digiin2_default_cfg ( &digiin2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{    
    uint8_t channel_data = 0;

    digiin2_pulse_latch( &digiin2 );

    if ( DIGIIN2_OK == digiin2_read_reg( &digiin2, DIGIIN2_REG_DISTATE, &channel_data ) )
    {
        if ( channel_data & DIGIIN2_CHANNEL_1_MASK )
        {
            log_printf( &logger, "Channel 1 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 1 counter: LOW \r\n" );
        }
        if ( channel_data & DIGIIN2_CHANNEL_2_MASK )
        {
            log_printf( &logger, "Channel 2 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 2 counter: LOW \r\n" );
        }
        if ( channel_data & DIGIIN2_CHANNEL_3_MASK )
        {
            log_printf( &logger, "Channel 3 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 3 counter: LOW \r\n" );
        }
        if ( channel_data & DIGIIN2_CHANNEL_4_MASK )
        {
            log_printf( &logger, "Channel 4 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 4 counter: LOW \r\n" );
        }
        if ( channel_data & DIGIIN2_CHANNEL_5_MASK )
        {
            log_printf( &logger, "Channel 5 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 5 counter: LOW \r\n" );
        }
        if ( channel_data & DIGIIN2_CHANNEL_6_MASK )
        {
            log_printf( &logger, "Channel 6 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 6 counter: LOW \r\n" );
        }
        if ( channel_data & DIGIIN2_CHANNEL_7_MASK )
        {
            log_printf( &logger, "Channel 7 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 7 counter: LOW \r\n" );
        }
        if ( channel_data & DIGIIN2_CHANNEL_8_MASK )
        {
            log_printf( &logger, "Channel 8 counter: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 8 counter: LOW \r\n" );
        }
        log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    }
    else
    {
        log_error( &logger, " Read error." );
    }
    
    if ( DIGIIN2_PIN_STATE_HIGH == digiin2_get_flt_pin( &digiin2 ) )
    {
        uint8_t flt_data = 0;
        digiin2_read_reg( &digiin2, DIGIIN2_REG_FAULT, &flt_data );
        log_printf( &logger, "Fault1 data: 0x%.2X \r\n", ( uint16_t ) flt_data );
        digiin2_read_reg( &digiin2, DIGIIN2_REG_FAULT2, &flt_data );
        log_printf( &logger, "Fault2 data: 0x%.2X \r\n", ( uint16_t ) flt_data );
        log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    }

    Delay_ms ( 1000 );
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

// ------------------------------------------------------------------------ END
