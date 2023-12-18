
---
# Current Limit 9 click

> Current Limit 9 Click is a compact add-on board representing a current-limiting solution for your application. This board features the NPS4053, a load switch with a precision adjustable current limit from Nexperia. It is a 5.5V, 55mΩ load switch that allows precise adjustment of the current limit in a range of 110mA up to 2.5A while preserving the constant current during the current limiting.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/currentlimit9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/current-limit-9-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Current Limit 9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Current Limit 9 Click driver.

#### Standard key functions :

- `currentlimit9_cfg_setup` Config Object Initialization function.
```c
void currentlimit9_cfg_setup ( currentlimit9_cfg_t *cfg );
```

- `currentlimit9_init` Initialization function.
```c
err_t currentlimit9_init ( currentlimit9_t *ctx, currentlimit9_cfg_t *cfg );
```

- `currentlimit9_default_cfg` Click Default Configuration function.
```c
err_t currentlimit9_default_cfg ( currentlimit9_t *ctx );
```

#### Example key functions :

- `currentlimit9_set_limit` This function sets the desired current limit threshold using the I2C serial interface.
```c
err_t currentlimit9_set_limit ( currentlimit9_t *ctx, currentlimit9_limit_t current_limit );
```

- `currentlimit9_get_fault` This function gets the state of the fault flag to indicate overcurrent, overtemperature, or reverse-voltage conditions.
```c
uint8_t currentlimit9_get_fault ( currentlimit9_t *ctx );
```

- `currentlimit9_enable` This function turns on the power switch and enables the internal MOSFET.
```c
void currentlimit9_enable ( currentlimit9_t *ctx );
```

## Example Description

> This library contains API for the Current Limit 9 Click driver.
> This driver provides the functions to set the current limiting conditions 
> in order to provide the threshold of the fault conditions.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration
> and sets the current limit threshold of 460 mA.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit9_cfg_t currentlimit9_cfg;  /**< Click config object. */

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
    currentlimit9_cfg_setup( &currentlimit9_cfg );
    CURRENTLIMIT9_MAP_MIKROBUS( currentlimit9_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == currentlimit9_init( &currentlimit9, &currentlimit9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT9_ERROR == currentlimit9_default_cfg ( &currentlimit9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT9_ERROR == currentlimit9_set_limit( &currentlimit9, CURRENTLIMIT9_LIMIT_0_46_A ) )
    {
        log_error( &logger, " Current limit threshold." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}
```

### Application Task

> This example demonstrates the use of the Current Limit 9 Click board. 
> The demo application checks the fault flag for overcurrent conditions.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( CURRENTLIMIT9_FAULT_FLAG == currentlimit9_get_fault( &currentlimit9 ) )
    {
        log_printf( &logger, "Fault flag: Overcurrent\r\n" );
    }
    else
    {
        log_printf( &logger, " Current limit is 460 mA\r\n" );
    }
    Delay_ms( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CurrentLimit9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
