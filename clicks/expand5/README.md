
---
# Expand 5 Click

> [Expand 5 Click](https://www.mikroe.com/?pid_product=MIKROE-4186) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4186&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Expand 5 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand5

### Example Key Functions

- `expand5_cfg_setup` Config Object Initialization function. 
```c
void expand5_cfg_setup ( expand5_cfg_t *cfg );
``` 
 
- `expand5_init` Initialization function. 
```c
err_t expand5_init ( expand5_t *ctx, expand5_cfg_t *cfg );
```

- `expand5_write_all_banks` Set all OUTPUT pins' logic levels in all banks function. 
```c
void expand5_write_all_banks ( expand5_t *ctx, uint8_t bank0, uint8_t bank1, uint8_t bank2 );
```
 
- `expand5_get_bank_pol` Get all pin polarity ( normal/inverted ) settings from one bank function. 
```c
uint8_t expand5_get_bank_pol ( expand5_t *ctx, uint8_t bank );
```

- `expand5_get_pin_dir` Get a single pin's direction ( I/O ) setting function. 
```c
uint8_t expand5_get_pin_dir ( expand5_t *ctx, uint16_t pin );
```

### Application Init

> Initalizes I2C driver, resets the device, configures all pins as output and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    expand5_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );
    
    //  Click initialization.

    expand5_cfg_setup( &cfg );
    EXPAND5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    expand5_init( &expand5, &cfg );

    Delay_ms ( 100 );

    log_printf( &logger, "------------------- \r\n" );
    log_printf( &logger, "   EXPAND 5 Click   \r\n" );
    log_printf( &logger, "------------------- \r\n" );
    expand5_reset( &expand5 );
    expand5_set_all_dir( &expand5, bank_out, bank_out, bank_out );
    Delay_ms ( 100 );
    log_printf( &logger, "  Pins configured   \r\n" );
    log_printf( &logger, "     as output      \r\n" );
    log_printf( &logger, "------------------- \r\n" );
}
```

### Application Task

> This example shows the capabilities of the EXPAND 5 Click by toggling each of the 24 available pins.

```c
void application_task ( void )
{
    for ( pin_num = EXPAND5_P00; pin_num <= EXPAND5_P27; pin_num++ )
    {
        expand5_write_all_banks ( &expand5, bank_low, bank_low, bank_low );
        expand5_write_pin ( &expand5, pin_num, EXPAND5_HIGH );
        log_printf( &logger, "Pin %u is high \r\n", ( uint16_t ) pin_num );

        Delay_ms ( 200 );
        expand5_write_all_banks ( &expand5, bank_low, bank_low, bank_low );
    }
    log_printf( &logger, "------------------- \r\n" );
    Delay_ms ( 1000 );
}
```


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
