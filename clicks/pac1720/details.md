
---
# PAC1720 click

> PAC1720 Click is a compact add-on board that contains an energy monitoring solution. This board features the PAC1720, an I2C configurable dual high-side bidirectional current sensing monitor with precision voltage measurement capabilities from Microchip Technology. The PAC1720 measures the voltage developed across external sense resistors to represent the high-side current of a battery or voltage regulator.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pac1720_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pac1720-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Oct 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the PAC1720 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for PAC1720 Click driver.

#### Standard key functions :

- `pac1720_cfg_setup` Config Object Initialization function.
```c
void pac1720_cfg_setup ( pac1720_cfg_t *cfg );
```

- `pac1720_init` Initialization function.
```c
err_t pac1720_init ( pac1720_t *ctx, pac1720_cfg_t *cfg );
```

- `pac1720_default_cfg` Click Default Configuration function.
```c
err_t pac1720_default_cfg ( pac1720_t *ctx );
```

#### Example key functions :

- `pac1720_set_vsource_config` This function sets the Voltage Source configuration (sample time and average samples) for the selected channel.
```c
err_t pac1720_set_vsource_config ( pac1720_t *ctx, pac1720_ch_sel_t ch, pac1720_sample_time_t stime, pac1720_avg_t avg );
```

- `pac1720_set_vsense_config` This function sets the Voltage Sense configuration (sample time, average samples, and sampling range) for the selected channel.
```c
err_t pac1720_set_vsense_config ( pac1720_t *ctx, pac1720_ch_sel_t ch, pac1720_sample_time_t stime, pac1720_avg_t avg, pac1720_cs_rng_t cs_rng );
```

- `pac1720_get_measurements` This function reads voltage, current, and power from the selected channel.
```c
err_t pac1720_get_measurements ( pac1720_t *ctx, pac1720_ch_sel_t ch, float *voltage, float *current, float *power );
```

## Example Description

> This example demonstrates the use of PAC1720 click board by reading the voltage, current, and power from both available channels.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    pac1720_cfg_t pac1720_cfg;  /**< Click config object. */

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
    pac1720_cfg_setup( &pac1720_cfg );
    PAC1720_MAP_MIKROBUS( pac1720_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == pac1720_init( &pac1720, &pac1720_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( PAC1720_ERROR == pac1720_default_cfg ( &pac1720 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the voltage, current, and power from both channels and displays the results on the USB UART approximately once per second.

```c

void application_task ( void )
{
    float voltage = 0, current = 0, power = 0;
    
    if ( PAC1720_OK == pac1720_get_measurements ( &pac1720, PAC1720_CHANNEL_1, &voltage, &current, &power ) )
    {
        log_printf( &logger, " Channel 1:\r\n" );
        log_printf( &logger, " U: %.3fV, I: %.3fA, P: %.3fW\r\n", voltage, current, power );
    }
    
    if ( PAC1720_OK == pac1720_get_measurements ( &pac1720, PAC1720_CHANNEL_2, &voltage, &current, &power ) )
    {
        log_printf( &logger, " Channel 2:\r\n" );
        log_printf( &logger, " U: %.3fV, I: %.3fA, P: %.3fW\r\n\n", voltage, current, power  );
    }
    
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.PAC1720

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
