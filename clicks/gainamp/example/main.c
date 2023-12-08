/*!
 * @file main.c
 * @brief GainAMP Click example
 *
 * # Description
 * This is an example that demonstrates the use of the GainAMP Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI module and set CS pin and RST pin as OUTPUT, 
 * initialization driver init and resets chip.
 *
 * ## Application Task
 * Sets the gain for both channels, channel A and channel B.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "gainamp.h"

static gainamp_t gainamp;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gainamp_cfg_t gainamp_cfg;  /**< Click config object. */

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

    gainamp_cfg_setup( &gainamp_cfg );
    GAINAMP_MAP_MIKROBUS( gainamp_cfg, MIKROBUS_1 );
    err_t init_flag  = gainamp_init( &gainamp, &gainamp_cfg );
    if ( ( SPI_MASTER_ERROR == init_flag ) || ( ADC_ERROR == init_flag ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    gainamp_reset( &gainamp );
    Delay_ms( 100 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    gainamp_set_gain( &gainamp, GAINAMP_CHANNEL_A_x1 | GAINAMP_CHANNEL_B_x5 );
    Delay_ms( 10000 );
    
    gainamp_set_gain( &gainamp, GAINAMP_CHANNEL_A_x10 | GAINAMP_CHANNEL_B_x100 );
    Delay_ms( 10000 );
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

// ------------------------------------------------------------------------ END
