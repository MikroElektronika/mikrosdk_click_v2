\mainpage Main Page

---
# Expand 15 Click

> Expand 15 Click is a compact add-on board that contains a multi-channel I/O expander. This board features the TCAL6416, a general-purpose I/O expansion for most microcontroller families from Texas Instruments.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand15_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/expand-15-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Mar 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Expand 15 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Expand 15 Click driver.

#### Standard key functions :

- `expand15_cfg_setup` Config Object Initialization function.
```c
void expand15_cfg_setup ( expand15_cfg_t *cfg );
```

- `expand15_init` Initialization function.
```c
err_t expand15_init ( expand15_t *ctx, expand15_cfg_t *cfg );
```

- `expand15_default_cfg` Click Default Configuration function.
```c
err_t expand15_default_cfg ( expand15_t *ctx );
```

#### Example key functions :

- `expand15_hw_reset` Expand 15 hardware reset function.
```c
void expand15_hw_reset ( expand15_t *ctx );
```

- `expand15_get_in_pin_state` Expand 15 get input pin state function.
```c
err_t expand15_get_in_pin_state ( expand15_t *ctx, uint8_t port, uint8_t *pin_state );
```

- `expand15_set_out_pin_state` Expand 15 set output pin state function.
```c
err_t expand15_set_out_pin_state ( expand15_t *ctx, uint8_t port, uint8_t pin_state );
```

## Example Description

> This example demonstrates the use of Expand 15 Click board by setting and reading 
 the ports state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which sets 
  half of the port 0 and port 1 pins as output ( P00, P02, P04, P06, P10, P12, P14 and P16) and the 
  half of the port 0 and port 1 pins as inputs ( P01, P03, P05, P07, P11, P13, P15 and P17).

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand15_cfg_t expand15_cfg;  /**< Click config object. */

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
    expand15_cfg_setup( &expand15_cfg );
    EXPAND15_MAP_MIKROBUS( expand15_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand15_init( &expand15, &expand15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( EXPAND15_ERROR == expand15_default_cfg ( &expand15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - - - - - - - - - - \r\n" );
}

```

### Application Task

> Sets the state of the output pins of one port and then reads the status of input pins of that port
 and displays the results on the USB UART approximately 2 seconds.

```c
void application_task ( void ) 
{
    uint8_t output_pin_state;
    uint8_t input_pin_state;
    
    // Setting port0 output pin ( P00, P02, P04 and P06 ) to high
    output_pin_state = EXPAND15_PIN_00_MASK | EXPAND15_PIN_02_MASK | EXPAND15_PIN_04_MASK | EXPAND15_PIN_06_MASK;
    expand15_set_out_pin_state( &expand15, EXPAND15_PORT_0, output_pin_state );
    Delay_ms ( 10 );
    
    // Checking state of the input pins on port0
    expand15_get_in_pin_state( &expand15, EXPAND15_PORT_0, &input_pin_state );
    log_printf( &logger, "OUTPUT PINS HIGH \r\n" );
    log_printf( &logger, "INPUT PINS |" );
    log_printf( &logger, " P01 : %c |", ( ( input_pin_state & EXPAND15_PIN_01_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P03 : %c |", ( ( input_pin_state & EXPAND15_PIN_03_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P05 : %c |", ( ( input_pin_state & EXPAND15_PIN_05_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P07 : %c \r\n", ( ( input_pin_state & EXPAND15_PIN_07_MASK ) ? 'H' : 'L' ) );
    Delay_ms ( 500 );
    
    // Setting port0 output pin ( P00, P02, P04 and P06 ) to low
    output_pin_state = EXPAND15_ALL_PINS_OFF;
    expand15_set_out_pin_state( &expand15, EXPAND15_PORT_0, output_pin_state );
    Delay_ms ( 10 );
    
    // Checking state of the input pins on port0
    expand15_get_in_pin_state( &expand15, EXPAND15_PORT_0, &input_pin_state );
    log_printf( &logger, "OUTPUT PINS LOW \r\n" );
    log_printf( &logger, "INPUT PINS |" );
    log_printf( &logger, " P01 : %c |", ( ( input_pin_state & EXPAND15_PIN_01_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P03 : %c |", ( ( input_pin_state & EXPAND15_PIN_03_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P05 : %c |", ( ( input_pin_state & EXPAND15_PIN_05_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P07 : %c \r\n", ( ( input_pin_state & EXPAND15_PIN_07_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - - - - - - - - - - \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // Setting port1 output pin ( P10, P12, P14 and P01 ) to high
    output_pin_state = EXPAND15_PIN_10_MASK | EXPAND15_PIN_12_MASK | EXPAND15_PIN_14_MASK | EXPAND15_PIN_16_MASK;
    expand15_set_out_pin_state( &expand15, EXPAND15_PORT_1, output_pin_state );
    Delay_ms ( 10 );
    
    // Checking state of the input pins on port1
    expand15_get_in_pin_state( &expand15, EXPAND15_PORT_1, &input_pin_state );
    log_printf( &logger, "OUTPUT PINS HIGH \r\n" );
    log_printf( &logger, "INPUT PINS |" );
    log_printf( &logger, " P11 : %c |", ( ( input_pin_state & EXPAND15_PIN_11_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P13 : %c |", ( ( input_pin_state & EXPAND15_PIN_13_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P15 : %c |", ( ( input_pin_state & EXPAND15_PIN_15_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P17 : %c \r\n", ( ( input_pin_state & EXPAND15_PIN_17_MASK ) ? 'H' : 'L' ) );
    Delay_ms ( 500 );
    
    // Setting port1 output pin ( P10, P12, P14 and P16 ) to low
    output_pin_state = EXPAND15_ALL_PINS_OFF;
    expand15_set_out_pin_state( &expand15, EXPAND15_PORT_1, output_pin_state );
    Delay_ms ( 10 );
    
    // Checking state of the input pins on port1
    expand15_get_in_pin_state( &expand15, EXPAND15_PORT_1, &input_pin_state );
    log_printf( &logger, "OUTPUT PINS LOW \r\n" );
    log_printf( &logger, "INPUT PINS |" );
    log_printf( &logger, " P11 : %c |", ( ( input_pin_state & EXPAND15_PIN_11_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P13 : %c |", ( ( input_pin_state & EXPAND15_PIN_13_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P15 : %c |", ( ( input_pin_state & EXPAND15_PIN_15_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, " P17 : %c \r\n", ( ( input_pin_state & EXPAND15_PIN_17_MASK ) ? 'H' : 'L' ) );
    log_printf( &logger, "- - - - - - - - - - - - - - - - - - - - - - - - - - \r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

## Note

> In order for this example to work as intended it is necessary to connect the input and output pins 
 eg. P00 and P01, P02 and P03 etc. Floating input pins will be shown as a high state.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand15

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
