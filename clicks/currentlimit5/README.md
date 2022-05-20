\mainpage Main Page

---
# Current Limit 5 click

> Current Limit 5 Click is a compact add-on board representing a current-limiting solution. This board features the MIC2099, a current-limit power distribution switch from Microchip Technology. This Click board™ represents a programmable current limit solution with various protection features and fault indication, which operates from a 2.5V to 5.5V input voltage range. Also, the current limit is adjustable from 100mA up to 1.05A programmed through the MCP4561 digital potentiometer. This Click board™ is suitable for applications in portable equipment and condition monitoring or power supplies, protecting them in short circuits or other overload conditions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/currentlimit5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/current-limit-5-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jan 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the Current Limit 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Current Limit 5 Click driver.

#### Standard key functions :

- `currentlimit5_cfg_setup` Config Object Initialization function.
```c
void currentlimit5_cfg_setup ( currentlimit5_cfg_t *cfg );
```

- `currentlimit5_init` Initialization function.
```c
err_t currentlimit5_init ( currentlimit5_t *ctx, currentlimit5_cfg_t *cfg );
```

#### Example key functions :

- `currentlimit5_set_ilimit` This function sets the current limit value by configuring the onboard digital potentiometer.
```c
err_t currentlimit5_set_ilimit ( currentlimit5_t *ctx, currentlimit5_ilimit_t ilimit );
```

- `currentlimit5_get_fault_pin` This function returns the fault pin logic state.
```c
uint8_t currentlimit5_get_fault_pin ( currentlimit5_t *ctx );
```

- `currentlimit5_enable_limit` This function enables the current limiting switch.
```c
void currentlimit5_enable_limit ( currentlimit5_t *ctx );
```

## Example Description

> This example demonstrates the use of Current Limit 5 click board by limiting
the current to a certain value and displaying an appropriate message when the current reaches the limit.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which sets the current limit to 200mA.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    currentlimit5_cfg_t currentlimit5_cfg;  /**< Click config object. */

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
    currentlimit5_cfg_setup( &currentlimit5_cfg );
    CURRENTLIMIT5_MAP_MIKROBUS( currentlimit5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == currentlimit5_init( &currentlimit5, &currentlimit5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENTLIMIT5_ERROR == currentlimit5_default_cfg ( &currentlimit5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Displays the fault indicator state on the USB UART.

```c
void application_task ( void )
{
    static uint8_t currentlimit_ind = 2;
    if ( currentlimit5_get_fault_pin ( &currentlimit5 ) )
    {
        if ( currentlimit_ind != 0 )
        {
            log_printf ( &logger, " The switch is in normal operation \r\n\n" );
            currentlimit_ind = 0;
        }
    }
    else
    {
        if ( currentlimit_ind != 1 )
        {
            log_printf ( &logger, " The switch is in the current limiting or thermal shutdown operation \r\n\n" );
            currentlimit_ind = 1;
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.CurrentLimit5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
