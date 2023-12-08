/*!
 * @file main.c
 * @brief eFuse3 Click example
 *
 * # Description
 * This library contains API for the eFuse 3 Click driver.
 * The library contains drivers to enable/disable the device, 
 * for reading ADC voltage, overflow status, output and current value [ A ].
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI driver and set default configuration.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the eFuse 3 Click board. 
 * Read and display device status information and current value [ A ].
 * The eFuse 3 includes an overvoltage clamp the circuit that limits the output voltage
 * during transients but does not shut the unit down, 
 * thereby allowing the load circuit to continue its operation.
 * The Electronic Fuse is to limit current and current limit 
 * Current limit ( 0.1 A - 1.8 A ) depends on the choice of resistor wired 
 * on the Rlimit ( 1 Ohm - 15 Ohm ) connector.
 * For example, for Rlimit resistance of 1 Ohm, current limit is 1 A 
 * ( 3.5 Ohm - 0.5 A, 7 Ohm - 0.25 A ). 
 * Read details from the ON Semiconductor NIS6150 datasheets.   
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "efuse3.h"

static efuse3_t efuse3;
static log_t logger;

static float voltage;
static float current;
static uint8_t overflow_status;

void application_init ( void ) {
    log_cfg_t log_cfg;        /**< Logger config object. */
    efuse3_cfg_t efuse3_cfg;  /**< Click config object. */

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

    efuse3_cfg_setup( &efuse3_cfg );
    EFUSE3_MAP_MIKROBUS( efuse3_cfg, MIKROBUS_1 );
    err_t init_flag  = efuse3_init( &efuse3, &efuse3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    efuse3_default_cfg ( &efuse3 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) {
    log_printf( &logger, " Status  :" );    
    
    if ( efuse3_get_flag( &efuse3 ) == EFUSE3_FLAG_NORMAL_OPERATION ) {
        log_printf( &logger, " Normal operation \r\n" );
    } else {
        log_printf( &logger, " Device OFF \r\n" );

        if ( overflow_status == EFUSE3_OVERFLOW_HIGH ) {
            log_printf( &logger, " Overflow high in the analog input voltage.\r\n" );    
        } else if ( overflow_status == EFUSE3_OVERFLOW_LOW ) {
            log_printf( &logger, " Overflow low in the analog input voltage.\r\n" ); 
        }
        
        efuse3_reset( &efuse3 );
        Delay_ms( 1000 );
    }
    
    log_printf( &logger, "- - - - - - - - - - - - - - \r\n" );
    efuse3_get_current( &efuse3, &current );
    log_printf( &logger, " Current : %.5f A\r\n", current );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms( 2000 );
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
