/*!
 * @file main.c
 * @brief Compass5 Click example
 *
 * # Description
 * This is an example that demonstrates the use of Compass 5 Click board that reads data 
 * from magnetic sensors for X, Y, and Z axes,processes it and displays it via the UART terminal.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C and starts to write log, performs power down mode, sets continuous measurement mode; also writes log.
 *
 * ## Application Task
 * When Compass 5 click is connected via I2C communication, then this example, collects data on the current position of the X, 
 * Y and Z axes, processes and displays via the UART terminal. All axis data is printed every 2 seconds.
 *
 * @author Jelena Milosavljevic
 *
 */

#include "board.h"
#include "log.h"
#include "compass5.h"

static compass5_t compass5;
static log_t logger;
uint8_t device_id;
uint8_t company_id;
static char log_txt[ 50 ];

void application_init ( void ) {
    log_cfg_t log_cfg;                /**< Logger config object. */
    compass5_cfg_t compass5_cfg;      /**< Click config object. */

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
    Delay_ms ( 100 );
    
    // Click initialization.
    compass5_cfg_setup( &compass5_cfg );
    COMPASS5_MAP_MIKROBUS( compass5_cfg, MIKROBUS_1 );
    err_t init_flag = compass5_init( &compass5, &compass5_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    compass5_sw_reset( &compass5 );
    Delay_ms ( 500 );
    
    compass5_get_id( &compass5, &company_id, &device_id );
    
    if  ( ( company_id == COMPASS5_COMPANI_ID_NUM ) && ( device_id == COMPASS5_DEVICE_ID_NUM ) ) {
        log_printf( &logger, "--------------------\r\n" );
        log_printf( &logger, "  Compass 3 click   \r\n" );
        log_printf( &logger, "--------------------\r\n" );
    }
    else {
        log_printf( &logger, "   Fatal error!!!   \r\n" );
        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    log_printf( &logger, "  Power Down Mode  \r\n" );
    log_printf( &logger, "-------------------\r\n" );
    compass5_set_operation_mode( &compass5, COMPASS5_MODE_POWER_DOWN );
    Delay_ms ( 100 );

    log_printf( &logger, "    Continuous     \r\n" );
    log_printf( &logger, " Measurement Mode  \r\n" );
    log_printf( &logger, "-------------------\r\n" );
    compass5_set_operation_mode( &compass5, COMPASS5_MODE_CON_MEASUREMENT_100HZ );
    Delay_ms ( 100 );

    log_printf( &logger, " Start Measurement \r\n" );
    log_printf( &logger, "-------------------\r\n" );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}

void application_task ( void ) {
    int16_t x_val;
    int16_t y_val;
    int16_t z_val;
    
    if ( compass5_check_data_ready( &compass5 ) == COMPASS5_DATA_READY ) {
        compass5_measurement_axis( &compass5, &x_val, &y_val, &z_val );
        Delay_ms ( 10 );
    
        log_printf( &logger, " X-axis: %d mG\r\n", x_val );
        log_printf( &logger, " Y-axis: %d mG\r\n", y_val );
        log_printf( &logger, " Z-axis: %d mG\r\n", z_val );        
        log_printf( &logger,  "--------------------\r\n" );
    }
    Delay_ms ( 1000 );
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
