
---
# Light 3 Click

> Light 3 Click is a compact add-on board for precise ambient light measurement in automotive applications. This board features the OPT4003-Q1, an automotive-grade digital ambient light sensor from Texas Instruments. This digital ambient light sensor excels in detecting both visible and near-infrared light with high accuracy, thanks to its dual-channel functionality and filters that mimic the human eye's response while efficiently segregating NIR light.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/light3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/light-3-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jan 2024.
- **Type**          : I2C type


# Software Support

We provide a library for the Light 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Light 3 Click driver.

#### Standard key functions :

- `light3_cfg_setup` Config Object Initialization function.
```c
void light3_cfg_setup ( light3_cfg_t *cfg );
```

- `light3_init` Initialization function.
```c
err_t light3_init ( light3_t *ctx, light3_cfg_t *cfg );
```

- `light3_default_cfg` Click Default Configuration function.
```c
err_t light3_default_cfg ( light3_t *ctx );
```

#### Example key functions :

- `light3_sw_reset` This function is used to perform software reset.
```c
err_t light3_sw_reset ( light3_t *ctx );
```

- `light3_write_reg` This function writes a desired data into the selected register by using I2C serial interface.
```c
err_t light3_write_reg ( light3_t *ctx, uint8_t reg, uint16_t data_in );
```

- `light3_get_ch0_data` This function reads ambient light data from the Channel 0 and performs the calculatios from raw data to Lux.
```c
err_t light3_get_ch0_data ( light3_t *ctx, float *lux );
```

## Example Description

> This example demonstrates the use of Light 3 Click board by measuring the ambient light level in Lux.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    light3_cfg_t light3_cfg;  /**< Click config object. */

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
    light3_cfg_setup( &light3_cfg );
    LIGHT3_MAP_MIKROBUS( light3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == light3_init( &light3, &light3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHT3_ERROR == light3_default_cfg ( &light3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reading channel 0 ambient light level in lux as soon as it is available ( once in 1.6 seconds ) and displaying it on the UART terminal.

```c
void application_task ( void ) 
{
    float lux_data = 0;
    if ( LIGHT3_PIN_STATE_LOW == light3_get_int_pin( &light3 ) )
    { 
        light3_get_ch0_data( &light3, &lux_data );
        log_printf( &logger, "Light level: %f lux \r\n", ( float ) lux_data );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Light3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
