/*!
 * @file main.c
 * @brief LDC2 Click example
 *
 * # Description
 * This example demonstrates the use of LDC 2 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and configures the click board.
 *
 * ## Application Task
 * Measures the resonance impedance and proximity as well as the inductance and sensor frequency 
 * approximately every 200ms and displays all values on the USB UART.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ldc2.h"

static ldc2_t ldc2;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    ldc2_cfg_t ldc2_cfg;    /**< Click config object. */

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
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.

    ldc2_cfg_setup( &ldc2_cfg );
    LDC2_MAP_MIKROBUS( ldc2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == ldc2_init( &ldc2, &ldc2_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    if ( LDC2_ERROR == ldc2_default_cfg ( &ldc2 ) )
    {
        log_error( &logger, " Default Config Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t prox_data = 0;
    float rp_data = 0;
    float freq = 0;
    float inductance = 0;
    
    if ( LDC2_OK == ldc2_measure_resonance_impedance( &ldc2, &prox_data, &rp_data ) )
    {
        log_printf( &logger, " Proximity: %u\r\n Resonance Impedance: %.3f kOhm\r\n\n", ( uint16_t ) prox_data, rp_data );
    }
    
    if ( LDC2_OK == ldc2_measure_inductance( &ldc2, &freq, &inductance ) )
    {
        log_printf( &logger, " Sensor Frequency: %.3f MHz\r\n Inductance: %.6f uH\r\n\n", freq, inductance );
    }
    
    Delay_ms( 200 );
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
