
---
# Pressure 10 Click

> [Pressure 10 Click](https://www.mikroe.com/?pid_product=MIKROE-4142) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4142&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> Pressure 10 Click features a digital interface barometric pressure sensor, based on 
> piezoresistive bridge. It can use both SPI and I2C communication protocols, allowing 
> it to be interfaced with a broad range of MCUs. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure10

### Example Key Functions

- `pressure10_cfg_setup` Config Object Initialization function. 
```c
void pressure10_cfg_setup ( pressure10_cfg_t *cfg );
``` 
 
- `pressure10_init` Initialization function. 
```c
err_t pressure10_init ( pressure10_t *ctx, pressure10_cfg_t *cfg );
```

- `pressure10_default_cfg` Click Default Configuration function. 
```c
void pressure10_default_cfg ( pressure10_t *ctx );
```

- `pressure10_send_cmd` Send command. 
```c
void pressure10_send_cmd ( pressure10_t *ctx, uint8_t cmd );
```
 
- `pressure10_check_communication` Check communication. 
```c
uint8_t pressure10_check_communication ( pressure10_t *ctx );
```

- `pressure10_get_status` Get status function. 
```c
void pressure10_get_status ( pressure10_t *ctx, pressure10_status_t *status_obj );
```

### Application Init

> Initializes the driver, checks the communication and configures the module for measurement.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure10_cfg_t cfg;

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

    pressure10_cfg_setup( &cfg );
    PRESSURE10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure10_init( &pressure10, &cfg );

    check_com = pressure10_check_communication( &pressure10 );
    if ( check_com == 0 )
    {
        log_printf( &logger, ">> Communication [OK]\r\n" );
    }
    else
    {
        log_printf( &logger, ">> Communication [ERROR]\r\n" );
        for( ; ; );
    }

    pressure10_default_cfg ( &pressure10 );
    log_printf( &logger, "----------------------------\r\n" );
}
```

### Application Task

> Reads the pressure and temperature data every 1500ms and displays the results on the USB UART.

```c
void application_task ( void )
{
    float temperature;
    float pressure;

    pressure = pressure10_get_pressure( &pressure10 );
    temperature = pressure10_get_temperature( &pressure10 );

    log_printf( &logger, ">> Temperature: %.2f C\r\n", temperature );

    log_printf( &logger, "----------------------------\r\n" );

    log_printf( &logger, ">> Pressure: %.2f mBar\r\n", pressure );

    log_printf( &logger, "----------------------------\r\n" );

    Delay_ms ( 1000 );
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
