/*!
 * @file main.c
 * @brief DAC10 Click example
 *
 * # Description
 * This example demonstrates the use of DAC 10 click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver, checks the communication by reading and verifying the device ID,
 * and enables the DAC output.
 *
 * ## Application Task
 * Changes the output voltage every 2 seconds and logs the voltage value on the USB UART.
 * It will go through the entire voltage range taking into account the number of steps 
 * which is defined below.
 *
 * @note
 * Measure the voltage at VCC_SEL jumper and adjust the reference voltage value below for better accuracy.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "dac10.h"

#define REFERENCE_VOLTAGE  3.3 // The reference voltage defined by the VCC_SEL on-board jumper. 
#define NUMBER_OF_STEPS    20  // The number of steps by which we will divide the entire voltage range. 

static dac10_t dac10;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    dac10_cfg_t dac10_cfg;  /**< Click config object. */

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
    Delay_ms( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    dac10_cfg_setup( &dac10_cfg );
    DAC10_MAP_MIKROBUS( dac10_cfg, MIKROBUS_1 );
    err_t init_flag = dac10_init( &dac10, &dac10_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    if ( DAC10_ERROR == dac10_check_device_id ( &dac10 ) ) 
    {
        log_error( &logger, " Check Device ID Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    dac10_enable_dac( &dac10 );
    Delay_ms( 100 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    float step = REFERENCE_VOLTAGE / NUMBER_OF_STEPS;
    float output_voltage = step;
    uint8_t cnt = 0;
    while ( cnt < NUMBER_OF_STEPS )
    {
        dac10_set_output_voltage ( &dac10, REFERENCE_VOLTAGE, output_voltage );
        log_printf( &logger, " DAC output voltage set to %.2f V\r\n", output_voltage );
        output_voltage += step;
        cnt++;
        Delay_ms( 2000 );
    }
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
