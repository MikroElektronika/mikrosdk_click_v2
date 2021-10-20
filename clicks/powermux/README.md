\mainpage Main Page

---
# Power MUX click

> Power MUX Click features power multiplexer that enables transition between two power supplies (such as a battery and a wall adapter), each operating at 2.8V to 5.5V and delivering up to 2A current depending on the package. This IC provides inrush current control and thermal protection to Power MUX Click, manual and auto-switching operating modes, cross-conduction blocking, and reverse-conduction blocking.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/powermux_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/power-mux-click)

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
    log_cfg_t log_cfg;  /**< Logger config object. */
    powermux_cfg_t powermux_cfg;  /**< Click config object. */

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
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == powermux_init( &powermux, &powermux_cfg ) ) {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    powermux_default_cfg ( &powermux );
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-----------------------------\r\n " );
    log_printf( &logger, "      Select mode: \r\n " );
    log_printf( &logger, "-----------------------------\r\n " );
    log_printf( &logger, " 1. Input from channel 1. \r\n " );
    log_printf( &logger, " 2. Input from channel 2. \r\n " );
    log_printf( &logger, " 3. Input OFF. \r\n " );
    log_printf( &logger, " 3. Auto mode. \r\n " );
    log_printf( &logger, "-----------------------------\r\n " );
}

```

### Application Task

> Waits for user input in order to change input mode of the Power MUX Click. 

```c

void application_task ( void ) 
{
    char uart_char;
    if ( log_read( &logger, &uart_char, 1 ) ) {
        switch ( uart_char ) {
            case '1' : {
                log_printf( &logger, " Output mode : Input channel 1 \r\n " );
                powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_1_ON );
                log_printf( &logger, "-----------------------------\r\n " );
                break;
            }
            case '2' : {
                log_printf( &logger, " Output mode : Input channel 2 \r\n " );
                powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_2_ON );
                log_printf( &logger, "-----------------------------\r\n " );
                break;
            }
            case '3' : {
                log_printf( &logger, " Output mode : Input channels OFF \r\n " );
                powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_OFF );
                log_printf( &logger, "-----------------------------\r\n " );
                break;
            }
            case '4' : {
                log_printf( &logger, " Output mode : AUTO \r\n " );
                powermux_set_mode( &powermux, POWERMUX_INPUT_CHANNEL_AUTO );
                log_printf( &logger, "-----------------------------\r\n " );
                break;
            }
            default : {
                log_printf( &logger, "      Select mode: \r\n " );
                log_printf( &logger, "-----------------------------\r\n " );
                log_printf( &logger, " 1. Input from channel 1. \r\n " );
                log_printf( &logger, " 2. Input from channel 2. \r\n " );
                log_printf( &logger, " 3. Input OFF. \r\n " );
                log_printf( &logger, " 3. Auto mode. \r\n " );
                log_printf( &logger, "-----------------------------\r\n " );
                break;
            }
        }
    }
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PowerMUX

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
