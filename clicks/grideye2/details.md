
---
# Grid-EYE 2 Click

> Grid-EYE 2 Click is a compact add-on board designed for thermal imaging and motion detection applications. This board features the AMG883543, an infrared array sensor from Panasonic with a 90° viewing angle and an 8x8 pixel matrix that measures temperatures from 0°C to 80°C with a resolution of 0.25°C. The sensor can detect objects up to 5 meters away and outputs temperature data via a digital interface. The board also supports the Click Snap feature, allowing the main sensor area to be detached for flexible positioning.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grideye2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/grid-eye-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Grid-EYE 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Grid-EYE 2 Click driver.

#### Standard key functions :

- `grideye2_cfg_setup` Config Object Initialization function.
```c
void grideye2_cfg_setup ( grideye2_cfg_t *cfg );
```

- `grideye2_init` Initialization function.
```c
err_t grideye2_init ( grideye2_t *ctx, grideye2_cfg_t *cfg );
```

- `grideye2_default_cfg` Click Default Configuration function.
```c
err_t grideye2_default_cfg ( grideye2_t *ctx );
```

#### Example key functions :

- `grideye2_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t grideye2_get_int_pin ( grideye2_t *ctx );
```

- `grideye2_read_grid` This function reads the temperature measurement of an 8x8 pixels grid and stores it in the ctx->grid_temp array.
```c
err_t grideye2_read_grid ( grideye2_t *ctx );
```

- `grideye2_clear_status` This function clears the interrupt status flags.
```c
err_t grideye2_clear_status ( grideye2_t *ctx );
```

## Example Description

> This example demonstrates the use of Grid-EYE 2 Click by reading and displaying the temperature measurements as an 8x8 pixels grid.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration which enables the data ready interrupt and sets data measurement to 10 frames per second.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    grideye2_cfg_t grideye2_cfg;  /**< Click config object. */

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
    grideye2_cfg_setup( &grideye2_cfg );
    GRIDEYE2_MAP_MIKROBUS( grideye2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == grideye2_init( &grideye2, &grideye2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( GRIDEYE2_ERROR == grideye2_default_cfg ( &grideye2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for a data ready interrupt and then reads the grid temperature measurements and displays the results on the USB UART in a form of an 8x8 pixels grid.

```c
void application_task ( void )
{
    // Wait for data ready interrupt
    while ( grideye2_get_int_pin ( &grideye2 ) );
    
    if ( GRIDEYE2_OK == grideye2_read_grid ( &grideye2 ) )
    {
        grideye2_clear_status ( &grideye2 );
        for ( uint8_t cnt = 0; cnt < GRIDEYE2_NUM_PIXELS; cnt++ )
        {
            if ( 0 == ( cnt % 8 ) )
            {
                log_printf( &logger, "\r\n" );
            }
            log_printf( &logger, "%.2f ", grideye2.grid_temp[ cnt ] );
        }
        log_printf( &logger, "\r\n" );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GridEYE2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
