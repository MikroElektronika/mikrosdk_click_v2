\mainpage Main Page

---
# SolidSwitch 8 Click

> SolidSwitch 8 Click is a compact add-on board for reliable load control in automotive and industrial applications. This board features the BTS3035EJXUMA1, a smart low-side switch from Infineon. It features a 35mΩ N-channel MOSFET, capable of handling load voltages from 6V to 18V and currents up to 5A, making it suitable for various resistive, inductive, and capacitive loads. The board includes essential protection mechanisms like overtemperature shutdown, overvoltage protection, and current limitation, ensuring reliable operation under demanding conditions. With integrated feedback through an open-drain status pin and a red LED indicator for visual alerts, it enhances diagnostics and safety.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/solidswitch8_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/solidswitch-8-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2024.
- **Type**          : GPIO type


# Software Support

We provide a library for the SolidSwitch 8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for SolidSwitch 8 Click driver.

#### Standard key functions :

- `solidswitch8_cfg_setup` Config Object Initialization function.
```c
void solidswitch8_cfg_setup ( solidswitch8_cfg_t *cfg );
```

- `solidswitch8_init` Initialization function.
```c
err_t solidswitch8_init ( solidswitch8_t *ctx, solidswitch8_cfg_t *cfg );
```

- `solidswitch8_default_cfg` Click Default Configuration function.
```c
err_t solidswitch8_default_cfg ( solidswitch8_t *ctx );
```

#### Example key functions :

- `solidswitch8_set_err_pin` This function sets the err pin state to the selected level of SolidSwitch 8 Click board.
```c
void solidswitch8_set_err_pin ( solidswitch8_t *ctx, uint8_t pin_state );
```

- `solidswitch8_set_in_pin` This function sets the in pin state to the selected level of SolidSwitch 8 Click board.
```c
void solidswitch8_set_in_pin ( solidswitch8_t *ctx, uint8_t pin_state );
```

- `solidswitch8_get_sts_pin` This function reads the state of the status pin of SolidSwitch 8 Click board.
```c
uint8_t solidswitch8_get_sts_pin ( solidswitch8_t *ctx );
```

## Example Description

> This example demonstrates the use of SolidSwitch 8 Click board by switching state of the switch.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver, performs the Click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch8_cfg_t solidswitch8_cfg;  /**< Click config object. */

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
    solidswitch8_cfg_setup( &solidswitch8_cfg );
    SOLIDSWITCH8_MAP_MIKROBUS( solidswitch8_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == solidswitch8_init( &solidswitch8, &solidswitch8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    solidswitch8_default_cfg ( &solidswitch8 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Switching state of the output every 5 seconds, and monitoring the status of the device.

```c
void application_task ( void ) 
{
    if ( SOLIDSWITCH8_PIN_STATE_LOW == solidswitch8_get_sts_pin( &solidswitch8 ) )
    {
        solidswitch8_set_err_pin( &solidswitch8, SOLIDSWITCH8_PIN_STATE_HIGH );
        log_error( &logger, " Detected over temperature condition." );
        for ( ; ; );
    }

    log_printf( &logger, " Switch state closed. \r\n" );
    solidswitch8_set_in_pin( &solidswitch8, SOLIDSWITCH8_PIN_STATE_HIGH );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, " Switch state open. \r\n" );
    solidswitch8_set_in_pin( &solidswitch8, SOLIDSWITCH8_PIN_STATE_LOW );
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
- Click.SolidSwitch8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
