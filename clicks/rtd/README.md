
---
# RTD Click

> [RTD Click](https://www.mikroe.com/?pid_product=MIKROE-2815) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2815&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This app measures temperature and converts the data to celsius degrees.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Rtd

### Example Key Functions

- `rtd_cfg_setup` Config Object Initialization function.
```c
void rtd_cfg_setup ( rtd_cfg_t *cfg ); 
```

- `rtd_init` Initialization function.
```c
err_t rtd_init ( rtd_t *ctx, rtd_cfg_t *cfg );
```

- `rtd_read_register` This function reads data from the chosen register.
```c
uint8_t rtd_read_register ( rtd_t *ctx, uint8_t reg_address );
```

- `rtd_read_temperature` This function reads data from temperature registers.
```c
uint16_t rtd_read_temperature ( rtd_t *ctx );
```

- `rtd_convert_temperature` This function convert data from temperature registers.
```c
float rtd_convert_temperature ( rtd_t *ctx, uint16_t input_data, uint16_t referent_resistance );
```

### Application Init

> Initializes RTD Click driver, and sets the
> proper configuration mode for three wire RTD.

```c
 
void application_init ( void )
{
    log_cfg_t log_cfg;
    rtd_cfg_t cfg;

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
    rtd_cfg_setup( &cfg );
    RTD_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    rtd_init( &rtd, &cfg );
    
    RTD_SET_DATA_SAMPLE_EDGE;

    rtd_write_register( &rtd, RTD_CONFIGURATION, 0xD0 );
    Delay_ms ( 100 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Measures temperature, converts the data to celsius degrees,
> and displays it on the USB UART.

```c
void application_task ( void )
{
    uint16_t read_value = 0;
    float converted_value = 0;

    read_value = rtd_read_temperature( &rtd );
    converted_value = rtd_convert_temperature( &rtd, read_value, RTD_REF_RESISTANCE_470 );

    log_printf( &logger, " Current temperature: %.2f \r\n", converted_value );

    Delay_ms ( 300 );
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
