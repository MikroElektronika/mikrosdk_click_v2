/*!
 * @file main.c
 * @brief I2cToCan Click example
 *
 * # Description
 * This library contains API for the I2C to CAN click driver.
 * This demo application shows an example of an I2C CAN click 
 * wired to the VAV Press click for reading 
 * differential pressure and temperature measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization and default settings, 
 * the app set VAV Press click I2C slave address ( 0x5C ) 
 * and enable device.
 *
 * ## Application Task
 * This is an example that shows the use of an I2C to CAN click board™.
 * Logs pressure difference [ Pa ] and temperature [ degree Celsius ] values 
 * of the VAV Press click wired to the I2C to CAN click board™.  
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @note
 * void get_dif_press_and_temp ( void ) - Get differential pressure and temperature function. 
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "i2ctocan.h"

#define I2CTOCAN_VAV_PRESS_DEV_ADDR                            0x5C
#define I2CTOCAN_VAV_PRESS_CMD_START_PRESSURE_CONVERSION       0x21
#define I2CTOCAN_VAV_PRESS_PRESS_SCALE_FACTOR                  1200
#define I2CTOCAN_VAV_PRESS_TEMP_SCALE_FACTOR                     72
#define I2CTOCAN_VAV_PRESS_READOUT_AT_KNOWN_TEMPERATURE         105
#define I2CTOCAN_VAV_PRESS_KNOWN_TEMPERATURE_C                   23.1

static i2ctocan_t i2ctocan;
static log_t logger;
static float diff_press;
static float temperature;

void get_dif_press_and_temp ( void ) {
    uint8_t rx_buf[ 4 ];
    int16_t readout_data;
    
    i2ctocan_generic_read( &i2ctocan, I2CTOCAN_VAV_PRESS_CMD_START_PRESSURE_CONVERSION, &rx_buf[ 0 ], 4 );
    
    readout_data = rx_buf[ 1 ];
    readout_data <<= 9;
    readout_data |= rx_buf[ 0 ];
    readout_data >>= 1;
    
    diff_press = ( float ) readout_data;
    diff_press /= I2CTOCAN_VAV_PRESS_PRESS_SCALE_FACTOR;
   
    readout_data = rx_buf[ 3 ];
    readout_data <<= 8;
    readout_data |= rx_buf[ 2 ];
    
    temperature = ( float ) readout_data;
    temperature -= I2CTOCAN_VAV_PRESS_READOUT_AT_KNOWN_TEMPERATURE;
    temperature /= I2CTOCAN_VAV_PRESS_TEMP_SCALE_FACTOR;
    temperature += I2CTOCAN_VAV_PRESS_KNOWN_TEMPERATURE_C;
    
}

void application_init ( void ) {
    log_cfg_t log_cfg;            /**< Logger config object. */
    i2ctocan_cfg_t i2ctocan_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    i2ctocan_cfg_setup( &i2ctocan_cfg );
    I2CTOCAN_MAP_MIKROBUS( i2ctocan_cfg, MIKROBUS_1 );
    err_t init_flag = i2ctocan_init( &i2ctocan, &i2ctocan_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    i2ctocan_default_cfg ( &i2ctocan );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
    
    log_printf( &logger, "--------------------------------\r\n" );
    log_printf( &logger, "     Set I2C Slave Address      \r\n" );
    i2ctocan_set_slave_address ( &i2ctocan, I2CTOCAN_VAV_PRESS_DEV_ADDR );
    Delay_ms( 100 );
    
    log_printf( &logger, "--------------------------------\r\n" );
    log_printf( &logger, "          Enable Device         \r\n" );
    log_printf( &logger, "--------------------------------\r\n" );
    i2ctocan_enable_device( &i2ctocan );
    Delay_ms( 100 );
}

void application_task ( void ) {
    get_dif_press_and_temp( );
    
    log_printf( &logger, " Diff. Pressure    : %.4f Pa\r\n", diff_press );
    log_printf( &logger, " Temperature       : %.4f C\r\n", temperature );
    log_printf( &logger, "--------------------------------\r\n" );
    Delay_ms( 2000 );
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
