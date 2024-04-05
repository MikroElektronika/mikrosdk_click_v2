\mainpage Main Page

---
# Charger 18 click

> Charger 18 Click is a compact add-on board representing a single-cell battery charger. This board features the LTC3553, a micropower, highly integrated power management, and battery charger for single-cell Li-Ion/Polymer battery applications from Analog Devices. Designed specifically for USB applications, it also includes a PowerPath manager with automatic load prioritization and input current limit, a battery charger, and numerous internal protection features. It also indicates a battery charge state, and it comes with a synchronous 200mA buck regulator and a 150mA low dropout linear regulator (LDO).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger18_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/charger-18-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the Charger 18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Charger 18 Click driver.

#### Standard key functions :

- `charger18_cfg_setup` Config Object Initialization function.
```c
void charger18_cfg_setup ( charger18_cfg_t *cfg );
```

- `charger18_init` Initialization function.
```c
err_t charger18_init ( charger18_t *ctx, charger18_cfg_t *cfg );
```

#### Example key functions :

- `charger18_buck_control` This function controls the buck regulator enable state of Charger 18 click board.
```c
void charger18_buck_control ( charger18_t *ctx, uint8_t state ); 
```

- `charger18_ldo_control` This function controls the low dropout (LDO) regulator enable state of Charger 18 click board.
```c
void charger18_ldo_control ( charger18_t *ctx, uint8_t state );
```

- `charger18_suspend_control` This function controls the suspend charging mode state of Charger 18 click board.
```c
void charger18_suspend_control ( charger18_t *ctx, uint8_t state ); 
```

## Example Description

> This example demonstrates the use of Charger 18 click board by controlling the status of the charger as well as the LDO and BUCK regulators.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the chip with the charger, LDO and BUCK regulators disabled.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger18_cfg_t charger18_cfg;  /**< Click config object. */

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
    charger18_cfg_setup( &charger18_cfg );
    CHARGER18_MAP_MIKROBUS( charger18_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == charger18_init( &charger18, &charger18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    charger18_power_control( &charger18, CHARGER18_CONTROL_ENABLE );
    log_printf( &logger, " POWER   : ON\r\n" );
    charger18_suspend_control( &charger18, CHARGER18_CONTROL_ENABLE );
    log_printf( &logger, " CHARGER : OFF\r\n" );
    charger18_buck_control( &charger18, CHARGER18_CONTROL_DISABLE );
    log_printf( &logger, " BUCK    : OFF\r\n" );
    charger18_ldo_control( &charger18, CHARGER18_CONTROL_DISABLE );
    log_printf( &logger, " LDO     : OFF\r\n" );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This function enables the charger, BUCK and LDO in the span of 25 seconds, and displays the status of each feature on the USB UART.

```c
void application_task ( void )
{
    charger18_suspend_control( &charger18, CHARGER18_CONTROL_DISABLE );
    log_printf( &logger, " CHARGER : ON\r\n" );
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
    charger18_suspend_control( &charger18, CHARGER18_CONTROL_ENABLE );
    log_printf( &logger, " CHARGER : OFF\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    charger18_buck_control( &charger18, CHARGER18_CONTROL_ENABLE );
    log_printf( &logger, " BUCK    : ON\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    charger18_buck_control( &charger18, CHARGER18_CONTROL_DISABLE );
    log_printf( &logger, " BUCK    : OFF\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    charger18_ldo_control( &charger18, CHARGER18_CONTROL_ENABLE );
    log_printf( &logger, " LDO     : ON\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    charger18_ldo_control( &charger18, CHARGER18_CONTROL_DISABLE );
    log_printf( &logger, " LDO     : OFF\r\n\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
