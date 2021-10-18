
---
# Compass 3 click

Compass 3 Click is an expansion board that can measure the three-axis magnetic field which is perfect for implementation in applications such as electric compasses. This board features MMC5883MA, a complete 3-axis magnetic sensor with signal processing from MEMSIC.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/compass3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/compass-3-click)

---


#### Click library 

- **Author**        : Jovan Stajkovic
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Compass3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Compass3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void compass3_cfg_setup ( compass3_cfg_t *cfg ); 
 
- Initialization function.
> COMPASS3_RETVAL compass3_init ( compass3_t *ctx, compass3_cfg_t *cfg );

- Click Default Configuration function.
> void compass3_default_cfg ( compass3_t *ctx );


#### Example key functions :

- Measures magnetic field surrounding the device.
> void compass3_full_measurement ( compass3_t *ctx, float *x_val, float *y_val, float *z_val );
 
- Function is used to measure temperature.
> float compass3_read_temp ( compass3_t *ctx );

- Function checks interrupt occurence.
> uint8_t compass3_check_int ( compass3_t *ctx );

## Examples Description

> 
> This demoapp measures the magnetic field surrounding the device.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Initalizes I2C driver and click driver, performs check, applies default 
> setup and writes an initial log.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    compass3_cfg_t cfg;

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
    log_printf( &logger, "---- Application Init ----\r\n" );

    //  Click initialization.

    compass3_cfg_setup( &cfg );
    COMPASS3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    compass3_init( &compass3, &cfg );
    Delay_ms( 100 );
    
    compass3_generic_read( &compass3, COMPASS3_DEVICE_ID, &test_val, 1 );

    if ( test_val == COMPASS3_DEVICE_ID_NUM )
    {
        log_printf( &logger, "--------------------\r\n" );
        log_printf( &logger, "   Compass 3 click  \r\n" );
        log_printf( &logger, "--------------------\r\n" );
    }
    else
    {
        log_printf( &logger, "   Fatal error!!!   \r\n" );
        for ( ; ; );
    }

    compass3_default_cfg ( &compass3 );
    Delay_ms( 100 );
}
  
```

### Application Task

>
> This example demonstrates the use of 
> Compass 3 Click board by measuring the magnetic field surrounding the device.
> 

```c

void application_task ( void )
{
    if ( compass3_check_int( &compass3 ) == COMPASS3_INTERRUPT )
    {
        compass3_full_measurement ( &compass3, &x_val, &y_val, &z_val );

        log_printf( &logger,"  X-axis : %2.f mG\r\n", x_val );
        log_printf( &logger,"  Y-axis : %2.f mG\r\n", y_val );
        log_printf( &logger,"  Z-axis : %2.f mG\r\n", z_val );

        Delay_ms( 1000 );
        log_printf( &logger, "--------------------\r\n" );
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Compass3

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
