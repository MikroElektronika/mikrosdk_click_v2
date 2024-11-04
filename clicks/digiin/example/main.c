/*!
 * @file main.c
 * @brief DIGI IN Click example
 *
 * # Description
 * This example demonstrates the use of DIGI IN Click board by reading and
 * displaying the state of the channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, performs the Click default configuration.
 *
 * ## Application Task
 * Reads and displays on the USB UART the channel state every second.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "digiin.h"

static digiin_t digiin;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digiin_cfg_t digiin_cfg;  /**< Click config object. */

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
    digiin_cfg_setup( &digiin_cfg );
    DIGIIN_MAP_MIKROBUS( digiin_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == digiin_init( &digiin, &digiin_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    while ( DIGIIN_PIN_STATE_HIGH == digiin_get_rdy_pin( &digiin ) )
    {
        log_printf( &logger, "Please check if 24V is connected \r\n" );
        Delay_ms ( 1000 );
    }

    if ( DIGIIN_ERROR == digiin_default_cfg ( &digiin ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t channel_data = 0;

    digiin_pulse_latch( &digiin );

    if ( DIGIIN_OK == digiin_read_reg( &digiin, DIGIIN_REG_DISTATE, &channel_data ) )
    {
        if ( channel_data & DIGIIN_CHANNEL_1_MASK )
        {
            log_printf( &logger, "Channel 1 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 1 State: LOW \r\n" );
        }
        if ( channel_data & DIGIIN_CHANNEL_2_MASK )
        {
            log_printf( &logger, "Channel 2 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 2 State: LOW \r\n" );
        }
        if ( channel_data & DIGIIN_CHANNEL_3_MASK )
        {
            log_printf( &logger, "Channel 3 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 3 State: LOW \r\n" );
        }
        if ( channel_data & DIGIIN_CHANNEL_4_MASK )
        {
            log_printf( &logger, "Channel 4 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 4 State: LOW \r\n" );
        }
        if ( channel_data & DIGIIN_CHANNEL_5_MASK )
        {
            log_printf( &logger, "Channel 5 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 5 State: LOW \r\n" );
        }
        if ( channel_data & DIGIIN_CHANNEL_6_MASK )
        {
            log_printf( &logger, "Channel 6 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 6 State: LOW \r\n" );
        }
        if ( channel_data & DIGIIN_CHANNEL_7_MASK )
        {
            log_printf( &logger, "Channel 7 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 7 State: LOW \r\n" );
        }
        if ( channel_data & DIGIIN_CHANNEL_8_MASK )
        {
            log_printf( &logger, "Channel 8 State: HIGH \r\n" );
        }
        else
        { 
            log_printf( &logger, "Channel 8 State: LOW \r\n" );
        }
        log_printf( &logger, "- - - - - - - - - - - - - -\r\n" );
    }
    if ( DIGIIN_PIN_STATE_LOW == digiin_get_flt_pin( &digiin ) )
    {
        uint8_t flt_data = 0;
        digiin_read_reg( &digiin, DIGIIN_REG_FAULT1, &flt_data );
        log_printf( &logger, "Fault1 data: 0x%.2X \r\n", ( uint16_t ) flt_data );
        digiin_read_reg( &digiin, DIGIIN_REG_FAULT2, &flt_data );
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
