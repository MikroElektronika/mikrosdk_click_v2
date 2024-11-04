/*!
 * @file main.c
 * @brief AnalogMux2 Click example
 *
 * # Description
 * This application controls the multiplexing of a single input channel
 * with an eight-channel matrix switch.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C and ADC driver, set Vref, STM32F407ZG - 2.048 V, PIC18F97J94 3.3 V, 
 * set the default configuration and start to write log.
 *
 * ## Application Task
 * This is an example that shows the use of a Analog MUX 2 Click board.
 * In this example, we switch from channel AN0 to channel AN7, 
 * read and display the analog value and voltage on the active channel.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "analogmux2.h"

static analogmux2_t analogmux2;
static log_t logger;

void application_init ( void ) {
    log_cfg_t log_cfg;                /**< Logger config object. */
    analogmux2_cfg_t analogmux2_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    analogmux2_cfg_setup( &analogmux2_cfg );
    ANALOGMUX2_MAP_MIKROBUS( analogmux2_cfg, MIKROBUS_1 );
    
    // Vref STM32F407ZG
    analogmux2_cfg.vref = 2.048;
    
    err_t init_flag = analogmux2_init( &analogmux2, &analogmux2_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    analogmux2_default_cfg ( &analogmux2 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms ( 100 );
}

void application_task ( void ) {   
    for ( uint8_t ch_pos = ANALOGMUX2_SET_CHANNEL_0; ch_pos <= ANALOGMUX2_SET_CHANNEL_7; ch_pos++ ) {
        analogmux2_set_channel( &analogmux2, ch_pos );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        
        uint16_t analogmux2_an_value = 0;
    
        log_printf( &logger, "   CHANNEL    : AN%u     \r\n", ( uint16_t ) analogmux2_get_channel( &analogmux2 ) );
        log_printf( &logger, "- - - - - - - - - - - - - \r\n" );

        if ( analogmux2_read_an_pin_value ( &analogmux2, &analogmux2_an_value ) != ADC_ERROR ) {
            log_printf( &logger, "   ADC Value  : %u\r\n", analogmux2_an_value );
        }
    
        float analogmux2_an_voltage = 0;

        if ( analogmux2_read_an_pin_voltage ( &analogmux2, &analogmux2_an_voltage ) != ADC_ERROR ) {
            log_printf( &logger, "   AN Voltage : %.3f V \r\n", analogmux2_an_voltage );
        }
        
        log_printf( &logger, "-------------------------\r\n" );
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
