
---
# IR Sense 5 click

> IR Sense 5 Click is a compact add-on board designed for accurate, non-contact surface temperature measurement. This board features the ZTP-148SRC1, a thermopile IR sensor from Amphenol, with a measurement range from -20 to +100°C, an active area of 0.7x0.7mm², and a typical field of view of 85 degrees. The board also integrates an OPA2365AIDR OpAmp for signal amplification and an MCP3221 analog-to-digital converter for digitizing the output. Additional features include output offset selection and test points for signal monitoring.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/irsense5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ir-sense-5-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Feb 2024.
- **Type**          : ADC/I2C type


# Software Support

We provide a library for the IR Sense 5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for IR Sense 5 Click driver.

#### Standard key functions :

- `irsense5_cfg_setup` Config Object Initialization function.
```c
void irsense5_cfg_setup ( irsense5_cfg_t *cfg );
```

- `irsense5_init` Initialization function.
```c
err_t irsense5_init ( irsense5_t *ctx, irsense5_cfg_t *cfg );
```

#### Example key functions :

- `irsense5_get_obj_temp` This function reads and calculate object temperature in degree Celsius [degC].
```c
err_t irsense5_get_obj_temp ( irsense5_t *ctx, float *obj_temp );
```

- `irsense5_get_amb_temp` This function reads and calculate ambient temperature in degree Celsius [degC].
```c
err_t irsense5_get_amb_temp ( irsense5_t *ctx, float *amb_temp );
```

- `irsense5_read_raw_adc_thm` This function reads the thermistor raw ADC value.
```c
err_t irsense5_read_raw_adc_thm ( irsense5_t *ctx, uint16_t *raw_adc );
```

## Example Description

> This library contains API for the IR Sense 5 Click driver 
> for measuring ambient and object temperature.

**The demo application is composed of two sections :**

### Application Init

> The initialization of the I2C and ADC module and log UART.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    irsense5_cfg_t irsense5_cfg;  /**< Click config object. */

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
    irsense5_cfg_setup( &irsense5_cfg );
    IRSENSE5_MAP_MIKROBUS( irsense5_cfg, MIKROBUS_1 );
    err_t init_flag = irsense5_init( &irsense5, &irsense5_cfg );
    if ( ( ADC_ERROR == init_flag ) || ( I2C_MASTER_ERROR == init_flag ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> The demo application measures ambient and object temperature in degrees Celsius.
> Results are being sent to the UART Terminal, where you can track their changes.

```c
void application_task ( void ) 
{
    float temperature = 0;
    if ( IRSENSE5_OK == irsense5_get_amb_temp ( &irsense5, &temperature ) )
    {
        log_printf( &logger, " Ambient Temperature: %.2f [degC]\r\n", temperature );
        Delay_ms ( 1000 );
    }

    if ( IRSENSE5_OK == irsense5_get_obj_temp ( &irsense5, &temperature ) )
    {
        log_printf( &logger, " Object Temperature:  %.2f [degC]\r\n\n", temperature );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.IRSense5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
