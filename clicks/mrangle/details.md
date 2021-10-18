
---
# MR Angle click

MR Angle Click is a compact add-on board that contains a magnetoresistive sensor with an integrated amplifier. This board features the KMZ60, a high precision sensor for magnetic angle measurement with single-ended cosine and sine outputs from NXP Semiconductors. The MR sensor element comes with two Wheatstone bridges for cosine and sine signals, supports functions for control circuit and signal amplification, and enables angular measurements with high accuracy by an excellent linearity and temperature drift behavior. The KMZ60 is fully automotive qualified as well as applicable for industrial and consumer applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/mr_angle_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/mr-angle-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Apr 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the MrAngle Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for MrAngle Click driver.

#### Standard key functions :

- `mrangle_cfg_setup` Config Object Initialization function.
```c
void mrangle_cfg_setup ( mrangle_cfg_t *cfg );
```

- `mrangle_init` Initialization function.
```c
MRANGLE_RETVAL mrangle_init ( mrangle_t *ctx, mrangle_cfg_t *cfg );
```

- `mrangle_default_cfg` Click Default Configuration function.
```c
void mrangle_default_cfg ( mrangle_t *ctx );
```

#### Example key functions :

- `mrangle_get_angle` MR Angle get angle function.
```c
err_t mrangle_get_angle ( mrangle_t *ctx, float *angle );
```

- `mrangle_get_temperature` MR Angle get temperature function.
```c
err_t mrangle_get_temperature ( mrangle_t *ctx, float *temperature );
```

- `mrangle_powerdown_mode` MR Angle powerdown mode function.
```c
err_t mrangle_powerdown_mode ( mrangle_t *ctx, mrangle_powerdown_mode_value_t pd_mode );
```

## Example Description

> This library contains API for the MR Angle click driver.
> This demo application shows an example of angle measurement.

**The demo application is composed of two sections :**

### Application Init

> Initialization of SPI module and log UART.
> After driver initialization, the app performs default settings.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;          /**< Logger config object. */
    mrangle_cfg_t mrangle_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    mrangle_cfg_setup( &mrangle_cfg );
    MRANGLE_MAP_MIKROBUS( mrangle_cfg, MIKROBUS_1 );
    err_t init_flag  = mrangle_init( &mrangle, &mrangle_cfg );
    if ( init_flag == SPI_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    mrangle_default_cfg ( &mrangle );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 1000 );
}

```

### Application Task

> This is an example that shows the use of an MR Angle click board™.
> The application task consists of reading the angle measurements in degrees ( 0 - 180 ).
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
    mrangle_get_angle( &mrangle, &angle );
    log_printf( &logger, "   Angle : %.2f degree   \r\n", angle );
    log_printf( &logger, "-------------------------\r\n" );
    Delay_ms( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.MrAngle

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all Mikroelektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
