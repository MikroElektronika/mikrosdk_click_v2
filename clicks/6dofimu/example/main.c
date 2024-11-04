/*!
 * \file 
 * \brief 6DofImu Click example
 * 
 * # Description
 * This example showcases how to initalize and use the 6DOF IMU Click. The Click contains a 
 * 6-axis inertial measurement unit ( accelerometer + gyroscope ). After configuring the Click
 * module for proper use, axis and temperature data will be measured every second.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * This function initializes and configures the Click and logger modules. In order for the 
 * device to work well, proper data needs to be written to the measurement control
 * registers as is done in the default_cfg(...) function.
 * 
 * ## Application Task  
 * This function reads and displays temperature and accelerometer/gyroscope axis data from
 * predefined registers. There is a 1 second delay between every read from the data output
 * registers.
 * 
 * *note:* 
 * <WARNING> If you write data to any of the "reserved" register addresses, you can permanently
 * damage the chip. If you are feeling adventurous, read the LSM6DS33 chip datasheet. 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c6dofimu.h"

// ------------------------------------------------------------------ VARIABLES

static c6dofimu_t c6dofimu;
static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( )
{
    log_cfg_t log_cfg;
    c6dofimu_cfg_t cfg;

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
    Delay_100ms( );

    //  Click initialization.

    c6dofimu_cfg_setup( &cfg );
    C6DOFIMU_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu_init( &c6dofimu, &cfg );
    Delay_ms ( 100 );
    c6dofimu_default_cfg( &c6dofimu );
    log_info( &logger, "---- Click Init ----" );
}

void application_task ( )
{
    float temperature; 

    c6dofimu_read_axis_data( &c6dofimu, C6DOFIMU_ACCEL_READ_MODE );
//     Delay_1sec( );
    c6dofimu_read_axis_data( &c6dofimu, C6DOFIMU_GYRO_READ_MODE );
//     Delay_1sec( );
    temperature = c6dofimu_read_temperature( &c6dofimu );

    log_printf( &logger, "--------------------------------------------\r\n" );
    log_printf( &logger, " * ACCEL * X: %d Y: %d Z: %d\r\n", c6dofimu.accel_axis.x,
                                                                   c6dofimu.accel_axis.y,
                                                                   c6dofimu.accel_axis.z );
    log_printf( &logger, " * GYRO * X: %d Y: %d Z: %d\r\n", c6dofimu.gyro_axis.x,
                                                                  c6dofimu.gyro_axis.y,
                                                                  c6dofimu.gyro_axis.z );
    log_printf( &logger, " * Temperature: %.2f C\r\n", temperature );
    Delay_ms ( 500 );
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
