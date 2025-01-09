
---
# DIGI POT 5 Click

> [DIGI POT 5 Click](https://www.mikroe.com/?pid_product=MIKROE-2863) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2863&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : SPI type

# Software Support

## Example Description

>
> This example demonstrates the use of the DIGI POT 5 Click board.
>

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DigiPot5

### Example Key Functions

- `digipot5_cfg_setup` Configuration Object Setup function. 
```c
void digipot5_cfg_setup ( digipot5_cfg_t *cfg );
```
 
- `digipot5_init` Click Initialization function. 
```c
digipot5_err_t digipot5_init ( digipot5_t *ctx, digipot5_cfg_t *cfg );
```

- `digipot5_default_cfg` Click Default Configuration function. 
```c
void digipot5_default_cfg ( digipot5_t *ctx );
```

- `digipot5_generic_write` Generic Write function. 
```c
digipot5_err_t digipot5_generic_write ( digipot5_t *ctx, digipot5_reg_t reg_addr, uint16_t data_in );
```
 
- `digipot5_generic_read` Generic Read function. 
```c
digipot5_err_t digipot5_generic_read ( digipot5_t *ctx, digipot5_reg_t reg_addr, uint16_t *data_out );
```

- `digipot5_increment_wiper` Increment Wiper function. 
```c
digipot5_reg_t digipot5_increment_wiper ( digipot5_t *ctx, digipot5_reg_t reg_addr );
```

### Application Init

>
> Initializes all necessary peripherals and pins used for the DIGI POT 5 Click.
> Also allows the device to be reset and configured to enable all wipers (4).
> UART console module will be initialized also in this function.
>

```c
void application_init( void )
{
    digipot5_cfg_t digipot5_cfg;
    log_cfg_t console_cfg;

    //  Click initialization.
    digipot5_cfg_setup( &digipot5_cfg );
    DIGIPOT5_MAP_MIKROBUS( digipot5_cfg, MIKROBUS_1 );
    digipot5_init( &digipot5, &digipot5_cfg );
    digipot5_reset( &digipot5 );
    digipot5_default_cfg( &digipot5 );

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
    log_write( &console, "***  DIGI POT 5 Initialization Done  ***",
               LOG_FORMAT_LINE );
    log_write( &console, "****************************************",
               LOG_FORMAT_LINE );
}
```

### Application Task

>
> Demonstrates the use of Click driver functions by performing a control of
> the all wipers positions. By checking the uart console, user can be informed
> about the all current wipers positions.
>

```c
void application_task( void )
{
    log_write( &console, "* Setting wiper 0 to zero scale.", LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER0_VOL,
                            DIGIPOT5_RES_ZEROSCALE );
    log_write( &console, "* Setting wiper 1 to 3k Ohm.", LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER1_VOL,
                            DIGIPOT5_RES_3KOHM );
    log_write( &console, "* Setting wiper 2 to half scale (5k Ohm).",
               LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER2_VOL,
                            DIGIPOT5_RES_5KOHM_HALFSCALE );
    log_write( &console, "* Setting wiper 3 to full scale (10k Ohm).",
               LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER3_VOL,
                            DIGIPOT5_RES_10KOHM_FULLSCALE );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_write( &console, "* Decrementing wiper 3 by 5 steps.",
               LOG_FORMAT_LINE );
    for ( i = 0; i < 5; i++ )
    {
        digipot5_decrement_wiper( &digipot5, DIGIPOT5_REG_WIPER3_VOL );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_write( &console, "* Incrementing wiper 0 by 10 steps.",
               LOG_FORMAT_LINE );
    for ( i = 0; i < 10; i++ )
    {
        digipot5_increment_wiper( &digipot5, DIGIPOT5_REG_WIPER0_VOL );
    }

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_write( &console, "* Setting wiper 0 to 2k Ohm.", LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER0_VOL,
                            DIGIPOT5_RES_2KOHM );
    log_write( &console, "* Setting wiper 1 to 2k Ohm.", LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER1_VOL,
                            DIGIPOT5_RES_2KOHM );
    log_write( &console, "* Setting wiper 2 to 2k Ohm.", LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER2_VOL,
                            DIGIPOT5_RES_2KOHM );
    log_write( &console, "* Setting wiper 3 to 2k Ohm.", LOG_FORMAT_LINE );
    digipot5_generic_write( &digipot5, DIGIPOT5_REG_WIPER3_VOL,
                            DIGIPOT5_RES_2KOHM );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_write( &console, "****************************************",
               LOG_FORMAT_LINE );
}
```

### Note

>
> Increment/decrement command can be issued only to volatile wiper locations.
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
