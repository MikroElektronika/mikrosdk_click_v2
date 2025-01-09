
---
# UVA Click

> [UVA Click](https://www.mikroe.com/?pid_product=MIKROE-4911) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4911&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of UVA Click board by reading and displaying the UVA data measurement results.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UVA

### Example Key Functions

- `uva_cfg_setup` Config Object Initialization function.
```c
void uva_cfg_setup ( uva_cfg_t *cfg );
```

- `uva_init` Initialization function.
```c
err_t uva_init ( uva_t *ctx, uva_cfg_t *cfg );
```

- `uva_default_cfg` Click Default Configuration function.
```c
err_t uva_default_cfg ( uva_t *ctx );
```

- `uva_read_data` This function reads the raw UVA data from registers.
```c
err_t uva_read_data ( uva_t *ctx, uint16_t *uva_data );
```

- `uva_soft_reset` This function executes the soft reset command.
```c
err_t uva_soft_reset ( uva_t *ctx );
```

- `uva_write_register` This function writes a data byte to the selected register by using I2C serial interface.
```c
err_t uva_write_register ( uva_t *ctx, uint8_t reg, uint8_t data_in );
```

### Application Init

> Initializes the driver and applies the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uva_cfg_t uva_cfg;  /**< Click config object. */

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
    uva_cfg_setup( &uva_cfg );
    UVA_MAP_MIKROBUS( uva_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == uva_init( &uva, &uva_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UVA_ERROR == uva_default_cfg ( &uva ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads the UVA data measurements every 100ms and displays the results on the USB UART.

```c
void application_task ( void )
{
    uint16_t uva_data = 0;
    if ( UVA_OK == uva_read_data ( &uva, &uva_data ) )
    {
        log_printf ( &logger, " UVA data: %u \r\n\n", uva_data );
        Delay_ms ( 100 );
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
