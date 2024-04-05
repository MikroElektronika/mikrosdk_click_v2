\mainpage Main Page

---
# eFuse 4 click

> eFuse 4 Click is a compact add-on board with a power path protection solution 
> that limits circuit currents and voltages to safe levels during fault conditions. 
> This board features the TPS25940, an eFuse power switch 
> with reverse current blocking from Texas Instruments. 
> The TPS25940 features a full suite of protection and monitoring functions, 
> including a DevSleep™ mode that supports compliance with the SATA™ Device Sleep standard. 
> The wide operating range from 2.7V to 18V allows control of many popular DC bus voltages. 
> The additional potentiometer sets the overload and short-circuit current limit of the TPS25940, 
> while the additional header allows external current monitoring.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/efuse4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/efuse-4-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Nov 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the eFuse 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for eFuse 4 Click driver.

#### Standard key functions :

- `efuse4_cfg_setup` Config Object Initialization function.
```c
void efuse4_cfg_setup ( efuse4_cfg_t *cfg );
```

- `efuse4_init` Initialization function.
```c
err_t efuse4_init ( efuse4_t *ctx, efuse4_cfg_t *cfg );
```

- `efuse4_default_cfg` Click Default Configuration function.
```c
err_t efuse4_default_cfg ( efuse4_t *ctx );
```

#### Example key functions :

- `efuse4_set_current_limit` eFuse 4 set current limit function.
```c
err_t efuse4_set_current_limit ( efuse4_t *ctx, efuse4_current_limit_t current_limit )
```

- `efuse4_set_resistance` eFuse 4 set resistance function.
```c
err_t efuse4_set_resistance ( efuse4_t *ctx, uint32_t res_ohm );
```

- `efuse4_set_digi_pot` eFuse 4 set normal mode function.
```c
void efuse4_set_normal_mode ( efuse4_t *ctx );
```

## Example Description

> This library contains API for the eFuse 4 Click driver.
> This driver provides the functions to set the current limiting conditions 
> in order to provide the threshold of the fault conditions.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, default settings turn on the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    efuse4_cfg_t efuse4_cfg;  /**< Click config object. */

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
    efuse4_cfg_setup( &efuse4_cfg );
    EFUSE4_MAP_MIKROBUS( efuse4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == efuse4_init( &efuse4, &efuse4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EFUSE4_ERROR == efuse4_default_cfg ( &efuse4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 100 );
    
    display_selection( );
    Delay_ms ( 100 );
}

```

### Application Task

> This example demonstrates the use of the eFuse 4 Click board™.
> Reading user's input from UART Terminal and using it as an index 
> for an array of pre-calculated values that define the current limit level.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{  
    static char index;
    
    if ( EFUSE4_ERROR != log_read( &logger, &index, 1 ) ) 
    {
        if ( ( index >= '0' ) && ( index <= '6' ) ) 
        {
            efuse4_set_current_limit ( &efuse4, limit_value_op[ index - 48 ] );
            log_printf( &logger, "  >>> Selected mode %d     \r\n", index - 48 );
            log_printf( &logger, "  Current limit is %d mA   \r\n", limit_value_op[ index - 48 ] );
            log_printf( &logger, "---------------------------\r\n" );
            Delay_ms ( 100 );
        }
        else 
        { 
            log_printf( &logger, "    Data not in range!    \r\n" );
            log_printf( &logger, "---------------------------\r\n" );
            display_selection( );
            Delay_ms ( 100 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.eFuse4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
