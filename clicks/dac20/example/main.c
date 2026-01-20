/*!
 * @file main.c
 * @brief DAC 20 Click example.
 *
 * # Description
 * This example demonstrates the control of DAC output voltage using the DAC 20 Click board.
 * The application sequentially increases the DAC output voltage on both channels in equal steps.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Gradually increases the DAC output voltage on both channels in equal steps every 2 seconds.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dac20.h"

// The number of steps by which we will divide the entire voltage range. 
#define NUMBER_OF_STEPS 16

static dac20_t dac20;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac20_cfg_t dac20_cfg;  /**< Click config object. */

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
    dac20_cfg_setup( &dac20_cfg );
    DAC20_MAP_MIKROBUS( dac20_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == dac20_init( &dac20, &dac20_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC20_ERROR == dac20_default_cfg ( &dac20 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t step = DAC20_VREF_INT / NUMBER_OF_STEPS;
    uint16_t output_voltage = step;
    for ( uint8_t cnt = 0; cnt < NUMBER_OF_STEPS; cnt++ )
    {
        if ( DAC20_OK == dac20_set_dac_voltage ( &dac20, DAC20_CHANNEL_ALL, output_voltage ) )
        {
            log_printf ( &logger, " All channels output voltage set to %u mV\r\n", output_voltage );
        }
        output_voltage += step;
        Delay_ms ( 1000 ); 
        Delay_ms ( 1000 );
    }
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
