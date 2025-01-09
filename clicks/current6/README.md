
---
# Current 6 Click

> [Current 6 Click](https://www.mikroe.com/?pid_product=MIKROE-4914) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4914&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2021.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Current 6 Click board by reading the input voltage and current measurements.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Current6

### Example Key Functions

- `current6_cfg_setup` Config Object Initialization function.
```c
void current6_cfg_setup ( current6_cfg_t *cfg );
```

- `current6_init` Initialization function.
```c
err_t current6_init ( current6_t *ctx, current6_cfg_t *cfg );
```

- `current6_default_cfg` Click Default Configuration function.
```c
err_t current6_default_cfg ( current6_t *ctx );
```

- `current6_get_alert_pin` This function returns the alert pin logic state.
```c
uint8_t current6_get_alert_pin ( current6_t *ctx );
```

- `current6_read_data` This function reads the input voltage and current measurement values.
```c
err_t current6_read_data ( current6_t *ctx, float *voltage, float *current );
```

- `current6_get_status` This function reads and clears the status register.
```c
err_t current6_get_status ( current6_t *ctx, uint16_t *status );
```

### Application Init

> Initializes the driver and performs the Click default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    current6_cfg_t current6_cfg;  /**< Click config object. */

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
    current6_cfg_setup( &current6_cfg );
    CURRENT6_MAP_MIKROBUS( current6_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == current6_init( &current6, &current6_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( CURRENT6_ERROR == current6_default_cfg ( &current6 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for the FIFO data interrupt and then reads the measurements of the input voltage and current and displays the results on the USB UART approximately once per second.

```c
void application_task ( void )
{
    if ( current6_get_alert_pin ( &current6 ) )
    {
        uint16_t status;
        if ( CURRENT6_OK == current6_get_status ( &current6, &status ) )
        {
            if ( status & CURRENT6_FIFO_CFG_DATA_OVERFLOW_MASK )
            {
                float voltage, current;
                if ( CURRENT6_OK == current6_read_data ( &current6, &voltage, &current ) )
                {
                    log_printf( &logger, " Voltage: %.3f V\r\n Current: %.3f A\r\n\n", voltage, current );
                }
            }
        }
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
