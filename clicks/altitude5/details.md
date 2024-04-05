
---
# Altitude 5 click

> Altitude 5 Click is a compact add-on board allowing high-resolution barometric pressure measurement. This board features the KP236, an analog barometric air pressure sensor based on a capacitive principle from Infineon Technologies. The KP236 is primarily developed for measuring barometric air pressure but can also be used in other application fields. It is surface micro-machined with a monolithic integrated signal conditioning circuit implemented in BiCMOS technology. The calibrated transfer function converts pressure into an analog output signal in a range of 40kPa to 115kPa. However, the choice of signal processing is up to the user; more precisely, the user can process the output signal in analog or digital form. The high accuracy and the high sensitivity of the KP236 make this Click board™ suitable for advanced automotive applications and industrial and consumer applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/altitude5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/altitude-5-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Sep 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Altitude5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Altitude5 Click driver.

#### Standard key functions :

- `altitude5_cfg_setup` Config Object Initialization function.
```c
void altitude5_cfg_setup ( altitude5_cfg_t *cfg );
```

- `altitude5_init` Initialization function.
```c
err_t altitude5_init ( altitude5_t *ctx, altitude5_cfg_t *cfg );
```

- `altitude5_default_cfg` Click Default Configuration function.
```c
err_t altitude5_default_cfg ( altitude5_t *ctx );
```

#### Example key functions :

- `altitude5_get_altitude` Altitude 5 get altitude function.
```c
err_t altitude5_get_altitude ( altitude5_t *ctx, float *altitude );
```

- `altitude5_get_pressure` Altitude 5 get pressure function.
```c
err_t altitude5_get_pressure ( altitude5_t *ctx, float *pressure );
```

- `altitude5_get_adc_voltage` Altitude 5 get ADC voltage function.
```c
err_t altitude5_get_adc_voltage ( altitude5_t *ctx, float *adc_vtg );
```

## Example Description

> This library contains API for Altitude 5 Click driver.
> The demo application reads ADC value, calculate pressure and altitude.

**The demo application is composed of two sections :**

### Application Init

> Initializes I2C or analog driver and log UART.
> After driver initialization the app set default settings.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;              /**< Logger config object. */
    altitude5_cfg_t altitude5_cfg;  /**< Click config object. */

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
    altitude5_cfg_setup( &altitude5_cfg );
    ALTITUDE5_MAP_MIKROBUS( altitude5_cfg, MIKROBUS_1 );
    err_t init_flag = altitude5_init( &altitude5, &altitude5_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    altitude5_default_cfg ( &altitude5 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 100 );
}

```

### Application Task

> This is an example that demonstrates the use of the Altitude 5 Click board™.
> In this example, we read ADC values and 
> display the Pressure ( mBar ) and Altitude ( m ) data.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) 
{
    static float pressure;
    static float altitude;
    
    altitude5_get_pressure( &altitude5, &pressure );
    log_printf( &logger, " Pressure    : %.2f mBar \r\n", pressure );
    Delay_ms ( 100 );
    
    altitude5_get_altitude( &altitude5, &altitude );
    log_printf( &logger, " Altitude    : %.2f m \r\n", altitude );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Altitude5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
 