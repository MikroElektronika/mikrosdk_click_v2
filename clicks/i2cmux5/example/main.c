/*!
 * @file main.c
 * @brief I2cMux5 Click example
 *
 * # Description
 * This app reads "Who am I" and "Status" register of the connected click boards
 * to the I2C MUX 5 click.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes I2C driver, set the default configuration and start to write log.
 *
 * ## Application Task
 * This is an example that demonstrates the use of the I2C MUX 5 click board.
 * In this example, we read "Who am I" ( or "Status" ) register
 * of the connected click boards to the I2C MUX 5 click.
 * Channel 1 : 6DOF IMU 9 click  [slave address: 0x69; reg: 0x75; ID val.: 0xA9],
 * Channel 2 : 6DOF IMU 11 click [slave address: 0x0E; reg: 0x00; ID val.: 0x2D],
 * Channel 3 : RTC 10 click      [slave address: 0x68; reg: 0x0F; St val.: 0x88],
 * Channel 4 : Accel 10 click    [slave address: 0x18; reg: 0x0F; ID val.: 0x44].
 * Results are being sent to the Usart Terminal where you can track their changes.
 *
 * @author Nenad Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "i2cmux5.h"

static i2cmux5_t i2cmux5;
static log_t logger;
static uint8_t rx_data;


void application_init ( void ) {
    log_cfg_t log_cfg;          /**< Logger config object. */
    i2cmux5_cfg_t i2cmux5_cfg;  /**< Click config object. */

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

    i2cmux5_cfg_setup( &i2cmux5_cfg );
    I2CMUX5_MAP_MIKROBUS( i2cmux5_cfg, MIKROBUS_1 );
    err_t init_flag = i2cmux5_init( &i2cmux5, &i2cmux5_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    i2cmux5_default_cfg ( &i2cmux5 );
    log_info( &logger, " Application Task \r\n" );
    Delay_ms( 100 );
    log_printf( &logger, "-------------------------------\r\n" );
    log_printf( &logger, "        I2C MUX 5 click        \r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    
}

void application_task ( void ) {   
    
    rx_data = i2cmux5_channel_read_byte( &i2cmux5, I2CMUX5_CH_1, I2CMUX5_SET_6DOF_IMU_9_ADDR, 0x75 );
    Delay_ms( 1000 );
    log_printf( &logger, " CH-1 6DOF IMU 9 click  : 0x%X \r\n", ( uint16_t )rx_data );
    
    rx_data = i2cmux5_channel_read_byte( &i2cmux5, I2CMUX5_CH_2, I2CMUX5_SET_6DOF_IMU_11_ADDR, 0x00 );
    Delay_ms( 1000 );
    log_printf( &logger, " CH-2 6DOF IMU 11 click : 0x%X \r\n", ( uint16_t )rx_data );
    
    rx_data = i2cmux5_channel_read_byte( &i2cmux5, I2CMUX5_CH_3, I2CMUX5_SET_RTC_10_ADDR, 0x0F ); 
    Delay_ms( 1000 );
    log_printf( &logger, " CH-3 RTC 10 click      : 0x%X \r\n", ( uint16_t )rx_data ); 
    
    rx_data = i2cmux5_channel_read_byte( &i2cmux5, I2CMUX5_CH_4, I2CMUX5_SET_ACCEL_10_ADDR, 0x0F );
    Delay_ms( 1000 );
    log_printf( &logger, " CH-4 Accel 10 click    : 0x%X \r\n", ( uint16_t )rx_data );
    log_printf( &logger, "-------------------------------\r\n" );
        
    i2cmux5_hw_reset( &i2cmux5 );
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
