\mainpage Main Page
 
 

---
# Timer click

Timer click is a mikroBUS add-on board with Maxim’s DS1682 total elapsed time recorder. The main feature of the IC is its elapsed time counter (ETC) used in conjunction with the ALARM pin.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/timer_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/timer-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Timer Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Timer Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void timer_cfg_setup ( timer_cfg_t *cfg ); 
 
- Initialization function.
> TIMER_RETVAL timer_init ( timer_t *ctx, timer_cfg_t *cfg );


#### Example key functions :

- Get elapsed time counter (ETC) data function
> uint32_t timer_get_etc_data ( timer_t *ctx );
 
- Get elapsed time counter (ETC) seconds function
> uint32_t timer_get_etc_seconds ( timer_t *ctx );

- Set elapsed time counter (ETC) time function
> void timer_get_time ( timer_t *ctx, uint16_t *time_days, uint8_t *time_hours, uint8_t *time_minutes, uint8_t *time_seconds );

## Examples Description

> This application is multifunctional 3-axis digital accelerometer that can also be configured as a 45-degree Tilt sensor.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C,
> soft reset, sets ETC and EC start ( seconds ), hardwere reset and > start write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    timer_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    timer_cfg_setup( &cfg );
    TIMER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    timer_init( &timer, &cfg );
    Delay_ms( 200 );

    log_printf( &logger, "   Driver  Init   \r\n" );
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "    Soft Reset    \r\n" );
    
    timer_soft_reset( &timer );
    Delay_ms( 500 );
    
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "  Set ETC and EC  \r\n" );
    
    timer_set_etc_seconds( &timer, 86390 );
    timer_set_ec_seconds( &timer, 0 );
    
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "  Hardwere Reset  \r\n" );
    
    timer_hw_reset( &timer );
    Delay_ms( 500 );
    
    log_printf( &logger, "------------------\r\n" );
    log_printf( &logger, "        ETC       \r\n" );
    log_printf( &logger, "------------------\r\n" );
}
  
```

### Application Task

> This is a example which demonstrates the use of Timer Click board.
> Timer Click communicates with register via I2C by write to 
> register and read from register,
> display time ( days, hours, minutes and seconds ) which we  
> received reading from the target register address of DS1682 total > elapsed time recorder.
> Results are being sent to the Usart Terminal where you can track  > their changes.
> All data logs write on usb uart changes for every 1 sec.

```c

void application_task ( )
{
    static uint8_t time_seconds_new = 0xFF;
    uint8_t time_hours;
    uint8_t time_minutes;
    uint8_t time_seconds;
    uint16_t time_days;

    timer_get_time( &timer, &time_days, &time_hours, &time_minutes, &time_seconds );
   
    if ( time_seconds_new != time_seconds )
    {
        log_printf
        ( 
            &logger, " %d days    %d:%d:%d \r\n", 
            time_days, 
            time_hours, 
            time_minutes, 
            time_seconds
        );
        log_printf( &logger, "------------------\r\n" );
        time_seconds_new = time_seconds;
    }
    Delay_ms( 1 );
}
```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Timer

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
