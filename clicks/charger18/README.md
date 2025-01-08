
---
# Charger 18 Click

> [Charger 18 Click](https://www.mikroe.com/?pid_product=MIKROE-4990) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4990&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Charger 18 Click board by controlling the status of the charger as well as the LDO and BUCK regulators.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger18

### Example Key Functions

- `charger18_cfg_setup` Config Object Initialization function.
```c
void charger18_cfg_setup ( charger18_cfg_t *cfg );
```

- `charger18_init` Initialization function.
```c
err_t charger18_init ( charger18_t *ctx, charger18_cfg_t *cfg );
```

- `charger18_buck_control` This function controls the buck regulator enable state of Charger 18 Click board.
```c
void charger18_buck_control ( charger18_t *ctx, uint8_t state ); 
```

- `charger18_ldo_control` This function controls the low dropout (LDO) regulator enable state of Charger 18 Click board.
```c
void charger18_ldo_control ( charger18_t *ctx, uint8_t state );
```

- `charger18_suspend_control` This function controls the suspend charging mode state of Charger 18 Click board.
```c
void charger18_suspend_control ( charger18_t *ctx, uint8_t state ); 
```

### Application Init

> Initializes the driver and enables the chip with the charger, LDO and BUCK regulators disabled.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    charger18_cfg_t charger18_cfg;  /**< Click config object. */

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
    charger18_cfg_setup( &charger18_cfg );
    CHARGER18_MAP_MIKROBUS( charger18_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == charger18_init( &charger18, &charger18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    charger18_power_control( &charger18, CHARGER18_CONTROL_ENABLE );
    log_printf( &logger, " POWER   : ON\r\n" );
    charger18_suspend_control( &charger18, CHARGER18_CONTROL_ENABLE );
    log_printf( &logger, " CHARGER : OFF\r\n" );
    charger18_buck_control( &charger18, CHARGER18_CONTROL_DISABLE );
    log_printf( &logger, " BUCK    : OFF\r\n" );
    charger18_ldo_control( &charger18, CHARGER18_CONTROL_DISABLE );
    log_printf( &logger, " LDO     : OFF\r\n" );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> This function enables the charger, BUCK and LDO in the span of 25 seconds, and displays the status of each feature on the USB UART.

```c
void application_task ( void )
{
    charger18_suspend_control( &charger18, CHARGER18_CONTROL_DISABLE );
    log_printf( &logger, " CHARGER : ON\r\n" );
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
    charger18_suspend_control( &charger18, CHARGER18_CONTROL_ENABLE );
    log_printf( &logger, " CHARGER : OFF\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    charger18_buck_control( &charger18, CHARGER18_CONTROL_ENABLE );
    log_printf( &logger, " BUCK    : ON\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    charger18_buck_control( &charger18, CHARGER18_CONTROL_DISABLE );
    log_printf( &logger, " BUCK    : OFF\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    charger18_ldo_control( &charger18, CHARGER18_CONTROL_ENABLE );
    log_printf( &logger, " LDO     : ON\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    charger18_ldo_control( &charger18, CHARGER18_CONTROL_DISABLE );
    log_printf( &logger, " LDO     : OFF\r\n\n" );
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
