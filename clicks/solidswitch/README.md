
---
# SolidSwitch Click

> [SolidSwitch Click](https://www.mikroe.com/?pid_product=MIKROE-4569) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4569&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of SolidSwitch Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SolidSwitch

### Example Key Functions

- `solidswitch_cfg_setup` Config Object Initialization function.
```c
void solidswitch_cfg_setup ( solidswitch_cfg_t *cfg );
```

- `solidswitch_init` Initialization function.
```c
err_t solidswitch_init ( solidswitch_t *ctx, solidswitch_cfg_t *cfg );
```

- `solidswitch_default_cfg` Click Default Configuration function.
```c
err_t solidswitch_default_cfg ( solidswitch_t *ctx );
```

- `solidswitch_write_single` SolidSwitch I2C writing logic state function.
```c
err_t solidswitch_write_single ( solidswitch_t *ctx, uint8_t logic_state );
```

- `solidswitch_read_single` SolidSwitch I2C reading logic state function.
```c
err_t solidswitch_read_single ( solidswitch_t *ctx, uint8_t *logic_state );
```

- `solidswitch_reset` SolidSwitch reset function.
```c
void solidswitch_reset ( solidswitch_t *ctx );
```

### Application Init

> Initializes the driver and logger and enables the Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    solidswitch_cfg_t solidswitch_cfg;  /**< Click config object. */

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

    solidswitch_cfg_setup( &solidswitch_cfg );
    SOLIDSWITCH_MAP_MIKROBUS( solidswitch_cfg, MIKROBUS_1 );
    err_t init_flag = solidswitch_init( &solidswitch, &solidswitch_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    solidswitch_default_cfg ( &solidswitch );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Enables different outputs every 3 seconds and displays all enabled outputs on USB UART.

```c
void application_task ( void )
{
    solidswitch_write_single ( &solidswitch, SOLIDSWITCH_ENABLE_OUT0 | SOLIDSWITCH_ENABLE_OUT1 );
    solidswitch_display_enabled_channels( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    solidswitch_write_single ( &solidswitch, SOLIDSWITCH_ENABLE_OUT6 | SOLIDSWITCH_ENABLE_OUT7 );
    solidswitch_display_enabled_channels( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    solidswitch_write_single ( &solidswitch, SOLIDSWITCH_ENABLE_ALL_OUTPUTS );
    solidswitch_display_enabled_channels( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    solidswitch_write_single ( &solidswitch, SOLIDSWITCH_DISABLE_ALL_OUTPUTS );
    solidswitch_display_enabled_channels( );
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
