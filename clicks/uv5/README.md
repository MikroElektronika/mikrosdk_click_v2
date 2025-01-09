
---
# UV 5 Click

> [UV 5 Click](https://www.mikroe.com/?pid_product=MIKROE-5535) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-5535&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : I2C type

# Software Support

## Example Description

> This example demonstrates the use of UV 5 Click board by measuring 
  the light irradiance of the UVA, UVB and UVC.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.UV5

### Example Key Functions

- `uv5_cfg_setup` Config Object Initialization function.
```c
void uv5_cfg_setup ( uv5_cfg_t *cfg );
```

- `uv5_init` Initialization function.
```c
err_t uv5_init ( uv5_t *ctx, uv5_cfg_t *cfg );
```

- `uv5_default_cfg` Click Default Configuration function.
```c
err_t uv5_default_cfg ( uv5_t *ctx );
```

- `uv5_get_rdy_pin` UV 5 get READY pin state function.
```c
uint8_t uv5_get_rdy_pin ( uv5_t *ctx );
```

- `uv5_sw_reset` UV 5 software reset function.
```c
err_t uv5_sw_reset ( uv5_t *ctx );
```

- `uv5_channel_uva_read` UV 5 read raw UVA data function.
```c
err_t uv5_channel_uva_read ( uv5_t *ctx, uint16_t *uva_data );
```

### Application Init

> Initializes the driver, and performs the Click default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    uv5_cfg_t uv5_cfg;  /**< Click config object. */

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
    uv5_cfg_setup( &uv5_cfg );
    UV5_MAP_MIKROBUS( uv5_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == uv5_init( &uv5, &uv5_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( UV5_ERROR == uv5_default_cfg ( &uv5 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Measuring light irradiance level by reading data from the UV 5 Click board 
  approximately every 4 seconds and displaying it using UART Serial terminal.

```c
void application_task ( void ) 
{
    float temp_data; 
    uint16_t uv_raw_data; 
    float uv_data; 
    
    if ( uv5_get_rdy_pin( &uv5 ) == 1 )
    {
        uv5_temperature_read( &uv5, &temp_data );
        log_printf( &logger, " Temp: %.2f degC\r\n", temp_data );

        uv5_channel_uva_read( &uv5, &uv_raw_data );
        uv_data = ( float ) ( ( FSRE_UVA / OUTCONV ) * uv_raw_data );
        log_printf( &logger, " UVA: %.2f uW/cm2 \r\n", uv_data );
        
        uv5_channel_uvb_read( &uv5, &uv_raw_data );
        uv_data = ( float ) ( ( FSRE_UVB / OUTCONV ) * uv_raw_data );
        log_printf( &logger, " UVB: %.2f uW/cm2 \r\n", uv_data );
        
        uv5_channel_uvc_read( &uv5, &uv_raw_data );
        uv_data = ( float ) ( ( FSRE_UVC / OUTCONV ) * uv_raw_data );
        log_printf( &logger, " UVC: %.2f uW/cm2 \r\n", uv_data );
        log_printf( &logger, " =================== \r\n" );
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
