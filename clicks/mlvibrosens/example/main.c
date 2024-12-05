/*!
 * @file main.c
 * @brief ML Vibro Sens Click example
 *
 * # Description
 * This example demonstrates the use of the ML Vibro Sens Click board by capturing and logging
 * acceleration data on the X, Y, and Z axes, along with temperature readings. The data is output 
 * over USB UART and can be visualized in real-time using tools like SerialPlot. Additionally, 
 * the vibro motor state changes periodically, cycling through different vibration states for 
 * added feedback.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the communication interface and configures the ML Vibro Sens Click board 
 * with default settings. This setup enables an interrupt on the INT pin when data is ready,
 * sets the acceleration sensitivity to a +/-4G range, and sets the output data rate to 100 Hz.
 *
 * ## Application Task
 * Monitors the data-ready interrupt, retrieves acceleration and temperature data when available,
 * and logs it over USB UART in the format X;Y;Z;TEMP. After every 1000 data readings, the 
 * vibro motor state cycles through predefined states to demonstrate the motor's functionality.
 *
 * @note
 * We recommend using the SerialPlot tool for data visualization. The temperature measurements
 * should be visualized independently. The data format for plotter is as follows: X;Y;Z;TEMP;
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "mlvibrosens.h"

static mlvibrosens_t mlvibrosens;
static log_t logger;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mlvibrosens_cfg_t mlvibrosens_cfg;  /**< Click config object. */

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
    mlvibrosens_cfg_setup( &mlvibrosens_cfg );
    MLVIBROSENS_MAP_MIKROBUS( mlvibrosens_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == mlvibrosens_init( &mlvibrosens, &mlvibrosens_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MLVIBROSENS_ERROR == mlvibrosens_default_cfg ( &mlvibrosens ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    static uint8_t vibro_state = MLVIBROSENS_VIBRO_STATE_IDLE;
    static uint16_t result_num = 0;
    static mlvibrosens_data_t accel_data;
    
    // Wait for a data ready interrupt
    while ( mlvibrosens_get_int_pin ( &mlvibrosens ) );

    if ( MLVIBROSENS_OK == mlvibrosens_get_data ( &mlvibrosens, &accel_data ) )
    {
        log_printf ( &logger, "%f;%f;%f;%d;\r\n", accel_data.x, accel_data.y, 
                                                  accel_data.z, accel_data.temperature ); 
    }
    if ( ++result_num > 1000 )
    {
        result_num = 0;
        if ( ++vibro_state > MLVIBROSENS_VIBRO_STATE_BOTH )
        {
            vibro_state = MLVIBROSENS_VIBRO_STATE_IDLE;
        }
        mlvibrosens_set_vibro_state ( &mlvibrosens, vibro_state );
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
