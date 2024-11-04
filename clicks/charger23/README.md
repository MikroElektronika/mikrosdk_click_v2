\mainpage Main Page

---
# Charger 23 Click

> Charger 23 Click is a compact add-on board providing a single-cell battery charging solution. This board features the ISL78693, a single-cell Li-ion or Li-polymer battery charger from Renesas. The ISL78693 can operate with an input voltage as low as 2.6V and works as a linear charger with the battery charged in a Constant Current/Constant Voltage (CC/CV) profile. The charge current is selectable with an external resistor between 250 and 500mA. Additional features include the preconditioning of an over-discharged battery, an NTC thermistor interface for charging the battery in a safe temperature range, automatic recharge, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/charger23_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/charger-23-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2022.
- **Type**          : GPIO type


# Software Support

We provide a library for the Charger 23 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Charger 23 Click driver.

#### Standard key functions :

- `charger23_cfg_setup` Config Object Initialization function.
```c
void charger23_cfg_setup ( charger23_cfg_t *cfg );
```

- `charger23_init` Initialization function.
```c
err_t charger23_init ( charger23_t *ctx, charger23_cfg_t *cfg );
```

#### Example key functions :

- `charger23_enable_device` This function enables the device by setting the EN pin to HIGH logic state.
```c
void charger23_enable_device ( charger23_t *ctx );
```

- `charger23_disable_device` This function disables the device by setting the EN pin to LOW logic state.
```c
void charger23_disable_device ( charger23_t *ctx );
```

- `charger23_get_charger_state` This function returns the charger state.
```c
uint8_t charger23_get_charger_state ( charger23_t *ctx );
```

## Example Description

> This example demonstrates the use of Charger 23 Click board by enabling the device and then reading and displaying the charger status.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and enables the device.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger23_cfg_t charger23_cfg;  /**< Click config object. */

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
    charger23_cfg_setup( &charger23_cfg );
    CHARGER23_MAP_MIKROBUS( charger23_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == charger23_init( &charger23, &charger23_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    charger23_enable_device ( &charger23 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the charger state and displays it on the USB UART on change.

```c
void application_task ( void )
{
    static uint8_t chg_state_old = CHARGER23_STATE_UNKNOWN;
    uint8_t chg_state = charger23_get_charger_state ( &charger23 );
    if ( chg_state_old != chg_state )
    {
        chg_state_old = chg_state;
        log_printf( &logger, "\r\n Charger state: " );
        switch ( chg_state )
        {
            case CHARGER23_STATE_IDLE:
            {
                log_printf( &logger, "Charge completed with no fault (Inhibit) or Standby\r\n" );
                break;
            }
            case CHARGER23_STATE_CHARGING:
            {
                log_printf( &logger, "Charging in one of the three modes\r\n" );
                break;
            }
            case CHARGER23_STATE_FAULT:
            {
                log_printf( &logger, "Fault\r\n" );
                break;
            }
            default:
            {
                log_printf( &logger, "Unknown\r\n" );
                break;
            }
        }
        Delay_ms ( 100 );
    }
}
```

## Note

> Depending on the CURR SEL onboard jumper position this Click board is able to charge batteries of 250mAh or 500mAh rated capacity.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger23

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
