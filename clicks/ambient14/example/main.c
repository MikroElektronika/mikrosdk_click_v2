/*!
 * @file main.c
 * @brief Ambient 14 Click example
 *
 * # Description
 * This example demonstrates the use of Ambient 14 click board by measuring 
 * the illuminance level (Lux) and the proximity data on the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the click default configuration.
 *
 * ## Application Task
 * Reads the proximity, ALS, and IR raw data counts when data is ready.
 * Calculates the illuminance level in Lux from ALS data counts and displays
 * the results on the USB UART approximately every 500ms.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ambient14.h"

static ambient14_t ambient14;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient14_cfg_t ambient14_cfg;  /**< Click config object. */

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
    ambient14_cfg_setup( &ambient14_cfg );
    AMBIENT14_MAP_MIKROBUS( ambient14_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient14_init( &ambient14, &ambient14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT14_ERROR == ambient14_default_cfg ( &ambient14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t proximity = 0;
    uint16_t als_data = 0;
    uint16_t ir_data = 0;
    float illuminance = 0;
    
    // Enable and wait for proximity interrupt
    ambient14_write_reg ( &ambient14, AMBIENT14_REG_INTENAB, AMBIENT14_INTENAB_PIEN );
    while ( ambient14_get_int_pin ( &ambient14 ) );

    // Read proximity data and clear interrupts
    if ( AMBIENT14_OK == ambient14_read_proximity ( &ambient14, &proximity ) )
    {
        log_printf ( &logger, " Proximity: %u\r\n", proximity );
    }
    ambient14_clear_interrupts ( &ambient14 );

    // Enable and wait for ALS interrupt
    ambient14_write_reg ( &ambient14, AMBIENT14_REG_INTENAB, AMBIENT14_INTENAB_AIEN );
    while ( ambient14_get_int_pin ( &ambient14 ) );

    // Read ALS and IR data counts, calculates illuminance level, and clear interrupts
    if ( AMBIENT14_OK == ambient14_read_als_ir ( &ambient14, &als_data, &ir_data ) )
    {
        log_printf ( &logger, " ALS: %u\r\n", als_data );
        log_printf ( &logger, " IR: %u\r\n", ir_data );
        if ( AMBIENT14_OK == ambient14_get_illuminance ( &ambient14, als_data, &illuminance ) )
        {
            log_printf ( &logger, " Illuminance: %.1f Lux\r\n\n", illuminance );
        }
    }
    ambient14_clear_interrupts ( &ambient14 );
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
