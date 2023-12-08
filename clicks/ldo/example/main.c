/*!
 * @file main.c
 * @brief LDO Click example
 *
 * # Description
 * This example demonstrates the use of LDO click by changing the output voltage.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the device default configuration.
 *
 * ## Application Task
 * Changes the output voltage every 3 seconds and displays on the USB UART 
 * the currently set voltage output value.
 *
 * @note
 * In order to have up to 3950mV at VOUT you will need to move the VIN SEL on-board jumper
 * to the VEXT position and provide at least 3950mV voltage input at the VEXT terminal.
 * Otherwise, the maximum level of VOUT will be limited to 3.3V system voltage.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "ldo.h"

static ldo_t ldo;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ldo_cfg_t ldo_cfg;  /**< Click config object. */

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
    ldo_cfg_setup( &ldo_cfg );
    LDO_MAP_MIKROBUS( ldo_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ldo_init( &ldo, &ldo_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LDO_ERROR == ldo_default_cfg ( &ldo ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    static uint16_t vout = LDO_VOUT_MIN;
    if ( LDO_OK == ldo_set_vout ( &ldo, vout ) )
    {
        log_printf ( &logger, " VOUT: %u mV\r\n\n", vout );
    }
    vout += LDO_VOUT_STEP;
    if ( vout > LDO_VOUT_MAX )
    {
        vout = LDO_VOUT_MIN;
    }
    Delay_ms ( 3000 );
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
