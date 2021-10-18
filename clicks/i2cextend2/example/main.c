/*!
 * @file main.c
 * @brief I2CExtend2 Click example
 *
 * # Description
 * This is an example which demonstrates the use of I2C Extend 2 Click board.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initialization driver enables - I2C,
 * check communication with device 6DOF IMU 11 Click
 * connected to the I2C Extend 2 Click ( Remote Mode ),
 * set default configuration and start measurement.
 *
 * ## Application Task
 * In this example, we read Accel and Mag axis of the connected
 * 6DOF IMU 11 Click boards to the I2C Extend 2 Click ( Remote Mode )
 * which is connected by a LAN cable to I2C Extend 2 Click ( Local Mode ).
 * Results are being sent to the Usart Terminal where you can track their changes.
 * All data logs write on USB uart changes for every 2 sec.
 *
 * @author Stefan Ilic
 *
 */

#include "board.h"
#include "log.h"
#include "i2cextend2.h"

static i2cextend2_t i2cextend2;
static log_t logger;
int16_t axis;

void i2cextend2_6dofimu11_get_axis ( i2cextend2_t *ctx, uint8_t axis_out_reg ) {
    uint16_t rx_val;
    uint8_t rx_buf[ 2 ];

    i2cextend2_rmt_multi_read( ctx, axis_out_reg, &rx_buf[ 0 ], 2 );

    rx_val = rx_buf[ 1 ];
    rx_val <<= 8;
    rx_val |= rx_buf[ 0 ];

    axis = ( int16_t ) rx_val;
}

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    i2cextend2_cfg_t i2cextend2_cfg;  /**< Click config object. */

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
    i2cextend2_cfg_setup( &i2cextend2_cfg );
    I2CEXTEND2_MAP_MIKROBUS( i2cextend2_cfg, MIKROBUS_1 );
    err_t init_flag = i2cextend2_init( &i2cextend2, &i2cextend2_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    i2cextend2_enable( &i2cextend2, I2CEXTEND2_EXTEND_ENABLE );

    if ( i2cextend2_rmt_read( &i2cextend2, C6DOFIMU11_REG_WHO_AM_I ) == C6DOFIMU11_WHO_AM_I_WIA_ID ) {
        log_printf( &logger, "        SUCCESS         \r\n" );
        log_printf( &logger, "------------------------\r\n" );
    } else {
        log_printf( &logger, "         ERROR          \r\n" );
        log_printf( &logger, "    Reset the device    \r\n" );
        log_printf( &logger, "------------------------\r\n" );
        for ( ; ; );
    }
    i2cextend2_rmt_write( &i2cextend2, C6DOFIMU11_REG_CNTL2, C6DOFIMU11_CNTL2_TEMP_EN_STANDBY_MODE |
                                                             C6DOFIMU11_CNTL2_MAG_EN_STANDBY_MODE |
                                                             C6DOFIMU11_CNTL2_ACCEL_EN_STANDBY_MODE );

    i2cextend2_rmt_write ( &i2cextend2, C6DOFIMU11_REG_INC3, C6DOFIMU11_INC3_IEL2_FIFO_TRIG |
                                                             C6DOFIMU11_INC3_IEL1_FIFO_TRIG );

    i2cextend2_rmt_write ( &i2cextend2, C6DOFIMU11_REG_CNTL2, C6DOFIMU11_CNTL2_GSEL_8G |
                                                             C6DOFIMU11_CNTL2_RES_MAX2 |
                                                             C6DOFIMU11_CNTL2_MAG_EN_OPERATING_MODE |
                                                             C6DOFIMU11_CNTL2_ACCEL_EN_OPERATING_MODE );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "------------------------\r\n" );
}

void application_task ( void ) {
    log_printf( &logger, "\t   Accel   \t|\t    Mag    \r\n" );
    log_printf( &logger, "------------------------------------------------\r\n" );

    i2cextend2_6dofimu11_get_axis( &i2cextend2, C6DOFIMU11_REG_ACCEL_XOUT_L );
    log_printf( &logger, "\t Accel X: %d\t|", axis );
    i2cextend2_6dofimu11_get_axis( &i2cextend2, C6DOFIMU11_REG_MAG_XOUT_L );
    log_printf( &logger, "\t Mag X: %d\r\n", axis );

    i2cextend2_6dofimu11_get_axis( &i2cextend2, C6DOFIMU11_REG_ACCEL_YOUT_L );
    log_printf( &logger, "\t Accel Y: %d\t|", axis );
    i2cextend2_6dofimu11_get_axis( &i2cextend2, C6DOFIMU11_REG_MAG_YOUT_L );
    log_printf( &logger, "\t Mag Y: %d\r\n", axis );

    i2cextend2_6dofimu11_get_axis( &i2cextend2, C6DOFIMU11_REG_ACCEL_ZOUT_L );
    log_printf( &logger, "\t Accel Z: %d\t|", axis );
    i2cextend2_6dofimu11_get_axis( &i2cextend2, C6DOFIMU11_REG_MAG_ZOUT_L );
    log_printf( &logger, "\t Mag Z: %d\r\n", axis );

    log_printf( &logger, "------------------------------------------------\r\n" );
    Delay_ms( 1000 );
}

void main ( void ) {
    application_init( );

    for ( ; ; ) {
        application_task( );
    }
}

// ------------------------------------------------------------------------ END
