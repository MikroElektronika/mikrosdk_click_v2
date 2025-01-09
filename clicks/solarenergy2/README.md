
---
# Solar Energy 2 Click

> [Solar Energy 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5594) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5594&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This library contains API for the Solar Energy 2 Click driver.
> This driver provides functions to configure the
> power management controller with an energy harvesting interface.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SolarEnergy2

### Example Key Functions

- `solarenergy2_cfg_setup` Config Object Initialization function.
```c
void solarenergy2_cfg_setup ( solarenergy2_cfg_t *cfg );
```

- `solarenergy2_init` Initialization function.
```c
err_t solarenergy2_init ( solarenergy2_t *ctx, solarenergy2_cfg_t *cfg );
```

- `solarenergy2_default_cfg` Click Default Configuration function.
```c
err_t solarenergy2_default_cfg ( solarenergy2_t *ctx );
```

- `solarenergy2_set_pwr_current_source` Solar Energy 2 power source selection function.
```c
err_t solarenergy2_set_pwr_current_source ( solarenergy2_t *ctx, uint8_t crt_src_sel )
```

- `solarenergy2_config_abs_voltage` Solar Energy 2 config absolute voltage function.
```c
err_t solarenergy2_config_abs_voltage ( solarenergy2_t *ctx, solarenergy2_abs_vtg_v_t abs_vtg );
```

- `solarenergy2_set_mppt_ratio` Solar Energy 2 set MPPT ratio function.
```c
err_t solarenergy2_set_mppt_ratio ( solarenergy2_t *ctx, uint8_t mppt_ratio );
```

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app set default settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solarenergy2_cfg_t solarenergy2_cfg;  /**< Click config object. */

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
    solarenergy2_cfg_setup( &solarenergy2_cfg );
    SOLARENERGY2_MAP_MIKROBUS( solarenergy2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == solarenergy2_init( &solarenergy2, &solarenergy2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SOLARENERGY2_ERROR == solarenergy2_default_cfg ( &solarenergy2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );    
}
```

### Application Task

> This is an example that shows the use of Solar Energy 2 Click board&trade;.
> The following example will charge the battery 
> if it is below the maximum voltage of the application of 3.40 V, 
> stop charging when the battery is full and monitor additional status and 
> storage element voltage information.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{   
    if ( SOLARENERGY2_OK == solarenergy2_get_status( &solarenergy2, &status ) )
    {
        if  ( SOLARENERGY2_OK == solarenergy2_get_bat_vtg_status( &solarenergy2, &vld_status ) )
        {
            display_status( );    
        }
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
