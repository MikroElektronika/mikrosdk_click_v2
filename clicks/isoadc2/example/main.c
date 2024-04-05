/*!
 * @file main.c
 * @brief IsoAdc2 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the ISO ADC 2 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI module and additional GPIO pins.
 *
 * ## Application Task
 * Every second reads ADC data and voltage in mV and logs result.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "isoadc2.h"

static isoadc2_t isoadc2;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    isoadc2_cfg_t isoadc2_cfg;  /**< Click config object. */

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

    isoadc2_cfg_setup( &isoadc2_cfg );
    ISOADC2_MAP_MIKROBUS( isoadc2_cfg, MIKROBUS_1 );
    err_t init_flag  = isoadc2_init( &isoadc2, &isoadc2_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    uint16_t rx_data;
    uint16_t mv_data;
    
    isoadc2_read_adc( &isoadc2, &rx_data );
    Delay_ms ( 100 );
    isoadc2_get_mv( &isoadc2, &mv_data );
    
    log_printf( &logger, " ADC: %d \r\n", rx_data );
    log_printf( &logger, " VIN: %d mV\r\n", mv_data );
    log_printf( &logger, "---------------\r\n" );

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
