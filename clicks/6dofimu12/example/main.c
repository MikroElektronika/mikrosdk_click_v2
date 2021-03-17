/*!
 * \file 
 * \brief C6DofImu12 Click example
 * 
 * # Description
 * This example demonstrates the use of 6DOF IMU 12 click board.
 *
 * The demo application is composed of two sections :
 * 
 * ## Application Init 
 * Initializes the driver and checks the communication then initializes the device 
 * and sets the device default configuration.
 * 
 * ## Application Task  
 * Measures acceleration and gyroscope data and displays the results on USB UART each second.
 * 
 * \author MikroE Team
 *
 */
// ------------------------------------------------------------------- INCLUDES

#include "board.h"
#include "log.h"
#include "c6dofimu12.h"
#include "c6dofimu12_config.h"

// ------------------------------------------------------------------ VARIABLES

static c6dofimu12_t c6dofimu12;
static c6dofimu12_accel_t c6dofimu12_accel;
static c6dofimu12_gyro_t c6dofimu12_gyro;

static log_t logger;

// ------------------------------------------------------ APPLICATION FUNCTIONS

void application_init ( void )
{
    uint8_t tx_buf;

    log_cfg_t log_cfg;
    c6dofimu12_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c6dofimu12_cfg_setup( &cfg );
    C6DOFIMU12_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c6dofimu12_init( &c6dofimu12, &cfg );
    Delay_ms( 100 );

    log_printf( &logger, " Driver init done \r\n" );
    log_printf( &logger, "----------------------------------\r\n");
    
    if ( c6dofimu12_check_id( &c6dofimu12 ) == C6DOFIMU12_SUCCESS )
    {
        log_printf( &logger, "  Communication OK\r\n" );
        log_printf( &logger, "----------------------------------\r\n");
    }
    else
    {
        log_printf( &logger, " Communication ERROR\r\n" );
        log_printf( &logger, " Reset the device\r\n" );
        log_printf( &logger, "----------------------------------\r\n");

        for ( ; ; );
    }
    
    tx_buf = C6DOFIMU12_PWR_CONF_ADV_PWR_SAVE_DISABLED | 
             C6DOFIMU12_FIFO_READ_DISABLED | 
             C6DOFIMU12_FAST_PWR_UP_DISABLED;
    c6dofimu12_generic_write( &c6dofimu12, C6DOFIMU12_REG_PWR_CONF_ADDR, &tx_buf, 1 );
    Delay_ms( 100 );
    tx_buf = C6DOFIMU12_CMD_INITIALIZATION_START;
    c6dofimu12_generic_write( &c6dofimu12, C6DOFIMU12_REG_INIT_CTRL_ADDR, &tx_buf, 1 );
    Delay_ms( 100 );
    c6dofimu12_generic_write( &c6dofimu12, C6DOFIMU12_REG_INIT_DATA_ADDR, bmi270_config_file, 8192 );
    Delay_ms( 100 );
    tx_buf = C6DOFIMU12_CMD_INITIALIZATION_STOP;
    c6dofimu12_generic_write( &c6dofimu12, C6DOFIMU12_REG_INIT_CTRL_ADDR, &tx_buf, 1 );
    Delay_ms( 100 );

    if ( c6dofimu12_check_init_status( &c6dofimu12 ) == C6DOFIMU12_SUCCESS )
    {
        log_printf( &logger, " Initialization completed\r\n" );
        log_printf( &logger, "----------------------------------\r\n");
    }
    else
    {
        log_printf( &logger, " Initialization ERROR\r\n" );
        log_printf( &logger, " Reset the device\r\n" );
        log_printf( &logger, "----------------------------------\r\n");
        
        for( ; ; );
    }
    c6dofimu12_default_cfg( &c6dofimu12 );
    Delay_ms( 100 );
}

void application_task ( void )
{
    c6dofimu12_get_data( &c6dofimu12, &c6dofimu12_accel, &c6dofimu12_gyro );

    log_printf( &logger, " Accel X: %d | Gyro X: %d\r\n", c6dofimu12_accel.x, c6dofimu12_gyro.x );
    log_printf( &logger, " Accel Y: %d | Gyro Y: %d\r\n", c6dofimu12_accel.y, c6dofimu12_gyro.y );
    log_printf( &logger, " Accel Z: %d | Gyro Z: %d\r\n", c6dofimu12_accel.z, c6dofimu12_gyro.z );
    log_printf( &logger, "----------------------------------\r\n");
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
