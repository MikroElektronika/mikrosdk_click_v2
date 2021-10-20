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

static float temperature_k;
static float temperature_pn;

void application_init ( void ) {
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
    err_t init_flag  = tempprobe_init( &tempprobe, &tempprobe_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, " Temp Probe initialization \r\n" );
    tempprobe_reset( &tempprobe );
    Delay_ms( 300 );
    err_t cfg_flag = tempprobe_default_cfg( &tempprobe );
    if ( TEMPPROBE_ERROR == cfg_flag ) {
        log_printf( &logger, " Config Error \r\n" );
        
        for ( ; ; );
    }
    Delay_ms( 300 );

    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    uint8_t check_state;

    tempprobe_write_byte( &tempprobe, TEMPPROBE_REG_COMM_STATUS, TEMPPROBE_START_CONV  );
    check_state = tempprobe_check_busy( &tempprobe );
    while ( check_state != TEMPPROBE_NO_BUSY_STATE ) {
        check_state = tempprobe_check_busy( &tempprobe );
    }

    tempprobe_read_temp( &tempprobe, TEMPPROBE_REG_PN_JUNCTION_CONV_RES , &temperature_k );
    log_printf( &logger, " PN-Junction: %.4f C\r\n", temperature_k );
    tempprobe_read_temp( &tempprobe, TEMPPROBE_REG_THERMO_K_CONV_RES, &temperature_pn );
    log_printf( &logger, " Thermo K:    %.4f C\r\n", temperature_pn );

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
