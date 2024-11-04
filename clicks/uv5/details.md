
---
# UV 5 Click

> UV 5 Click is a compact add-on board that can measure UV radiation. This board features the AS7331, a spectral UVA/B/C sensor from ams. The sensor can measure UVA, UVB, and UVC, which are the main types of UV rays from the UV radiation of the sunlight. It uses ADC with a high dynamic range (16… 24-bit) for measurements from low to high radiation conditions and has a high sensitivity, which makes it usable for fluorescence light conditions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/uv5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/uv-5-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Sep 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the UV 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for UV 5 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example demonstrates the use of UV 5 Click board by measuring 
  the light irradiance of the UVA, UVB and UVC.

**The demo application is composed of two sections :**

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

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.UV5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
