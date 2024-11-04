\mainpage Main Page

---
# Boost 8 Click

> Boost 8 Click is a compact add-on board that steps up the voltage from its input (supply) to its output (load).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/boost8_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/boost-8-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2022.
- **Type**          : GPIO type


# Software Support

We provide a library for the Boost 8 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Boost 8 Click driver.

#### Standard key functions :

- `boost8_cfg_setup` Config Object Initialization function.
```c
void boost8_cfg_setup ( boost8_cfg_t *cfg );
```

- `boost8_init` Initialization function.
```c
err_t boost8_init ( boost8_t *ctx, boost8_cfg_t *cfg );
```

- `boost8_default_cfg` Click Default Configuration function.
```c
void boost8_default_cfg ( boost8_t *ctx );
```

#### Example key functions :

- `boost8_enable_positive_voltage` Enable positive voltage output function.
```c
void boost8_enable_positive_voltage( boost8_t *ctx );
```

- `boost8_disable_positive_voltage` Disable positive voltage output function.
```c
void boost8_disable_positive_voltage( boost8_t *ctx );
```

- `boost8_enable_negative_voltage` Enable negative voltage output function.
```c
void boost8_enable_negative_voltage( boost8_t *ctx );
```

## Example Description

> This is an example that demonstrates the use of the Boost 8 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes EN+ and EN- pins, UART log, and performs default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    boost8_cfg_t boost8_cfg;  /**< Click config object. */

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
    boost8_cfg_setup( &boost8_cfg );
    BOOST8_MAP_MIKROBUS( boost8_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == boost8_init( &boost8, &boost8_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    boost8_default_cfg ( &boost8 );
    
    log_info( &logger, " Application Task " );
    boost8_list_of_commands();
}

```

### Application Task

> Waits for user input in order to determine what output should be enabled.

```c
void application_task ( void ) 
{
    char inx;
    
    // Waiting for the user input and performing actions based on a selected command.
    if ( log_read( &logger, &inx, 1 ) != BOOST8_ERROR )
    {
        switch(inx)
        {
            case '1' :
            {
                log_printf( &logger, "Turning on positive output \r\n" );
                boost8_enable_positive_voltage( &boost8 );
                break;
            }
            case '2' :
            {
                log_printf( &logger, "Turning off positive output \r\n" );
                boost8_disable_positive_voltage( &boost8 );
                break;
            }
            case '3' :
            {
                log_printf( &logger, "Turning on negative output \r\n" );
                boost8_enable_negative_voltage( &boost8 );
                break;
            }
            case '4':
            {
                log_printf( &logger, "Turning off negative output \r\n" );
                boost8_disable_negative_voltage( &boost8 );
                break;
            }
            case '5' :
            {
                log_printf( &logger, "Turning on both outputs \r\n" );
                boost8_enable_both_outputs( &boost8 );
                break;
            }
            case '6' :
            {
                log_printf( &logger, "Turning off both outputs \r\n" );
                boost8_disable_both_outputs( &boost8 );
                break;
            }
            default:
            {
                log_printf( &logger, "> Invalid command \r\n" );
                boost8_list_of_commands();
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
- Click.Boost8

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
