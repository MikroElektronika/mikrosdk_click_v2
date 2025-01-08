
---
# Heart Rate 5 Click

> [Heart Rate 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3012) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3012&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example showcases ability for device to read Heart Rate 5 Click Board

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HeartRate5

### Example Key Functions

- `heartrate5_cfg_setup` Config Object Initialization function.
```c
void heartrate5_cfg_setup ( heartrate5_cfg_t *cfg );
```

- `heartrate5_init` Initialization function.
```c
err_t heartrate5_init ( heartrate5_t *ctx, heartrate5_cfg_t *cfg );
```

- `heartrate5_default_cfg` Click Default Configuration function.
```c
err_t heartrate5_default_cfg ( heartrate5_t *ctx );
```

- `heartrate5_write_reg` Heart Rate 5 register write function.
```c
void heartrate5_write_reg( heartrate5_t *ctx, uint8_t reg_addr, uint32_t write_data ); 
```

- `heartrate5_read_reg` Heart Rate 5 register reading function.
```c
uint32_t heartrate5_read_reg( heartrate5_t *ctx, uint8_t reg_addr ); 
```

- `heartrate5_sw_reset` Heart Rate 5 software reset function.
```c
void heartrate5_sw_reset( heartrate5_t *ctx );
```

### Application Init

> Configures the micro controller for communication and initializes the Click board. 

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    heartrate5_cfg_t heartrate5_cfg;  /**< Click config object. */

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
    heartrate5_cfg_setup( &heartrate5_cfg );
    HEARTRATE5_MAP_MIKROBUS( heartrate5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == heartrate5_init( &heartrate5, &heartrate5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HEARTRATE5_ERROR == heartrate5_default_cfg ( &heartrate5 ) )
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
    if( heartrate5_get_led2_aled2_val( &heartrate5 ) < 10 )
    {
        sensor_value = heartrate5_get_aled1_val( &heartrate5 );
        log_printf( &logger, "%lu,%lu \r\n", sensor_value, time );
        time += 10;
        Delay_ms ( 10 );
    }
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
