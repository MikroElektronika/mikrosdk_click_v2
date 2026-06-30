/*!
 * @file main.c
 * @brief Smart IMU Click example
 *
 * # Description
 * This example demonstrates the use of the Smart IMU Click board by uploading
 * the BHI385 BSX-SAM firmware, enabling corrected accelerometer and gyroscope
 * virtual sensors at 10 Hz, and continuously reading and logging 6-axis IMU
 * data over UART.
 *
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and performs the Click default configuration.
 *
 * ## Application Task
 * Polls the host interrupt pin. When asserted, reads the interrupt
 * status register to determine which FIFO channels have pending data.
 * Wake-Up and Status FIFOs are drained and discarded; the Non-Wake-Up FIFO
 * is parsed for accelerometer and gyroscope samples. When a valid sample is
 * found, the results are displayed on the USB UART.
 *
 * @author Milan Ivancic
 *
 */

#include "board.h"
#include "log.h"
#include "smartimu.h"

#ifndef MIKROBUS_POSITION_SMARTIMU
    #define MIKROBUS_POSITION_SMARTIMU MIKROBUS_1
#endif

static smartimu_t smartimu;
static log_t logger;
static smartimu_data_t meas_data;

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartimu_cfg_t smartimu_cfg;  /**< Click config object. */

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
    smartimu_cfg_setup( &smartimu_cfg );
    SMARTIMU_MAP_MIKROBUS( smartimu_cfg, MIKROBUS_POSITION_SMARTIMU );
    err_t init_flag = smartimu_init( &smartimu, &smartimu_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_printf( &logger, " Uploading smartimu_firmware and booting...\r\n" );
    if ( SMARTIMU_ERROR == smartimu_default_cfg ( &smartimu ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

void application_task ( void )
{
    uint8_t int_status = 0;
    uint8_t sample_found = 0;

    if ( smartimu_get_int_pin( &smartimu ) )
    {
        if ( SMARTIMU_OK == smartimu_generic_read( &smartimu, SMARTIMU_REG_INT_STATUS, &int_status, 1u ) )
        {
            /* Wake-Up FIFO pending -> drain it. */
            if ( int_status & ( SMARTIMU_INT_STAT_W_IMMEDIATE |
                                SMARTIMU_INT_STAT_W_LATENCY   |
                                SMARTIMU_INT_STAT_W_NO_WATER ) )
            {
                smartimu_drain_fifo_channel( &smartimu, SMARTIMU_REG_CHAN_FIFO_W );
            }

            /* Status / Debug FIFO pending -> drain it. */
            if ( int_status & SMARTIMU_INT_STAT_STATUS_CH )
            {
                smartimu_drain_fifo_channel( &smartimu, SMARTIMU_REG_CHAN_STATUS );
            }

            /* Non-Wake-Up FIFO pending -> parse accel/gyro data. */
            if ( int_status & ( SMARTIMU_INT_STAT_NW_IMMEDIATE |
                                SMARTIMU_INT_STAT_NW_LATENCY   |
                                SMARTIMU_INT_STAT_NW_NO_WATER ) )
            {
                if ( SMARTIMU_OK == smartimu_read_fifo_channel( &smartimu,
                                                                SMARTIMU_REG_CHAN_FIFO_NW,
                                                                &meas_data,
                                                                &sample_found ) )
                {
                    if ( sample_found )
                    {
                        log_printf( &logger, " Accel X: %.3f g\r\n", meas_data.accel.x );
                        log_printf( &logger, " Accel Y: %.3f g\r\n", meas_data.accel.y );
                        log_printf( &logger, " Accel Z: %.3f g\r\n", meas_data.accel.z );
                        log_printf( &logger, " Gyro  X: %.3f dps\r\n", meas_data.gyro.x );
                        log_printf( &logger, " Gyro  Y: %.3f dps\r\n", meas_data.gyro.y );
                        log_printf( &logger, " Gyro  Z: %.3f dps\r\n", meas_data.gyro.z );
                        log_printf( &logger, "-----------------------------\r\n" );
                    }
                }
            }
        }
    }
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
