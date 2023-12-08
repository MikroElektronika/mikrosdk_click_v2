/*!
 * @file main.c
 * @brief VCTMonitor Click example
 *
 * # Description
 * This is an example which demonstrates the use of VCT Monitor Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables the USB uart terminal and I2C.  
 *
 * ## Application Task
 * Reads temperature, current value, and differential voltage every 4 seconds.
 *
 * @note
 * The click has been tested using the following:
 *       - Power supply - 4V
 *       - Current (Load) - 0A to 3A
 *       - External MMBT3904 temperature sensor
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "vctmonitor.h"

static vctmonitor_t vctmonitor;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    vctmonitor_cfg_t vctmonitor_cfg;  /**< Click config object. */

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
    vctmonitor_cfg_setup( &vctmonitor_cfg );
    VCTMONITOR_MAP_MIKROBUS( vctmonitor_cfg, MIKROBUS_1 );
    err_t init_flag = vctmonitor_init( &vctmonitor, &vctmonitor_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    float temperature;
    float voltage;
    float current;

    voltage = vctmonitor_read_voltage_differential( &vctmonitor );
    log_printf( &logger, " Voltage    : %.2f mV \r\n", voltage );

    current = vctmonitor_read_current( &vctmonitor );
    log_printf( &logger, " Current    : %.2f mA \r\n", current );

    temperature = vctmonitor_read_temperature( &vctmonitor );
    log_printf( &logger, " Temperature: %.2f C \r\n", temperature );

    log_printf( &logger, "- - - - - - - - - - - -\r\n" );
    Delay_ms( 4000 );     
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
