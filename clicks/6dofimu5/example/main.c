/*!
 * \file 
 * \brief C6DofImu5 Click example
 * 
 * # Description
 * This example demonstrates the use of 6DOF IMU 5 Click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver, checks the communication and sets the device 
 * default configuration.
 * 
 * ## Application Task  
 * Measures acceleration, gyroscope, temperature and pressure data and 
 * displays the results on USB UART each second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c6dofimu5.h"

// ------------------------------------------------------------------ VARIABLES

static c6dofimu5_t c6dofimu5;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu5_cfg_t cfg;
    uint8_t id_val;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c6dofimu5_cfg_setup( &cfg );
    C6DOFIMU5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu5_init( &c6dofimu5, &cfg );
    
    c6dofimu5_read_bytes ( &c6dofimu5, C6DOFIMU5_WHO_AM_I, &id_val, 1 );
    if ( id_val == C6DOFIMU5_WHO_AM_I_VAL )
    {
        log_printf( &logger, "-------------------------\r\n " );
        log_printf( &logger, "   6DOF  IMU  5  Click   \r\n " );
        log_printf( &logger, "-------------------------\r\n " );
        c6dofimu5_power ( &c6dofimu5, C6DOFIMU5_POWER_ON );
    }
    else
    {   
        log_printf( &logger, "-------------------------\r\n " );
        log_printf( &logger, "     FATAL  ERROR!!!     \r\n " );
        log_printf( &logger, "-------------------------\r\n " );
        for ( ; ; );
    }

    c6dofimu5_default_cfg( &c6dofimu5 );
    c6dofimu5_baro_settings( &c6dofimu5 );

    log_printf( &logger, "    ---Initialised---    \r\n " );
    log_printf( &logger, "-------------------------\r\n " );

    Delay_ms ( 100 );
}

void application_task ( void )
{
    float x_gyro;
    float y_gyro;
    float z_gyro;
    float x_accel;
    float y_accel;
    float z_accel;
    uint32_t raw_pres;
    uint16_t raw_temp;
    c6dofimu5_process_data_t process_data;

    c6dofimu5_acceleration_rate( &c6dofimu5, &x_accel, &y_accel, &z_accel );
    c6dofimu5_angular_rate( &c6dofimu5, &x_gyro, &y_gyro, &z_gyro );

    log_printf( &logger, " Accel X: %.2f \t Gyro X: %.2f\r\n", x_accel, x_gyro );
    log_printf( &logger, " Accel Y: %.2f \t Gyro Y: %.2f\r\n", y_accel, y_gyro );
    log_printf( &logger, " Accel Z: %.2f \t Gyro Z: %.2f\r\n", z_accel, z_gyro );
    
    log_printf( &logger, "-------------------------\r\n " );

    c6dofimu5_read_raw_data( &c6dofimu5, &raw_pres, &raw_temp );

    process_data.p_raw = raw_pres;
    process_data.t_raw = raw_temp;

    c6dofimu5_process_data( &c6dofimu5, &process_data );

    log_printf( &logger, "Pressure: %.2f mBar\r\n " , process_data.pressure * 0.01 );
    log_printf( &logger, "Temperature: %.2f Celsius\r\n " , process_data.temperature );

    log_printf( &logger, "-------------------------\r\n" );
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
