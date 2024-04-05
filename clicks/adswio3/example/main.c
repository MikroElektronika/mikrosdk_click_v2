/*!
 * @file main.c
 * @brief AD-SWIO 3 Click example
 *
 * # Description
 * This library contains API for the AD-SWIO 3 Click driver 
 * for measurements of the analog output, analog input, digital input, 
 * resistance temperature detector (RTD), and thermocouple measurements.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of SPI and log UART.
 * After driver initialization, the app executes a default configuration 
 * that enables and sets it to measure IOP/ION voltage input from 0V to 12V, 
 * with 4.8k SPS and enabled four diagnostics measurements (AVDD, VASS, VACC and LVIN).
 *
 * ## Application Task
 * This example demonstrates the use of the AD-SWIO 3 Click board. 
 * The demo application reads and displays the voltage level input, 
 * measured by the voltage between the I/OP and I/ON screw terminals 
 * and NTC thermistor temperature in degrees Celsius.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "adswio3.h"

static adswio3_t adswio3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    adswio3_cfg_t adswio3_cfg;  /**< Click config object. */

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
    adswio3_cfg_setup( &adswio3_cfg );
    ADSWIO3_MAP_MIKROBUS( adswio3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == adswio3_init( &adswio3, &adswio3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ADSWIO3_ERROR == adswio3_default_cfg ( &adswio3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms ( 100 );

    for ( uint8_t n_cnt = ADSWIO3_GPIO_CONFIG_SEL_A; n_cnt <= ADSWIO3_GPIO_CONFIG_SEL_D; n_cnt ++ )
    {
        if ( ADSWIO3_ERROR == adswio3_set_gpio_config( &adswio3, n_cnt, 
                                                              ADSWIO3_GPIO_CONFIG_GPO_DATA_HIGH, 
                                                              ADSWIO3_GPIO_CONFIG_GP_WK_PD_DIS, 
                                                              ADSWIO3_GPIO_CONFIG_MODE_OUT ) )
        {
            log_error( &logger, " Set GPIO configuration. " );
            for ( ; ; );
        }
        Delay_ms ( 100 );
    }

    float diag_vtg = 0;
    log_printf( &logger, "_________________________\r\n" );
    log_printf( &logger, " > Diagnostic Voltages <\r\n" );
    if ( ADSWIO3_OK == adswio3_get_diag_vtg( &adswio3, ADSWIO3_DIAG_RESULT_SEL_0, &diag_vtg ) )
    {
        log_printf( &logger, " AVDD: %.2f V\r\n", diag_vtg );
        Delay_ms ( 100 );
    }

    if ( ADSWIO3_OK == adswio3_get_diag_vtg( &adswio3, ADSWIO3_DIAG_RESULT_SEL_1, &diag_vtg ) )
    {
        log_printf( &logger, " VASS: %.2f V\r\n", diag_vtg );
        Delay_ms ( 100 );
    }

    if ( ADSWIO3_OK == adswio3_get_diag_vtg( &adswio3, ADSWIO3_DIAG_RESULT_SEL_2, &diag_vtg ) )
    {
        log_printf( &logger, " VACC: %.2f V\r\n", diag_vtg );
        Delay_ms ( 100 );
    }

    if ( ADSWIO3_OK == adswio3_get_diag_vtg( &adswio3, ADSWIO3_DIAG_RESULT_SEL_3, &diag_vtg ) )
    {
        log_printf( &logger, " LVIN: %.2f V\r\n", diag_vtg );
        Delay_ms ( 100 );
    }
    log_printf( &logger, "_________________________\r\n" );
    Delay_ms ( 1000 );
}

void application_task ( void )
{
    float ntc_temp = 0, iop_ion_vtg = 0;
    if ( ADSWIO3_OK == adswio3_get_ntc_temp( &adswio3, ADSWIO3_DIAG_RESULT_SEL_3, &ntc_temp ) )
    {
        log_printf( &logger, " NTC Temperature: %.2f degC\r\n", ntc_temp );
        
        Delay_ms ( 100 );
    }
    
    if ( ADSWIO3_OK == adswio3_get_voltage_input( &adswio3, 0, &iop_ion_vtg ) )
    {
        log_printf( &logger, "IOP/ION Voltage: %.3f V\r\n", iop_ion_vtg );
        Delay_ms ( 100 );
    }
    log_printf( &logger, "_________________________\r\n" );
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
