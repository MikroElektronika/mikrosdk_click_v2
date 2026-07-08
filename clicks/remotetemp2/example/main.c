/*!
 * @file main.c
 * @brief Remote Temp 2 Click example
 *
 * # Description
 * This example demonstrates the use of Remote Temp 2 Click board by reading
 * and displaying the temperature measurements from the local sensor and both
 * remote channel sensors (CH1 and CH2), and monitoring the alert and critical
 * temperature states.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Reads the temperature measurements in degrees Celsius from the local sensor
 * and both remote channels, and displays the results on the USB UART
 * approximately once per second. Also monitors and reports the alert and
 * critical temperature states via the ALR and TCR pins.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "remotetemp2.h"

#ifndef MIKROBUS_POSITION_REMOTETEMP2
    #define MIKROBUS_POSITION_REMOTETEMP2 MIKROBUS_1
#endif

static remotetemp2_t remotetemp2;
static log_t logger;

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    remotetemp2_cfg_t remotetemp2_cfg;  /**< Click config object. */

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
    remotetemp2_cfg_setup( &remotetemp2_cfg );
    REMOTETEMP2_MAP_MIKROBUS( remotetemp2_cfg, MIKROBUS_POSITION_REMOTETEMP2 );
    if ( I2C_MASTER_ERROR == remotetemp2_init( &remotetemp2, &remotetemp2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( REMOTETEMP2_ERROR == remotetemp2_default_cfg ( &remotetemp2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    uint8_t status = 0;
    int8_t local_temp = 0;
    float ch1_temp = 0;
    float ch2_temp = 0;    

    remotetemp2_read_local_temp( &remotetemp2, &local_temp );
    remotetemp2_read_temp_ch1( &remotetemp2, &ch1_temp );
    remotetemp2_read_temp_ch2( &remotetemp2, &ch2_temp );

    log_printf( &logger, " Local temperature      : %d degC \r\n", ( int16_t ) local_temp );
    log_printf( &logger, " Remote CH1 temperature : %.4f degC \r\n", ch1_temp );
    log_printf( &logger, " Remote CH2 temperature : %.4f degC \r\n", ch2_temp );
    log_printf( &logger, " ---------------------------------- \r\n" );

    if ( !remotetemp2_get_alr_pin( &remotetemp2 ) )
    {
        remotetemp2_get_status( &remotetemp2, &status );
        if ( ( REMOTETEMP2_STATUS_THIGH | REMOTETEMP2_STATUS_TLOW ) & status )
        {
            log_printf( &logger, " Alert - remote temperature is above 30 degC \r\n" );
            log_printf( &logger, " ---------------------------------- \r\n" );
        }
    }

    if ( !remotetemp2_get_tcr_pin( &remotetemp2 ) )
    {
        remotetemp2_get_status( &remotetemp2, &status );
        if ( REMOTETEMP2_STATUS_TCRIT & status )
        {
            log_printf( &logger, " Critical alert - temperature is above 30 degC \r\n" );
            log_printf( &logger, " ---------------------------------- \r\n" );
        }   
    }

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
