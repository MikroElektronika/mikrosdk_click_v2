
# Magneto 5 click

Magneto 5 click is a very accurate and reliable magnetic sensor device, which features the MEMSIC MMC34160PJ, a 3-axis magnetic sensor IC

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/magneto5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/magneto-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Magneto5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Magneto5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void magneto5_cfg_setup ( magneto5_cfg_t *cfg ); 
 
- Initialization function.
> MAGNETO5_RETVAL magneto5_init ( magneto5_t *ctx, magneto5_cfg_t *cfg );

- Click Default Configuration function.
> void magneto5_default_cfg ( magneto5_t *ctx );


#### Example key functions :

- Functions reads axis data.
> void magneto5_get_axis_data ( magneto5_t *ctx, int16_t *axis_buffer, uint8_t max_resolution );
 
- Functions reads axis data value.
> float magneto5_get_axis_value ( magneto5_t *ctx, uint8_t axis, uint8_t max_resolution );

- Functions sets configuration register 0.
> void magneto5_config_register_0 ( magneto5_t *ctx, uint8_t config_data );

## Examples Description
 
> This application is is a very accurate and reliable magnetic         sensor device. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and set measurement mode and channel. 

```c

void application_init ( void )
{
 log_cfg_t log_cfg;
    magneto5_cfg_t cfg;

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
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    magneto5_cfg_setup( &cfg );
    MAGNETO5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    magneto5_init( &magneto5, &cfg );
}
  
```

### Application Task

> Reads X / Y / Z data axis and logs to USBUART every 1 sec. 

```c

void application_task ( void )
{
//  Task implementation.

    x_axis = magneto5_get_axis_value( &magneto5, MAGNETO5_AXIS_X, MAGNETO5_CH3_12bits_1ms );
    log_printf ( &logger, "-- X axis : %d \r\n ", x_axis );

    y_axis = magneto5_get_axis_value( &magneto5, MAGNETO5_AXIS_Y, MAGNETO5_CH3_12bits_1ms );
    log_printf ( &logger, "-- Y axis : %d \r\n ",  y_axis );

    z_axis = magneto5_get_axis_value( &magneto5, MAGNETO5_AXIS_Z, MAGNETO5_CH3_12bits_1ms );
    log_printf ( &logger, "-- Z axis : %d \r\n ", z_axis );

    Delay_ms( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Magneto5

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
