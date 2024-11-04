/*!
 * @file main.c
 * @brief CDC Click example
 *
 * # Description
 * This example demonstrates the use of CDC Click board by reading capacitance
 * measurements from C3/C2 and C5/C4 ports calculated from pure capacitance ratio
 * between those ports and port C1/C0 which is used as external C reference.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Starts measurement and reads the results. The results data is displayed on the USB UART.
 *
 * @note
 * For better accuracy and higher measurement range, add 200pF external
 * capacitor between C1/C0 ports and set it below as CDC_EXT_CAP_C1_C0_PF macro
 * before running the application. This way you will be able to measure capacitance
 * in range from 1 to 2000pF.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "cdc.h"

// Settings for reference capacitors
#define CDC_EXT_CAP_C1_C0_PF        0.0f
#define CDC_INT_CAP_PF              10.0f
#define CDC_REF                     ( CDC_EXT_CAP_C1_C0_PF + CDC_INT_CAP_PF )

static cdc_t cdc;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    cdc_cfg_t cdc_cfg;  /**< Click config object. */

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
    cdc_cfg_setup( &cdc_cfg );
    CDC_MAP_MIKROBUS( cdc_cfg, MIKROBUS_1 );
    err_t init_flag = cdc_init( &cdc, &cdc_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CDC_ERROR == cdc_default_cfg ( &cdc ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    cdc_results_t results;
    cdc_send_opcode ( &cdc, CDC_OPCODE_CDC_START );
    Delay_ms ( 200 );
    if ( CDC_OK == cdc_read_results ( &cdc, &results ) )
    {
        log_printf ( &logger, " C1/C0: %.1f pF\r\n", 
                     results.res_0 * CDC_REF - CDC_INT_CAP_PF );
        log_printf ( &logger, " C3/C2: %.1f pF\r\n", 
                     results.res_1 * CDC_REF - CDC_INT_CAP_PF );
        log_printf ( &logger, " C5/C4: %.1f pF\r\n\n", 
                     results.res_2 * CDC_REF - CDC_INT_CAP_PF );
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
