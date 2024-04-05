\mainpage Main Page

---
# Current Limit 10 click

> Current Limit 10 Click is a compact add-on board representing a current-limiting solution for your application. This board features the HS2950P, a load protection HotSwitch from Semtech. It features a wide input voltage range of 2.7V up to 29V and can provide up to 5A output current. The HS2950P features an adjustable current limit, over-voltage protection, automatic output discharge, and soft start. It automatically restarts from all faults except OVP and UVLO.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/currentlimit10_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/current-limit-10-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Current Limit 10 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Current Limit 10 Click driver.

#### Standard key functions :

- `currentlimit10_cfg_setup` Config Object Initialization function.
```c
void currentlimit10_cfg_setup ( currentlimit10_cfg_t *cfg );
```

- `currentlimit10_init` Initialization function.
```c
err_t currentlimit10_init ( currentlimit10_t *ctx, currentlimit10_cfg_t *cfg );
```

- `currentlimit10_default_cfg` Click Default Configuration function.
```c
err_t currentlimit10_default_cfg ( currentlimit10_t *ctx );
```

#### Example key functions :

- `currentlimit10_set_limit` This function sets the desired current limit threshold using the I2C serial interface.
```c
err_t currentlimit10_set_limit ( currentlimit10_t *ctx, float current_limit );
```

- `currentlimit10_get_fault` This function gets the state of the fault flag to indicate overcurrent, overtemperature, or reverse-voltage conditions.
```c
uint8_t currentlimit10_get_fault ( currentlimit10_t *ctx );
```

- `currentlimit10_enable` This function turns on the power switch and enables the internal MOSFET.
```c
void currentlimit10_enable ( currentlimit10_t *ctx );
```

## Example Description

> This library contains API for the Current Limit 10 Click driver.
> This driver provides the functions to set the current limiting conditions 
> in order to provide the threshold of the fault conditions.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration
> and and sets the current limit threshold of 750 mA.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit10_cfg_t currentlimit10_cfg;  /**< Click config object. */

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
    currentlimit10_cfg_setup( &currentlimit10_cfg );
    CURRENTLIMIT10_MAP_MIKROBUS( currentlimit10_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == currentlimit10_init( &currentlimit10, &currentlimit10_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT10_ERROR == currentlimit10_default_cfg ( &currentlimit10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    if ( CURRENTLIMIT10_ERROR == currentlimit10_set_limit( &currentlimit10, 0.75 ) )
    {
        log_error( &logger, " Current limit threshold." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This example demonstrates the use of the Current Limit 10 Click board. 
> The demo application checks the fault flag for overcurrent conditions.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( CURRENTLIMIT10_FAULT_FLAG == currentlimit10_get_fault( &currentlimit10 ) )
    {
        log_printf( &logger, "Fault flag: Overcurrent\r\n" );
    }
    else
    {
        log_printf( &logger, " Current limit is 0.75 A\r\n" );
    }
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CurrentLimit10

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
