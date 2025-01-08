
---
# Ambient Click

> [Ambient Click](https://www.mikroe.com/?pid_product=MIKROE-1890) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1890&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : ADC type

# Software Support

## Example Description

> This application turns light intensity into voltage.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient

### Example Key Functions

- `ambient_cfg_setup` Config Object Initialization function.
```c
void ambient_cfg_setup ( ambient_cfg_t *cfg ); 
```

- `ambient_init` Initialization function.
```c
err_t ambient_init ( ambient_t *ctx, ambient_cfg_t *cfg );
```

- `ambient_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t ambient_read_an_pin_voltage ( ambient_t *ctx, float *data_out );
```

- `ambient_get_light_intensity` Calculates the light intensity from analog voltage measurement of the Melexis MLX75305 IC on Ambient Click board.
```c
uint16_t ambient_get_light_intensity ( ambient_t *ctx );
```

### Application Init

> Initialization driver and logger.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient_cfg_t cfg;

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
    ambient_cfg_setup( &cfg );
    AMBIENT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient_init( &ambient, &cfg );

    log_info( &logger, " Application Task " );
}
```

### Application Task

> This is an example which demonstrates the use of Ambient Click board.
Ambient Click reads ADC voltage once per second and converts it to light intensity [ uW/cm2 ].
Results are being sent to the USB UART where you can track their changes.

```c
void application_task ( void )
{
    uint16_t light_intensity = ambient_get_light_intensity( &ambient );
    log_printf( &logger, " Light Intensity: %u uW/cm2\r\n\n", light_intensity );
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
