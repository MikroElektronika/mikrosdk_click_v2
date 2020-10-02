\mainpage Main Page
 
 

---
# Accel 10 click

Accel 10 Click features an ultra-low power triaxial "femto" accelerometer sensor with embedded intelligence, labeled as the LIS2DW12TR. This Click board™ allows linear motion and gravitational force measurements in ranges of ±2 g, ±4 g, ±8, and ±16 g in three perpendicular axes. 

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/accel10_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/accel-10-click>)

---


#### Click library 

- **Author**        : Nenad Filipovic
- **Date**          : Jan 2020.
- **Type**          : I2C/SPI type


# Software Support

We provide a library for the Accel10 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Accel10 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void accel10_cfg_setup ( accel10_cfg_t *cfg ); 
 
- Initialization function.
> ACCEL10_RETVAL accel10_init ( accel10_t *ctx, accel10_cfg_t *cfg );

- Click Default Configuration function.
> void accel10_default_cfg ( accel10_t *ctx );


#### Example key functions :

- Check data ready function.
> uint8_t accel10_check_data_ready ( accel10_t *ctx );
 
- Read Accel data function.
> void accel10_get_data ( accel10_t *ctx, accel10_data_t *p_accel_data );

- Read temperature function.
> int8_t accel10_read_temperature ( accel10_t *ctx );

## Examples Description

> 
> This is an example which demonstrates the use of Accel 10 Click board.
> 

**The demo application is composed of two sections :**

### Application Init 

>
> Configuring clicks and log objects.
> 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel10_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_printf( &logger, " - Application Init -\r\n" );

    //  Click initialization.

    accel10_cfg_setup( &cfg );
    ACCEL10_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel10_init( &accel10, &cfg );
    Delay_ms( 100 );
    
    log_printf( &logger, "---------------------\r\n" );
    log_printf( &logger, "    Accel 10 Click\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    
    // Checking communication
    if ( accel10_check_id( &accel10 ) == ACCEL10_SUCCESS )
    {
        
        log_printf( &logger, "  Communication  OK\r\n" );
        log_printf( &logger, "---------------------\r\n" );
        Delay_ms( 100 );
    }
    else
    {
        log_printf( &logger, " Communication ERROR\r\n" );
        log_printf( &logger, "  Reset the device\r\n" );
        log_printf( &logger, "---------------------\r\n" );
        for ( ; ; );
    }
    
    accel10_default_cfg ( &accel10 );
    log_printf( &logger, "   Default config.\r\n" );
    log_printf( &logger, "---------------------\r\n" );
    Delay_ms( 100 );
}
  
```

### Application Task

>
> Measured and display Accel data coordinates values for X-axis, Y-axis and Z-axis.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB uart changes for every 1 sec.
> 

```c

void application_task ( void )
{
    if ( accel10_check_data_ready( &accel10 ) == ACCEL10_STATUS_DATA_READY )
    {
        accel10_get_data ( &accel10, &accel_data );
        Delay_ms( 10 );
        
        log_printf( &logger, "  Accel X :  %4d\r\n", accel_data.x );
        log_printf( &logger, "  Accel Y :  %4d\r\n", accel_data.y );
        log_printf( &logger, "  Accel Z :  %4d\r\n", accel_data.z );
    
        temperature = accel10_read_temperature( &accel10 );
        Delay_ms( 10 );

        log_printf( &logger, " Temperature :  %4d\r\n", temperature );
        log_printf( &logger, "---------------------\r\n" );
        Delay_ms( 1000 );
    }
} 

```

## Note



The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel10

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
