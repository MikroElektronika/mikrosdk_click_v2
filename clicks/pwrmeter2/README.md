
---
# PWR Meter 2 Click

> [PWR Meter 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3169) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3169&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : SPI type

# Software Support

## Example Description

> This app measuring and monitoring voltage up to 24V and current up to 5A.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.PwrMeter2

### Example Key Functions

- `pwrmeter2_cfg_setup` Config Object Initialization function.
```c
void pwrmeter2_cfg_setup ( pwrmeter2_cfg_t *cfg ); 
```

- `pwrmeter2_init` Initialization function.
```c
err_t pwrmeter2_init ( pwrmeter2_t *ctx, pwrmeter2_cfg_t *cfg );
```

- `pwrmeter2_default_cfg` Click Default Configuration function.
```c
err_t pwrmeter2_default_cfg ( pwrmeter2_t *ctx );
```

- `pwrmeter2_get_data` This function gets the calculated voltage( V ), current( A ) and power( W ) data.
```c
err_t pwrmeter2_get_data ( pwrmeter2_t *ctx, float *voltage, float *current, float *power );
```

- `pwrmeter2_write_reg` This function writes 24-bit data to the register.
```c
err_t pwrmeter2_write_reg ( pwrmeter2_t *ctx, uint8_t reg, uint32_t data_in );
```

- `pwrmeter2_read_reg` This function reads the desired number of 24-bit data from the register/registers.
```c
err_t pwrmeter2_read_reg ( pwrmeter2_t *ctx, uint8_t reg, uint32_t *data_out, uint8_t len );
```

### Application Init

> Initializes device.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pwrmeter2_cfg_t pwrmeter2_cfg;  /**< Click config object. */

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
    pwrmeter2_cfg_setup( &pwrmeter2_cfg );
    PWRMETER2_MAP_MIKROBUS( pwrmeter2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == pwrmeter2_init( &pwrmeter2, &pwrmeter2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PWRMETER2_ERROR == pwrmeter2_default_cfg ( &pwrmeter2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Gets calculated voltage, current and power data every 500 milliseconds and shows results on UART.

```c
void application_task ( void )
{
    float voltage = 0;
    float current = 0;
    float power = 0;
    if ( PWRMETER2_OK == pwrmeter2_get_data( &pwrmeter2, &voltage, &current, &power ) )
    {
        log_printf( &logger, " U = %.3f V\r\n", voltage );
        log_printf( &logger, " I = %.3f A\r\n", current );
        log_printf( &logger, " P = %.3f W\r\n\n", power );
        Delay_ms ( 500 );
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
