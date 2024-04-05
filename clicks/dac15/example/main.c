/*!
 * @file main.c
 * @brief DAC 15 Click example
 *
 * # Description
 * This example demonstrates the use of DAC 15 Click board™ 
 * by changing the output voltage level on the VOUTA and VOUTB.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C or SPI module and log UART.
 * After driver initialization, the app executes a default configuration.
 *
 * ## Application Task
 * The demo application changes the output voltage level on the VOUTA and VOUTB.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dac15.h"

static dac15_t dac15;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac15_cfg_t dac15_cfg;  /**< Click config object. */

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
    dac15_cfg_setup( &dac15_cfg );
    DAC15_MAP_MIKROBUS( dac15_cfg, MIKROBUS_1 );
    err_t init_flag = dac15_init( &dac15, &dac15_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DAC15_ERROR == dac15_default_cfg ( &dac15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, " -------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void )
{   
    static uint16_t dac_data = 0;
    for ( uint16_t n_cnt = 0; n_cnt < 60000; n_cnt += 5000 )
    {
        dac_data = n_cnt;
        if ( DAC15_OK == dac15_set_dac_data( &dac15, DAC15_SET_DAC_A, dac_data ) )
        {
            log_printf( &logger, "VOUTA: %u -> %.2f V\r\n", 
                        dac_data, 
                        ( float ) dac_data * DAC15_VREF_3V3 / DAC15_MAX_DAC_DATA );
        }
        
        dac_data = DAC15_DAC_RES_16BIT - n_cnt;
        if ( DAC15_OK == dac15_set_dac_data( &dac15, DAC15_SET_DAC_B, dac_data ) )
        {
            log_printf( &logger, "VOUTB: %u -> %.2f V\r\n", 
                        dac_data, 
                        ( float ) dac_data * DAC15_VREF_3V3 / DAC15_MAX_DAC_DATA );
        }
        log_printf( &logger, " -------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
