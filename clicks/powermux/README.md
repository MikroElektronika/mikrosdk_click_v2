\mainpage Main Page

---
# Power MUX Click

> Power MUX Click features power multiplexer that enables transition between two power supplies (such as a battery and a wall adapter), each operating at 2.8V to 5.5V and delivering up to 2A current depending on the package. This IC provides inrush current control and thermal protection to Power MUX Click, manual and auto-switching operating modes, cross-conduction blocking, and reverse-conduction blocking.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/powermux_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/power-mux-click)

---


#### Click library

- **Author**        : Mikroe Team
- **Date**          : Sep 2021.
- **Type**          : GPIO type


# Software Support

We provide a library for the PowerMUX Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for PowerMUX Click driver.

#### Standard key functions :

- `powermux_cfg_setup` Config Object Initialization function.
```c
void powermux_cfg_setup ( powermux_cfg_t *cfg );
```

- `powermux_init` Initialization function.
```c
err_t powermux_init ( powermux_t *ctx, powermux_cfg_t *cfg );
```

- `powermux_default_cfg` Click Default Configuration function.
```c
void powermux_default_cfg ( powermux_t *ctx );
```

#### Example key functions :

- `powermux_int_pin_read` Power MUX pin reading function.
```c
uint8_t powermux_int_pin_read ( powermux_t *ctx );
```

- `powermux_set_mode` Power MUX mode set function.
```c
void powermux_set_mode ( powermux_t *ctx, uint8_t mode );
```

## Example Description

> This Click features power multiplexer that enables transition between two power supplies, 
> each operating at 2.8V to 5.5V and delivering up to 2A current depending on the package.

**The demo application is composed of two sections :**

### Application Init

> Enables GPIO and starts write log.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;
    powermux_cfg_t powermux_cfg;

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
    powermux_cfg_setup( &powermux_cfg );
    POWERMUX_MAP_MIKROBUS( powermux_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == powermux_init( &powermux, &powermux_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    powermux_default_cfg ( &powermux );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes power inputs every 3 seconds and displays the currently set mode on the USB UART.

```c

void application_task ( void ) 
{
    log_printf( &logger, " OUTPUT : IN1\r\n\n" );
    powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_1_ON );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " OUTPUT : IN2\r\n\n" );
    powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_2_ON );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " OUTPUT : OFF\r\n\n" );
    powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_OFF );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf( &logger, " OUTPUT : AUTO\r\n\n" );
    powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_AUTO );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerMUX

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
