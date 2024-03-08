
---
# Buck 15 click

> Buck 15 Click is a compact add-on board for precision voltage regulation across various applications. This board features the TPS62903, a synchronous step-down DC/DC converter from Texas Instruments. It is known for its adaptability, rapid transient response, and high output voltage accuracy of ±1.5% across all operating temperatures. Featuring the innovative DCS-control topology, it supports a wide input voltage range of 3V to 17V, an adjustable output voltage from 0.4V to 5V, and currents up to 3A. This Click board™ can be used in a variety of automotive applications, such as the ADAS, body electronics and lighting, infotainment and cluster, hybrid, electric, and powertrain systems, any application with a 12V input voltage or a 1-4 cell lithium battery pack, and more.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/buck15_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/buck-15-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Buck 15 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Buck 15 Click driver.

#### Standard key functions :

- `buck15_cfg_setup` Config Object Initialization function.
```c
void buck15_cfg_setup ( buck15_cfg_t *cfg );
```

- `buck15_init` Initialization function.
```c
err_t buck15_init ( buck15_t *ctx, buck15_cfg_t *cfg );
```

- `buck15_default_cfg` Click Default Configuration function.
```c
err_t buck15_default_cfg ( buck15_t *ctx );
```

#### Example key functions :

- `buck15_set_vout` This function sets the voltage output by using an I2C serial interface.
```c
err_t buck15_set_vout ( buck15_t *ctx, buck15_vout_t vout );
```

- `buck15_set_vset` This function sets the wiper position for the output voltage settings by using an I2C serial interface.
```c
err_t buck15_set_vset ( buck15_t *ctx, uint8_t vset_wp );
```

- `buck15_enable_device` This function enables the device by setting the EN pin to high logic state.
```c
void buck15_enable_device ( buck15_t *ctx );
```

## Example Description

> This example demonstrates the use of the Buck 15 Click board by changing the output voltage.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the device default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    buck15_cfg_t buck15_cfg;  /**< Click config object. */

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
    buck15_cfg_setup( &buck15_cfg );
    BUCK15_MAP_MIKROBUS( buck15_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == buck15_init( &buck15, &buck15_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( BUCK15_ERROR == buck15_default_cfg ( &buck15 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    log_printf( &logger, "____________\r\n" );
    Delay_ms( 100 );
}
```

### Application Task

> The demo application changes the output voltage and displays the currently set voltage output value.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    for ( buck15_vout_t vout = BUCK15_VOUT_0V6; vout <= BUCK15_VOUT_5V; vout++ )
    {
        if ( BUCK15_OK == buck15_set_vout( &buck15, vout ) )
        {
            log_printf( &logger, " Vout : %.1f [V]\r\n", vout_table[ vout ] );
            log_printf( &logger, "____________\r\n" );
            Delay_ms( 5000 );
        }
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Buck15

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
