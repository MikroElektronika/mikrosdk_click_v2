/*!
 * @file main.c
 * @brief Charger3 Click example
 *
 * # Description
 * This example demonstrates the utilization of Charger 3 Click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The application init sets up the UART LOG and I2C communication
 * drivers. The default configuration disables write protection
 * and sets the operation mode to charging.
 *
 * ## Application Task
 * Task consists of two operations. First, the desired battery
 * charging current is set by the user. Since setting the current
 * doesn't implicitly reveals the resistance, the value
 * of AD5175 digipot is directly read from the RDAC register,
 * calculated and displayed on the uart log.
 *
 * *note:*
 * While the resistance of the AD5175 can be directly set and read,
 * the total resistance value on the PROG pin should be accounted for
 * ( this means an additional 1kohm in series ) setting of the
 * battery charging current.
 *
 * @author Stefan Nikolic
 *
 */

#include "board.h"
#include "log.h"
#include "charger3.h"

static charger3_t charger3;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger3_cfg_t charger3_cfg;  /**< Click config object. */

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

    charger3_cfg_setup( &charger3_cfg );
    CHARGER3_MAP_MIKROBUS( charger3_cfg, MIKROBUS_1 );
    err_t init_flag = charger3_init( &charger3, &charger3_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    Delay_ms ( 100 );
    charger3_default_cfg ( &charger3 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, " ------------------------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) {
    float result;
    
    charger3_set_current( &charger3, 0.4 );
    Delay_ms ( 1000 );
    result = charger3_calc_digipot_res( &charger3 );
    log_printf( &logger, " Digipot res value: %.2f ohm\r\n", result );
    log_printf( &logger, " ------------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
