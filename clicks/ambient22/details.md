
---
# Ambient 22 Click

> Ambient 22 Click is a compact add-on board that measures the intensity of visible light. This board features the OPT3005, a single-chip lux meter from Texas Instruments that transforms light intensity to a digital signal output that can be directly communicated via an I2C interface. The sensor's spectral response tightly matches the human eye's photopic response along with extreme rejection to 850nm and 940nm infrared light over a wide angle of incidence. Measurements can be made from 20mlux up to 166klux without manually selecting full-scale ranges using the built-in, full-scale setting feature.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient22_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ambient-22-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Feb 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient 22 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Ambient 22 Click driver.

#### Standard key functions :

- `ambient22_cfg_setup` Config Object Initialization function.
```c
void ambient22_cfg_setup ( ambient22_cfg_t *cfg );
```

- `ambient22_init` Initialization function.
```c
err_t ambient22_init ( ambient22_t *ctx, ambient22_cfg_t *cfg );
```

- `ambient22_default_cfg` Click Default Configuration function.
```c
err_t ambient22_default_cfg ( ambient22_t *ctx );
```

#### Example key functions :

- `ambient22_get_int_pin` This function returns the INT pin logic state.
```c
uint8_t ambient22_get_int_pin ( ambient22_t *ctx );
```

- `ambient22_read_lux` This function checks for a conversion ready flag bit and then reads the ambient light level in lux.
```c
err_t ambient22_read_lux ( ambient22_t *ctx, float *lux );
```

- `ambient22_write_register` This function writes a desired data to the selected register by using I2C serial interface.
```c
err_t ambient22_write_register ( ambient22_t *ctx, uint8_t reg, uint16_t data_in );
```

## Example Description

> This example demonstrates the use of Ambient 22 Click board by measuring the ambient light level in lux.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    ambient22_cfg_t ambient22_cfg;  /**< Click config object. */

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
    ambient22_cfg_setup( &ambient22_cfg );
    AMBIENT22_MAP_MIKROBUS( ambient22_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == ambient22_init( &ambient22, &ambient22_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( AMBIENT22_ERROR == ambient22_default_cfg ( &ambient22 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Waits for the data ready interrupt, then reads the ambient light level in lux and displays the results on the USB UART. By default, the data ready interrupt triggers every 800ms.

```c
void application_task ( void )
{
    float lux;
    // Wait for a data ready interrupt
    while ( ambient22_get_int_pin ( &ambient22 ) );
    
    if ( AMBIENT22_OK == ambient22_read_lux ( &ambient22, &lux ) )
    {
        log_printf( &logger, " Ambient light: %.2f lux\r\n\n", lux );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient22

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
