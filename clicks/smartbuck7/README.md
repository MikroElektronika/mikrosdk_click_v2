
---
# Smart Buck 7 Click

> [Smart Buck 7 Click](https://www.mikroe.com/?pid_product=MIKROE-6708) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6708&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Smart Buck 7 Click board. The application cyclically enables 
different combinations of the four buck converter outputs (1.2V, 1.8V, 2.5V, and 3.3V) and logs which 
outputs are currently active. It also monitors the PG (Power Good) pin and logs any fault conditions, 
including undervoltage and over-temperature events.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartBuck7

### Example Key Functions

- `smartbuck7_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void smartbuck7_cfg_setup ( smartbuck7_cfg_t *cfg );
```

- `smartbuck7_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t smartbuck7_init ( smartbuck7_t *ctx, smartbuck7_cfg_t *cfg );
```

- `smartbuck7_default_cfg` This function executes a default configuration of Smart Buck 7 Click board.
```c
err_t smartbuck7_default_cfg ( smartbuck7_t *ctx );
```

- `smartbuck7_get_pg_pin` This function reads the logic level of the PG pin.
```c
uint8_t smartbuck7_get_pg_pin ( smartbuck7_t *ctx );
```

- `smartbuck7_enable_buck` This function enables one or more buck regulators by setting their control bits.
```c
err_t smartbuck7_enable_buck ( smartbuck7_t *ctx, uint8_t buck_sel );
```

- `smartbuck7_disable_buck` This function disables one or more buck regulators by clearing their control bits.
```c
err_t smartbuck7_disable_buck ( smartbuck7_t *ctx, uint8_t buck_sel );
```

### Application Init

> Initializes the logger and the Smart Buck 7 Click driver, and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck7_cfg_t smartbuck7_cfg;  /**< Click config object. */

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
    smartbuck7_cfg_setup( &smartbuck7_cfg );
    SMARTBUCK7_MAP_MIKROBUS( smartbuck7_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == smartbuck7_init( &smartbuck7, &smartbuck7_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTBUCK7_ERROR == smartbuck7_default_cfg ( &smartbuck7 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Cycles through various buck output combinations, logs the enabled outputs, checks the PG pin for fault indication, and logs any detected fault status.

```c
void application_task ( void )
{
    smartbuck7_status_t status;
    static uint8_t buck_en = SMARTBUCK7_BUCK_4;
    if ( smartbuck7_get_pg_pin ( &smartbuck7 ) )
    {
        log_printf( &logger, "\r\n Fault indication detected via PG pin!\r\n" );
        if ( SMARTBUCK7_OK == smartbuck7_read_status ( &smartbuck7, &status ) )
        {
            smartbuck7_display_status ( status );
        }
        smartbuck7_clear_status( &smartbuck7 );
    }
    if ( buck_en > SMARTBUCK7_BUCK_ALL )
    {
        if ( SMARTBUCK7_OK == smartbuck7_disable_buck ( &smartbuck7, SMARTBUCK7_BUCK_ALL ) )
        {
            log_printf( &logger, "\r\n Outputs enabled: - NONE -\r\n" );
            buck_en = SMARTBUCK7_BUCK_4;
        }
    }
    else if ( SMARTBUCK7_OK == smartbuck7_enable_buck ( &smartbuck7, buck_en ) )
    {
        log_printf( &logger, "\r\n Outputs enabled: -" );
        if ( buck_en & SMARTBUCK7_BUCK_3 )
        {
            log_printf( &logger, " 3.3V -" );
        }
        if ( buck_en & SMARTBUCK7_BUCK_1 )
        {
            log_printf( &logger, " 1.2V -" );
        }
        if ( buck_en & SMARTBUCK7_BUCK_2 )
        {
            log_printf( &logger, " 1.8V -" );
        }
        if ( buck_en & SMARTBUCK7_BUCK_4 )
        {
            log_printf( &logger, " 2.5V -" );
        }
        log_printf( &logger, "\r\n" );
        buck_en = ( buck_en << 1 ) | SMARTBUCK7_BUCK_4;
    }
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Note

> Ensure all outputs are properly loaded and that the input voltage is within recommended levels to evaluate fault detection reliably.

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
