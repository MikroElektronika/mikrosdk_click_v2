 
---
# Brushless7 click

Brushless 7 Click is, as its name said, a motor driver based expansion board for controlling BLCD motors with any microcontroller.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>


[click Product page](https://www.mikroe.com/brushless-7-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Brushless7 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Brushless7 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void brushless7_cfg_setup ( brushless7_cfg_t *cfg ); 
 
- Initialization function.
> BRUSHLESS7_RETVAL brushless7_init ( brushless7_t *ctx, brushless7_cfg_t *cfg );

- Click Default Configuration function.
> void brushless7_default_cfg ( brushless7_t *ctx );


#### Example key functions :

- Function for changeing duty of device
> uint8_t brushless7_change_duty ( brushless7_t *ctx, float duty_ptc );
 
- Function for setting max rpm parameter of device
> uint8_t brushless7_max_speed_rpm ( brushless7_t *ctx, uint8_t max_speed_rpm );

- Function for setting type of device control
> uint8_t brushless7_control_mode_set ( brushless7_t *ctx, uint8_t ctrl_type );

## Examples Description

> This demo app changes values of duty and rpm.

**The demo application is composed of two sections :**

### Application Init 

> Setts default configuration and sets parameters for selected mode. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    brushless7_cfg_t cfg;
    uint8_t error_flag = 0;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    brushless7_cfg_setup( &cfg );
    BRUSHLESS7_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    brushless7_init( &brushless7, &cfg );
    
    Delay_ms( 100 );

    brushless7_default_cfg( &brushless7 );
    
    demo_type_data = BRUSHLESS7_CTRL_TYPE_DUTY;

    brushless7_control_mode_set( &brushless7, demo_type_data );
    brushless7_rotating_direction( &brushless7, BRUSHLESS7_DIR_CW );

    if ( BRUSHLESS7_CTRL_TYPE_DUTY == demo_type_data )
    {
        error_flag |= brushless7_max_duty( &brushless7, 95.0 );
        error_flag |= brushless7_start_duty( &brushless7, 5.0 );
        error_flag |= brushless7_stop_duty( &brushless7, 2.0 );
        brushless7_change_duty( &brushless7, 20 );
        log_printf( &logger, " ----- DUTY CONTROL ----- \r\n" );
    }
    else if ( BRUSHLESS7_CTRL_TYPE_RPM == demo_type_data )
    {
        error_flag |= brushless7_max_speed_rpm( &brushless7, BRUSHLESS7_MAX_SPEED_4096 );
        error_flag |= brushless7_start_rpm( &brushless7, 400 );
        log_printf( &logger, " ----- RPM CONTROL ----- \r\n" );
    }
    
    if ( BRUSHLESS7_DEV_ERROR == error_flag )
    {
        log_printf( &logger, " ----- ERROR ----- \r\n" );
        for( ; ; );
    }

    log_printf( &logger, " ***** APP TASK ***** \r\n" );
}
  
```

### Application Task

> Sets 3 different speed of motor in span of 20 seconds.

```c

void application_task ( void )
{
    if ( BRUSHLESS7_CTRL_TYPE_DUTY == demo_type_data )
    {
        log_printf( &logger, " ----- 20 ----- \r\n" );
        stop_start( );
        brushless7_change_duty( &brushless7, 20 );
        Delay_ms( 20000 );
        log_printf( &logger, " ----- 40 ----- \r\n" );
        stop_start( );
        brushless7_change_duty( &brushless7, 40 );
        Delay_ms( 20000 );
        log_printf( &logger, " ----- 8 ----- \r\n" );
        stop_start( );
        brushless7_change_duty( &brushless7, 8 );
        Delay_ms( 20000 );
    }
    else if ( BRUSHLESS7_CTRL_TYPE_RPM == demo_type_data )
    {
        log_printf( &logger, " ----- 400 ----- \r\n" );
        stop_start( );
        brushless7_start_rpm( &brushless7, 400 );
        Delay_ms( 20000 );
        log_printf( &logger, " ----- 1000 ----- \r\n" );
        stop_start( );
        brushless7_start_rpm( &brushless7, 1000 );
        Delay_ms( 20000 );
        log_printf( &logger, " ----- 100 ----- \r\n" );
        stop_start( );
        brushless7_start_rpm( &brushless7, 100 );
        Delay_ms( 20000 );
    }
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Brushless7

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
