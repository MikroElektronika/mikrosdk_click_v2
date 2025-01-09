
---
# Hall Current 6 Click

> [Hall Current 6 Click](https://www.mikroe.com/?pid_product=MIKROE-3443) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3443&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> 
> This application reads current data.
> 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.HallCurrent6

### Example Key Functions

- `hallcurrent6_cfg_setup` Config Object Initialization function.
```c
void hallcurrent6_cfg_setup ( hallcurrent6_cfg_t *cfg ); 
```

- `hallcurrent6_init` Initialization function.
```c
err_t hallcurrent6_init ( hallcurrent6_t *ctx, hallcurrent6_cfg_t *cfg );
```

- `hallcurrent6_read_data` Reads ADC current data
```c
uint16_t hallcurrent6_read_data ( hallcurrent6_t *ctx );
```

- `hallcurrent6_get_current` Reads current data
```c
float hallcurrent6_get_current ( hallcurrent6_t *ctx );
```

- `hallcurrent6_generic_read` Generic read function.
```c
void hallcurrent6_generic_read ( hallcurrent6_t *ctx, uint8_t reg, uint8_t *data_buf, uint8_t len );
```

### Application Init

>
> Initializations driver init
> 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    hallcurrent6_cfg_t cfg;

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
    log_info( &logger, "---- App Init ----" );

    //  Click initialization.

    hallcurrent6_cfg_setup( &cfg );
    HALLCURRENT6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    hallcurrent6_init( &hallcurrent6, &cfg );

    log_info( &logger, "---- App Init Done ----" );
}
```

### Application Task

>
> Reads Current data in mA and logs this data to USBUART every 1 sec.
> 

```c
void application_task ( void )
{
    float current;

    current = hallcurrent6_get_current( &hallcurrent6 );
    log_printf( &logger, " Current value: %.2f mA \r\n" , current);
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
