
---
# Expand 8 Click

> [Expand 8 Click](https://www.mikroe.com/?pid_product=MIKROE-4442) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4442&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2021.
- **Type**          : SPI type

# Software Support

## Example Description

> This is an example that demonstrates the use of the Expand 8 Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Expand8

### Example Key Functions

- `expand8_cfg_setup` Config Object Initialization function.
```c
void expand8_cfg_setup ( expand8_cfg_t *cfg );
```

- `expand8_init` Initialization function.
```c
err_t expand8_init ( expand8_t *ctx, expand8_cfg_t *cfg );
```

- `expand8_write_data` Generic write data function.
```c
void expand8_write_data ( expand8_t *ctx, uint8_t addr, uint8_t tx_data );
```

- `expand8_read_data` Generic read data function.
```c
uint8_t expand8_read_data ( expand8_t *ctx, uint8_t addr );
```

- `expand8_set_port` Set port function.
```c
err_t expand8_set_port ( expand8_t *ctx, uint8_t sel_port, uint8_t sel_imped );
```

### Application Init

> Initialization driver enables - SPI, also write log.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    expand8_cfg_t expand8_cfg;  /**< Click config object. */

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

    expand8_cfg_setup( &expand8_cfg );
    EXPAND8_MAP_MIKROBUS( expand8_cfg, MIKROBUS_1 );
    err_t init_flag  = expand8_init( &expand8, &expand8_cfg );
    if ( SPI_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
    select_port = EXPAND8_ADDR_OUT_LVL_PORT_P0;
    Delay_ms ( 100 );
}
```

### Application Task

> This example is working by toggling each of 10 available ports every 1 second.
> Results are being sent to the Uart Terminal where you can track their changes.

```c
void application_task ( void )
{
    expand8_set_port( &expand8, select_port, EXPAND8_SET_LOW_IMPEDANCE );
    
    log_printf( &logger, "     Port P%d - ON\r\n", ( uint16_t ) select_port );
    log_printf( &logger, "- - - - - - - - - - -\r\n" );
    Delay_ms ( 1000 );
    
    expand8_set_port( &expand8, select_port, EXPAND8_SET_HIGH_IMPEDANCE );
    
    log_printf( &logger, "     Port P%d - OFF\r\n", ( uint16_t ) select_port );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms ( 1000 );
    
    select_port++;

    if ( select_port > EXPAND8_ADDR_OUT_LVL_PORT_P9 ) {
        select_port = EXPAND8_ADDR_OUT_LVL_PORT_P0;
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
