
---
# NDIR CO2 Click

> [NDIR CO2 Click](https://www.mikroe.com/?pid_product=MIKROE-3134) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3134&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This application measures absolute CO2 concetration.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.NDIRCO2

### Example Key Functions

- `ndirco2_cfg_setup` Config Object Initialization function. 
```c
void ndirco2_cfg_setup ( ndirco2_cfg_t *cfg );
``` 
 
- `ndirco2_init` Initialization function. 
```c
err_t ndirco2_init ( ndirco2_t *ctx, ndirco2_cfg_t *cfg );
```

- `ndirco2_read_co2` CO2 Concentration Read function. 
```c
void ndirco2_read_co2 ( ndirco2_t *ctx, uint8_t set_check_mode, uint16_t *output_data );
```
 
- `ndirco2_check_average_complete` Average Complete Check function. 
```c
uint8_t ndirco2_check_average_complete ( ndirco2_t *ctx );
```

- `ndirco2_set_mode` Mode Set function. 
```c
void ndirco2_set_mode ( ndirco2_t *ctx, uint8_t select_mode );
```

### Application Init

> Initializes I2C driver and performs driver reset and determines
> number of averaging measurements.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    ndirco2_cfg_t cfg;

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

    ndirco2_cfg_setup( &cfg );
    NDIRCO2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ndirco2_init( &ndirco2, &cfg );

    Delay_ms ( 300 );

    ndirco2_reset( &ndirco2 );
    ndirco2_write_register( &ndirco2, NDIRCO2_AVERAGING_COUNT_REG, 0x03 );
    ndirco2_set_mode( &ndirco2, NDIRCO2_CONTINUOUS_OP_MODE );
    log_printf( &logger, "NDIR CO2 is initialized \r\n" );
    Delay_ms ( 200 );
}
```

### Application Task

> Reads CO2 concentration data in ppm unit after each completed measurement.
> One measurement is finished after 300 ms, and period between two measurements is 2 seconds.
> Results of measurements logs on USBUART.

```c
void application_task ( )
{
    uint16_t co2_data;

    ndirco2_read_co2( &ndirco2, NDIRCO2_CHECK_EACH_MEASURE, &co2_data );
    log_printf( &logger, "CO2 concentration is: %d ppm \r\n", co2_data );
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
