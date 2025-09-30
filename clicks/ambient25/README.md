
---
# Ambient 25 Click

> [Ambient 25 Click](https://www.mikroe.com/?pid_product=MIKROE-6711) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6711&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of Ambient 25 Click by reading and displaying the values from two modulator channels.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient25

### Example Key Functions

- `ambient25_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void ambient25_cfg_setup ( ambient25_cfg_t *cfg );
```

- `ambient25_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t ambient25_init ( ambient25_t *ctx, ambient25_cfg_t *cfg );
```

- `ambient25_default_cfg` This function executes a default configuration of Ambient 25 Click board.
```c
err_t ambient25_default_cfg ( ambient25_t *ctx );
```

- `ambient25_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t ambient25_get_int_pin ( ambient25_t *ctx );
```

- `ambient25_read_data` This function checks if the als measurement data are ready for all channels and reads them.
```c
err_t ambient25_read_data ( ambient25_t *ctx, ambient25_data_t *data_out );
```

### Application Init

> Initializes the driver and performs the Click default configuration which sets the ALS gain level to 32x and 4x for modulators 0 and 1.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient25_cfg_t ambient25_cfg;  /**< Click config object. */

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
    ambient25_cfg_setup( &ambient25_cfg );
    AMBIENT25_MAP_MIKROBUS( ambient25_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient25_init( &ambient25, &ambient25_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT25_ERROR == ambient25_default_cfg ( &ambient25 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Waits for a data ready interrupt then reads data from two modulator channels and displays the results on the USB UART every 200ms approximately.

```c
void application_task ( void )
{
    ambient25_data_t als_data;

    // Wait for a data ready interrupt
    while ( ambient25_get_int_pin ( &ambient25 ) );

    if ( AMBIENT25_OK == ambient25_read_data ( &ambient25, &als_data ) )
    {
        log_printf ( &logger, "\r\n ALS data 0: " );
        if ( AMBIENT25_ALS_DATA_SATURATION != als_data.als_data_0 )
        {
            log_printf ( &logger, "%u", als_data.als_data_0 );
        }
        else
        {
            log_printf ( &logger, "SATURATION" );
        }
        log_printf ( &logger, "\r\n ALS data 1: " );
        if ( AMBIENT25_ALS_DATA_SATURATION != als_data.als_data_1 )
        {
            log_printf ( &logger, "%u", als_data.als_data_1 );
        }
        else
        {
            log_printf ( &logger, "SATURATION" );
        }
        log_printf ( &logger, "\r\n" );
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
