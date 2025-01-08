
---
# Heart Rate 7 Click

> [Heart Rate 7 Click](https://www.mikroe.com/?pid_product=MIKROE-2998) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2998&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases ability for device to read Heart Rate 7 Click Board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate7

### Example Key Functions

- `heartrate7_cfg_setup` Config Object Initialization function.
```c
void heartrate7_cfg_setup ( heartrate7_cfg_t *cfg );
```

- `heartrate7_init` Initialization function.
```c
err_t heartrate7_init ( heartrate7_t *ctx, heartrate7_cfg_t *cfg );
```

- `heartrate7_default_cfg` Click Default Configuration function.
```c
err_t heartrate7_default_cfg ( heartrate7_t *ctx );
```

- `heartrate7_write_reg` Heart Rate 7 register write function.
```c
void heartrate7_write_reg( heartrate7_t *ctx, uint8_t reg_addr, uint32_t write_data ); 
```

- `heartrate7_read_reg` Heart Rate 7 register reading function.
```c
uint32_t heartrate7_read_reg( heartrate7_t *ctx, uint8_t reg_addr ); 
```

- `heartrate7_sw_reset` Heart Rate 7 software reset function.
```c
void heartrate7_sw_reset( heartrate7_t *ctx );
```

### Application Init

> Configures the micro controller for communication and initializes the Click board. 

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate7_cfg_t heartrate7_cfg;  /**< Click config object. */

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
    heartrate7_cfg_setup( &heartrate7_cfg );
    HEARTRATE7_MAP_MIKROBUS( heartrate7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate7_init( &heartrate7, &heartrate7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEARTRATE7_ERROR == heartrate7_default_cfg ( &heartrate7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This section shows how the data is processed and sent to the MikroPlot application.

```c
void application_task ( void ) 
{
    sensor_value = heartrate7_get_aled1_val( &heartrate7 );
    log_printf( &logger, "%lu,%lu \r\n", sensor_value, time );
    time += 10;
    Delay_ms ( 10 );
}
```

### Note

> For testing this example application SerialPlot was used. 
> There you can see heart rate graphicly shown.

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
