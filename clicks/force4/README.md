
---
# Force 4 Click

> [Force 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4193) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4193&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example shows the use of Force 4 Click.
> It reads 12bit ADC value, using I2C communication,
> at the interval of one second. 
> The result is represented on the UART terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Force4

### Example Key Functions

- `force4_cfg_setup` Config Object Initialization function. 
```c
void force4_cfg_setup ( force4_cfg_t *cfg );
``` 
 
- `force4_init` Initialization function. 
```c
err_t force4_init ( force4_t *ctx, force4_cfg_t *cfg );
```

- `force4_read_adc` This function reads 12bit ADC data from device. 
```c
uint16_t force4_read_adc ( force4_t *ctx );
```

### Application Init

> Initializes the driver and logger, and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    force4_cfg_t cfg;

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
    Delay_ms ( 100 );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    force4_cfg_setup( &cfg );
    FORCE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force4_init( &force4, &cfg );
    Delay_ms ( 100 );
}
```

### Application Task

> It reads 12bit ADC value, using I2C communication,
> at the interval of one second.
> The result is represented on the UART terminal.

```c
void application_task ( void )
{
    adc_val = force4_read_adc( &force4 );
    log_printf( &logger, "ADC value: %d\r\n", adc_val );
    Delay_ms ( 1000 );
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
