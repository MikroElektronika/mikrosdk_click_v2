
---
# Charger 27 Click

> [Charger 27 Click](https://www.mikroe.com/?pid_product=MIKROE-5960) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5960&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Oct 2023.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of the Charger 27 Click board 
> by enabling charge or discharge mode and 
> indicating valid input supply and charging completion.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger27

### Example Key Functions

- `charger27_cfg_setup` Config Object Initialization function.
```c
void charger27_cfg_setup ( charger27_cfg_t *cfg );
```

- `charger27_init` Initialization function.
```c
err_t charger27_init ( charger27_t *ctx, charger27_cfg_t *cfg );
```

- `charger27_set_mode` This function is used for the charge or discharge mode selection.
```c
err_t charger27_set_mode ( charger27_t *ctx, uint8_t mode );
```

- `charger27_check_chg_completion` This function checks the charging completion indicator state.
```c
uint8_t charger27_check_chg_completion ( charger27_t *ctx );
```

- `charger27_check_input_supply` This function checks valid input supply indicator state.
```c
uint8_t charger27_check_input_supply ( charger27_t *ctx );
```

### Application Init

> Initialization of GPIO module and log UART.
> After driver initialization, the app sets charge mode.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger27_cfg_t charger27_cfg;  /**< Click config object. */

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
    charger27_cfg_setup( &charger27_cfg );
    CHARGER27_MAP_MIKROBUS( charger27_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == charger27_init( &charger27, &charger27_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }

    if ( CHARGER27_OK == charger27_set_mode( &charger27, CHARGER27_MODE_CHARGE ) )
    {
        log_printf( &logger, " > Charge mode <\r\n" );
        Delay_ms ( 100 );
    }
}
```

### Application Task

> The demo application operates as a switching charger to charge a 1S battery 
> from a wide input power range of 5V to 16V, which can cover a USB PD voltage level.
> The app also checks if the charging has been completed or is suspended.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( CHARGER27_CHG_CHARGE == charger27_check_chg_completion( &charger27 ) )
    {
        log_printf( &logger, " Charging.\r\n" );
        Delay_ms ( 1000 );
    }
    else
    {
        log_printf( &logger, " Charging has completed or is suspended.\r\n" );
        Delay_ms ( 1000 );
    }
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
