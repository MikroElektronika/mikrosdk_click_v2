 

---
# Ambient 2 Click

Ambient 2 Click carries TI’s OPT3001 Ambient Light sensor.
It’s a small (2mm x 2mm) single-chip lux meter that measures only the visible part of the light spectrum from any kind of source (mimicking the way humans see light).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient2_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ambient-2-click)

---


#### Click library

- **Author**        : Nemanja Medakovic
- **Date**          : Oct 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ambient2 Click driver.

#### Standard key functions :

- Configuration Object Setup function.
> void ambient2_cfg_setup ( ambient2_cfg_t *cfg ); 
 
- Click Initialization function.
> ambient2_err_t ambient2_init( ambient2_t *ctx, ambient2_cfg_t *cfg );

- Click Default Configuration function.
> void ambient2_default_cfg ( ambient2_t *ctx );


#### Example key functions :

- Generic Write function.
> void ambient2_generic_write( ambient2_t *ctx, ambient2_reg_addr_t reg_addr, ambient2_data_t data_in );
 
- Generic Read function.
> ambient2_data_t ambient2_generic_read( ambient2_t *ctx, ambient2_reg_addr_t reg_addr );

- Sensor Results Read function.
> void ambient2_get_sens_results( ambient2_t *ctx );

## Examples Description

>
> This is a example which demonstrates the use of Ambient 2 Click board.
> This example measures and calculates abmient light from OPT3001 sensor.
>

**The demo application is composed of two sections :**

### Application Init

>
> Initializes I2C driver and all used pins for Ambient 2 Click. 
> Also executes a default configuration for this Click, which means
> that Click will work in continuous conversion mode, in automatic full scale
> range, with conversion time of 800ms.
>

```c

void application_init( void )
{
    ambient2_cfg_t ambient2_cfg;
    log_cfg_t console_cfg;

    //  Click initialization.
    ambient2_cfg_setup( &ambient2_cfg );
    AMBIENT2_MAP_MIKROBUS( ambient2_cfg, MIKROBUS_1 );
    ambient2_init( &ambient2, &ambient2_cfg );
    ambient2_default_cfg( &ambient2 );

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( console_cfg );
    log_init( &console, &console_cfg );
    log_write( &console, "* * *  Ambient 2 initialization done  * * *", LOG_FORMAT_LINE );
    log_write( &console, "*******************************************", LOG_FORMAT_LINE );
}
  
```

### Application Task

>
> Reads sensor data every time when conversion cycle was done
> and data was ready for reading. Sends results to the uart terminal.
>

```c

void application_task( void )
{
    if ( ambient2_generic_read( &ambient2, AMBIENT2_REG_CONFIGURATION ) & AMBIENT2_FLAG_MASK_CONV_READY )
    {
        ambient2_get_sens_results( &ambient2 );

        log_printf( &console, "** Ambient Light Sensor : %.2f lux **\r\n", ambient2.sens_data.amb_light_lx );
        log_printf( &console, "** Ambient Light Range : %.2f lux **\r\n", ambient2.sens_data.amb_light_range );
        log_printf( &console, "** Ambient Light Percents : %d %% **\r\n\n", ambient2.sens_data.amb_light_per );
    }
}  

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient2

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
