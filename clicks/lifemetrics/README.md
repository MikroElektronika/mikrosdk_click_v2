
---
# Life Metrics Click

> [Life Metrics Click](https://www.mikroe.com/?pid_product=MIKROE-6851) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6851&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Life Metrics Click board by reading
ECG/PPG samples from the AFE FIFO and (optionally) reading accelerometer and
temperature measurements. ECG/PPG samples are parsed and logged in a simple
format suitable for plotting (e.g. serial plotter).

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LifeMetrics

### Example Key Functions

- `lifemetrics_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void lifemetrics_cfg_setup ( lifemetrics_cfg_t *cfg );
```

- `lifemetrics_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t lifemetrics_init ( lifemetrics_t *ctx, lifemetrics_cfg_t *cfg );
```

- `lifemetrics_default_cfg` This function executes a default configuration of Life Metrics Click board.
```c
err_t lifemetrics_default_cfg ( lifemetrics_t *ctx );
```

- `lifemetrics_afe_read_fifo` This function checks FIFO interrupt/status flags and reads FIFO sample data into the provided buffer.
```c
err_t lifemetrics_afe_read_fifo ( lifemetrics_t *ctx, uint8_t *fifo_data, uint16_t *fifo_data_size );
```

- `lifemetrics_accel_get_data` This function reads both acceleration and accelerometer temperature data.
```c
err_t lifemetrics_accel_get_data ( lifemetrics_t *ctx, lifemetrics_accel_data_t *data_out );
```

- `lifemetrics_temp_read_temp` This function reads the raw data from the temperature sensor and converts it to degrees Celsius.
```c
err_t lifemetrics_temp_read_temp ( lifemetrics_t *ctx, float *temp );
```

### Application Init

> Initializes the logger and Life Metrics Click driver, performs default device
configuration, reads the external temperature sensor ID, and starts AFE
measurements when enabled.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lifemetrics_cfg_t lifemetrics_cfg;  /**< Click config object. */

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
    lifemetrics_cfg_setup( &lifemetrics_cfg );
    LIFEMETRICS_MAP_MIKROBUS( lifemetrics_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == lifemetrics_init( &lifemetrics, &lifemetrics_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIFEMETRICS_ERROR == lifemetrics_default_cfg ( &lifemetrics ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    uint16_t temp_id[ 3 ] = { 0 };
    if ( LIFEMETRICS_OK == lifemetrics_temp_read_id ( &lifemetrics, temp_id ) )
    {
        log_printf ( &logger, " Temp Sensor ID: 0x%.4X%.4X%.4X\r\n", 
                     temp_id[ 2 ], temp_id[ 1 ], temp_id[ 0 ] );
    }
#if ENABLE_ECG_PPG_LOG
    if ( LIFEMETRICS_OK == lifemetrics_afe_start_meas ( &lifemetrics ) )
    {
        log_printf( &logger, " AFE measurement has started\r\n" );
    }
#endif
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and parses AFE FIFO samples (ECG/PPG) and logs them. When enabled, it
also reads accelerometer data and temperature values and logs the results.

```c
void application_task ( void )
{
#if ENABLE_ECG_PPG_LOG
    uint8_t fifo_data[ LIFEMETRICS_AFE_FIFO_BUFFER_SIZE ] = { 0 };
    uint16_t fifo_data_size = 0;
    if ( LIFEMETRICS_OK == lifemetrics_afe_read_fifo ( &lifemetrics, fifo_data, &fifo_data_size ) )
    {
        lifemetrics_afe_log_fifo ( fifo_data, fifo_data_size );
    }
#endif
#if ENABLE_ACCEL_TEMP_LOG
    float temperature = 0;
    lifemetrics_accel_data_t meas_data;
    if ( LIFEMETRICS_OK == lifemetrics_accel_get_data ( &lifemetrics, &meas_data ) )
    {
        log_printf( &logger, "Accel X: %.3f g\r\n", meas_data.accel.x );
        log_printf( &logger, "Accel Y: %.3f g\r\n", meas_data.accel.y );
        log_printf( &logger, "Accel Z: %.3f g\r\n", meas_data.accel.z );
        if ( LIFEMETRICS_OK == lifemetrics_temp_read_temp ( &lifemetrics, &temperature ) )
        {
            log_printf ( &logger, "Temperature: %.2f degC\r\n", temperature );
        }
    }
#endif
}
```

### Note

> We recommend using the SerialPlot tool for data visualizing. 
Make sure to set up ECG electrodes properly.
Use prefix "E:" in the app for ECG data filtering, and prefix "P:" for PPG filtering.

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
