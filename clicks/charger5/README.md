
---
# Charger 5 Click

> [Charger 5 Click](https://www.mikroe.com/?pid_product=MIKROE-2848) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2848&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : SPI type

# Software Support

## Example Description

>
> This example demonstrates the use of the Charger 5 Click board.
>

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger5

### Example Key Functions

- `charger5_cfg_setup` Configuration Object Setup function. 
```c
void charger5_cfg_setup ( charger5_cfg_t *cfg );
```
 
- `charger5_init` Click Initialization function. 
```c
charger5_err_t charger5_init ( charger5_t *ctx, charger5_cfg_t *cfg );
```

- `charger5_default_cfg` Click Default Configuration function. 
```c
void charger5_default_cfg ( charger5_t *ctx );
```

- `charger5_generic_write` Generic Write function. 
```c
charger5_err_t charger5_generic_write ( charger5_t *ctx, uint8_t reg_addr, uint16_t transfer_data );
```
 
- `charger5_generic_read` Generic Read function. 
```c
uint16_t charger5_generic_read ( charger5_t *ctx, uint8_t reg_addr );
```

- `charger5_increment_wiper` Increment Wiper function. 
```c
charger5_err_t charger5_increment_wiper ( charger5_t *ctx, uint8_t reg_addr, uint8_t n_steps );
```

### Application Init

>
> Initializes peripherals and pins used for the Charger 5 Click and prepares the Charger 5 Click for properly working.
>

```c
void application_init( void )
{
    charger5_cfg_t charger5_cfg;
    log_cfg_t console_cfg;

    //  Click initialization.
    charger5_cfg_setup( &charger5_cfg );
    CHARGER5_MAP_MIKROBUS( charger5_cfg, MIKROBUS_1 );
    charger5_init( &charger5, &charger5_cfg );
    charger5_default_cfg( &charger5 );

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( console_cfg );
    log_init( &console, &console_cfg );
    log_write( &console, "***  Charger 5 initialization done  ***",
               LOG_FORMAT_LINE );
    log_write( &console, "***************************************",
               LOG_FORMAT_LINE );
}
```

### Application Task

>
> Demonstrates the use of driver functions. It will set charging current to 500 mA,
> then will increment that value by 10 steps, and after that will decrement it by 5 steps.
>

```c
void application_task( void )
{
    charger5_generic_write( &charger5, CHARGER5_REG_WIPER0_VOL,
                            CHARGER5_CURRENT_500MA );
    log_write( &console, "Output current is set to 500 mA.",
               LOG_FORMAT_LINE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    charger5_increment_wiper( &charger5, CHARGER5_REG_WIPER0_VOL,
                              CHARGER5_STEPS_10 );
    log_write( &console, "Output current value is incremented by 10 steps.",
               LOG_FORMAT_LINE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    charger5_decrement_wiper( &charger5, CHARGER5_REG_WIPER0_VOL,
                              CHARGER5_STEPS_5 );
    log_write( &console, "Output current value is decremented by 5 steps.",
               LOG_FORMAT_LINE );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

>
> Increment/decrement command can only be issued to volatile memory locations.
>

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
