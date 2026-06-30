
---
# Smart IMU Click

> [Smart IMU Click](https://www.mikroe.com/?pid_product=MIKROE-6932) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6932&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Apr 2026.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of the Smart IMU Click board by uploading
the BHI385 BSX-SAM firmware, enabling corrected accelerometer and gyroscope
virtual sensors at 10 Hz, and continuously reading and logging 6-axis IMU
data over UART.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartIMU

### Example Key Functions

- `smartimu_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void smartimu_cfg_setup ( smartimu_cfg_t *cfg );
```

- `smartimu_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t smartimu_init ( smartimu_t *ctx, smartimu_cfg_t *cfg );
```

- `smartimu_default_cfg` This function executes a default configuration of Smart IMU Click board.
```c
err_t smartimu_default_cfg ( smartimu_t *ctx );
```

- `smartimu_send_command` This function builds and sends a command packet to the BHI385 via DMA channel 0 (register 0x00).
```c
err_t smartimu_send_command ( smartimu_t *ctx, uint16_t cmd_id, uint8_t *payload, uint16_t payload_len );
```

- `smartimu_upload_firmware` This function uploads a firmware binary image to the BHI385 program RAM using the bootloader upload protocol.
```c
err_t smartimu_upload_firmware ( smartimu_t *ctx, const uint8_t *fw_data, uint32_t fw_size ); 
```

- `smartimu_configure_vir_sensor` This function configures a virtual sensor on the BHI385 by sending a configure sensor command (0x000D).
```c
err_t smartimu_configure_vir_sensor ( smartimu_t *ctx, uint8_t sensor_id, float odr_hz, uint32_t latency_ms );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
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
```

### Application Task

> Polls the host interrupt pin. When asserted, reads the interrupt
status register to determine which FIFO channels have pending data.
Wake-Up and Status FIFOs are drained and discarded; the Non-Wake-Up FIFO
is parsed for accelerometer and gyroscope samples. When a valid sample is
found, the results are displayed on the USB UART.

```c
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
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
