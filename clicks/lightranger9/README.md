\mainpage Main Page

---
# LightRanger 9 click

> LightRanger 9 Click is a compact add-on board suitable for range-finding and distance sensing applications. This board features the TMF8828, a dToF (direct time of flight) optical distance sensor with an integrated Vertical Cavity Surface Emitting Laser (VCSEL) achieving up to 5m target detection distance from ams AG. Due to its lens on the SPAD, it supports 3x3, 4x4, 3x6, and 8x8 multizone output data and a wide, dynamically adjustable field of view. All raw data processing is performed inside the TMF8828, providing distance information and confidence values through its I2C interface. A unique addition to this Click board™ represents an additional 0.7mm thick protective lens that further reduces interference and improves the sensor's accuracy.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lightranger9_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lightranger-9-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2022.
- **Type**          : I2C type


# Software Support

We provide a library for the LightRanger 9 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LightRanger 9 Click driver.

#### Standard key functions :

- `lightranger9_cfg_setup` Config Object Initialization function.
```c
void lightranger9_cfg_setup ( lightranger9_cfg_t *cfg );
```

- `lightranger9_init` Initialization function.
```c
err_t lightranger9_init ( lightranger9_t *ctx, lightranger9_cfg_t *cfg );
```

- `lightranger9_default_cfg` Click Default Configuration function.
```c
err_t lightranger9_default_cfg ( lightranger9_t *ctx );
```

#### Example key functions :

- `lightranger9_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t lightranger9_get_int_pin ( lightranger9_t *ctx );
```

- `lightranger9_clear_interrupts` This function reads and clears the interrupt status register.
```c
err_t lightranger9_clear_interrupts ( lightranger9_t *ctx );
```

- `lightranger9_get_capture` This function reads and parses a single sub-capture block of 132 bytes.
```c
err_t lightranger9_get_capture ( lightranger9_t *ctx, lightranger9_capture_t *capture );
```

## Example Description

> This example demonstrates the use of LightRanger 9 click board by reading and displaying all four sub-captures data measurements on the USB UART.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lightranger9_cfg_t lightranger9_cfg;  /**< Click config object. */

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
    lightranger9_cfg_setup( &lightranger9_cfg );
    LIGHTRANGER9_MAP_MIKROBUS( lightranger9_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == lightranger9_init( &lightranger9, &lightranger9_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHTRANGER9_ERROR == lightranger9_default_cfg ( &lightranger9 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads all four sub-captures data approximately every 500ms and logs them to the USB UART
in a form of two object 8x8 maps. Other data such as DIE temperature, ambient light, system tick, etc., are also being displayed.

```c
void application_task ( void )
{
    while ( lightranger9_get_int_pin ( &lightranger9 ) );

    lightranger9_capture_t capture;
    if ( ( LIGHTRANGER9_OK == lightranger9_clear_interrupts ( &lightranger9 ) ) && 
         ( LIGHTRANGER9_OK == lightranger9_get_capture ( &lightranger9, &capture ) ) )
    {
        lightranger9_log_results ( capture );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger9

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
