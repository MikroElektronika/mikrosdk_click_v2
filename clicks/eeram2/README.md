
---
# EERAM 2 Click

> [EERAM 2 Click](https://www.mikroe.com/?pid_product=MIKROE-4129) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4129&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates the use of EERAM 2 Click board. 

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Eeram2

### Example Key Functions

- `eeram2_cfg_setup` Config Object Initialization function. 
```c
void eeram2_cfg_setup ( eeram2_cfg_t *cfg );
``` 
 
- `eeram2_init` Initialization function. 
```c
err_t eeram2_init ( eeram2_t *ctx, eeram2_cfg_t *cfg );
```

- `eeram2_set_on_hold_status` Set On-hold status function. 
```c
void eeram2_set_on_hold_status ( eeram2_t *ctx, uint8_t en_hold );
```
 
- `eeram2_set_command` Set command function. 
```c
void eeram2_set_command ( eeram2_t *ctx, uint8_t command );
```

- `eeram2_set_write_status` Set write status function. 
```c
void eeram2_set_write_status ( eeram2_t *ctx, uint8_t en_write );
```

### Application Init

> Initialization driver enables - SPI. 

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    eeram2_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    eeram2_cfg_setup( &cfg );
    EERAM2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    eeram2_init( &eeram2, &cfg );

    eeram2_set_on_hold_status( &eeram2, EERAM2_HOLD_DISABLE );
    Delay_ms ( 100 );

    eeram2_set_write_status( &eeram2, EERAM2_WRITE_ENABLE );
    Delay_ms ( 100 );
}
```

### Application Task

> Writes a desired number of bytes to the memory and then verifies if it is written correctly
> by reading from the same memory location and displaying its content on the USB UART.

```c
void application_task ( void )
{
    check_status = eeram2_write_continuous( &eeram2, 0x00543210, &demo_data[ 0 ], 9 );

    if ( check_status == EERAM2_ERROR )
    {
        log_printf( &logger, "   ERROR Writing    \r\n" );
        log_printf( &logger, "--------------------\r\n" );
        for ( ; ; );
    }

    log_printf( &logger, "     Writing...     \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 100 );

    check_status = eeram2_read_continuous( &eeram2, 0x00543210, &read_data[ 0 ], 9 );

    if ( check_status == EERAM2_ERROR )
    {
        log_printf( &logger, "   Reading ERROR    \r\n" );
        log_printf( &logger, "--------------------\r\n" );
        for ( ; ; );
    }

    log_printf( &logger, " Read data : %s", read_data );
    log_printf( &logger, "--------------------\r\n" );
    
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
