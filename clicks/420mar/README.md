
---
# 4-20 mA R Click

> [4-20 mA R Click](https://www.mikroe.com/?pid_product=MIKROE-1387) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1387&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example showcases how to initialize, configure and use the 4-20 mA R Click. It is a
  simple SPI communication module that acts as a receiver in a 4-20 current loop. The Click
  reads current data and converts the analog signal to a digital 12-bit format. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.420MaR

### Example Key Functions

- `c420mar_cfg_setup` Config Object Initialization function. 
```c
void c420mar_cfg_setup ( c420mar_cfg_t *cfg );
``` 
 
- `c420mar_init` Initialization function. 
```c
err_t c420mar_init ( c420mar_t *ctx, c420mar_cfg_t *cfg );
```

- `c420mar_default_cfg` Click Default Configuration function. 
```c
void c420mar_default_cfg ( c420mar_t *ctx );
```

- `c420mar_read_data` This function reads the 16-bit current value from the SPI data register, and then normalizes and converts it to float. 
```c
float c420mar_read_data ( c420mar_t *ctx );
```

### Application Init

> This function initializes and configures the logger and Click modules. 

```c
void application_init ( )
{
    log_cfg_t log_cfg;
    c420mar_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    c420mar_cfg_setup( &cfg );
    c420MAR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c420mar_init( &c420mar, &cfg );
}
```

### Application Task

> This function reads and displays current data every half a second. 

```c
void application_task ( )
{
    float current;

    current = c420mar_read_data( &c420mar );

    log_printf( &logger, "-----------------------------\r\n" );
    log_printf( &logger, " * Current: %.3f mA * \r\n", current );

    Delay_ms ( 500 );
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
