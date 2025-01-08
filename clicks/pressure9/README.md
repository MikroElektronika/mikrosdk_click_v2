
---
# Pressure 9 Click

> [Pressure 9 Click](https://www.mikroe.com/?pid_product=MIKROE-3441) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3441&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Jovan Stajkovic
- **Date**          : nov 2019.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> The demo application displays the pressure and temperature measurement using Pressure 9 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Pressure9

### Example Key Functions

- `pressure9_cfg_setup` Config Object Initialization function.
```c
void pressure9_cfg_setup ( pressure9_cfg_t *cfg ); 
```

- `pressure9_init` Initialization function.
```c
err_t pressure9_init ( pressure9_t *ctx, pressure9_cfg_t *cfg );
```

- `pressure9_default_cfg` Click Default Configuration function.
```c
void pressure9_default_cfg ( pressure9_t *ctx );
```

- `pressure9_get_pressure_data` Get Pressure data in mBar
```c
float pressure9_get_pressure_data ( pressure9_t *ctx );
```

- `pressure9_get_temperature_data` Get Temperature data in C
```c
float pressure9_get_temperature_data ( pressure9_t *ctx );
```

- `pressure9_configuration` Writing data to the configuration registers
```c
void pressure9_configuration ( pressure9_t *ctx, uint8_t reg_adr, uint8_t data_in );
```

### Application Init

> Initialization the driver, test comunication, and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    pressure9_cfg_t cfg;

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
    pressure9_cfg_setup( &cfg );
    PRESSURE9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pressure9_init( &pressure9, &cfg );
    Delay_ms ( 100 );

    // Test comunication
    uint8_t product_id = 0;
    pressure9_generic_read( &pressure9, PRESSURE9_REG_PRODUCT_ID, &product_id, 1 );
    if ( PRESSURE9_PRODUCT_ID != product_id )
    {
        log_error( &logger, "Read product ID." );
        for ( ; ; );
    }

    pressure9_default_cfg( &pressure9 );
    Delay_ms ( 100 );

    log_info( &logger, " Application Task " );
} 
```

### Application Task

> Reads Temperature data in [C] and Pressure data in [mBar] and this data logs to the USB UART every 2 sec.

```c
void application_task ( void )
{
    pressure = pressure9_get_pressure_data( &pressure9 );
    log_printf( &logger, " Pressure: %.2f mBar\r\n", pressure );

    temperature = pressure9_get_temperature_data( &pressure9 );
    log_printf( &logger, " Temperature: %.2f degC\r\n", temperature );

    log_printf( &logger, "-----------------------------\r\n" );
    Delay_ms ( 1000 );
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
