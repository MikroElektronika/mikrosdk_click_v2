/*!
 * @file main.c
 * @brief I2C Isolator 5 Click example
 *
 * # Description
 * This library contains API for the I2C Isolator 5 Click driver.
 * This demo application shows an example of an I2C Isolator 5 Click 
 * wired to the VAV Press Click for reading 
 * differential pressure and temperature measurement.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization of I2C module and log UART.
 * After driver initialization and default settings, 
 * the app set VAV Press Click I2C slave address ( 0x5C ) 
 * and enable device.
 *
 * ## Application Task
 * This is an example that shows the use of an I2C Isolator 5 Click board™.
 * Logs pressure difference [ Pa ] and temperature [ degree Celsius ] values 
 * of the VAV Press Click written to the I2C Isolator 5 Click board™.  
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "i2cisolator5.h"

#define I2CISOLATOR5_VAV_PRESS_DEV_ADDR                             0x5C
#define I2CISOLATOR5_VAV_PRESS_CMD_START_PRESSURE_CONVERSION        0x21
#define I2CISOLATOR5_VAV_PRESS_PRESS_SCALE_FACTOR                   1200
#define I2CISOLATOR5_VAV_PRESS_TEMP_SCALE_FACTOR                    72
#define I2CISOLATOR5_VAV_PRESS_READOUT_AT_KNOWN_TEMPERATURE         105
#define I2CISOLATOR5_VAV_PRESS_KNOWN_TEMPERATURE_C                  23.1

static i2cisolator5_t i2cisolator5;
static log_t logger;
static float diff_press;
static float temperature;

/**
 * @brief I2C Isolator 5 get pressure difference and temperature function.
 * @details This function reads pressure difference and temperature from the VAV Press Click.
 * @return @li @c  0 - Success,
 *         @li @c -1 - Error.
 * See #err_t definition for detailed explanation.
 * @note None.
 */
err_t i2cisolator5_get_press_and_temp ( void );

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cisolator5_cfg_t i2cisolator5_cfg;  /**< Click config object. */

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
    i2cisolator5_cfg_setup( &i2cisolator5_cfg );
    I2CISOLATOR5_MAP_MIKROBUS( i2cisolator5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == i2cisolator5_init( &i2cisolator5, &i2cisolator5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Set VAV Press Click I2C Slave Address \r\n" );
    i2cisolator5_set_slave_address ( &i2cisolator5, I2CISOLATOR5_VAV_PRESS_DEV_ADDR );
    Delay_ms ( 100 );
    
    log_info( &logger, " Application Task " );
}

void application_task ( void ) 
{
    if ( I2CISOLATOR5_OK == i2cisolator5_get_press_and_temp( ) )
    {
        log_printf( &logger, " Diff. Pressure : %.4f Pa \r\n", diff_press );
        log_printf( &logger, " Temperature : %.2f C \r\n", temperature );
        log_printf( &logger, "--------------------------------\r\n" );
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

err_t i2cisolator5_get_press_and_temp ( void ) 
{
    err_t error_flag = I2CISOLATOR5_OK;
    uint8_t rx_buf[ 4 ] = { 0 };
    uint8_t tx_cmd = I2CISOLATOR5_VAV_PRESS_CMD_START_PRESSURE_CONVERSION;
    int16_t readout_data;
    
    error_flag |= i2cisolator5_write_then_read( &i2cisolator5, &tx_cmd, 1, rx_buf, 4 );
    
    if ( I2CISOLATOR5_OK == error_flag )
    {
        readout_data = rx_buf[ 1 ];
        readout_data <<= 8;
        readout_data |= rx_buf[ 0 ];
        readout_data <<= 1;
        readout_data >>= 1;
    
        diff_press = ( float ) readout_data;
        diff_press /= I2CISOLATOR5_VAV_PRESS_PRESS_SCALE_FACTOR;
   
        readout_data = rx_buf[ 3 ];
        readout_data <<= 8;
        readout_data |= rx_buf[ 2 ];
    
        temperature = ( float ) readout_data;
        temperature -= I2CISOLATOR5_VAV_PRESS_READOUT_AT_KNOWN_TEMPERATURE;
        temperature /= I2CISOLATOR5_VAV_PRESS_TEMP_SCALE_FACTOR;
        temperature += I2CISOLATOR5_VAV_PRESS_KNOWN_TEMPERATURE_C;
    }
    
    return error_flag;
}

// ------------------------------------------------------------------------ END
