/*!
 * @file main.c
 * @brief PROFET 2 7A Click Example.
 *
 * # Description
 * This example showcases the ability of the PROFET 2 7A Click board.
 * It configures Host MCU for communication and then enables 
 * and disables output channel. Besides that, it reads the voltage 
 * of IS pin and calculates current on output for the channel 0.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of the communication modules(ADC and UART) 
 * and additional pins for controlling the device.
 *
 * ## Application Task
 * On every iteration of the task device switches between 
 * DIAGNOSTIC and OFF mode while it reads the voltage of IS pin 
 * and with that calculates current on output for channel 0.
 * 
 * @note
 * Formula for calculating current on load: 
 * I_load = voltage(IS) x kILIS(5450) / rsens(1.2 kΩ)
 *
 * Click board won't work properly on the PIC18F97J94 MCU card.
 *
 * @author Luka Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "profet27a.h"

static profet27a_t profet27a;   /**< PROFET 2 7A Click driver object. */
static log_t logger;    /**< Logger object. */

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    profet27a_cfg_t profet27a_cfg;  /**< Click config object. */

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
    profet27a_cfg_setup( &profet27a_cfg );
    PROFET27A_MAP_MIKROBUS( profet27a_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == profet27a_init( &profet27a, &profet27a_cfg ) )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    profet27a_default_cfg ( &profet27a );
    log_info( &logger, " Application Task " );
    Delay_ms( 1000 );
}

void application_task ( void ) 
{
    static uint8_t mode = PROFET27A_DIAGNOSTIC_ON;
    float profet27a_an_voltage = 0;
    
    err_t error_val = profet27a_set_mode( &profet27a, PROFET27A_CHANNEL_0, mode );
    
    if ( error_val )
    {
        log_error( &logger, "Channe/Mode" );
    }
    
    if ( PROFET27A_DIAGNOSTIC_ON == profet27a.mode )
    {
        mode = PROFET27A_MODE_OFF;
        log_printf( &logger, " > Output ON Channel %u in diagnostic mode\r\n", ( uint16_t )profet27a.channel );
        Delay_ms( 1000 );
    }
    else
    {
        mode = PROFET27A_DIAGNOSTIC_ON;
        log_printf( &logger, " > Output OFF\r\n" );
    }

    if ( profet27a_read_an_pin_voltage ( &profet27a, &profet27a_an_voltage ) != ADC_ERROR )
    {
        log_printf( &logger, " > IS Voltage \t~ %.3f[V]\r\n", profet27a_an_voltage );
        
        float current = profet27a_an_voltage * profet27a.kilis / profet27a.rsens;
        log_printf( &logger, " > OUT Current \t~ %.3f[A]\r\n", current );
    }
    
    log_printf( &logger, "*******************************************\r\n" );
    
    Delay_ms( 2000 );
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
