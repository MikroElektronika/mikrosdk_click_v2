
---
# Ambient 2 Click

> [Ambient 2 Click](https://www.mikroe.com/?pid_product=MIKROE-1903) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-1903&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nemanja Medakovic
- **Date**          : Oct 2019.
- **Type**          : I2C type

# Software Support

## Example Description

>
> This is a example which demonstrates the use of Ambient 2 Click board.
> This example measures and calculates abmient light from OPT3001 sensor.
>

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient2

### Example Key Functions

- `ambient2_cfg_setup` Configuration Object Setup function. 
```c
void ambient2_cfg_setup ( ambient2_cfg_t *cfg );
``` 
 
- `ambient2_init` Click Initialization function. 
```c
ambient2_err_t ambient2_init ( ambient2_t *ctx, ambient2_cfg_t *cfg );
```

- `ambient2_default_cfg` Click Default Configuration function. 
```c
void ambient2_default_cfg ( ambient2_t *ctx );
```

- `ambient2_generic_write` Generic Write function. 
```c
void ambient2_generic_write ( ambient2_t *ctx, ambient2_reg_addr_t reg_addr, ambient2_data_t data_in );
```
 
- `ambient2_generic_read` Generic Read function. 
```c
ambient2_data_t ambient2_generic_read ( ambient2_t *ctx, ambient2_reg_addr_t reg_addr );
```

- `ambient2_get_sens_results` Sensor Results Read function. 
```c
void ambient2_get_sens_results ( ambient2_t *ctx );
```

### Application Init

>
> Initializes I2C driver and all used pins for Ambient 2 Click. 
> Also executes a default configuration for this Click, which means
> that Click will work in continuous conversion mode, in automatic full scale
> range, with conversion time of 800ms.
>

```c
void application_init( void )
{
    ambient2_cfg_t ambient2_cfg;
    log_cfg_t console_cfg;

    //  Click initialization.
    ambient2_cfg_setup( &ambient2_cfg );
    AMBIENT2_MAP_MIKROBUS( ambient2_cfg, MIKROBUS_1 );
    ambient2_init( &ambient2, &ambient2_cfg );
    ambient2_default_cfg( &ambient2 );

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( console_cfg );
    log_init( &console, &console_cfg );
    log_write( &console, "* * *  Ambient 2 initialization done  * * *", LOG_FORMAT_LINE );
    log_write( &console, "*******************************************", LOG_FORMAT_LINE );
}
```

### Application Task

>
> Reads sensor data every time when conversion cycle was done
> and data was ready for reading. Sends results to the uart terminal.
>

```c
void application_task( void )
{
    if ( ambient2_generic_read( &ambient2, AMBIENT2_REG_CONFIGURATION ) & AMBIENT2_FLAG_MASK_CONV_READY )
    {
        ambient2_get_sens_results( &ambient2 );

        log_printf( &console, "** Ambient Light Sensor : %.2f lux **\r\n", ambient2.sens_data.amb_light_lx );
        log_printf( &console, "** Ambient Light Range : %.2f lux **\r\n", ambient2.sens_data.amb_light_range );
        log_printf( &console, "** Ambient Light Percents : %d %% **\r\n\n", ambient2.sens_data.amb_light_per );
    }
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
