/*!
 * \file 
 * \brief c13DOF Click example
 * 
 * # Description
 * This example displays values registered by sensors on click board.
 * 
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver enables -
 * BME680 Low power gas, pressure, temperature & humidity sensor, 
 * BMI088 6-axis Motion Tracking Sensor and
 * BMM150 Geomagnetic Sensor, also write log.
 * 
 * ## Application Task  
 * This is a example which demonstrates the use of 13DOF Click board.
 * Measures and display temperature in degrees Celsius [ C ], humidity data [ % ], 
 * pressure [ mbar ] and gas resistance data from the BME680 sensor.
 * Measures and display Accel and Gyro data coordinates values 
 * for X-axis, Y-axis and Z-axis from the BMI088 sensor.
 * Measures and display Geomagnetic data coordinates values for 
 * X-axis, Y-axis and Z-axis from the BMM150 sensor.
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on usb uart changes for each second.
 * 
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c13dof.h"

// ------------------------------------------------------------------ VARIABLES

static c13dof_t c13dof;
static log_t logger;
float temperature;
float pressure;
float humidity;
int32_t gas_res;
int16_t accel_x;
int16_t accel_y;
int16_t accel_z;
int16_t gyro_x;
int16_t gyro_y;
int16_t gyro_z;
int16_t mag_x;
int16_t mag_y;
int16_t mag_z;
uint16_t r_hall;
uint8_t ready_check;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    c13dof_cfg_t cfg;

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

    c13dof_cfg_setup( &cfg );
    C13DOF_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c13dof_init( &c13dof, &cfg );
    c13dof_default_cfg( &c13dof );
}

void application_task ( void )
{
    temperature = c13dof_bme680_get_temperature( &c13dof );

    log_printf( &logger, "----------------------------------------------------------\n");
    log_printf( &logger, "Temperature : %.2f C \r\n", temperature );

    humidity = c13dof_bme680_get_humidity( &c13dof );
    log_printf( &logger, "Humidity : %.2f %% \r\n", humidity );

    pressure = c13dof_bme680_get_pressure( &c13dof );
    log_printf( &logger, "Pressure : %.2f mbar \r\n", pressure );

    gas_res = c13dof_bme680_get_gas_resistance( &c13dof );
    log_printf( &logger, "Gas Resistance : %ld \r\n", gas_res );
    
    ready_check = c13dof_bmm150_check_ready( &c13dof );

    while ( ready_check != C13DOF_BMM150_DATA_READY )
    {
        ready_check = c13dof_bmm150_check_ready( &c13dof );
    }
    
    c13dof_bmi088_read_accel( &c13dof, &accel_x, &accel_y, &accel_z );
    c13dof_bmi088_read_gyro( &c13dof, &gyro_x, &gyro_y, &gyro_z );
    c13dof_bmm150_read_geo_mag_data( &c13dof, &mag_x, &mag_y, &mag_z, &r_hall );
    
    log_printf( &logger, "Accel X : %d ", accel_x );
    log_printf( &logger, " Y : %d ", accel_y );
    log_printf( &logger, " Z : %d \r\n", accel_z );
    
    log_printf( &logger, "Gyro X : %d ", gyro_x );
    log_printf( &logger, " Y : %d ", gyro_y );
    log_printf( &logger, " Z : %d \r\n", gyro_z );
        
    log_printf( &logger, "Mag X : %d ", mag_x );
    log_printf( &logger, " Y : %d ", mag_y );
    log_printf( &logger, " Z : %d \r\n", mag_z );

    Delay_ms ( 1000 );
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
