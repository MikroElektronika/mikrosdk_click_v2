
---
# Expand 15 Click

> [Expand 15 Click](https://www.mikroe.com/?pid_product=MIKROE-5679) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5679&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Mar 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Expand 15 Click board by setting and reading 
 the ports state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand15

### Example Key Functions

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

### Note

> In order for this example to work as intended it is necessary to connect the input and output pins 
 eg. P00 and P01, P02 and P03 etc. Floating input pins will be shown as a high state.

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
