
---
# Proximity 22 Click

> [Proximity 22 Click](https://www.mikroe.com/?pid_product=MIKROE-6552) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6552&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Proximity 22 Click board by reading
and displaying proximity, ambient light (ALS), and temperature measurements.
The data is read only when a new measurement is ready, indicated by an interrupt.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity22

### Example Key Functions

- `proximity22_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void proximity22_cfg_setup ( proximity22_cfg_t *cfg );
```

- `proximity22_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t proximity22_init ( proximity22_t *ctx, proximity22_cfg_t *cfg );
```

- `proximity22_default_cfg` This function executes a default configuration of Proximity 22 Click board.
```c
err_t proximity22_default_cfg ( proximity22_t *ctx );
```

- `proximity22_get_int_pin` This function returns the logic state of the INT pin.
```c
uint8_t proximity22_get_int_pin ( proximity22_t *ctx );
```

- `proximity22_read_data` This function reads proximity, temperature, and ALS data if available.
```c
err_t proximity22_read_data ( proximity22_t *ctx, proximity22_data_t *data_out );
```

### Application Init

> Initializes the logger and the Proximity 22 Click driver, then sets the default configuration.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    proximity22_cfg_t proximity22_cfg;  /**< Click config object. */

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
    proximity22_cfg_setup( &proximity22_cfg );
    PROXIMITY22_MAP_MIKROBUS( proximity22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == proximity22_init( &proximity22, &proximity22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PROXIMITY22_ERROR == proximity22_default_cfg ( &proximity22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a data ready interrupt and then reads the proximity, temperature,
and ALS data (red, green, blue, and clear channels), displaying the results via UART
approximately every 200 ms.

```c
void application_task ( void )
{
    proximity22_data_t meas_data;

    // Wait for a data ready interrupt
    while ( proximity22_get_int_pin ( &proximity22 ) );

    if ( PROXIMITY22_OK == proximity22_read_data ( &proximity22, &meas_data ) )
    {
        log_printf ( &logger, " Proximity: %u\r\n", meas_data.proximity );
        log_printf ( &logger, " Temperature: %.1f degC\r\n", meas_data.temperature );
        log_printf ( &logger, " ALS data (RGBC): %u;%u;%u;%u\r\n\n", meas_data.als.red, 
                                                                     meas_data.als.green, 
                                                                     meas_data.als.blue, 
                                                                     meas_data.als.clear );
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
