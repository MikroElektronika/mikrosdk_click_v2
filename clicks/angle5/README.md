
---
# Angle 5 Click

> [Angle 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4270) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4270&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : sep 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> Angle 5 Click is a magnetic rotational sensor. 
> It communicates with the target microcontroller over SPI interface.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Angle5

### Example Key Functions

- `angle5_cfg_setup` Config Object Initialization function. 
```c
void angle5_cfg_setup ( angle5_cfg_t *cfg );
``` 
 
- `angle5_init` Initialization function. 
```c
err_t angle5_init ( angle5_t *ctx, angle5_cfg_t *cfg );
```

- `angle5_read_raw_angle` Use this function to read raw angle data. 
```c
uint16_t angle5_read_raw_angle( angle5_t *ctx );
```
 
- `angle5_read_angle_deg` Use this function to read angle data. 
```c
float angle5_read_angle_deg( angle5_t *ctx );
```

### Application Init

> Initializes the driver.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    angle5_cfg_t cfg;

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

    angle5_cfg_setup( &cfg );
    ANGLE5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    angle5_init( &angle5, &cfg );
}
```

### Application Task

> Reads the angle position of the magnet and displays the results on the USB UART.

```c
void application_task ( void )
{
    float new_angle = 0;
    
    new_angle = angle5_read_angle_deg( &angle5 );
    log_printf( &logger, "Angle: %.2f\r\n", new_angle );

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
