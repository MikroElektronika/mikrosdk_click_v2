 

---
# Fan 2 click

Fan 2 click carries the MAX31760 precision fan-speed controller.
It can measure temperature and adjust the fan speed to keep the temperature at the same level.
Fan 2 click can also control two fans at the same time.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/fan2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/fan-2-click)

---


#### Click library

- **Author**        : Nemanja Medakovic
- **Date**          : Nov 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Fan2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers).
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account.

## Library Description

> This library contains API for Fan2 Click driver.

#### Standard key functions :

- Configuration Object Initialization function.
> void fan2_cfg_setup( fan2_cfg_t *cfg );
 
- Click Initialization function.
> fan2_err_t fan2_init( fan2_t *ctx, fan2_cfg_t *cfg );

- Click Default Configuration function.
> void fan2_default_cfg( fan2_t *ctx, fan2_wire_t n_wires );

#### Example key functions :

- Generic Byte Write function.
> fan2_err_t fan2_generic_write_byte( fan2_t *ctx, uint8_t reg_addr, uint8_t data_in );
 
- Tachometer Read function.
> fan2_err_t fan2_read_tacho( fan2_t *ctx, uint8_t tacho_addr, uint32_t *tacho_rpm );

- Direct Fan Speed Control function.
> fan2_err_t fan2_direct_speed_control( fan2_t *ctx, float speed_per );

## Examples Description

>
> This example demonstrates the use of Fan 2 Click board.
> It demonstrates sensor measurements and fan control.
>

**The demo application is composed of two sections :**

### Application Init

>
> Initializes I2C driver and executes a default configuration for Fan 2 click.
> Also initializes UART logger for results logging.
>

```c

void application_init( void )
{
    fan2_cfg_t fan2_cfg;
    log_cfg_t log_cfg;

    //  UART logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );
    
    //  Click initialization.
    fan2_cfg_setup( &fan2_cfg );
    FAN2_MAP_MIKROBUS( fan2_cfg, MIKROBUS_1 );
    fan2_init( &fan2, &fan2_cfg );
    
    fan2_default_cfg( &fan2 );
    fan2_speed = FAN2_HALF_SPEED_PER;
    Delay_ms( 1000 );

    log_printf( &logger, "* * *  Fan 2 initialization done  * * *\r\n" );
    log_printf( &logger, "***************************************\r\n" );
    flag = 0;
}

```

### Application Task

>
> Increments the fan speed from half speed to maximum, and on each step measures
> the current fan speed in RPM and the remote temperature in Celsius.
> Fan speed will be incremented/decremented each second for 10 percents.
>

```c

void application_task( void )
{
    fan2_direct_speed_control( &fan2, fan2_speed );

    Delay_ms( 1000 );
    fan2_read_tacho( &fan2, FAN2_REG_TACH1_CNT, &fan2_curr_speed );
    
    fan2_read_temp( &fan2, FAN2_REG_REMOTE_TEMP_READ, &fan2_temp );

    log_printf( &logger, "* Fan 2 set speed : %.2f %%\r\n", fan2_speed );
    log_printf( &logger, "* Fan 2 current speed : %u RPM\r\n", fan2_curr_speed );
    log_printf( &logger, "* Fan 2 remote temperature : %.2f %s\r\n", fan2_temp, deg_cels );
    log_printf( &logger, "***************************************\r\n" );
    
    if ( flag == 0 ) {
        if ( fan2_speed < FAN2_MAX_SPEED_PER)
            fan2_speed += 10;
        else
            flag = 1;
    }
    
    if ( flag == 1 ) {
        if ( fan2_speed > FAN2_MIN_SPEED_PER)
            fan2_speed -= 10;
        else {
            fan2_speed = FAN2_HALF_SPEED_PER;
            flag = 0;
        }
    }
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Fan2

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
