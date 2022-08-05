
---
# Magnetic Rotary 3 click

> Magnetic Rotary 3 Click is a compact add-on board for accurate magnet-position sensing. This board features the AS5147, an SPI-configurable high-resolution rotary position sensor for fast absolute angle measurement over a full 360-degree range from ams AG.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneticrotary3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magnetic-rotary-3-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : May 2022.
- **Type**          : SPI type


# Software Support

We provide a library for the Magnetic Rotary 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Magnetic Rotary 3 Click driver.

#### Standard key functions :

- `magneticrotary3_cfg_setup` Config Object Initialization function.
```c
void magneticrotary3_cfg_setup ( magneticrotary3_cfg_t *cfg );
```

- `magneticrotary3_init` Initialization function.
```c
err_t magneticrotary3_init ( magneticrotary3_t *ctx, magneticrotary3_cfg_t *cfg );
```

#### Example key functions :

- `magneticrotary3_write_register` This function writes a desired data to the selected register by using SPI serial interface.
```c
err_t magneticrotary3_write_register ( magneticrotary3_t *ctx, uint16_t reg, uint16_t data_in );
```

- `magneticrotary3_read_register` This function reads data from the selected register by using SPI serial interface.
```c
err_t magneticrotary3_read_register ( magneticrotary3_t *ctx, uint16_t reg, uint16_t *data_out );
```

- `magneticrotary3_get_angle` This function reads the absolute position raw data and converts it to degrees (Angle).
```c
err_t magneticrotary3_get_angle ( magneticrotary3_t *ctx, float *angle );
```

## Example Description

> This example demonstrates the use of Magnetic Rotary 3 click board by reading and displaying the magnet's angular position in degrees.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and logger.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneticrotary3_cfg_t magneticrotary3_cfg;  /**< Click config object. */

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
    magneticrotary3_cfg_setup( &magneticrotary3_cfg );
    MAGNETICROTARY3_MAP_MIKROBUS( magneticrotary3_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneticrotary3_init( &magneticrotary3, &magneticrotary3_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the magnet's angular position in degrees every 100ms and displays the results on the USB UART.

```c
void application_task ( void )
{
    float angle;
    if ( MAGNETICROTARY3_OK == magneticrotary3_get_angle ( &magneticrotary3, &angle ) )
    {
        log_printf( &logger, " Angle: %.1f degrees\r\n\n", angle );
        Delay_ms ( 100 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MagneticRotary3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
