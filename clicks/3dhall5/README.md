
---
# 3D Hall 5 Click

> [3D Hall 5 Click](https://www.mikroe.com/?pid_product=MIKROE-3197) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3197&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Katarina Perendic
- **Date**          : okt 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

>  The Demo application displays and reads 3 magnetic axes.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.3dHall5

### Example Key Functions

- `c3dhall5_cfg_setup` Config Object Initialization function. 
```c
void c3dhall5_cfg_setup ( c3dhall5_cfg_t *cfg );
``` 
 
- `c3dhall5_init` Initialization function. 
```c
err_t c3dhall5_init ( c3dhall5_t *ctx, c3dhall5_cfg_t *cfg );
```

- `c3dhall5_default_cfg` Click Default Configuration function. 
```c
void c3dhall5_default_cfg ( c3dhall5_t *ctx );
```

- `c3dhall5_get_axis_data` Axis data. 
```c
int16_t c3dhall5_get_axis_data( c3dhall5_t *ctx, uint8_t axis );
```
 
- `c3dhall5_set_offset` Set offest. 
```c
void c3dhall5_set_offset( c3dhall5_t *ctx, uint8_t offset_axis, int16_t offset );
```

- `c3dhall5_get_interrupt_state` Interrupt state. 
```c
uint8_t c3dhall5_get_interrupt_state( c3dhall5_t *ctx );
```

### Application Init

> Configuring Clicks and log objects. 
> Reads device ID for check communication.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall5_cfg_t cfg;

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

    c3dhall5_cfg_setup( &cfg );
    C3DHALL5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall5_init( &c3dhall5, &cfg );

    c3dhall5_default_cfg ( &c3dhall5 );
    
    device_id = c3dhall5_get_device_id ( &c3dhall5 );
    log_info( &logger, "** Device ID: 0x%x", device_id );
}
```

### Application Task

> Reads the magnetics X / Y / Z axis data every 1 seconds.

```c
void application_task ( void )
{
    int16_t axis_X;
    int16_t axis_Y;
    int16_t axis_Z;

    //  Task implementation.
    
    axis_X = c3dhall5_get_axis_data( &c3dhall5, C3DHALL5_AXIS_X );
    axis_Y = c3dhall5_get_axis_data( &c3dhall5, C3DHALL5_AXIS_Y );
    axis_Z = c3dhall5_get_axis_data( &c3dhall5, C3DHALL5_AXIS_Z );
    
    log_printf( &logger, "----- AXIS -----\r\n" );
    log_printf( &logger, "** X: %d \r\n", axis_X );
    log_printf( &logger, "** Y: %d \r\n", axis_Y );
    log_printf( &logger, "** Z: %d \r\n", axis_Z );
    log_printf( &logger, "----------------\r\n" );
    
    Delay_ms ( 1000 );
}
```

### Note

> Default communication that is set is I2C communication. 
> If you want to use SPI, you have to set up the cfg structure.

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
