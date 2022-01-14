
---
# Magnetic Rotary 2 click

> Magnetic Rotary 2 Click is a compact add-on board used for accurate magnet-position sensing. This board features the AEAT-9922, an angular magnetic rotary sensor providing accurate angular measurement over a full 360 degrees of rotation from Broadcom Limited. The AEAT-9922 uses integrated Hall sensor elements with complex analog and digital signal processing within a single device. The absolute angle measurement provides an instant indication of the magnet's angular position with a selectable and one-time programmable resolution from 10 to 18 bits.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneticrotary2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magnetic-rotary-2-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the MagneticRotary2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for MagneticRotary2 Click driver.

#### Standard key functions :

- `magneticrotary2_cfg_setup` Config Object Initialization function.
```c
void magneticrotary2_cfg_setup ( magneticrotary2_cfg_t *cfg );
```

- `magneticrotary2_init` Initialization function.
```c
err_t magneticrotary2_init ( magneticrotary2_t *ctx, magneticrotary2_cfg_t *cfg );
```

- `magneticrotary2_default_cfg` Click Default Configuration function.
```c
err_t magneticrotary2_default_cfg ( magneticrotary2_t *ctx );
```

#### Example key functions :

- `magneticrotary2_write_register` This function writes a data byte to the selected register by using SPI serial interface.
```c
err_t magneticrotary2_write_register ( magneticrotary2_t *ctx, uint8_t reg, uint8_t data_in );
```

- `magneticrotary2_read_register` This function reads a data byte from the selected register by using SPI serial interface.
```c
err_t magneticrotary2_read_register ( magneticrotary2_t *ctx, uint8_t reg, uint8_t *data_out );
```

- `magneticrotary2_get_angle` This function reads the absolute position raw data and converts it to degrees (Angle).
```c
err_t magneticrotary2_get_angle ( magneticrotary2_t *ctx, float *angle );
```

## Example Description

> This example demonstrates the use of Magnetic Rotary 2 click board by reading and displaying the magnet's angular position in degrees.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    magneticrotary2_cfg_t magneticrotary2_cfg;  /**< Click config object. */

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
    magneticrotary2_cfg_setup( &magneticrotary2_cfg );
    MAGNETICROTARY2_MAP_MIKROBUS( magneticrotary2_cfg, MIKROBUS_1 );
    if ( SPI_MASTER_ERROR == magneticrotary2_init( &magneticrotary2, &magneticrotary2_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( MAGNETICROTARY2_ERROR == magneticrotary2_default_cfg ( &magneticrotary2 ) )
    {
        log_error( &logger, " Default configuration." );
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
    float angle = 0;
    
    if ( MAGNETICROTARY2_OK == magneticrotary2_get_angle ( &magneticrotary2, &angle ) )
    {
        log_printf( &logger, " Angle: %.2f degrees\r\n\n", angle );
        Delay_ms ( 100 );
    }
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MagneticRotary2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
