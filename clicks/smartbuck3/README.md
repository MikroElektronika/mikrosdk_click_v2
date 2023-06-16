\mainpage Main Page

---
# Smart Buck 3 click

> Smart Buck 3 Click is a compact add-on board that contains a high-frequency synchronous step-down DC-DC converter. 
> This board features the TPS62366A, a processor supply with I2C compatible interface and a remote sense 
> from Texas Instruments. As input, it uses voltages in the range of 2.5V up to 5.5V, 
> including support for common battery technologies. As output, the converter can scale voltage 
> from 0.5V up to 1.77V in 10mV steps, retaining up to 2.5A peak output current, operating at 2.5MHz 
> of the typical switching frequency.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/smartbuck3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/smart-buck-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Smart Buck 3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Smart Buck 3 Click driver.

#### Standard key functions :

- `smartbuck3_cfg_setup` Config Object Initialization function.
```c
void smartbuck3_cfg_setup ( smartbuck3_cfg_t *cfg );
```

- `smartbuck3_init` Initialization function.
```c
err_t smartbuck3_init ( smartbuck3_t *ctx, smartbuck3_cfg_t *cfg );
```

- `smartbuck3_default_cfg` Click Default Configuration function.
```c
err_t smartbuck3_default_cfg ( smartbuck3_t *ctx );
```

#### Example key functions :

- `smartbuck3_set_voltage` Smart Buck 3 set voltage function.
```c
err_t smartbuck3_set_voltage ( smartbuck3_t *ctx, uint16_t vout_mv );
```

- `smartbuck3_get_voltage` Smart Buck 3 get voltage function.
```c
err_t smartbuck3_get_voltage ( smartbuck3_t *ctx, uint16_t *vout_mv );
```

- `smartbuck3_set_operation_mode` Smart Buck 3 set operation mode function.
```c
err_t smartbuck3_set_operation_mode ( smartbuck3_t *ctx, uint8_t op_mode );
```

## Example Description

> This example demonstrates the use of Smart Buck 3 Click board™.
> This driver provides functions for device configurations 
> and for the sets and reads the output voltage.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> After initializing the driver, the default configuration is executed 
> and the device is turned on.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck3_cfg_t smartbuck3_cfg;  /**< Click config object. */

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
    smartbuck3_cfg_setup( &smartbuck3_cfg );
    SMARTBUCK3_MAP_MIKROBUS( smartbuck3_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == smartbuck3_init( &smartbuck3, &smartbuck3_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    
    if ( SMARTBUCK3_ERROR == smartbuck3_default_cfg ( &smartbuck3 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    Delay_ms( 100 );
    log_info( &logger, " Application Task " );
    vout_mv = SMARTBUCK3_VOUT_MIN;
}
```

### Application Task

> This example demonstrates the use of the Smart Buck 3 Click board™.
> Changes the output voltage every 3 seconds 
> and displays the current voltage output value.
> Results are sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    if ( SMARTBUCK3_OK == smartbuck3_set_voltage( &smartbuck3, vout_mv ) )
    {
        Delay_ms( 100 );
        if ( SMARTBUCK3_OK == smartbuck3_get_voltage( &smartbuck3, &vout_mv ) )
        {
            log_printf ( &logger, " Vout: %u mV\r\n", vout_mv );    
        }
    }
    vout_mv += 100;
    if ( vout_mv > SMARTBUCK3_VOUT_MAX )
    {
        vout_mv = SMARTBUCK3_VOUT_MIN;
    }
    Delay_ms( 3000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartBuck3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
