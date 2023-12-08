/*!
 * @file main.c
 * @brief Microwave 6 Click Example.
 *
 * # Description
 * This example demonstrates the use of the Microwave 6 Click board™ 
 * by reading and displaying the results of AD conversion and motion detection.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * The initialization of I2C or ADC module and log UART.
 * After driver initialization, the app calculates the reference ADC value.
 *
 * ## Application Task
 * The demo application reads the ADC results, takes an ADC sample, 
 * compares the difference between the taken samples and the ADC reference value, 
 * and reports the movement if the difference is higher/lower than the selected threshold value.
 * Results are being sent to the UART Terminal, where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "microwave6.h"

#define MICROWAVE6_THRESHOLD    0.5f
#define MICROWAVE6_FLAG_CLEAR   0
#define MICROWAVE6_FLAG_SET     1

static microwave6_t microwave6;   /**< Microwave 6 Click driver object. */
static log_t logger;    /**< Logger object. */
static float reference = 0, voltage = 0;
static uint8_t flag = MICROWAVE6_FLAG_CLEAR;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    microwave6_cfg_t microwave6_cfg;  /**< Click config object. */

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
    microwave6_cfg_setup( &microwave6_cfg );
    MICROWAVE6_MAP_MIKROBUS( microwave6_cfg, MIKROBUS_1 );
    err_t init_flag = microwave6_init( &microwave6, &microwave6_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Calibrating the sensor...\r\n" );
    log_printf( &logger, " There must be no movement near the sensor!\r\n" );
    log_printf( &logger, "----------------------------------\r\n" );
    Delay_ms( 3000 );
    
    if ( MICROWAVE6_OK == microwave6_read_voltage( &microwave6, &reference ) )
    {
        log_printf( &logger, " The sensor has been calibrated!\r\n" );
        log_printf( &logger, "  Detector AN Voltage : %.3f[V]\r\n", reference );
        log_printf( &logger, "----------------------------------\r\n" );
        Delay_ms( 100 );
    }
    else
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    log_printf( &logger, "The motion detector unit is ready.\r\n" );
    log_printf( &logger, "----------------------------------\r\n" );
    Delay_ms( 100 );
}

void application_task ( void ) 
{
    if ( MICROWAVE6_OK == microwave6_read_voltage( &microwave6, &voltage ) )
    {
        if ( ( ( voltage + MICROWAVE6_THRESHOLD ) < reference ) || 
             ( ( voltage - MICROWAVE6_THRESHOLD ) > reference ) )
        {
            if ( MICROWAVE6_FLAG_SET == flag )
            {
                log_printf( &logger, " Motion detected!\r\n" );
                log_printf( &logger, " Detector AN Voltage : %.3f[V]\r\n", voltage );
                log_printf( &logger, "----------------------------------\r\n" );
                flag = MICROWAVE6_FLAG_CLEAR;
                Delay_ms( 100 );
            }
        }
        else
        {
            flag = MICROWAVE6_FLAG_SET;
        }
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
