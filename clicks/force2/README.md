
---
# Force 2 Click

> [Force 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4046) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4046&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : ADC type

# Software Support

## Example Description

> This example demonstrates the use of Force 2 Click board by reading and displaying the voltage from AN pin and the calculated force (N) value.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Force2

### Example Key Functions

- `force2_cfg_setup` Config Object Initialization function.
```c
void force2_cfg_setup ( force2_cfg_t *cfg ); 
```

- `force2_init` Initialization function.
```c
err_t force2_init ( force2_t *ctx, force2_cfg_t *cfg );
```

- `force2_read_an_pin_value` This function reads results of AD conversion of the AN pin.
```c
err_t force2_read_an_pin_value ( force2_t *ctx, uint16_t *data_out );
```

- `force2_read_an_pin_voltage` This function reads results of AD conversion of the AN pin and converts them to proportional voltage level.
```c
err_t force2_read_an_pin_voltage ( force2_t *ctx, float *data_out );
```

### Application Init

> Initalizes the driver and logger and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    force2_cfg_t cfg;

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
    force2_cfg_setup( &cfg );
    FORCE2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    force2_init( &force2, &cfg );

    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "    Force 2 Click   \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 500 );
}
```

### Application Task

> Reads and displays the voltage from AN pin, then calculates and displays the force in N.

```c
void application_task ( void )
{
    float voltage = 0;
    if ( FORCE2_OK == force2_read_an_pin_voltage ( &force2, &voltage ) ) 
    {
        log_printf( &logger, " AN Voltage: %.3f V\r\n", voltage );
        log_printf( &logger, " Force: %.1f N\r\n", 
                    FORCE2_FORCE_MAX - voltage * FORCE2_FORCE_MAX / FORCE2_VREF );
        log_printf( &logger, "-----------------------------\r\n" );
        Delay_ms ( 1000 );
    }
}
```

### Note

> Adjust the gain and range onboard potentiometers in order to get zero N when there's no force applied to the sensor.

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
