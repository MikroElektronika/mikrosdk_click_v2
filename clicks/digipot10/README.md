
---
# DIGI POT 10 Click

> [DIGI POT 10 Click](https://www.mikroe.com/?pid_product=MIKROE-6797) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6797&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Sep 2025.
- **Type**          : I2C/SPI type

# Software Support

## Example Description

> This example demonstrates the use of the DIGI POT 10 Click board.
The application gradually changes the wiper positions of both potentiometers
in opposite directions and logs their values.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT10

### Example Key Functions

- `digipot10_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void digipot10_cfg_setup ( digipot10_cfg_t *cfg );
```

- `digipot10_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t digipot10_init ( digipot10_t *ctx, digipot10_cfg_t *cfg );
```

- `digipot10_default_cfg` This function executes a default configuration of DIGI POT 10 Click board.
```c
err_t digipot10_default_cfg ( digipot10_t *ctx );
```

- `digipot10_set_wiper_0` This function sets the value of wiper 0 volatile register.
```c
err_t digipot10_set_wiper_0 ( digipot10_t *ctx, uint16_t wiper );
```

- `digipot10_set_wiper_1` This function sets the value of wiper 1 volatile register.
```c
err_t digipot10_set_wiper_1 ( digipot10_t *ctx, uint16_t wiper );
```

### Application Init

> Initializes the driver, checks communication, and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot10_cfg_t digipot10_cfg;  /**< Click config object. */

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
    digipot10_cfg_setup( &digipot10_cfg );
    DIGIPOT10_MAP_MIKROBUS( digipot10_cfg, MIKROBUS_1 );
    err_t init_flag = digipot10_init( &digipot10, &digipot10_cfg );
    if ( ( I2C_MASTER_ERROR == init_flag ) || ( SPI_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( DIGIPOT10_ERROR == digipot10_default_cfg ( &digipot10 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Alternately increments and decrements the wiper positions of both channels, while logging their values every second.

```c
void application_task ( void )
{
    static int16_t wiper_pos = DIGIPOT10_WIPER_ZERO_SCALE;
    static int16_t wiper_step = 33;

    if ( DIGIPOT10_OK == digipot10_set_wiper_0 ( &digipot10, wiper_pos ) )
    {
        log_printf( &logger, " Wiper 0 position: %u\r\n", wiper_pos );
    }
    if ( DIGIPOT10_OK == digipot10_set_wiper_1 ( &digipot10, ( DIGIPOT10_WIPER_FULL_SCALE - wiper_pos ) ) )
    {
        log_printf( &logger, " Wiper 1 position: %u\r\n\n", ( DIGIPOT10_WIPER_FULL_SCALE - wiper_pos ) );
    }

    wiper_pos += wiper_step;
    if ( ( wiper_pos > DIGIPOT10_WIPER_FULL_SCALE ) || 
         ( wiper_pos < DIGIPOT10_WIPER_ZERO_SCALE ) )
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
