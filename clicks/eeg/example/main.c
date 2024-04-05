/*!
 * @file main.c
 * @brief EEG Click Example.
 *
 * # Description
 * This example demonstrates the use of EEG Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes Click board.
 *
 * ## Application Task
 * Reads ADC value and sends results on serial plotter every 5 ms.
 *
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "eeg.h"

static eeg_t eeg;   /**< EEG Click driver object. */
static log_t logger;    /**< Logger object. */
uint32_t time = 0;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    eeg_cfg_t eeg_cfg;  /**< Click config object. */

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
    log_printf( &logger, " ----------------------------------------------\r\n" );
    log_printf( &logger, "                ***EEG click***               \r\n" );
    log_printf( &logger, "----------------------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // Click initialization.
    eeg_cfg_setup( &eeg_cfg );
    EEG_MAP_MIKROBUS( eeg_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == eeg_init( &eeg, &eeg_cfg ) ){
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint16_t eeg_an_value = 0;
        
    if ( eeg_read_an_pin_value( &eeg, &eeg_an_value ) != ADC_ERROR ) {
        log_printf( &logger, " %u,%lu\r\n", eeg_an_value, time );
        Delay_ms ( 5 );
        time += 5;
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
