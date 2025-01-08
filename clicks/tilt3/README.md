
---
# Tilt 3 Click

> [Tilt 3 Click](https://www.mikroe.com/?pid_product=MIKROE-4779) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4779&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2021.
- **Type**          : GPIO type

# Software Support

## Example Description

> This example demonstrates the use of Tilt 3 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Tilt3

### Example Key Functions

- `tilt3_cfg_setup` Config Object Initialization function.
```c
void tilt3_cfg_setup ( tilt3_cfg_t *cfg );
```

- `tilt3_init` Initialization function.
```c
err_t tilt3_init ( tilt3_t *ctx, tilt3_cfg_t *cfg );
```

- `tilt3_enable_switch` This function enables the tilt switch by setting the EN pin to the high logic state.
```c
void tilt3_enable_switch ( tilt3_t *ctx );
```

- `tilt3_disable_switch` This function disables the tilt switch by setting the EN pin to the low logic state.
```c
void tilt3_disable_switch ( tilt3_t *ctx );
```

- `tilt3_get_switch_state` This function returns the INT pin logic state which indicates the tilt switch state. 
```c
uint8_t tilt3_get_switch_state ( tilt3_t *ctx );
```

### Application Init

> Initializes the driver and enables the tilt switch.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;      /**< Logger config object. */
    tilt3_cfg_t tilt3_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    tilt3_cfg_setup( &tilt3_cfg );
    TILT3_MAP_MIKROBUS( tilt3_cfg, MIKROBUS_1 );
    if ( DIGITAL_OUT_UNSUPPORTED_PIN == tilt3_init( &tilt3, &tilt3_cfg ) ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    tilt3_enable_switch( &tilt3 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> As soon as the tilt switch state changes, it displays a corresponding message on the USB UART.

```c
void application_task ( void )
{
    uint8_t state = tilt3_get_switch_state ( &tilt3 );
    if ( tilt3_switch_state != state )
    {
        tilt3_switch_state = state;
        
        if ( TILT3_SWITCH_ON == tilt3_switch_state )
        {
            log_printf( &logger, " Tilt switch ON!\r\n\n" );
        }
        else
        {
            log_printf( &logger, " Tilt switch OFF!\r\n\n" );
        }
        Delay_ms ( 500 );
    }
}
```

### Note

> Tilt switches OFF at an angle of 60 degrees minimum and switches ON at the horizontal position (up to 10 degrees).
> The tilt LED will turn ON when the tilt switch is OFF. 

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
