
---
# Heart Rate 14 Click

> [Heart Rate 14 Click](https://www.mikroe.com/?pid_product=MIKROE-7001) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7001&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : May 2026.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Heart Rate 14 Click board by reading
and displaying PPG measurements which can be visualized on the SerialPlot application.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate14

### Example Key Functions

- `heartrate14_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void heartrate14_cfg_setup ( heartrate14_cfg_t *cfg );
```

- `heartrate14_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t heartrate14_init ( heartrate14_t *ctx, heartrate14_cfg_t *cfg );
```

- `heartrate14_default_cfg` This function executes a default configuration of Heart Rate 14 Click board.
```c
err_t heartrate14_default_cfg ( heartrate14_t *ctx );
```

- `heartrate14_flush_fifo` This function clears all data from the FIFO and resets its write/read pointers and data counter to zero.
```c
err_t heartrate14_flush_fifo ( heartrate14_t *ctx );
```

- `heartrate14_wait_data_ready` This function waits until the INT pin goes LOW signaling that new data is ready to be read from the FIFO.
```c
err_t heartrate14_wait_data_ready ( heartrate14_t *ctx );
```

- `heartrate14_get_fifo_data` This function reads the FIFO whenever a new sample is ready.
```c
err_t heartrate14_get_fifo_data ( heartrate14_t *ctx, heartrate14_fifo_data_t *fifo_data );
```

### Application Init

> Initializes the driver and performs the Click default configuration for heart rate measurement.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate14_cfg_t heartrate14_cfg;  /**< Click config object. */

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
    heartrate14_cfg_setup( &heartrate14_cfg );
    HEARTRATE14_MAP_MIKROBUS( heartrate14_cfg, MIKROBUS_POSITION_HEARTRATE14 );
    if ( I2C_MASTER_ERROR == heartrate14_init( &heartrate14, &heartrate14_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEARTRATE14_ERROR == heartrate14_default_cfg ( &heartrate14 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt, then reads the PPG measurements and displays it on the
USB UART (SerialPlot).

```c
void application_task ( void ) 
{
    heartrate14_fifo_data_t fifo_data = { 0 };

    if ( HEARTRATE14_OK == heartrate14_get_fifo_data( &heartrate14, &fifo_data ) )
    {
        /* In the default configuration, ledc1 holds the Green LED PPG signal.*/
        log_printf( &logger, "%lu\r\n", fifo_data.ledc1 );
    }
    else
    {
        log_info( &logger, " No new data available." );
    }
}
```

### Note

> We recommend using the SerialPlot tool for data visualizing.

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
