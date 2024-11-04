
---
# Ambient 6 Click

Ambient 6 Click can sense the intensity of the ambient light, providing the measurement data in digital format over the I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient6_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ambient-6-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient6 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ambient6 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ambient6_cfg_setup ( ambient6_cfg_t *cfg ); 
 
- Initialization function.
> AMBIENT6_RETVAL ambient6_init ( ambient6_t *ctx, ambient6_cfg_t *cfg );

- Click Default Configuration function.
> void ambient6_default_cfg ( ambient6 *ctx );

#### Example key functions :

- Functions for read 16bit Ambient Data (ALS)
> uint16_t ambient6_get_ambient_data ( ambient6_t *ctx );
 
- Functions for configuration device for measurement
> void ambient6_configuration ( ambient6_t *ctx, uint16_t config_data);

- Functions for get Ambient Light Data
> float ambient6_get_ambient_light ( ambient6_t *ctx );

## Examples Description

> This application measurement ambient light

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver init and default configuration device for measurement

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient6_cfg_t cfg;

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

    ambient6_cfg_setup( &cfg );
    AMBIENT6_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient6_init( &ambient6, &cfg );
    ambient6_default_cfg( &ambient6 );    
}
```

### Application Task

> Read Ambient Light in lux[lx] and this data logs to USBUART every 1sec.

```c
void application_task ( )
{
    float ambient_light;
    
    ambient_light = ambient6_get_ambient_light( &ambient6 );
    log_printf( &logger, "Ambient Light: %f lx \r\n", ambient_light );
    Delay_1sec( );
} 
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient6

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
