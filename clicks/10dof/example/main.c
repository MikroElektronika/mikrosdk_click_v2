/*!
 * \file 
 * \brief C10Dof Click example
 * 
 * # Description
 * This example shows temperature,humidity,pressure, and values such as 
 * accel, gyro and magnetometer coordinates for X,Y and Z axis.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables - I2C,
 * set default configuration of BMP180 and BNO055 chip, also display logs.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of 10DOF Click board.
 * Measured temperature, humidity pressure data from the BME180 chip sensor
 * and accel, gyro and magnetometar coordinates values for X-axis, Y-axis and Z-axis.
 * Display temperature data to degrees Celsius [ C ],
 * pressure data [ mbar ], rate in dps, accel in mg and magnetometar in �T.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for every 3 sec.
 * 
 * ## NOTE
 * Additional pull-up on I2C lines might be required.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c10dof.h"

// ------------------------------------------------------------------ VARIABLES

static c10dof_t c10dof;
static log_t logger;
static int16_t accelX;
static int16_t accelY;
static int16_t accelZ;
static int16_t gyroX;
static int16_t gyroY;
static int16_t gyroZ;
static int16_t magX;
static int16_t magY;
static int16_t magZ;
static float temperature;
static float pressure;
static char deg_cel[ 4 ];

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c10dof_cfg_t cfg;

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

    c10dof_cfg_setup( &cfg );
    C10DOF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c10dof_init( &c10dof, &cfg );
    c10dof_default_cfg( &c10dof );
}

void application_task ( void )
{
    c10dof_read_accel( &c10dof, &accelX, &accelY, &accelZ );
    Delay_ms( 10 );
    c10dof_read_gyro( &c10dof, &gyroX,  &gyroY, &gyroZ );
    Delay_ms( 10 );
    c10dof_read_mag( &c10dof, &magX,  &magY, &magZ );
    Delay_ms( 10 );
    
    temperature = c10dof_get_temperature( &c10dof );
    Delay_ms( 10 );
    c10dof_get_measurements( &c10dof, &temperature, &pressure );
    Delay_ms( 10 );

    log_printf( &logger, "Accel X : %d  |  ", accelX );
    log_printf( &logger, "Gyro X  : %d  |  ", gyroX );
    log_printf( &logger, "Mag X   : %d  |  ", magX );
    log_printf( &logger, "Temp.   : %.2f C  \r\n", temperature, deg_cel);

    log_printf( &logger, "Accel Y : %d  |  ", accelY);
    log_printf( &logger, "Gyro Y  : %d  |  ", gyroY);
    log_printf( &logger, "Mag Y   : %d  |  \r\n", magY);

    log_printf( &logger, "Accel Z : %d  |  ", accelZ);
    log_printf( &logger, "Gyro Z  : %d  |  ", gyroZ);
    log_printf( &logger, "Mag Z   : %d  |  ", magZ);
    log_printf( &logger, "Press.  : %.2f mbar \r\n", pressure);

    log_printf( &logger, "--------------------------------------------------------------------\r\n", pressure);
    Delay_ms( 500 );
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
