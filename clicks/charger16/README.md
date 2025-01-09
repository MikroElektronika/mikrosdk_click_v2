
---
# Charger 16 Click

> [Charger 16 Click](https://www.mikroe.com/?pid_product=MIKROE-4768) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4768&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Nenad Filipovic
- **Date**          : Jul 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This library contains API for the Charger 16 Click driver.
> This demo application shows use of a Charger 16 Click board&trade;.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger16

### Example Key Functions

- `charger16_cfg_setup` Config Object Initialization function.
```c
void charger16_cfg_setup ( charger16_cfg_t *cfg );
```

- `charger16_init` Initialization function.
```c
err_t charger16_init ( charger16_t *ctx, charger16_cfg_t *cfg );
```

- `charger16_default_cfg` Click Default Configuration function.
```c
err_t charger16_default_cfg ( charger16_t *ctx );
```

- `charger16_enable_charging` Charger 16 enable charging function.
```c
err_t charger16_enable_charging ( charger16_t *ctx );
```

- `charger16_disable_charging` Charger 16 disable charging function.
```c
err_t charger16_disable_charging ( charger16_t *ctx );
```

### Application Init

> Initialization of GPIO module and log UART.
> After driver initialization the app set default settings.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    charger16_cfg_t charger16_cfg;  /**< Click config object.  */

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

    charger16_cfg_setup( &charger16_cfg );
    CHARGER16_MAP_MIKROBUS( charger16_cfg, MIKROBUS_1 );
    if ( charger16_init( &charger16, &charger16_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    charger16_default_cfg ( &charger16 );
    log_info( &logger, " Application Task " );
    Delay_ms ( 100 );
}
```

### Application Task

> This is an example that shows the use of an Charger 16 Click board&trade;.
> The app turns the battery charge on and off every 10 seconds.
> Results are being sent to the Usart Terminal where you can track their changes.

```c
void application_task ( void ) 
{
    log_printf( &logger, "-----------------\r\n" );
    log_printf( &logger, " Enable charging \r\n" );
    charger16_enable_charging( &charger16 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, " Disable charging \r\n" );
    charger16_disable_charging( &charger16 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
