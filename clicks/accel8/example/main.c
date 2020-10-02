/*!
 * \file 
 * \brief Accel8 Click example
 * 
 * # Description
 * This application measures accelermeter and gyroscopic data and temperature.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initialization driver init, reset chip and start configuration chip for measurement.
 * 
 * ## Application Task  
 * Reads Accel X/Y/Z axis, Gyro X/Y/Z axis and device Temperature. 
 * All data logs on the USBUART every 2 sec.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "accel8.h"

// ------------------------------------------------------------------ VARIABLES

static accel8_t accel8;
static log_t logger;
static range_retval_t range;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel8_cfg_t cfg;

    uint8_t temp_write;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 115200;
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    accel8_cfg_setup( &cfg );
    ACCEL8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    temp_write = accel8_init( &accel8, &cfg );
	
	if ( temp_write ==  ACCEL8_INIT_ERROR )
	{
		log_info( &logger, "ERROR\r\n" );
		for ( ; ; );
	}

    log_printf( &logger, " *-* Device Reset *-* \r\n");
    temp_write = ACCEL8_PM1_DEVICE_RESET;
    accel8_generic_write( &accel8, ACCEL8_REG_PWR_MGMT_1, &temp_write, 1 );
    temp_write = ACCEL8_GYRO_RESET | ACCEL8_ACCEL_RESET | ACCEL8_TEMP_RESET;
    accel8_generic_write( &accel8, ACCEL8_REG_SIGNAL_PATH_RESET, &temp_write, 1 );
	Delay_ms( 500 );
    log_printf( &logger, " *-* Device Configuration *-* \r\n" );
    accel8_default_cfg ( &accel8, ACCEL8_ACCEL_CFG_FULL_SCALE_RANGE_2g, ACCEL8_GYRO_CFG_FULL_SCALE_RANGE_250dbs, &range);

    Delay_ms( 1000 );
    log_printf( &logger, " --- Start Measurement --- \r\n" );Delay_ms( 100 );
}

void application_task ( void )
{   
    float temperature;
    int16_t x_gyro_axis;
    int16_t y_gyro_axis;
    int16_t z_gyro_axis;
    int16_t x_accel_axis;
    int16_t y_accel_axis;
    int16_t z_accel_axis;

    //  Task implementation.

    accel8_get_accel_axis( &accel8,&x_accel_axis, &y_accel_axis, &z_accel_axis );
    accel8_get_gyro_axis( &accel8, &x_gyro_axis, &y_gyro_axis , &z_gyro_axis );
    temperature = accel8_get_temperature( &accel8 );
    
    // LOGS DATA

    log_printf( &logger, "________________ Accel 8 click _________\r\n" );
    log_printf( &logger, "|  Data   | X axis | Y axis | Z axis |  Range  |\r\n" );
    log_printf( &logger, "|______|______|______|_____|________|\r\n" );
    log_printf( &logger, "|  Accel  | %d    | %d    | %d    | %dg    |\r\n", x_accel_axis, y_accel_axis, z_accel_axis, &range.accel_range );
    log_printf( &logger, "|_______|______|_____|_______|_______|\r\n" );
    log_printf( &logger, "|  Gyro    | %d     | %d     | %d     | %ddps   |\r\n", x_gyro_axis, y_gyro_axis, z_gyro_axis, &range.gyro_range );
    log_printf( &logger, "|_______|_______|______|______|________|\r\n" );
    log_printf( &logger, "|  Temp   | %.2f  C         |\r\n" , temperature);
    log_printf( &logger, "|_______|____________|\r\n" );

    log_printf( &logger, " \r\n" );
    Delay_ms( 1000 );
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
