\mainpage Main Page

---
# LED Flash 4 Click

> LED Flash 4 Click is a compact add-on board for high-performance LED flash and torch applications. This board features the AS1170, a high-current LED driver from ams OSRAM. The AS1170 operates as an inductive, highly efficient DC-DC step-up converter with an external power supply range of 2.7V to 4.4V, featuring two internal current sinks for independent control of onboard flash LEDs. It includes essential protection functions such as flash timeout, overvoltage, overtemperature, undervoltage, and short circuit protection, ensuring reliable operation even in demanding environments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ledflash4_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/led-flash-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the LED Flash 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LED Flash 4 Click driver.

#### Standard key functions :

- `ledflash4_cfg_setup` Config Object Initialization function.
```c
void ledflash4_cfg_setup ( ledflash4_cfg_t *cfg );
```

- `ledflash4_init` Initialization function.
```c
err_t ledflash4_init ( ledflash4_t *ctx, ledflash4_cfg_t *cfg );
```

- `ledflash4_default_cfg` Click Default Configuration function.
```c
err_t ledflash4_default_cfg ( ledflash4_t *ctx );
```

#### Example key functions :

- `ledflash4_set_led1_current` This function sets the LED1 maximum current in mA.
```c
err_t ledflash4_set_led1_current ( ledflash4_t *ctx, uint16_t led_current );
```

- `ledflash4_set_led2_current` This function sets the LED2 maximum current in mA.
```c
err_t ledflash4_set_led2_current ( ledflash4_t *ctx, uint16_t led_current );
```

- `ledflash4_set_stb_pin` This function sets the strobe (STB) pin logic state.
```c
void ledflash4_set_stb_pin ( ledflash4_t *ctx, uint8_t state );
```

## Example Description

> This example demonstrates the use of LED Flash 4 Click board by toggling the LEDs output.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which sets
the Click in flash mode with the LED current of 50mA for both LEDs. The strobe pin is set to active high level type.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ledflash4_cfg_t ledflash4_cfg;  /**< Click config object. */

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
    ledflash4_cfg_setup( &ledflash4_cfg );
    LEDFLASH4_MAP_MIKROBUS( ledflash4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ledflash4_init( &ledflash4, &ledflash4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LEDFLASH4_ERROR == ledflash4_default_cfg ( &ledflash4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Toggles the LEDs output every 2 seconds using the strobe pin, and displays the LEDs state on the USB UART.

```c
void application_task ( void )
{
    log_printf( &logger, " LEDs ON\r\n\n" );
    ledflash4_set_stb_pin ( &ledflash4, LEDFLASH4_STROBE_PIN_HIGH );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " LEDs OFF\r\n\n" );
    ledflash4_set_stb_pin ( &ledflash4, LEDFLASH4_STROBE_PIN_LOW );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LEDFlash4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
