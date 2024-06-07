\mainpage Main Page

---
# Light 2 click

> Light 2 Click is a compact add-on board designed for accurate and flexible light measurement in various environments. This board features the ISL76682, a high-sensitivity, light-to-digital sensor with an I2C interface from Renesas, made specifically for automotive applications. Key features include a photodiode array that closely mimics the human eye's response, an ADC for flicker rejection, and four selectable light measurement ranges via I2C, enhancing both flexibility and accuracy. With a typical power consumption of 55µA in Standard mode and two power-down modes to minimize energy use, the board is efficient and adaptable to different lighting conditions.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/light2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/light-2-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Nov 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Light 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Light 2 Click driver.

#### Standard key functions :

- `light2_cfg_setup` Config Object Initialization function.
```c
void light2_cfg_setup ( light2_cfg_t *cfg );
```

- `light2_init` Initialization function.
```c
err_t light2_init ( light2_t *ctx, light2_cfg_t *cfg );
```

- `light2_default_cfg` Click Default Configuration function.
```c
err_t light2_default_cfg ( light2_t *ctx );
```

#### Example key functions :

- `light2_read_raw_data` This function reads raw data from the ADC of Light 2 click board.
```c
err_t light2_read_raw_data ( light2_t *ctx, uint16_t *data_out );
```

- `light2_get_cal_const` This function is used to get a calculation constant depending on Light 2 click board configuration.
```c
err_t light2_get_cal_const ( light2_t *ctx );
```

- `light2_get_light_data` This function is used to read light data of Light 2 click board configuration.
```c
err_t light2_get_light_data ( light2_t *ctx, float *light_data );
```

## Example Description

> This example demonstrates the use of Light 2 click board by measuring 
  the ambient light level in Lux.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    light2_cfg_t light2_cfg;  /**< Click config object. */

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
    light2_cfg_setup( &light2_cfg );
    LIGHT2_MAP_MIKROBUS( light2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == light2_init( &light2, &light2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( LIGHT2_ERROR == light2_default_cfg ( &light2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the ADC voltage and then calculates the illuminance from it.
  The calculated value of illuminance in lux is being displayed on the USB UART approximately once per second. 

```c
void application_task ( void ) 
{
    float lux_data = 0;

    light2_get_light_data( &light2, &lux_data );
    log_printf( &logger, " LUX data: %.2f LUX \r\n", lux_data );

    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Light2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
