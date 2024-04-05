\mainpage Main Page

---
# Solar Energy 2 click

> Solar Energy 2 Click is a compact add-on board that can recharge a battery 
> by harvesting the solar power of the Sun or by other means. 
> This board features the EM8500, a power management controller with an energy harvesting interface 
> from EM Microelectronic. The controller is specifically designed for efficient harvesting 
> over various DC sources such as photovoltaic (solar) or thermal electric generators (TEG). 
> It can recharge the connected LiPo battery or supercapacitor (or even a conventional capacitor). 
> In addition, the EM8500 can use the same battery as a power source for powering the connected system.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/solarenergy2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/solar-energy-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Solar Energy 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Solar Energy 2 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This library contains API for the Solar Energy 2 Click driver.
> This driver provides functions to configure the
> power management controller with an energy harvesting interface.

**The demo application is composed of two sections :**

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

> This is an example that shows the use of Solar Energy 2 Click board™.
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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SolarEnergy2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
