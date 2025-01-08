
---
# DIGI POT 9 Click

> [DIGI POT 9 Click](https://www.mikroe.com/?pid_product=MIKROE-4727) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4727&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of DIGI POT 9 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT9

### Example Key Functions

- `digipot9_cfg_setup` Config Object Initialization function.
```c
void digipot9_cfg_setup ( digipot9_cfg_t *cfg );
```

- `digipot9_init` Initialization function.
```c
err_t digipot9_init ( digipot9_t *ctx, digipot9_cfg_t *cfg );
```

- `digipot9_default_cfg` Click Default Configuration function.
```c
void digipot9_default_cfg ( digipot9_t *ctx );
```

- `digipot9_generic_write` This function writes two data bytes to the selected command and address by using SPI serial interface.
```c
err_t digipot9_generic_write ( digipot9_t *ctx, uint8_t command, uint8_t address, uint16_t data_in );
```

- `digipot9_generic_read` This function reads two data bytes from the selected command and address by using SPI serial interface.
```c
err_t digipot9_generic_read ( digipot9_t *ctx, uint8_t command, uint8_t address, uint16_t *data_out );
```

- `digipot9_set_wiper_1` This function sets wiper 1 to desired value.
```c
err_t digipot9_set_wiper_1 ( digipot9_t *ctx, uint16_t data_in );
```

### Application Init

> Initializes the driver and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;            /**< Logger config object. */
    digipot9_cfg_t digipot9_cfg;  /**< Click config object. */

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

    digipot9_cfg_setup( &digipot9_cfg );
    DIGIPOT9_MAP_MIKROBUS( digipot9_cfg, MIKROBUS_1 );
    err_t init_flag  = digipot9_init( &digipot9, &digipot9_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    digipot9_default_cfg ( &digipot9 );
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Iterates through the entire wiper range and sets both wipers to 
> the iterator value once per second. 
> The current wiper position will be displayed on the USB UART.

```c
void application_task ( void )
{
    for ( uint16_t cnt = DIGIPOT9_WIPER_ZERO_SCALE; cnt <= DIGIPOT9_WIPER_FULL_SCALE; cnt += 50 )
    {
        digipot9_set_wiper_1 ( &digipot9, cnt );
        digipot9_set_wiper_2 ( &digipot9, cnt );
        log_printf( &logger, " * Wipers position set to %u *\r\n", cnt );
        
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
