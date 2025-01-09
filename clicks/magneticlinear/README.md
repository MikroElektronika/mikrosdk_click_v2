
---
# Magnetic linear Click

> [Magnetic linear Click](https://www.mikroe.com/?pid_product=MIKROE-3274) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3274&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type

# Software Support

## Example Description

> This application reads magnetics linear data.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneticlinear

### Example Key Functions

- `magneticlinear_cfg_setup` Config Object Initialization function. 
```c
void magneticlinear_cfg_setup ( magneticlinear_cfg_t *cfg );
``` 
 
- `magneticlinear_init` Initialization function. 
```c
err_t magneticlinear_init ( magneticlinear_t *ctx, magneticlinear_cfg_t *cfg );
```

- `magneticlinear_default_cfg` Click Default Configuration function. 
```c
void magneticlinear_default_cfg ( magneticlinear_t *ctx );
```

- `magneticlinear_read_data` This function reads Magnetics Linear data. 
```c
uint16_t magneticlinear_read_data ( magneticlinear_t *ctx );
```

### Application Init

> Device initialization.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    magneticlinear_cfg_t cfg;

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

    magneticlinear_cfg_setup( &cfg );
    MAGNETICLINEAR_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneticlinear_init( &magneticlinear, &cfg );
}
```

### Application Task

> Reads magnetic linear data and logs it to USB UART every 500ms.

```c
void application_task ( void )
{
    uint16_t magnetic_data;
    
    magnetic_data = magneticlinear_read_data( &magneticlinear );

    log_printf( &logger, " Magnetic Linear data : %u\r\n", magnetic_data );
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
