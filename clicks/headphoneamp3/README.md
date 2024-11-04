\mainpage Main Page

---
# Headphone AMP 3 Click

> Headphone AMP 3 Click is a compact add-on board that contains a stereo headphone amplifier. This board features the INA1620, a high-fidelity audio operational amplifier with integrated thin-film resistors and EMI filters from Texas Instruments. Over its dual amplifiers, it achieves a very low noise density and drives a 32Ω load at 150mW of output power. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/headphoneamp3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/headphone-amp-3-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Apr 2023.
- **Type**          : GPIO type


# Software Support

We provide a library for the Headphone AMP 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Headphone AMP 3 Click driver.

#### Standard key functions :

- `headphoneamp3_cfg_setup` Config Object Initialization function.
```c
void headphoneamp3_cfg_setup ( headphoneamp3_cfg_t *cfg );
```

- `headphoneamp3_init` Initialization function.
```c
err_t headphoneamp3_init ( headphoneamp3_t *ctx, headphoneamp3_cfg_t *cfg );
```

- `headphoneamp3_default_cfg` Click Default Configuration function.
```c
void headphoneamp3_default_cfg ( headphoneamp3_t *ctx );
```

#### Example key functions :

- `headphoneamp3_enable_power` Headphone AMP 3 power pin setting function.
```c
void headphoneamp3_enable_power ( headphoneamp3_t *ctx, uint8_t state );
```

- `headphoneamp3_enable_amp` Headphone AMP 3 amp pin setting function.
```c
void headphoneamp3_enable_amp ( headphoneamp3_t *ctx, uint8_t state );
```

## Example Description

> This library contains API for the Headphone AMP 3 Click driver.
  This demo application shows use of a Headphone AMP 3 Click board™.

**The demo application is composed of two sections :**

### Application Init

> Initialization of GPIO module and log UART.
  After driver initialization the app set default settings.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    headphoneamp3_cfg_t headphoneamp3_cfg;  /**< Click config object. */

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
    headphoneamp3_cfg_setup( &headphoneamp3_cfg );
    HEADPHONEAMP3_MAP_MIKROBUS( headphoneamp3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == headphoneamp3_init( &headphoneamp3, &headphoneamp3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    headphoneamp3_default_cfg ( &headphoneamp3 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> This example demonstrates the use of the Headphone AMP 3 Click board™.
  The app is enabling and disabling headphone output by changing ENA pin state every 10 seconds. 

```c
void application_task ( void ) 
{
    log_printf( &logger, " Enabling headphone output \r\n" );
    headphoneamp3_enable_amp( &headphoneamp3, HEADPHONEAMP3_ENABLE );
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
    
    log_printf( &logger, " Disabling headphone output \r\n" );
    headphoneamp3_enable_amp( &headphoneamp3, HEADPHONEAMP3_DISABLE );
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
- Click.HeadphomeAMP3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
