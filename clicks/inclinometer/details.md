
---
# Inclinometer click

> Inclinometer Click is a compact add-on board that offers best-in-class characteristics for inclination measurements. This board features the SCL3300, a high-performance inclinometer sensor component from Murata.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/inclinometer_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/inclinometer-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Jun 2021.
- **Type**          : SPI type


# Software Support

We provide a library for the Inclinometer Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Inclinometer Click driver.

#### Standard key functions :

- `inclinometer_cfg_setup` Config Object Initialization function.
```c
void inclinometer_cfg_setup ( inclinometer_cfg_t *cfg );
```

- `inclinometer_init` Initialization function.
```c
err_t inclinometer_init ( inclinometer_t *ctx, inclinometer_cfg_t *cfg );
```

- `inclinometer_default_cfg` Click Default Configuration function.
```c
err_t inclinometer_default_cfg ( inclinometer_t *ctx );
```

#### Example key functions :

- `inclinometer_get_axes` Axes reading.
```c
err_t inclinometer_get_axes ( inclinometer_t *ctx, inclinometer_accel_t *axes_data );
```

- `inclinometer_get_angle` Angle reading.
```c
err_t inclinometer_get_angle ( inclinometer_t *ctx, inclinometer_accel_t *angle_data );
```

- `inclinometer_get_temperature` Temperature reading.
```c
err_t inclinometer_get_temperature ( inclinometer_t *ctx, float *temperature );
```

## Example Description

> This example showcases ability of device to configure it for 
resolution and read Axis/Angle/Temperature data.

**The demo application is composed of two sections :**

### Application Init

> Initialization of the Host communication modules(UART, SPI). 
Sets default configuration where powe-up sequence is done with 
selecting MODE1 and enabling output on Angle channels. 
Read status and checks WhoAmI register. In the end example type
is selected( for reading Axes, Angles or Temperature data ).

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    inclinometer_cfg_t inclinometer_cfg;  /**< Click config object. */

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
    inclinometer_cfg_setup( &inclinometer_cfg );
    INCLINOMETER_MAP_MIKROBUS( inclinometer_cfg, MIKROBUS_1 );
    err_t init_flag  = inclinometer_init( &inclinometer, &inclinometer_cfg );
    if ( SPI_MASTER_ERROR == init_flag )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    //Powerup
    init_flag = inclinometer_default_cfg ( &inclinometer );
    if ( INCLINOMETER_ERROR == init_flag )
    {
        log_error( &logger, " Default configuration. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    example_type = EXAMPLE_AXIS;
    Delay_ms ( 1000 );
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Depending on the example type selected task is reading different data.
If EXAMPLE_AXIS selected it reads 3 axes values in range of -1<->1g. 
If EXAMPLE_ANGLE is slected it reads 3 angle values in range of 
-90<->90deg. EXAMPLE_TEMP reads temperature data from device in degC.

```c

void application_task ( void )
{
    switch ( example_type )
    {
        case EXAMPLE_AXIS:
        {
            inclinometer_accel_t axes_data;
            inclinometer_get_axes( &inclinometer, &axes_data );
            log_printf( &logger, "> ACCEL X[g]: %.2f\r\n", axes_data.x );
            log_printf( &logger, "> ACCEL Y[g]: %.2f\r\n", axes_data.y );
            log_printf( &logger, "> ACCEL Z[g]: %.2f\r\n", axes_data.z );
            break;
        }
        case EXAMPLE_ANGLE:
        {
            inclinometer_accel_t angle_data;
            inclinometer_get_angle( &inclinometer, &angle_data );
            log_printf( &logger, "> ANGLE X[deg]: %.2f\r\n", angle_data.x );
            log_printf( &logger, "> ANGLE Y[deg]: %.2f\r\n", angle_data.y );
            log_printf( &logger, "> ANGLE Z[deg]: %.2f\r\n", angle_data.z );
            break;
        }
        case EXAMPLE_TEMP:
        {
            float temp_data = 0;
            inclinometer_get_temperature( &inclinometer, &temp_data );
            log_printf( &logger, "> Temperature[degC]: %.2f\r\n", temp_data );
            break;
        }
        default:
        {
            log_error( &logger, " Example type." );
            break;
        }
    }
    log_printf( &logger, "*************************************\r\n" );
    Delay_ms ( 100 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Inclinometer

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](http://shop.mikroe.com/usb-uart-click),
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. The
terminal available in all MikroElektronika
[compilers](http://shop.mikroe.com/compilers), or any other terminal application
of your choice, can be used to read the message.

---
