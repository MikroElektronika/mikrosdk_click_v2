
---
# MIC 3 click

> The MIC 3 Click is a Click board™ that features the SSM2167-1RMZ-R7, a Microphone Preamplifier, from Analog Device. This Click board™ is a low voltage Microphone preamplifier with Variable compression and noise gating.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mic3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mic-3-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the MIC3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for MIC3 Click driver.

#### Standard key functions :

- `mic3_cfg_setup` Config Object Initialization function.
```c
void mic3_cfg_setup ( mic3_cfg_t *cfg );
```

- `mic3_init` Initialization function.
```c
err_t mic3_init ( mic3_t *ctx, mic3_cfg_t *cfg );
```

- `mic3_default_cfg` Click Default Configuration function.
```c
err_t mic3_default_cfg ( mic3_t *ctx );
```

#### Example key functions :

- `mic3_shd_pin_set` MIC 3 SHD pin setting function.
```c
void mic3_shd_pin_set ( mic3_t *ctx, uint8_t state ); 
```

## Example Description

> This is an example that demonstrates the use of the MIC 3 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SHD to output and log module, maping GPIO for Mikrobus1, and seting SHD pin to HIGH state.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    mic3_cfg_t mic3_cfg;  /**< Click config object. */

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
    mic3_cfg_setup( &mic3_cfg );
    MIC3_MAP_MIKROBUS( mic3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == mic3_init( &mic3, &mic3_cfg ) ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    mic3_default_cfg ( &mic3 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Turning microphone on for the 5 seconds, then turning it off for 5 seconds.

```c

void application_task ( void ) 
{
    log_printf( &logger, " - Microphone is turned on  - \r\n" );
    mic3_shd_pin_set( &mic3, MIC3_PIN_STATE_HIGH );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " - Microphone is turned off  - \r\n" );
    mic3_shd_pin_set( &mic3, MIC3_PIN_STATE_LOW );
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
- Click.MIC3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
