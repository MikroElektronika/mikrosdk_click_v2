
---
# DIGI POT 15 Click

> [DIGI POT 15 Click](https://www.mikroe.com/?pid_product=MIKROE-6940) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6940&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2026.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of the DIGI POT 15 Click board for
controlling the digital potentiometer wiper position. The application
continuously changes the wiper value across its range to simulate
variable resistance.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT15

### Example Key Functions

- `digipot15_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void digipot15_cfg_setup ( digipot15_cfg_t *cfg );
```

- `digipot15_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t digipot15_init ( digipot15_t *ctx, digipot15_cfg_t *cfg );
```

- `digipot15_default_cfg` This function executes a default configuration of DIGI POT 15 Click board.
```c
err_t digipot15_default_cfg ( digipot15_t *ctx );
```

- `digipot15_set_wiper` This function sets the value of wiper volatile register.
```c
err_t digipot15_set_wiper ( digipot15_t *ctx, uint16_t wiper );
```

### Application Init

> Initializes the logger and DIGI POT 15 Click driver, and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot15_cfg_t digipot15_cfg;  /**< Click config object. */

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
    digipot15_cfg_setup( &digipot15_cfg );
    DIGIPOT15_MAP_MIKROBUS( digipot15_cfg, MIKROBUS_POSITION_DIGIPOT15 );
    err_t init_flag = digipot15_init( &digipot15, &digipot15_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIPOT15_ERROR == digipot15_default_cfg ( &digipot15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically updates the wiper position in steps across the full scale range and logs the current value to the serial terminal.

```c
void application_task ( void )
{
    static int16_t wiper_pos = DIGIPOT15_WIPER_ZERO_SCALE;
    static int16_t wiper_step = 33;

    if ( DIGIPOT15_OK == digipot15_set_wiper ( &digipot15, wiper_pos ) )
    {
        log_printf( &logger, " Wiper position: %u\r\n", wiper_pos );
    }

    wiper_pos += wiper_step;
    if ( ( wiper_pos > DIGIPOT15_WIPER_FULL_SCALE ) || 
         ( wiper_pos < DIGIPOT15_WIPER_ZERO_SCALE ) )
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
