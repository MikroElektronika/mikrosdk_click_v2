
---
# Buck 24 Click

> [Buck 24 Click](https://www.mikroe.com/?pid_product=MIKROE-6705) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6705&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : May 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Buck 24 Click board by monitoring the output voltage, 
current, and power via I2C communication. It also checks the Power-Good (PG) status pin to detect 
undervoltage conditions.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck24

### Example Key Functions

- `buck24_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void buck24_cfg_setup ( buck24_cfg_t *cfg );
```

- `buck24_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t buck24_init ( buck24_t *ctx, buck24_cfg_t *cfg );
```

- `buck24_default_cfg` This function executes a default configuration of Buck 24 Click board.
```c
err_t buck24_default_cfg ( buck24_t *ctx );
```

- `buck24_get_pg_pin` This function reads the logic level of the PG (power-good) pin.
```c
uint8_t buck24_get_pg_pin ( buck24_t *ctx );
```

- `buck24_read_data_avg` This function reads multiple samples of measurement data and returns their average values.
```c
err_t buck24_read_data_avg ( buck24_t *ctx, uint16_t num_conv, buck24_data_t *data_out );
```

### Application Init

> Initializes the logger and the Click board driver, and applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck24_cfg_t buck24_cfg;  /**< Click config object. */

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
    buck24_cfg_setup( &buck24_cfg );
    BUCK24_MAP_MIKROBUS( buck24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == buck24_init( &buck24, &buck24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCK24_ERROR == buck24_default_cfg ( &buck24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Checks if the Power-Good (PG) pin is active and logs an undervoltage warning if triggered.
Reads and logs the average voltage, current, and power values from the device every second.

```c
void application_task ( void )
{
    buck24_data_t buck;

    if ( !buck24_get_pg_pin ( &buck24 ) )
    {
        log_printf( &logger, " Undervoltage: below 90%% of nominal voltage\r\n" );
    }

    if ( BUCK24_OK == buck24_read_data_avg ( &buck24, BUCK24_DEFAULT_NUM_CONV, &buck ) )
    {
        log_printf( &logger, " Voltage: %.3f V\r\n", buck.bus_v );
        log_printf( &logger, " Current: %.3f A\r\n", buck.current );
        log_printf( &logger, " Power: %.2f W\r\n\n", buck.power );
    }

    Delay_ms ( 1000 );
}
```

### Note

> Use an on-board VOUT SEL switch to select the buck output voltage level (1.0V, 1.8V, 2.5V, 3.3V).

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
