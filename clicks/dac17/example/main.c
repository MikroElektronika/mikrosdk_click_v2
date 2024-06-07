/*!
 * @file main.c
 * @brief DAC 17 Click example
 *
 * # Description
 * This example demonstrates the use of DAC 17 Click board 
 * by changing the voltage level on the output channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs click default configuration.
 *
 * ## Application Task
 * Changes the output channels voltage level starting from full scale ( REF voltage ),  
 * to the mid-scale ( half of the REF voltage ), and then to zero every two seconds.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "dac17.h"

static dac17_t dac17;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac17_cfg_t dac17_cfg;  /**< Click config object. */

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
    dac17_cfg_setup( &dac17_cfg );
    DAC17_MAP_MIKROBUS( dac17_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == dac17_init( &dac17, &dac17_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC17_ERROR == dac17_default_cfg ( &dac17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    #define DAC17_OUTPUT_ZERO           0x0000u
    #define DAC17_OUTPUT_MID_SCALE      0x0800u
    #define DAC17_OUTPUT_FULL_SCALE     0x0FFFu

    log_printf( &logger, " Setting all channels to full scale output \r\n" );
    dac17_set_all_dac_output( &dac17, DAC17_OUTPUT_FULL_SCALE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Setting all channels outputs to zero \r\n" );
    dac17_set_all_dac_output( &dac17, DAC17_OUTPUT_ZERO );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Setting all channels outputs to mid scale \r\n" );
    dac17_set_all_dac_output( &dac17, DAC17_OUTPUT_MID_SCALE );
    Delay_ms ( 1000 );
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
