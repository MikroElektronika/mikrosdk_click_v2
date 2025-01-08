
---
# Air quality 4 Click

> [Air quality 4 Click](https://www.mikroe.com/?pid_product=MIKROE-2896) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2896&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type

# Software Support

## Example Description

> This example measures the quality od air.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.AirQuality4

### Example Key Functions

- `airquality4_cfg_setup` Config Object Initialization function. 
```c
void airquality4_cfg_setup ( airquality4_cfg_t *cfg );
``` 
 
- `airquality4_init` Initialization function. 
```c
err_t airquality4_init ( airquality4_t *ctx, airquality4_cfg_t *cfg );
```

- `airquality4_default_cfg` Click Default Configuration function. 
```c
void airquality4_default_cfg ( airquality4_t *ctx );
```

- `air_quality4_soft_reset` Function calls general reset witch resets all states on the chip. 
```c
void air_quality4_soft_reset ( airquality4_t *ctx );
```
 
- `air_quality4_get_co2_and_tvoc` Function writes 2 bytes CO2 data and 2 bytes TVOC data without CRC data. 
```c
void air_quality4_get_co2_and_tvoc ( airquality4_t *ctx, uint16_t *value );
```

- `air_quality4_get_h2_and_ehtoh` Function writes 2 bytes H2 data and 2 bytes EthOH data without CRC data. 
```c
void air_quality4_get_h2_and_ehtoh ( airquality4_t *ctx, uint16_t *value );
```

### Application Init

> Initializes Click driver and gets ID data.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    airquality4_cfg_t cfg;

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

    airquality4_cfg_setup( &cfg );
    AIRQUALITY4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    airquality4_init( &airquality4, &cfg );
    airquality4_default_cfg( &airquality4 );
}
```

### Application Task

> Performs measurements of air concentracion for H2, EthOH, CO2 and TVOC data.

```c
void application_task ( void )
{
    air_quality4_get_h2_and_ethon( &airquality4, data_buffer);

    log_printf( &logger, "H2 value is: %u\n", data_buffer[ 0 ] );
    log_printf( &logger, "EthOH value is:  %u\n", data_buffer[ 1 ] );

    air_quality4_set_baseline( &airquality4 );
    air_quality4_get_co2_and_tvoc( &airquality4, &data_buffer[ 0 ] );
    
    log_printf( &logger, "CO2 value is: %u\n", data_buffer[ 0 ] );
    log_printf( &logger, "TVOC value is: %u\n\n", data_buffer[ 1 ] );

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
