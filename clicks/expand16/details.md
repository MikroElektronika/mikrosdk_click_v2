
---
# Expand 16 click

> Expand 16 Click is a compact add-on board with a multi-port I/O expander. This board features the FLX6408, a fully configurable 8-bit GPIO expander from ON Semiconductor. It brings eight independently configurable input/output ports, with a 6mA output drive, when configured in the output mode. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/expand16_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/expand-16-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Expand 16 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Expand 16 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of Expand 16 click board by setting and reading 
  the ports state.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration which sets 
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

## Note

> In order for this example to work as intended it is necessary to connect the input and output pins 
  eg. GPIO0 and GPIO4, GPIO1 and GPIO5 etc. Floating input pins will be shown as a low state.

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand16

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
