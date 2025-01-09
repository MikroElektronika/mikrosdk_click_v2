
---
# Pressure 4 Click

> [Pressure 4 Click](https://www.mikroe.com/?pid_product=MIKROE-3020) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3020&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This app measure barometric pressure.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure4

### Example Key Functions

- `pressure4_cfg_setup` Config Object Initialization function.
```c
void pressure4_cfg_setup ( pressure4_cfg_t *cfg ); 
```

- `pressure4_init` Initialization function.
```c
err_t pressure4_init ( pressure4_t *ctx, pressure4_cfg_t *cfg );
```

- `pressure4_default_cfg` Click Default Configuration function.
```c
void pressure4_default_cfg ( pressure4_t *ctx );
```

- `pressure4_read_id` This function returns the contents of the chipid register.
```c
uint8_t pressure4_read_id ( pressure4_t *ctx );
```

- `pressure4_get_temperature` This function returning the calculated temperature value.
```c
float pressure4_get_temperature ( pressure4_t *ctx );
```

- `pressure4_get_pressure` This function returning the calculated value of the pressure.
```c
float pressure4_get_pressure ( pressure4_t *ctx );
```

### Application Init

> Initializes the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure4_cfg_t cfg;

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

    //  Click initialization.
    pressure4_cfg_setup( &cfg );
    PRESSURE4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure4_init( &pressure4, &cfg );

    pressure4_default_cfg( &pressure4 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The pressure and temperature data is read from the sensor 
> and it is printed to the UART.

```c
void application_task ( void )
{
    float pressure = 0;
    float temperature = 0;

    temperature = pressure4_get_temperature( &pressure4 );
    log_printf( &logger, "Temperature : %.2f degC\r\n", temperature );
    Delay_ms ( 100 );
    
    pressure = pressure4_get_pressure( &pressure4 );
    log_printf( &logger, "Pressure : %.2f mBar\r\n", pressure );
    log_printf( &logger, "========================\r\n" );

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