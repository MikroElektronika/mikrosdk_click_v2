/*!
 * @file main.c
 * @brief HallCurrent7 Click example
 *
 * # Description
 * This example shows the capabilities of the Hall Current 7 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initalizes I2C driver and makes an initial log.
 *
 * ## Application Task
 * Measuring current passing through the on board Hall Effect Sensor and 
 * displaying data every two seconds. 
 *
 * @note
 * In order to get correct calculations user should change "v_ref" 
 * value to his own power supply voltage.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "hallcurrent7.h"

static hallcurrent7_t hallcurrent7;
static log_t logger;

int16_t current;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    hallcurrent7_cfg_t hallcurrent7_cfg;  /**< Click config object. */

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
    hallcurrent7_cfg_setup( &hallcurrent7_cfg );
    HALLCURRENT7_MAP_MIKROBUS( hallcurrent7_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent7_init( &hallcurrent7, &hallcurrent7_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    current = hallcurrent7_avg_current( &hallcurrent7, HALLCURRENT7_VREF_5000_mV );
    log_printf( &logger, "Current: %d mA\r\n", current );

    log_printf( &logger, "------------------------\r\n" );
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
