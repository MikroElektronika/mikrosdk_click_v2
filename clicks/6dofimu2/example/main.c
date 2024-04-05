/*!
 * \file 
 * \brief 6DofImu2 Click example
 * 
 * # Description
 * 6DOF IMU 2 Click is capable of precise acceleration and angular rate (gyroscopic) measurement.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Application Init performs Logger and Click initialization.
 * 
 * ## Application Task  
 * This is an example which demonstrates the usage of 6DOF IMU 2 Click board.
 * It measures accel and gyro coordinates (X,Y,Z) and then the results 
 * are being sent to the UART Terminal where you can track their changes for every 1 sec.
 * 
 * *note:*
 * Default communication that is set is I2C communication.
 * If you want to use SPI, you have to set up the cfg structure.
 * Also, after uploading your code on development board it needs HW Reset 
 * ( button on Board ) so the values would be properly read.
 * 
 * \author Mihajlo Djordjevic
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c6dofimu2.h"

// ------------------------------------------------------------------ VARIABLES

static c6dofimu2_t c6dofimu2;
static log_t logger;

c6dofimu2_accel_data_t accel_data;
c6dofimu2_gyro_data_t gyro_data;


// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c6dofimu2_cfg_t cfg;

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

    c6dofimu2_cfg_setup( &cfg );
    C6DOFIMU2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu2_init( &c6dofimu2, &cfg );
    
    log_printf( &logger, "--------------------------\r\n\n" );
    log_printf( &logger, " --- 6DOF IMU 2 Click ---\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 100 );
    
    c6dofimu2_default_cfg( &c6dofimu2, &cfg );
    Delay_ms ( 100 );
    
    log_printf( &logger, " ---- Initialization ---\r\n" );
    log_printf( &logger, "--------------------------\r\n\n" );
    Delay_ms ( 100 );
}

void application_task ( void )
{
    c6dofimu2_read_accel( &c6dofimu2, &accel_data );
    Delay_ms ( 100 );
    c6dofimu2_read_gyro( &c6dofimu2, &gyro_data );
    Delay_ms ( 100 );
    
    log_printf( &logger, "    Accel    |    Gyro    \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, " X = %d  | X = %d \r\n", accel_data.accel_x, gyro_data.gyro_x );
    log_printf( &logger, " Y = %d  | Y = %d \r\n", accel_data.accel_y, gyro_data.gyro_y );
    log_printf( &logger, " Z = %d  | Z = %d \r\n", accel_data.accel_z, gyro_data.gyro_z );
    log_printf( &logger, "--------------------------\r\n" );    
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
