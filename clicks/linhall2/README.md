
---
# LIN Hall 2 Click

> [LIN Hall 2 Click](https://www.mikroe.com/?pid_product=MIKROE-5932) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5932&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Oct 2023.
- **Type**          : ADC type

# Software Support

## Example Description

> This is an example which demonstrates the use of LIN Hall 2 Click board by measuring 
  magnetic field density and showing it in mT as well as detecting the orientation of the magnet.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LINHall2

### Example Key Functions

- `linhall2_cfg_setup` Config Object Initialization function.
```c
void linhall2_cfg_setup ( linhall2_cfg_t *cfg );
```

- `linhall2_init` Initialization function.
```c
err_t linhall2_init ( linhall2_t *ctx, linhall2_cfg_t *cfg );
```

- `linhall2_read_an_pin_voltage` LIN Hall 2 read AN pin voltage level function.
```c
err_t linhall2_read_an_pin_voltage ( linhall2_t *ctx, float *data_out );
```

- `linhal2_set_en_pin` LIN Hall 2 set EN pin state function.
```c
void linhal2_set_en_pin ( linhall2_t *ctx, uint8_t pin_state );
```

- `linhal2_get_flux_density` LIN Hall 2 read flux density function.
```c
err_t linhal2_get_flux_density ( linhall2_t *ctx, float *data_out );
```

### Application Init

> The initialization of ADC module and log UART.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    linhall2_cfg_t linhall2_cfg;  /**< Click config object. */

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
    linhall2_cfg_setup( &linhall2_cfg );
    LINHALL2_MAP_MIKROBUS( linhall2_cfg, MIKROBUS_1 );
    if ( ADC_ERROR == linhall2_init( &linhall2, &linhall2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    linhal2_set_en_pin( &linhall2, LINHALL2_ENABLE_DEVICE );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application reads the Magnetic field density and showing it in mT 
 as well as the orientation of the magnet.

```c
void application_task ( void ) 
{
    float mag_flux = 0;
    if ( LINHALL2_OK == linhal2_get_flux_density ( &linhall2, &mag_flux ) ) 
    {
        log_printf( &logger, " Magnetic flux density: %.3f[mT]\r\n", mag_flux );
        if ( 0 < mag_flux )
        {
            log_printf( &logger, " Magnetic field oriented South \r\n\n" );
        }
        else
        {
            log_printf( &logger, " Magnetic field oriented North \r\n\n" );
        }
        Delay_ms ( 1000 );
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
