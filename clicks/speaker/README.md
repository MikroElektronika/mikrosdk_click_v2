\mainpage Main Page

---
# Speaker click

Speaker Click is a compact add-on board that contains an audio power amplifier with a high-quality audio reproduction. This board features the MAX9717, a 1.4W mono bridge-tied load (BTL) architecture audio power amplifier from Maxim Integrated.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/speaker_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/speaker-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the Speaker Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Speaker Click driver.

#### Standard key functions :

- `speaker_cfg_setup` Config Object Initialization function.
```c
void speaker_cfg_setup ( speaker_cfg_t *cfg );
```

- `speaker_init` Initialization function.
```c
SPEAKER_RETVAL speaker_init ( speaker_t *ctx, speaker_cfg_t *cfg );
```

- `speaker_default_cfg` Click Default Configuration function.
```c
void speaker_default_cfg ( speaker_t *ctx );
```

#### Example key functions :

- `speaker_shutdown` Speaker shutdown mode function.
```c
err_t speaker_shutdown ( speaker_t *ctx );
```

- `speaker_normal_operation` Speaker normal operation mode function.
```c
err_t speaker_normal_operation ( speaker_t *ctx );
```

- `speaker_enable_slave_amp` Speaker enables the slave amplifier function.
```c
err_t speaker_enable_slave_amp ( speaker_t *ctx );
```

## Example Description

> This library contains API for the Speaker click driver.
> This application controls the operating modes of the 
> Speaker click board™.

**The demo application is composed of two sections :**

### Application Init

> Initialization of GPIO module and log UART.
> After driver initialization, the application performs the default settings.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;          /**< Logger config object. */
    speaker_cfg_t speaker_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    speaker_cfg_setup( &speaker_cfg );
    SPEAKER_MAP_MIKROBUS( speaker_cfg, MIKROBUS_1 );
    if ( speaker_init( &speaker, &speaker_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    speaker_default_cfg ( &speaker );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that shows the use of a Speaker click board™.
> The task of the application consists of 
> switching two modes of operation: normal and shutdown modes.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "  Normal Operation Mode \r\n" );
    speaker_normal_operation( &speaker );
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
    
    log_printf( &logger, "-------------------------\r\n" );
    log_printf( &logger, "   Enter Shutdown Mode  \r\n" );
    speaker_shutdown( &speaker );
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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Speaker

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
