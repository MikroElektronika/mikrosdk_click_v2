
---
# 3D Hall 3 Click

> [3D Hall 3 Click](https://www.mikroe.com/?pid_product=MIKROE-3310) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3310&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Petar Suknjaja
- **Date**          : Dec 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example returns values of X,Y and Z axes.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.3DHall3

### Example Key Functions

- `c3dhall3_cfg_setup` Config Object Initialization function. 
```c
void c3dhall3_cfg_setup ( c3dhall3_cfg_t *cfg );
``` 
 
- `c3dhall3_init` Initialization function. 
```c
err_t c3dhall3_init ( c3dhall3_t *ctx, c3dhall3_cfg_t *cfg );
```

- `c3dhall3_default_cfg` Click Default Configuration function. 
```c
void c3dhall3_default_cfg ( c3dhall3_t *ctx );
```

- `c3dhall3_read_xyz` This function reads xyz values from the module. 
```c
void c3dhall3_read_xyz ( c3dhall3_t *ctx, int16_t *out_xyz );
```
 
- `c3dhall3_write_offset ` This function writes offest values to the module. 
```c
void c3dhall3_write_offset  ( c3dhall3_t *ctx, uint8_t axis, uint16_t offset  );
```

- `c3dhall3_interrupt_threshold` This function sets desired threshold value. 
```c
void c3dhall3_interrupt_threshold ( c3dhall3_t *ctx, uint16_t threshold );
```

### Application Init

> Initializes driver and sets basic configuration. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    c3dhall3_cfg_t cfg;

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

    c3dhall3_cfg_setup( &cfg );
    C3DHALL3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    c3dhall3_init( &c3dhall3, &cfg );
    c3dhall3_default_cfg ( &c3dhall3 );
    log_info( &logger, "---- System Init ----" );
}
```

### Application Task

> Reads the values of the X,Y and Z axes.

```c
void application_task ( void )
{
    int16_t axes_xyz[3];

    //  Task implementation.
    
    c3dhall3_read_xyz( &c3dhall3, axes_xyz );
    log_printf( &logger, "X: %d \r\n", axes_xyz[ 0 ] );
    log_printf( &logger, "Y: %d \r\n", axes_xyz[ 1 ] );
    log_printf( &logger, "Z: %d \r\n", axes_xyz[ 2 ] );

    Delay_ms ( 100 );
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
