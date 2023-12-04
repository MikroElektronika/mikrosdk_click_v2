
---
# Smart Buck 2 click

> Smart Buck 2 Click is a compact add-on board that contains a high-frequency synchronous step-down DC-DC converter. This board features the TPS62363, a 3A processor supply with remote sense from Texas Instruments. The converter is optimized for battery-powered portable applications for a small solution size. It has an input range of 2.5V to 5.5V, which is common for battery technologies. The converter provides up to 3A peak load current operating at 2.5MHz typical switching frequency.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/smartbuck2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/smart-buck-2-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Aug 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Smart Buck 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Smart Buck 2 Click driver.

#### Standard key functions :

- `smartbuck2_cfg_setup` Config Object Initialization function.
```c
void smartbuck2_cfg_setup ( smartbuck2_cfg_t *cfg );
```

- `smartbuck2_init` Initialization function.
```c
err_t smartbuck2_init ( smartbuck2_t *ctx, smartbuck2_cfg_t *cfg );
```

- `smartbuck2_default_cfg` Click Default Configuration function.
```c
err_t smartbuck2_default_cfg ( smartbuck2_t *ctx );
```

#### Example key functions :

- `smartbuck2_set_voltage` Smart Buck 2 set voltage function.
```c
err_t smartbuck2_set_voltage ( smartbuck2_t *ctx, uint16_t vout_mv );
```

- `smartbuck2_get_voltage` Smart Buck 2 get voltage function.
```c
err_t smartbuck2_get_voltage ( smartbuck2_t *ctx, uint16_t *vout_mv );
```

## Example Description

> This library contains API for the Smart Buck 2 Click board™.
> This driver provides functions for device configurations 
> and for the sets and reads the output voltage.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After driver initialization, the app executes a default configuration.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck2_cfg_t smartbuck2_cfg;  /**< Click config object. */

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
    smartbuck2_cfg_setup( &smartbuck2_cfg );
    SMARTBUCK2_MAP_MIKROBUS( smartbuck2_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == smartbuck2_init( &smartbuck2, &smartbuck2_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTBUCK2_ERROR == smartbuck2_default_cfg ( &smartbuck2 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
}
```

### Application Task

> This example demonstrates the use of the Smart Buck 2 Click board™.
> The demo application changes the output voltage in steps of 100mv every 3 seconds 
> and displays the output voltage value.
> Results are sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( SMARTBUCK2_OK == smartbuck2_set_voltage( &smartbuck2, vout_mv ) )
    {
        Delay_ms( 100 );
        if ( SMARTBUCK2_OK == smartbuck2_get_voltage( &smartbuck2, &vout_mv ) )
        {
            log_printf( &logger, " Output voltage: %u [mV]\r\n", vout_mv );
        }
    }
    vout_mv += DEMO_VOUT_STEP_100MV;
    if ( vout_mv > SMARTBUCK2_VOUT_MAX )
    {
        vout_mv = SMARTBUCK2_VOUT_MIN;
    }
    Delay_ms( 3000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartBuck2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
