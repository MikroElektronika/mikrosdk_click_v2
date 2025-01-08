
---
# Pressure 6 Click

> [Pressure 6 Click](https://www.mikroe.com/?pid_product=MIKROE-3216) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3216&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> The example gets the pressure and temperature values from the sensors and logs on terminal.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure6

### Example Key Functions

- `pressure6_cfg_setup` Config Object Initialization function. 
```c
void pressure6_cfg_setup ( pressure6_cfg_t *cfg );
``` 
 
- `pressure6_init` Initialization function. 
```c
err_t pressure6_init ( pressure6_t *ctx, pressure6_cfg_t *cfg );
```

- `pressure6_default_cfg` Click Default Configuration function. 
```c
void pressure6_default_cfg ( pressure6_t *ctx );
```

- `pressure6_get_temperature` This function gets the temperature data from the sensor. 
```c
uint8_t pressure6_get_temperature ( pressure6_t *ctx );
```
 
- `pressure6_power_on` This function turns the sensor on. 
```c
void pressure6_power_on ( pressure6_t *ctx );
```

- `pressure6_get_pressure` This function gets pressure data from the sensor. 
```c
uint16_t pressure6_get_pressure ( pressure6_t *ctx );
```

### Application Init

> Driver initialization and powering ON procedure to wake up the sensor and seting up the measurement mode.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure6_cfg_t cfg;

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

    pressure6_cfg_setup( &cfg );
    PRESSURE6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure6_init( &pressure6, &cfg );
}
```

### Application Task

> Read Pressure data and Temperature data and logs data to USBUART every 1 sec.

```c
void application_task ( void )
{
    //  Task implementation.
    
    pressure6_waiting_for_new_data( &pressure6 );
    Pressure = pressure6_get_pressure( &pressure6 );
    Temperature = pressure6_get_temperature( &pressure6 );

    log_printf( &logger, "Pressure: %u\r\n", pressure);
    log_printf( &logger, "Temperature: %u\r\n", temperature);

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
