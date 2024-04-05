\mainpage Main Page

---
# eFuse 5 click

> eFuse 5 Click is a compact add-on board with a power path protection solution that limits circuit currents 
> and voltages to safe levels during fault conditions. 
> This board features the TPS16530, an easy-to-use, positive 58V, 
> 4.5A eFuse with a 31mΩ integrated FET from Texas Instruments. 
> This industrial eFuse has programmable undervoltage, overcurrent, inrush current protection, 
> and output current monitoring features. 
> Besides, it allows flexibility to configure the device between the two current-limiting fault responses 
> (latch off and auto-retry).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/efuse5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/efuse-5-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the eFuse 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for eFuse 5 Click driver.

#### Standard key functions :

- `efuse5_cfg_setup` Config Object Initialization function.
```c
void efuse5_cfg_setup ( efuse5_cfg_t *cfg );
```

- `efuse5_init` Initialization function.
```c
err_t efuse5_init ( efuse5_t *ctx, efuse5_cfg_t *cfg );
```

- `efuse5_default_cfg` Click Default Configuration function.
```c
err_t efuse5_default_cfg ( efuse5_t *ctx );
```

#### Example key functions :

- `efuse5_set_current_limit` eFuse 5 set the current limit function.
```c
err_t efuse5_set_current_limit ( efuse5_t *ctx, efuse5_current_limit_t current_limit );
```

- `efuse5_set_resistance` eFuse 5 set the resistance function.
```c
err_t efuse5_set_resistance ( efuse5_t *ctx, uint16_t res_ohm );
```

- `efuse5_get_fault` eFuse 5 gets fault condition state function.
```c
uint8_t efuse5_get_fault ( efuse5_t *ctx );
```

## Example Description

> This library contains API for the eFuse 5 Click driver.
> This driver provides the functions to set the current limiting conditions 
> to provide the threshold of the fault conditions.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, default settings turn on the device.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    efuse5_cfg_t efuse5_cfg;  /**< Click config object. */

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
    efuse5_cfg_setup( &efuse5_cfg );
    EFUSE5_MAP_MIKROBUS( efuse5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == efuse5_init( &efuse5, &efuse5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EFUSE5_ERROR == efuse5_default_cfg( &efuse5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
}
```

### Application Task

> This example demonstrates the use of the eFuse 5 Click board™.
> In this example, the app sets the current limit to 600 mA for 10 seconds 
> and then sets the current limit to 1200 mA for the next 10 seconds
> to protect the electrical circuit against excessive current.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( EFUSE5_OK == efuse5_set_current_limit( &efuse5, EFUSE5_CURRENT_LIMIT_600_mA ) )
    {
        log_printf( &logger, "  Current limit:  600 mA   \r\n" );
        log_printf( &logger, "---------------------------\r\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    if ( EFUSE5_OK == efuse5_set_current_limit( &efuse5, EFUSE5_CURRENT_LIMIT_1200_mA ) )
    {
        log_printf( &logger, "  Current limit: 1200 mA   \r\n" );
        log_printf( &logger, "---------------------------\r\n" );
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
- Click.eFuse5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
