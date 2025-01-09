
---
# DIGI POT 8 Click

> [DIGI POT 8 Click](https://www.mikroe.com/?pid_product=MIKROE-4596) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4596&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of DIGI POT 8 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT8

### Example Key Functions

- `digipot8_cfg_setup` Config Object Initialization function.
```c
void digipot8_cfg_setup ( digipot8_cfg_t *cfg );
```

- `digipot8_init` Initialization function.
```c
err_t digipot8_init ( digipot8_t *ctx, digipot8_cfg_t *cfg );
```

- `digipot8_write_data` DIGI POT 8 write data function.
```c
err_t digipot8_write_data ( digipot8_t *ctx, uint8_t reg, uint8_t data_in )
```

- `digipot8_set_wiper_1` DIGI POT 8 set wiper 2 function.
```c
err_t digipot8_set_wiper_1 ( digipot8_t *ctx, uint8_t data_in );
```

- `digipot8_set_wiper_2` DIGI POT 8 set wiper 3 function.
```c
err_t digipot8_set_wiper_2 ( digipot8_t *ctx, uint8_t data_in );
```

### Application Init

> Initializes the driver and makes an initial log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot8_cfg_t digipot8_cfg;  /**< Click config object. */

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

    digipot8_cfg_setup( &digipot8_cfg );
    DIGIPOT8_MAP_MIKROBUS( digipot8_cfg, MIKROBUS_1 );
    err_t init_flag  = digipot8_init( &digipot8, &digipot8_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}
```

### Application Task

> Iterates through the entire wiper range and sets all wipers to 
> the iterator value each second. 
> The current wiper position will be displayed on USB UART.

```c
void application_task ( void )
{
    for ( uint8_t cnt = DIGIPOT8_WIPER_POSITION_MIN; cnt < DIGIPOT8_WIPER_POSITION_MAX; cnt += 5 )
    {
        digipot8_set_wiper_1 ( &digipot8, cnt );
        digipot8_set_wiper_2 ( &digipot8, cnt );
        digipot8_set_wiper_3 ( &digipot8, cnt );
        digipot8_set_wiper_4 ( &digipot8, cnt );
        digipot8_set_wiper_5 ( &digipot8, cnt );
        digipot8_set_wiper_6 ( &digipot8, cnt );
        log_printf( &logger, " * All wipers position set to %d *\r\n", ( uint16_t ) cnt );
        
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
