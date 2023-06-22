/*!
 * @file main.c
 * @brief TempProbe Click example
 *
 * # Description
 * This is an example that demonstrates the use of the Temp Probe Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI interface, setting temperature format to celsius and performs a device 
 * configuration for proper functioning and configures the desired channels. 
 *
 * ## Application Task
 * Measure temperatures from all sensors and display the measurements on the serial port.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "tempprobe.h"

static tempprobe_t tempprobe;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    tempprobe_cfg_t tempprobe_cfg;  /**< Click config object. */

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
    tempprobe_cfg_setup( &tempprobe_cfg );
    TEMPPROBE_MAP_MIKROBUS( tempprobe_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == tempprobe_init( &tempprobe, &tempprobe_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );
        for ( ; ; );
    }
    tempprobe_reset( &tempprobe );
    Delay_ms( 300 );
    if ( TEMPPROBE_ERROR == tempprobe_default_cfg( &tempprobe ) ) 
    {
        log_error( &logger, " Config Error " );
        for ( ; ; );
    }
    Delay_ms( 300 );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float temperature_k = 0;
    float temperature_pn = 0;
    tempprobe_write_byte( &tempprobe, TEMPPROBE_REG_COMM_STATUS, TEMPPROBE_START_CONV );
    while ( TEMPPROBE_NO_BUSY_STATE != tempprobe_check_busy( &tempprobe ) );

    tempprobe_read_temp( &tempprobe, TEMPPROBE_REG_PN_JUNCTION_CONV_RES, &temperature_pn );
    log_printf( &logger, " PN-Junction: %.2f C\r\n", temperature_pn );
    tempprobe_read_temp( &tempprobe, TEMPPROBE_REG_THERMO_K_CONV_RES, &temperature_k );
    log_printf( &logger, " Thermo K:    %.2f C\r\n", temperature_k );

    log_printf( &logger, "------------------------\r\n" );
    Delay_ms( 1500 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
