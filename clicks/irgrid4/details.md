
---
# IR Grid 4 click

> IR Grid 4 Click is a compact add-on board for high-precision, non-contact temperature measurement and thermal imaging. This board is based on the MLX90641, a fully calibrated thermal IR array from Melexis. It captures temperature data across a 16x12 matrix (192 pixels) and accurately measures temperatures from -40°C to +300°C with a typical accuracy of 1°C. The board supports the innovative 'Click Snap' feature, allowing the sensor area to be detached for flexible positioning.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irgrid4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ir-grid-4-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jul 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the IR Grid 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IR Grid 4 Click driver.

#### Standard key functions :

- `irgrid4_cfg_setup` Config Object Initialization function.
```c
void irgrid4_cfg_setup ( irgrid4_cfg_t *cfg );
```

- `irgrid4_init` Initialization function.
```c
err_t irgrid4_init ( irgrid4_t *ctx, irgrid4_cfg_t *cfg );
```

- `irgrid4_default_cfg` Click Default Configuration function.
```c
err_t irgrid4_default_cfg ( irgrid4_t *ctx );
```

#### Example key functions :

- `irgrid4_get_measurement` This function reads the RAM frame data and calculates ambient temperature and a 16x12 IR grid object temperature.
```c
err_t irgrid4_get_measurement ( irgrid4_t *ctx, float *t_amb, float *t_obj );
```

- `irgrid4_set_refresh_rate` This function sets the IR data refresh rate.
```c
err_t irgrid4_set_refresh_rate ( irgrid4_t *ctx, uint8_t refresh_rate );
```

- `irgrid4_enable_led1` This function enables the LED1.
```c
void irgrid4_enable_led1 ( irgrid4_t *ctx );
```

## Example Description

> This example demonstrates the use of IR Grid 4 click by reading and displaying
the ambient and object temperature measurements in a 16x12 pixels grid format.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irgrid4_cfg_t irgrid4_cfg;  /**< Click config object. */

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
    irgrid4_cfg_setup( &irgrid4_cfg );
    IRGRID4_MAP_MIKROBUS( irgrid4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == irgrid4_init( &irgrid4, &irgrid4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( IRGRID4_ERROR == irgrid4_default_cfg ( &irgrid4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the ambient and object temperature measurements every 500ms and displays the results on the USB UART in a form of a 16x12 pixels grid.

```c
void application_task ( void )
{
    float image[ 192 ] = { 0 };
    float ambient_temp = 0;
    if ( IRGRID4_OK == irgrid4_get_measurement ( &irgrid4, &ambient_temp, image ) )
    {
        log_printf( &logger, " Ambient temperature: %.2f degC\r\n", ambient_temp );
        log_printf( &logger, "--- Object temperature image ---\r\n" );
        for ( uint8_t pixel_cnt = 0; pixel_cnt < 192; pixel_cnt++ ) 
        {
            log_printf( &logger, "%.2f", image[ pixel_cnt ] );
            if ( 15 == ( pixel_cnt % 16 ) ) 
            {
                log_printf( &logger, "\r\n" );
            }
            else 
            {
                log_printf( &logger, " | " );
            }
        }
        log_printf( &logger, "--------------------------------\r\n" );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IRGrid4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
