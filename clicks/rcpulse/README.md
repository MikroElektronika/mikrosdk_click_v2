
---
# RC Pulse Click

> [RC Pulse Click](https://www.mikroe.com/?pid_product=MIKROE-7072) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-7072&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : Jul 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the RC Pulse Click board for
generating pulse signals with a specific duration. The application 
continuously changes the wiper position of a digital potentiometer AD5235 
and generates a trigger for the dual retriggerable monostable multivibrator 
TPUL2T122A which generates a pulse signal with a duration determined by 
the set wiper position.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.RCPulse

### Example Key Functions

- `rcpulse_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void rcpulse_cfg_setup ( rcpulse_cfg_t *cfg );
```

- `rcpulse_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t rcpulse_init ( rcpulse_t *ctx, rcpulse_cfg_t *cfg );
```

- `rcpulse_default_cfg` This function executes a default configuration of RC Pulse Click board.
```c
err_t rcpulse_default_cfg ( rcpulse_t *ctx );
```

- `rcpulse_set_wiper` This function sets the wiper position of the selected channel via the SPI serial interface.
```c
err_t rcpulse_set_wiper ( rcpulse_t *ctx, uint8_t channel, uint16_t wiper );
```

- `rcpulse_get_wiper` This function reads the current wiper position of the selected channel via the SPI serial interface.
```c
err_t rcpulse_get_wiper ( rcpulse_t *ctx, uint8_t channel, uint16_t *wiper );
```

- `rcpulse_trigger` This function generates a trigger pulse on the PWM pin.
```c
void rcpulse_trigger ( rcpulse_t *ctx );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    rcpulse_cfg_t rcpulse_cfg;  /**< Click config object. */

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
    rcpulse_cfg_setup( &rcpulse_cfg );
    RCPULSE_MAP_MIKROBUS( rcpulse_cfg, MIKROBUS_POSITION_RCPULSE );
    if ( SPI_MASTER_ERROR == rcpulse_init( &rcpulse, &rcpulse_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( RCPULSE_ERROR == rcpulse_default_cfg ( &rcpulse ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically sweeps the wiper position back and forth across the full scale
range (0 to 1023) in steps of 33. For each step it reads the wiper back,
logs the set and read values, and fires a trigger for generating a pulse 
signal with a duration determined by the set wiper position.

```c
void application_task ( void )
{
    static int16_t wiper_pos = RCPULSE_DEMO_WIPER_MIN;
    static int16_t wiper_step = RCPULSE_DEMO_WIPER_STEP;
    uint16_t wiper_read = 0;

    if ( RCPULSE_OK == rcpulse_set_wiper( &rcpulse, RCPULSE_DEMO_CHANNEL, ( uint16_t ) wiper_pos ) )
    {
        if ( RCPULSE_OK == rcpulse_get_wiper( &rcpulse, RCPULSE_DEMO_CHANNEL, &wiper_read ) )
        {
            log_printf( &logger, " Wiper set: %d | read: %u\r\n", wiper_pos, wiper_read );
            rcpulse_trigger( &rcpulse );
            log_printf( &logger, " Pulse triggered\r\n" );
            log_printf( &logger, " -------------------------------\r\n" );
        }
        else
        {
            log_error( &logger, " Failed to get wiper." );
        }
    }
    else
    {
        log_error( &logger, " Failed to set wiper." );
    }

    wiper_pos += wiper_step;
    if ( ( RCPULSE_WIPER_MAX < wiper_pos ) || ( RCPULSE_DEMO_WIPER_MIN > wiper_pos ) )
    {
        wiper_step = -wiper_step;
        wiper_pos += wiper_step;
        wiper_pos += wiper_step;
    }

    Delay_ms ( 1000 );
}
```

### Note

> At wiper position 0 the external timing resistance drops to about 50 Ohms,
well below the 6.5 kOhm one-shot minimum, which is why the demo starts from step 33.

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
