/*!
 * @file main.c
 * @brief AnalogMux3 Click example
 *
 * # Description
 * This is an example that demonstrates the use of the Analog MUX 3 click board.
 * This application controls the multiplexing of a single input channel
 * with an eight-channel matrix switch.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes SPI and ADC driver, set Vref, STM32F407ZG - 2.048 V, PIC18F97J94 3.3 V, 
 * set the default configuration and start to write log.
 *
 * ## Application Task
 * This is an example that shows the use of a Analog MUX 3 click board.
 * In this example, we switch from channel AN0 to channel AN7, 
 * read and display the analog value and voltage on the active channel.
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "analogmux3.h"

static analogmux3_t analogmux3;
static log_t logger;

uint8_t read_data; 

uint8_t read_byte; 

void application_init ( void ) {
    log_cfg_t log_cfg;                /**< Logger config object. */
    analogmux3_cfg_t analogmux3_cfg;  /**< Click config object. */

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

    analogmux3_cfg_setup( &analogmux3_cfg );
    ANALOGMUX3_MAP_MIKROBUS( analogmux3_cfg, MIKROBUS_1 );
    
    // Vref STM32F407ZG
    analogmux3_cfg.vref = 2.048;
    
    // Vref PIC18F97J94
    // analogmux3_cfg.vref = 3.3;
    
    err_t init_flag  = analogmux3_init( &analogmux3, &analogmux3_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    analogmux3_default_cfg ( &analogmux3 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}

void application_task ( void ) {
    for ( uint8_t ch_pos = ANALOGMUX3_SET_CHANNEL_0; ch_pos <= ANALOGMUX3_SET_CHANNEL_7; ch_pos++ ) {
        analogmux3_set_channel( &analogmux3, ch_pos );
        Delay_ms( 1000 );
        
        uint16_t analogmux3_an_value = 0;
    
        log_printf( &logger, "   CHANNEL    : AN%u     \r\n", ch_pos );
        log_printf( &logger, "- - - - - - - - - - - - - \r\n" );

        if ( analogmux3_read_an_pin_value ( &analogmux3, &analogmux3_an_value ) != ADC_ERROR ) {
            log_printf( &logger, "   ADC Value  : %u\r\n", analogmux3_an_value );
        }
    
        float analogmux3_an_voltage = 0;

        if ( analogmux3_read_an_pin_voltage ( &analogmux3, &analogmux3_an_voltage ) != ADC_ERROR ) {
            log_printf( &logger, "   AN Voltage : %.3f V \r\n", analogmux3_an_voltage );
        }
        
        log_printf( &logger, "-------------------------\r\n" );
    }   
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
