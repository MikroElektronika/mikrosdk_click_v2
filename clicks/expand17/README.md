
---
# Expand 17 Click

> [Expand 17 Click](https://www.mikroe.com/?pid_product=MIKROE-6054) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6054&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Dec 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Expand 17 Click board by setting and reading the ports state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand17

### Example Key Functions

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

### Note

> In order for this example to work as intended it is necessary to connect the input and output pins 
 eg. IO1 and IO5, IO2 and IO6 etc. Floating input pins will be shown as a high state.

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
