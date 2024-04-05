/*!
 * @file main.c
 * @brief Buck 20 Click example
 *
 * # Description
 * This example demonstrates the use of Buck 20 click by changing the output voltage.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and enables the device.
 *
 * ## Application Task
 * Changes the output voltage every 3 seconds and displays on the USB UART the digipot
 * wiper position, as well as an approximate buck R1 and voltage output.
 * 
 * @note
 * An approximate buck R1 and VOUT values do not have to be 100% accurate for all wiper settings
 * but they are a good reference point. VOUT ranges from ~1.3V to ~5V, and it is the most accurate
 * around 3.3V since all passive components are set for that output.
 * 
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "buck20.h"

static buck20_t buck20;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck20_cfg_t buck20_cfg;  /**< Click config object. */

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
    buck20_cfg_setup( &buck20_cfg );
    BUCK20_MAP_MIKROBUS( buck20_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == buck20_init( &buck20, &buck20_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    buck20_set_wiper_1 ( &buck20, BUCK20_WIPER_ZERO_SCALE );
    buck20_enable_device ( &buck20 );
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint16_t digipot_wiper = BUCK20_WIPER_ZERO_SCALE;
    float buck_r1_kohm, buck_vout;
    if ( BUCK20_OK == buck20_set_wiper_1 ( &buck20, digipot_wiper ) )
    {
        buck_r1_kohm = BUCK20_RESISTOR_R6_KOHM + 
                       ( float ) ( BUCK20_DIGIPOT_MAX_KOHM * digipot_wiper ) / BUCK20_WIPER_FULL_SCALE;
        buck_vout = BUCK20_BUCK_VREF + ( buck_r1_kohm * BUCK20_BUCK_VREF ) / BUCK20_BUCK_R2_KOHM;
        log_printf( &logger, " Digipot wiper position: %u\r\n", digipot_wiper );
        log_printf( &logger, " Approximate R1 (Digipot+R6): %.2f kOhm\r\n", buck_r1_kohm );
        log_printf( &logger, " Approximate buck voltage output: %.2f V\r\n\n", buck_vout );
        digipot_wiper += 50;
        if ( digipot_wiper > BUCK20_WIPER_FULL_SCALE )
        {
            digipot_wiper = BUCK20_WIPER_ZERO_SCALE;
        }
    }
    Delay_ms ( 1000 );
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
