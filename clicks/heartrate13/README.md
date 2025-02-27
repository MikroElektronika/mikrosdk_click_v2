
---
# Heart Rate 13 Click

> [Heart Rate 13 Click](https://www.mikroe.com/?pid_product=MIKROE-6490) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6490&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2024.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Heart Rate 13 Click board by reading and displaying the PPG measurements which can be visualized on the SerialPlot application.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate13

### Example Key Functions

- `heartrate13_cfg_setup` Config Object Initialization function.
```c
void heartrate13_cfg_setup ( heartrate13_cfg_t *cfg );
```

- `heartrate13_init` Initialization function.
```c
err_t heartrate13_init ( heartrate13_t *ctx, heartrate13_cfg_t *cfg );
```

- `heartrate13_default_cfg` Click Default Configuration function.
```c
err_t heartrate13_default_cfg ( heartrate13_t *ctx );
```

- `heartrate13_get_pd_data` This function waits for the data ready interrupt and then reads data from photodiodes PD1, PD2, and PD3.
```c
err_t heartrate13_get_pd_data ( heartrate13_t *ctx, heartrate13_pd_data_t *pd_data );
```

- `heartrate13_set_mode` This function sets the device operating mode.
```c
err_t heartrate13_set_mode ( heartrate13_t *ctx, uint8_t mode );
```

- `heartrate13_sw_reset` This function executes software reset of the device.
```c
err_t heartrate13_sw_reset ( heartrate13_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration for heart rate measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate13_cfg_t heartrate13_cfg;  /**< Click config object. */

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
    heartrate13_cfg_setup( &heartrate13_cfg );
    HEARTRATE13_MAP_MIKROBUS( heartrate13_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate13_init( &heartrate13, &heartrate13_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEARTRATE13_ERROR == heartrate13_default_cfg ( &heartrate13 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the data ready interrupt, then reads the PPG measurements and displays it on the USB UART (SerialPlot).

```c
void application_task ( void )
{
    heartrate13_pd_data_t pd_data;
    if ( HEARTRATE13_OK == heartrate13_get_pd_data ( &heartrate13, &pd_data ) )
    {
        log_printf ( &logger, "%u\r\n", pd_data.pd3 );
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
