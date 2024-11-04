\mainpage Main Page

---
# Expand 17 Click

> Expand 17 Click is a compact add-on board designed to expand the number of input/output pins in your system. This board features the TCAL6408, an 8-bit I/O expander from Texas Instruments, which communicates via the I2C protocol. The TCAL6408 features programmable output drive strength, latchable inputs, pull-up/pull-down resistors, and configurable open-drain or push-pull outputs, offering flexible and enhanced I/O performance with minimal power consumption and reduced EMI.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand17_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/expand-17-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Expand 17 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Expand 17 Click driver.

#### Standard key functions :

- `expand17_cfg_setup` Config Object Initialization function.
```c
void expand17_cfg_setup ( expand17_cfg_t *cfg );
```

- `expand17_init` Initialization function.
```c
err_t expand17_init ( expand17_t *ctx, expand17_cfg_t *cfg );
```

- `expand17_default_cfg` Click Default Configuration function.
```c
err_t expand17_default_cfg ( expand17_t *ctx );
```

#### Example key functions :

- `expand17_set_io_dir` This function is used to set input or output direction of pins.
```c
err_t expand17_set_io_dir ( expand17_t *ctx, uint8_t input_pins, uint8_t output_pins );
```

- `expand17_set_output_state` This function is used to set output state of the pins.
```c
err_t expand17_set_output_state ( expand17_t *ctx, uint8_t clr_mask, uint8_t set_mask );
```

- `expand17_get_input_state` This function is used to get state of the input pins.
```c
err_t expand17_get_input_state ( expand17_t *ctx, uint8_t *input_state );
```

## Example Description

> This example demonstrates the use of Expand 17 Click board by setting and reading the ports state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which sets 
 half of pins as output ( IO5, IO6, IO7 and IO8 ) and the 
 half of the pins as inputs ( IO1, IO2, IO3 and IO4 ).

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand17_cfg_t expand17_cfg;  /**< Click config object. */

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
    expand17_cfg_setup( &expand17_cfg );
    EXPAND17_MAP_MIKROBUS( expand17_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand17_init( &expand17, &expand17_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND17_ERROR == expand17_default_cfg ( &expand17 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Sets the state of the output pins and then reads the status of the input pins
 and displays the results on the USB UART approximately every 2 seconds.

```c
void application_task ( void ) 
{
    uint8_t input_state = 0;

    log_printf( &logger, " Setting output pins state: HIGH \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    expand17_set_output_state( &expand17, EXPAND17_NO_IO_PIN_MASK, EXPAND17_IO_5_PIN_MASK | 
                                          EXPAND17_IO_6_PIN_MASK | EXPAND17_IO_7_PIN_MASK | 
                                          EXPAND17_IO_8_PIN_MASK );

    log_printf( &logger, " State of input pins: \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    expand17_get_input_state( &expand17, &input_state );
    if ( input_state & EXPAND17_IO_1_PIN_MASK )
    {
        log_printf( &logger, " IO1 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO1 - LOW \r\n" );
    }
    if ( input_state & EXPAND17_IO_2_PIN_MASK )
    {
        log_printf( &logger, " IO2 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO2 - LOW \r\n" );
    }
    if ( input_state & EXPAND17_IO_3_PIN_MASK )
    {
        log_printf( &logger, " IO3 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO3 - LOW \r\n" );
    }
    if ( input_state & EXPAND17_IO_4_PIN_MASK )
    {
        log_printf( &logger, " IO4 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO4 - LOW \r\n" );
    }
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_printf( &logger, " Setting output pins state: LOW \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    expand17_set_output_state( &expand17, EXPAND17_IO_5_PIN_MASK | EXPAND17_IO_6_PIN_MASK | 
                                          EXPAND17_IO_7_PIN_MASK | EXPAND17_IO_8_PIN_MASK, 
                                          EXPAND17_NO_IO_PIN_MASK );

    log_printf( &logger, " State of input pins: \r\n" );
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    expand17_get_input_state( &expand17, &input_state );
    if ( input_state & EXPAND17_IO_1_PIN_MASK )
    {
        log_printf( &logger, " IO1 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO1 - LOW \r\n" );
    }
    if ( input_state & EXPAND17_IO_2_PIN_MASK )
    {
        log_printf( &logger, " IO2 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO2 - LOW \r\n" );
    }
    if ( input_state & EXPAND17_IO_3_PIN_MASK )
    {
        log_printf( &logger, " IO3 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO3 - LOW \r\n" );
    }
    if ( input_state & EXPAND17_IO_4_PIN_MASK )
    {
        log_printf( &logger, " IO4 - HIGH \r\n" );
    }
    else
    {
        log_printf( &logger, " IO4 - LOW \r\n" );
    }
    log_printf( &logger, " = = = = = = = = = = = = = = = = = \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Note

> In order for this example to work as intended it is necessary to connect the input and output pins 
 eg. IO1 and IO5, IO2 and IO6 etc. Floating input pins will be shown as a high state.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand17

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
