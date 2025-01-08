
---
# Magneto 8 Click

> [Magneto 8 Click](https://www.mikroe.com/?pid_product=MIKROE-4204) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4204&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Magneto 8 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto8

### Example Key Functions

- `magneto8_cfg_setup` Config Object Initialization function.
```c 
void magneto8_cfg_setup ( magneto8_cfg_t *cfg ); 
```

- `magneto8_init` Initialization function.
```c
err_t magneto8_init ( magneto8_t *ctx, magneto8_cfg_t *cfg );
```

- `magneto8_default_cfg` Click Default Configuration function.
```c
void magneto8_default_cfg ( magneto8_t *ctx );
```

- `magneto8_get_magnitude` Gets magnitude data
```c
uint16_t magneto8_get_magnitude ( magneto8_t *ctx );
```

- `magneto8_get_angle_data` Gets Angle data
```c
float magneto8_get_angle_data ( magneto8_t *ctx );
```

- `magneto8_psh_pin_state` Gets PSH pin state
```c
uint8_t magneto8_psh_pin_state ( magneto8_t *ctx );
```

### Application Init

> Initializes the driver and applies the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    magneto8_cfg_t cfg;

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

    magneto8_cfg_setup( &cfg );
    MAGNETO8_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto8_init( &magneto8, &cfg );

    magneto8_default_cfg( &magneto8 );
    log_printf( &logger, "--- Configuration done ---- \r\n" );
    Delay_ms ( 500 );
}
```

### Application Task

> Reads angle and magnitude data and displays it on the USB UART every 500ms.

```c
void application_task ( void )
{
    float angle;
    uint16_t mag;

    mag  = magneto8_get_magnitude( &magneto8 );
    log_printf( &logger, "Magnitude: %d \r\n", mag );
    
    angle = magneto8_get_angle_data( &magneto8 );
    log_printf( &logger, "Angle : %.1f deg\r\n", angle );

    log_printf( &logger, "---------------------- \r\n" );
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
