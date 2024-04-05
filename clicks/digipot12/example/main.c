/*!
 * @file main.c
 * @brief DIGI POT 12 Click example
 *
 * # Description
 * This library contains API for DIGI POT 12 Click driver.
 * The demo application uses a digital potentiometer 
 * to change the resistance values of both channels.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C module, log UART, and additional pins.
 * After the driver init, the app executes a default configuration.
 *
 * ## Application Task
 * This example demonstrates the use of the DIGI POT 12 Click board™.
 * The demo application iterates through the entire wiper range and 
 * sets the resistance of both channels in steps of approximately 1kOhm.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "digipot12.h"

static digipot12_t digipot12;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot12_cfg_t digipot12_cfg;  /**< Click config object. */

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
    digipot12_cfg_setup( &digipot12_cfg );
    DIGIPOT12_MAP_MIKROBUS( digipot12_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == digipot12_init( &digipot12, &digipot12_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIPOT12_ERROR == digipot12_default_cfg ( &digipot12 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ----------------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) 
{
    static float res_kohm;
    for ( uint8_t n_cnt = DIGIPOT12_RES_0_KOHM; n_cnt <= DIGIPOT12_RES_10_KOHM; n_cnt++ )
    {
        if ( DIGIPOT12_OK == digipot12_set_resistance( &digipot12, DIGIPOT12_WIPER_SEL_1, ( float ) n_cnt ) )
        {
            if ( DIGIPOT12_OK == digipot12_get_resistance( &digipot12, DIGIPOT12_WIPER_SEL_1, &res_kohm ) )
            {
                log_printf( &logger, " Rwb1 : %.2f kOhm\r\n", res_kohm );
                Delay_ms ( 100 );
            }
        }
        
        if ( DIGIPOT12_OK == digipot12_set_resistance( &digipot12, DIGIPOT12_WIPER_SEL_2, ( float ) ( DIGIPOT12_RES_10_KOHM - n_cnt ) ) )
        {
            if ( DIGIPOT12_OK == digipot12_get_resistance( &digipot12, DIGIPOT12_WIPER_SEL_2, &res_kohm ) )
            {
                log_printf( &logger, " Rwb2 : %.2f kOhm\r\n", res_kohm );
                Delay_ms ( 100 );
            }
        }
        log_printf( &logger, " ----------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
