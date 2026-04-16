/*!
 * @file main.c
 * @brief Ultrasonic 3 Click example
 *
 * # Description
 * This example demonstrates ranging with Ultrasonic 3 Click (Chirp/TDK time-of-flight).
 * The example periodically triggers a measurement and prints the measured
 * distance to the USB UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialize the USB UART logger and the Ultrasonic 3 driver, then apply
 * the default configuration to start the sensor and prepare it for continuous single-shot ranging.
 *
 * ## Application Task
 * Triggers a measurement and logs results (distance, sample number, and amplitude) every 100ms.
 *
 * @note
 * Make sure to configure falling-edge external interrupt on INT pin in bsp.c for your selected setup.
 * Currently, only 3 interrupts are pre-configured for the following setups:
 * - MCU Card for STM32 STM32F407ZG (MIKROBUS1)
 * - MCU Card for Tiva TM4C129XNCZAD (MIKROBUS1)
 * - MCU Card for PIC32 PIC32MX795F512L (MIKROBUS1)
 *
 * @author Stefan Filipovic
 * 
 */

#include "board.h"
#include "log.h"
#include "ultrasonic3.h"

#ifndef MIKROBUS_POSITION_ULTRASONIC3
    #define MIKROBUS_POSITION_ULTRASONIC3 MIKROBUS_1
#endif

static ultrasonic3_t ultrasonic3;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ultrasonic3_cfg_t ultrasonic3_cfg;  /**< Click config object. */

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
    ultrasonic3_cfg_setup( &ultrasonic3_cfg );
    ULTRASONIC3_MAP_MIKROBUS( ultrasonic3_cfg, MIKROBUS_POSITION_ULTRASONIC3 );
    if ( SPI_MASTER_ERROR == ultrasonic3_init( &ultrasonic3, &ultrasonic3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( ULTRASONIC3_ERROR == ultrasonic3_default_cfg ( &ultrasonic3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    ultrasonic3_get_measurements ( );
    Delay_ms ( 100 );
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

/*
 * chbsp_print_str() - Board support package print string function
 *
 * This function should print debug information to the console over a serial port.
 */
void chbsp_print_str ( const char *str )
{
    log_printf ( &logger, str );
}

// ------------------------------------------------------------------------ END
