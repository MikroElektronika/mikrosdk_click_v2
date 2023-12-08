/*!
 * @file main.c
 * @brief VCPMonitor3 Click example
 *
 * # Description
 * VCP Monitor 3 Click show it's full usage by reading current, voltage, power, die temperature 
 * and voltage at DVCC using SPI or I2C communication protocol.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initalizes SPI or I2C driver and sets up the device.
 *
 * ## Application Task
 * This example shows capabilities of VCP Monitor 3 Click board
 * by reading current, voltage, power, die temperature and 
 * voltage at DVCC and displaying the results via USART terminal.
 *
 * @author Mikroe Team
 *
 */

#include "board.h"
#include "log.h"
#include "vcpmonitor3.h"

static vcpmonitor3_t vcpmonitor3;
static log_t logger;

static float cur_data;
static float volt_data;
static float pow_data;
static float die_temp;
static float volt_vcc;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    vcpmonitor3_cfg_t vcpmonitor3_cfg;  /**< Click config object. */

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
    vcpmonitor3_cfg_setup( &vcpmonitor3_cfg );
    VCPMONITOR3_MAP_MIKROBUS( vcpmonitor3_cfg, MIKROBUS_1 );
    err_t init_flag  = vcpmonitor3_init( &vcpmonitor3, &vcpmonitor3_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( VCPMONITOR3_ERROR == vcpmonitor3_default_cfg ( &vcpmonitor3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    volt_data = vcpmonitor3_read_v( &vcpmonitor3 );
    log_printf( &logger, " Voltage :         %.2f V \r\n", volt_data );
    
    cur_data = vcpmonitor3_read_i( &vcpmonitor3 );
    log_printf( &logger, " Current :         %.2f A \r\n", cur_data );
    
    pow_data = vcpmonitor3_read_p( &vcpmonitor3 );
    log_printf( &logger, " Power :           %.2f W \r\n", pow_data );
   
    die_temp = vcpmonitor3_read_temp( &vcpmonitor3 );
    log_printf( &logger, " Die Temperature : %.2f C \r\n", die_temp );

    volt_vcc = vcpmonitor3_read_vcc( &vcpmonitor3 );
    log_printf( &logger, " Voltage at DVCC : %.2f V \r\n", volt_vcc );

    log_printf( &logger, " ------------------------------- \r\n" );
    Delay_ms( 1000 );
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
