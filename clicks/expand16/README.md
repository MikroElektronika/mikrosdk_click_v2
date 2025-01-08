
---
# Expand 16 Click

> [Expand 16 Click](https://www.mikroe.com/?pid_product=MIKROE-5939) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5939&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Expand 16 Click board by setting and reading 
  the ports state.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand16

### Example Key Functions

- `expand16_cfg_setup` Config Object Initialization function.
```c
void expand16_cfg_setup ( expand16_cfg_t *cfg );
```

- `expand16_init` Initialization function.
```c
err_t expand16_init ( expand16_t *ctx, expand16_cfg_t *cfg );
```

- `expand16_default_cfg` Click Default Configuration function.
```c
err_t expand16_default_cfg ( expand16_t *ctx );
```

- `expand16_write_reg` Expand 16 register write function.
```c
err_t expand16_write_reg ( expand16_t *ctx, uint8_t reg, uint8_t data_in );
```

- `expand16_set_io_dir` Expand 16 set pin input or output direction function.
```c
err_t expand16_set_io_dir ( expand16_t *ctx, uint8_t input_pins, uint8_t output_pins );
```

- `expand16_set_output_state` Expand 16 set output pins state function.
```c
err_t expand16_set_output_state ( expand16_t *ctx, uint8_t clr_mask, uint8_t set_mask );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets 
  half of the pins as output ( GPIO4, GPIO5, GPIO6 and GPIO7 ) and the 
  other half of the pins as inputs ( GPIO0, GPIO1, GPIO2 and GPIO3 ).

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    expand16_cfg_t expand16_cfg;    /**< Click config object. */

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
    expand16_cfg_setup( &expand16_cfg );
    EXPAND16_MAP_MIKROBUS( expand16_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == expand16_init( &expand16, &expand16_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    uint8_t dev_id = 0;
    expand16_read_reg( &expand16, EXPAND16_REG_DEV_ID_AND_CTRL, &dev_id ); 
    if ( EXPAND16_DEVICE_ID != ( dev_id & EXPAND16_DEVICE_ID_MASK ) )
    {
        log_error( &logger, " Communication error." );
        for ( ; ; );
    }
    
    if ( EXPAND16_ERROR == expand16_default_cfg ( &expand16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Sets the state of the output pins and then reads the status of input pins
  and displays the results on the USB UART approximately 2 seconds.

```c
void application_task ( void ) 
{
    uint8_t tmp_data = 0;

    log_printf( &logger, "Output pins state: HIGH \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    expand16_set_output_state( &expand16, EXPAND16_PIN_MASK_NONE, EXPAND16_PIN_MASK_GPIO_4 | 
                                          EXPAND16_PIN_MASK_GPIO_5 | EXPAND16_PIN_MASK_GPIO_6 | 
                                          EXPAND16_PIN_MASK_GPIO_7 );
    expand16_read_reg( &expand16, EXPAND16_REG_INPUT_STATE, &tmp_data ); 
    show_input_pin_state( tmp_data );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "Output pins state: LOW \r\n" );
    log_printf( &logger, "- - - - - - - - - - - - -\r\n" );
    expand16_set_output_state( &expand16, EXPAND16_PIN_MASK_GPIO_4 | EXPAND16_PIN_MASK_GPIO_5 | 
                                          EXPAND16_PIN_MASK_GPIO_6 | EXPAND16_PIN_MASK_GPIO_7, 
                                          EXPAND16_PIN_MASK_NONE );
    expand16_read_reg( &expand16, EXPAND16_REG_INPUT_STATE, &tmp_data ); 
    show_input_pin_state( tmp_data );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> In order for this example to work as intended it is necessary to connect the input and output pins 
  eg. GPIO0 and GPIO4, GPIO1 and GPIO5 etc. Floating input pins will be shown as a low state.

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
