/*!
 * @file main.c
 * @brief Magneto 9 Click Example.
 *
 * # Description
 * This example demonstrates the use of Magneto 9 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger.
 *
 * ## Application Task
 * Reads the ADC voltage and calculates the magnetic field strength from it.
 * Voltage increases with increasing positive (south) applied magnetic field.
 * All data are being displayed on the USB UART where you can track their changes.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "magneto9.h"

static magneto9_t magneto9;   /**< Magneto 9 Click driver object. */
static log_t logger;          /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    magneto9_cfg_t magneto9_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    magneto9_cfg_setup( &magneto9_cfg );
    MAGNETO9_MAP_MIKROBUS( magneto9_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == magneto9_init( &magneto9, &magneto9_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float voltage = 0;
    
    if ( MAGNETO9_OK == magneto9_read_an_pin_voltage ( &magneto9, &voltage ) )
    {
        float field_strength = MAGNETO9_VOLTAGE_TO_FIELD_STRENGTH ( voltage );
        log_printf( &logger, " ADC Voltage : %.3f V\r\n", voltage );
        log_printf( &logger, " Magnetic field strength : %.3f mT\r\n", field_strength );
        if ( field_strength < 0 )
        {
            log_printf( &logger, " The North Pole magnetic field prevails.\r\n\n" );
        }
        else
        {
            log_printf( &logger, " The South Pole magnetic field prevails.\r\n\n" );
        }
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
