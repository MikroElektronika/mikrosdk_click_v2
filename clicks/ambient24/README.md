
---
# Ambient 24 Click

> [Ambient 24 Click](https://www.mikroe.com/?pid_product=MIKROE-6534) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-6534&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Mar 2025.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of the Ambient 24 Click board, which measures 
ambient light and infrared (IR) intensity. The application initializes the device 
and continuously reads ALS and IR data, displaying the results via UART logging.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient24

### Example Key Functions

- `ambient24_cfg_setup` This function initializes Click configuration structure to initial values.
```c
void ambient24_cfg_setup ( ambient24_cfg_t *cfg );
```

- `ambient24_init` This function initializes all necessary pins and peripherals used for this Click board.
```c
err_t ambient24_init ( ambient24_t *ctx, ambient24_cfg_t *cfg );
```

- `ambient24_default_cfg` This function executes a default configuration of Ambient 24 Click board.
```c
err_t ambient24_default_cfg ( ambient24_t *ctx );
```

- `ambient24_get_data` This function reads the raw IR data and ambient light intensity in lux based on raw ALS data.
```c
err_t ambient24_get_data ( ambient24_t *ctx, float *als_data, uint16_t *ir_data );
```

### Application Init

> Initializes the logger and configures the Ambient 24 Click board. It establishes 
I2C communication and applies the default configuration settings.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient24_cfg_t ambient24_cfg;  /**< Click config object. */

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
    ambient24_cfg_setup( &ambient24_cfg );
    AMBIENT24_MAP_MIKROBUS( ambient24_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient24_init( &ambient24, &ambient24_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT24_ERROR == ambient24_default_cfg ( &ambient24 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Continuously reads ambient light and infrared sensor data and logs the results 
in lux and raw IR values, respectively. The readings are updated every 200ms.

```c
void application_task ( void )
{
    float als_data = 0;
    uint16_t ir_data = 0;
    if ( AMBIENT24_OK == ambient24_get_data ( &ambient24, &als_data, &ir_data ) )
    {
        log_printf ( &logger, " ALS Data: %.1f lux\r\n", als_data );
        log_printf ( &logger, " IR Data: %u\r\n\n", ir_data );
        Delay_ms ( 200 );
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
