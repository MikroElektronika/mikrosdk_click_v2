
---
# Hydrogen 2 Click

> [Hydrogen 2 Click](https://www.mikroe.com/?pid_product=MIKROE-6875) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6875&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Dec 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Hydrogen 2 Click board for
measuring hydrogen gas concentration and internal sensor temperature.
Basic device information such as sensor ID, product code, firmware
revision, and manufacturer code is also displayed.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Hydrogen2

### Example Key Functions

- `hydrogen2_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void hydrogen2_cfg_setup ( hydrogen2_cfg_t *cfg );
```

- `hydrogen2_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t hydrogen2_init ( hydrogen2_t *ctx, hydrogen2_cfg_t *cfg );
```

- `hydrogen2_default_cfg` This function executes a default configuration of Hydrogen 2 Click board.
```c
err_t hydrogen2_default_cfg ( hydrogen2_t *ctx );
```

- `hydrogen2_get_conc` This function triggers a hydrogen concentration measurement and reads the response.
```c
err_t hydrogen2_get_conc ( hydrogen2_t *ctx, int16_t *conc );
```

- `hydrogen2_get_temp` This function triggers a temperature measurement and reads the response.
```c
err_t hydrogen2_get_temp ( hydrogen2_t *ctx, int8_t *temp );
```

- `hydrogen2_read_id` This function reads the device identification data.
```c
err_t hydrogen2_read_id ( hydrogen2_t *ctx );
```

### Application Init

> Initializes the logger and Hydrogen 2 Click driver, applies the default
configuration, and reads out device identification information.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    hydrogen2_cfg_t hydrogen2_cfg;  /**< Click config object. */

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
    hydrogen2_cfg_setup( &hydrogen2_cfg );
    HYDROGEN2_MAP_MIKROBUS( hydrogen2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == hydrogen2_init( &hydrogen2, &hydrogen2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( HYDROGEN2_ERROR == hydrogen2_default_cfg ( &hydrogen2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_printf ( &logger, " Sensor ID: 0x%.8LX\r\n", hydrogen2.info.sensor_id );
    log_printf ( &logger, " Product Code: 0x%.4LX\r\n", hydrogen2.info.product_code );
    log_printf ( &logger, " FW Revision Number: 0x%.4LX\r\n", hydrogen2.info.fw_rev_num );
    log_printf ( &logger, " Manufacturer Code: 0x%.2LX\r\n", hydrogen2.info.man_code );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Periodically reads hydrogen concentration data and temperature
values from the sensor and logs them to the serial terminal.

```c
void application_task ( void )
{
    int16_t raw_conc = 0;
    int8_t temp = 0;
    if ( HYDROGEN2_OK == hydrogen2_get_conc ( &hydrogen2, &raw_conc ) )
    {
        log_printf ( &logger, " H2: %.2f %%\r\n", raw_conc * HYDROGEN2_H2_RES );
    }
    if ( HYDROGEN2_OK == hydrogen2_get_temp ( &hydrogen2, &temp ) )
    {
        log_printf ( &logger, " T: %d degC\r\n\n", temp );
    }
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
