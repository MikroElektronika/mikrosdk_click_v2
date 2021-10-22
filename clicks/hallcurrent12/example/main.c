/*!
 * @file main.c
 * @brief HallCurrent12 Click example
 *
 * # Description
 * This library contains API for Hall Current 12 Click driver.
 * The demo application reads ADC value and current ( A ).
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver and log UART.
 * After driver initialization the app set default settings.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the Hall Current 12 Click board™.
 * In this example, we read and display the ADC values and current ( A ) data.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @note
 * Switches: 
 *   Sensitivity : Low ( GAIN = 1 ),
 *   Vout_Sel    : ADC ( I2C serial interface ),
 *   Vref_Sel    : GND ( unidirectional measurement ).
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "hallcurrent12.h"

static hallcurrent12_t hallcurrent12;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;                      /**< Logger config object. */
    hallcurrent12_cfg_t hallcurrent12_cfg;  /**< Click config object. */

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
    hallcurrent12_cfg_setup( &hallcurrent12_cfg );
    HALLCURRENT12_MAP_MIKROBUS( hallcurrent12_cfg, MIKROBUS_1 );
    err_t init_flag = hallcurrent12_init( &hallcurrent12, &hallcurrent12_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    hallcurrent12_default_cfg ( &hallcurrent12 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    static uint16_t adc_data;
    static float current;
    
    hallcurrent12_get_adc( &hallcurrent12, &adc_data );
    log_printf( &logger, " ADC Value   : %d \r\n", adc_data );
    Delay_ms( 100 );
    
    hallcurrent12_get_current ( &hallcurrent12, &current );
    log_printf( &logger, " Current     : %.3f A \r\n", current );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms( 1000 );
}

void main ( void ) 
{
    application_init( );

    for ( ; ; ) 
    {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
