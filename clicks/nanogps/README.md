
---
# Nano GPS Click

> [Nano GPS Click](https://www.mikroe.com/?pid_product=MIKROE-1912) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1912&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : apr 2020.
- **Type**          : UART GPS/GNSS type

# Software Support

## Example Description

> This example reads and processes data from Nano GPS Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Nanogps

### Example Key Functions

- `nanogps_cfg_setup` Config Object Initialization function. 
```c
void nanogps_cfg_setup ( nanogps_cfg_t *cfg );
``` 
 
- `nanogps_init` Initialization function. 
```c
err_t nanogps_init ( nanogps_t *ctx, nanogps_cfg_t *cfg );
```

- `nanogps_generic_parser` Generic parser function. 
```c
nanogps_error_t nanogps_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );
```

- `nanogps_generic_read` Generic read function. 
```c
int32_t nanogps_generic_read ( nanogps_t *ctx, char *data_buf, uint16_t max_len );
```

- `nanogps_module_wakeup` Wake-up module. 
```c
void nanogps_module_wakeup ( nanogps_t *ctx );
```

### Application Init

> Initializes driver and wake-up module.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    nanogps_cfg_t cfg;

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

    nanogps_cfg_setup( &cfg );
    NANOGPS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanogps_init( &nanogps, &cfg );

    nanogps_module_wakeup( &nanogps );
}
```

### Application Task

> Reads the received data and parses it.

```c
void application_task ( void )
{
    nanogps_process(  );
    parser_application( current_parser_buf );
}
```

### Note

> Depending on the environmental conditions and the satellites availability
> it may take some time for the module to receive the position fix.

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
