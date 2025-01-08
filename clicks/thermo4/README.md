
---
# Thermo 4  Click

> [Thermo 4 Click](https://www.mikroe.com/?pid_product=MIKROE-2632) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2632&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This demo example returns temperature values in three different format.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Thermo4

### Example Key Functions

- `thermo4_cfg_setup` Config Object Initialization function. 
```c
void thermo4_cfg_setup ( thermo4_cfg_t *cfg );
``` 
 
- `thermo4_init` Initialization function. 
```c
err_t thermo4_init ( thermo4_t *ctx, thermo4_cfg_t *cfg );
```

- `thermo4_default_cfg` Click Default Configuration function. 
```c
void thermo4_default_cfg ( thermo4_t *ctx );
```

- `thermo4_read_temperature_c` This function reads temperature values in Celsius format. 
```c
float thermo4_read_temperature_c ( thermo4_t *ctx );
```
 
- `thermo4_read_temperature_f` This function reads temperature values in Farenheit format. 
```c
float thermo4_read_temperature_f ( thermo4_t *ctx );
```

- `thermo4_reset` This function is used to reset the sensor. 
```c
void thermo4_reset ( thermo4_t *ctx );
```

### Application Init

> Initializes the driver and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    thermo4_cfg_t cfg;

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
    
    //  Click initialization.
    
    thermo4_cfg_setup( &cfg );
    THERMO4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    thermo4_init( &thermo4, &cfg );
    log_info( &logger, "---- Application Init ----" );
}
```

### Application Task

> Returns temperature values from the sensor.

```c
void application_task ( void )
{
    temp_in_celsius = thermo4_read_temperature_c( thermo4 );
    temp_in_faren = thermo4_read_temperature_f( thermo4 );
    temp_in_kelvin = thermo4_read_temperature_k( thermo );
    
    log_printf(" Temperature celsius : %f %c\r\n", temp_in_celsius, deg_cel);
    log_printf(" Temperature farenheit : %f %c\r\n", temp_in_faren, deg_far);
    log_printf(" Temperature kelvin : %f K\r\n", temp_in_kelvin);
    
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
