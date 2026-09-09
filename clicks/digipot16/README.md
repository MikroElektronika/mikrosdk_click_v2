
---
# DIGI POT 16 Click

> [DIGI POT 16 Click](https://www.mikroe.com/?pid_product=MIKROE-6979) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6979&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Milan Ivancic
- **Date**          : May 2026.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of the DIGI POT 16 Click board for
controlling the digital potentiometer wiper position. The application
continuously changes the wiper value across its range to simulate
variable resistance.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT16

### Example Key Functions

- `digipot16_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void digipot16_cfg_setup ( digipot16_cfg_t *cfg );
```

- `digipot16_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t digipot16_init ( digipot16_t *ctx, digipot16_cfg_t *cfg );
```

- `digipot16_default_cfg` This function executes a default configuration of DIGI POT 16 Click board.
```c
err_t digipot16_default_cfg ( digipot16_t *ctx );
```

- `digipot16_set_wiper` This function sets the wiper position by sending Command 1 via SPI.
```c
err_t digipot16_set_wiper ( digipot16_t *ctx, uint16_t wiper );
```

- `digipot16_get_wiper` This function reads back the current wiper position from the RDAC register.
```c
err_t digipot16_get_wiper ( digipot16_t *ctx, uint16_t *wiper );
```

- `digipot16_get_resistance` This function calculates the resistance values between the wiper and both terminals (RWB and RWA).
```c
err_t digipot16_get_resistance ( digipot16_t *ctx, uint32_t *rwb_ohm, uint32_t *rwa_ohm );
```

### Application Init

> Initializes the logger and DIGI POT 16 Click driver, and applies the
default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot16_cfg_t digipot16_cfg;  /**< Click config object. */

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
    digipot16_cfg_setup( &digipot16_cfg );
    DIGIPOT16_MAP_MIKROBUS( digipot16_cfg, MIKROBUS_POSITION_DIGIPOT16 );
    if ( SPI_MASTER_ERROR == digipot16_init( &digipot16, &digipot16_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIPOT16_ERROR == digipot16_default_cfg ( &digipot16 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically sweeps the wiper position back and forth across the full scale
range (0 to 1023) in steps of 33. Logs the current wiper position and the
corresponding calculated resistances RWB and RWA to the serial terminal.

```c
void application_task ( void )
{
    static int16_t wiper_pos = DIGIPOT16_WIPER_ZERO_SCALE;
    static int16_t wiper_step = 33;
    uint32_t rwb_ohm = 0;
    uint32_t rwa_ohm = 0;

    if ( DIGIPOT16_OK == digipot16_set_wiper ( &digipot16, ( uint16_t ) wiper_pos ) )
    {
        if ( DIGIPOT16_OK == digipot16_get_resistance ( &digipot16, &rwb_ohm, &rwa_ohm ) )
        {
            log_printf( &logger, " Wiper position: %d\r\n", wiper_pos );
            log_printf( &logger, " RWB: %lu Ohm\r\n", rwb_ohm );
            log_printf( &logger, " RWA: %lu Ohm\r\n", rwa_ohm );
            log_printf( &logger, " -------------------------------\r\n");
        }
        else
        {
            log_error ( &logger, " Failed to get resistance." );
        }
    }
    else
    {
        log_error ( &logger, " Failed to set wiper." );
    }

    wiper_pos += wiper_step;
    if ( ( wiper_pos > DIGIPOT16_WIPER_FULL_SCALE ) ||
         ( wiper_pos < DIGIPOT16_WIPER_ZERO_SCALE ) )
    {
        wiper_step = -wiper_step;
        wiper_pos += wiper_step;
        wiper_pos += wiper_step;
    }

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
