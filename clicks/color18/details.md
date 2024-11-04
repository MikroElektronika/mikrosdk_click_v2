
---
# Color 18 Click

> Color 18 Click is a compact add-on board for accurate ambient light detection and flicker monitoring. This board features the TCS3530, a true color ambient light sensor from ams OSRAM. The TCS3530 features true color XYZ sensing, flicker detection up to 7kHz, and eight concurrent sensing channels with independent gain configurations. It also includes a UV/IR blocking filter for precise light measurements and a unique Click Snap feature, allowing the main sensor area to become movable by breaking the PCB for flexible implementation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/color18_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/color-18-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Color 18 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Color 18 Click driver.

#### Standard key functions :

- `color18_cfg_setup` Config Object Initialization function.
```c
void color18_cfg_setup ( color18_cfg_t *cfg );
```

- `color18_init` Initialization function.
```c
err_t color18_init ( color18_t *ctx, color18_cfg_t *cfg );
```

- `color18_default_cfg` Click Default Configuration function.
```c
err_t color18_default_cfg ( color18_t *ctx );
```

#### Example key functions :

- `color18_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t color18_get_int_pin ( color18_t *ctx );
```

- `color18_read_data` This function checks if the color measurement data are ready for all channels and reads them.
```c
err_t color18_read_data ( color18_t *ctx, color18_data_t *data_out );
```

- `color18_clear_fifo` This function clears the FIFO buffers and interrupts.
```c
err_t color18_clear_fifo ( color18_t *ctx );
```

## Example Description

> This example demonstrates the use of Color 18 Click by reading and displaying the values from all 8 modulator channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    color18_cfg_t color18_cfg;  /**< Click config object. */

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
    color18_cfg_setup( &color18_cfg );
    COLOR18_MAP_MIKROBUS( color18_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == color18_init( &color18, &color18_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( COLOR18_ERROR == color18_default_cfg ( &color18 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for a data ready interrupt then reads data from all 8 modulator channels and displays the results on the USB UART every 200ms approximately.

```c
void application_task ( void )
{
    color18_data_t color_data;

    // Wait for a data ready interrupt
    while ( color18_get_int_pin ( &color18 ) );

    if ( COLOR18_OK == color18_read_data ( &color18, &color_data ) )
    {
        log_printf ( &logger, "X: %u\r\n", color_data.x );
        log_printf ( &logger, "Y: %u\r\n", color_data.y );
        log_printf ( &logger, "Z: %u\r\n", color_data.z );
        log_printf ( &logger, "IR: %u\r\n", color_data.ir );
        log_printf ( &logger, "HgL: %u\r\n", color_data.hgl );
        log_printf ( &logger, "HgH: %u\r\n", color_data.hgh );
        log_printf ( &logger, "Clear: %u\r\n", color_data.clear );
        log_printf ( &logger, "Flicker: %u\r\n\n", color_data.flicker );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Color18

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
