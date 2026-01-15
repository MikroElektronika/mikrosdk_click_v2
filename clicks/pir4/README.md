
---
# PIR 4 Click

> [PIR 4 Click](https://www.mikroe.com/?pid_product=MIKROE-6859) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6859&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Nov 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates how to read motion-detection data from
the PIR 4 Click board using either continuous output mode or
upper/lower counter mode, depending on the configuration.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PIR4

### Example Key Functions

- `pir4_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void pir4_cfg_setup ( pir4_cfg_t *cfg );
```

- `pir4_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t pir4_init ( pir4_t *ctx, pir4_cfg_t *cfg );
```

- `pir4_default_cfg` This function executes a default configuration of PIR 4 Click board.
```c
err_t pir4_default_cfg ( pir4_t *ctx );
```

- `pir4_read_continuous_out` This function reads a continuous output sample when the corresponding status flag and INT pin indicate that new data is available.
```c
err_t pir4_read_continuous_out ( pir4_t *ctx, int16_t *data_out );
```

- `pir4_read_out` This function reads the overcount and status information when the INT pin is asserted and the detection conditions are met.
```c
err_t pir4_read_out ( pir4_t *ctx, uint8_t *oc_up, uint8_t *oc_lo );
```

### Application Init

> Initializes the logger and the PIR 4 Click driver, then applies the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pir4_cfg_t pir4_cfg;  /**< Click config object. */

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
    pir4_cfg_setup( &pir4_cfg );
    PIR4_MAP_MIKROBUS( pir4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pir4_init( &pir4, &pir4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PIR4_ERROR == pir4_default_cfg ( &pir4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads motion-detection data.  
In continuous mode, raw PIR output is logged for plotting.  
In counter mode, upper and lower event counts are displayed.

```c
void application_task ( void )
{
#if ( PIR4_INT_SEL_DEFAULT == PIR4_INT_SEL_CONTINUOUS_OUT )
    int16_t pir_out = 0;
    if ( PIR4_OK == pir4_read_continuous_out ( &pir4, &pir_out ) )
    {
        // Use serial plotter to visualize data
        log_printf ( &logger, "%d\r\n", pir_out );
    }
#else
    uint8_t oc_upper = 0;
    uint8_t oc_lower = 0;
    if ( PIR4_OK == pir4_read_out ( &pir4, &oc_upper, &oc_lower ) )
    {
        log_printf ( &logger, " Motion detected! Upper count: %u, lower count: %u\r\n\n", 
                     ( uint16_t ) oc_upper, ( uint16_t ) oc_lower );
    }
#endif
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
