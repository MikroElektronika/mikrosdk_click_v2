
---
# Brushless 3 click

Brushless 3 click carries the DRV10983, a three-phase sensorless motor driver with integrated power MOSFETs. When an external power supply is applied, you can drive a brushless DC motor through the PWM pin, AN pin or I2C interface.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/brushless3_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/brushless-3-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Brushless3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Brushless3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void brushless3_cfg_setup ( brushless3_cfg_t *cfg ); 
 
- Initialization function.
> BRUSHLESS3_RETVAL brushless3_init ( brushless3_t *ctx, brushless3_cfg_t *cfg );

- Click Default Configuration function.
> void brushless3_default_cfg ( brushless3_t *ctx );


#### Example key functions :

- Function get the speed command ( % ) based on analog or PWM or I2C by read the value from the target Speed CMD register address.
> float brushless3_get_speed_cmd ( brushless3_t *ctx );
 
- Function set the direction of rotation in the forward direction by sets PWM and RST pin on Brushless 3 Click board.
> void brushless3_forward_direction ( brushless3_t *ctx );

- Function set the direction of rotation in the reverse direction by sets PWM and clear RST pin on Brushless 3 Click board.
> void brushless3_reverse_direction ( brushless3_t *ctx ); 

## Examples Description

> This click has three-phase sensorless motor driver and with an external power supply it drives a brushless DC motor. 

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C, set default parameter value.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    brushless3_cfg_setup( &cfg );
    BRUSHLESS3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless3_init( &brushless3, &cfg );

    brushless3_default_cfg( &brushless3 ); 
    brushless3_forward_direction( &brushless3 );
    brushless3_set_default_param( &brushless3 );
}
  
```

### Application Task

> This is an example which demonstrates the use of Brushless 3 Click board.
> Read and display float motor frequency value from the DRV10983 sensorless 
> BLDC motor driver on Brushless 3 click board. Results are being sent to 
> the Usart Terminal where you can track their changes. 
> All data logs write on usb uart changes for every 3 sec.

```c

void application_task ( void )
{
    velocity = brushless3_get_speed( &brushless3 );
    log_printf( &logger, " Motor frequency: %.2f Hz\r\n",  velocity );
    log_printf( &logger, "-----------------------\r\n" );
}  

``` 

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless3

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
