
---
# Accel 14 click

Accel 14 Click is digital acceleration and vibration sensor Click board™. It features an ultra-wide bandwidth, low-noise, 3-axis digital vibration sensor, labeled as IIS3DWB, from STMicroelectronics. This Click board™ allows selectable full-scale acceleration measurements in ranges of ±2 g, ±4 g, ±8, and ±16 g in three axes, and it’s capable of measuring accelerations with a bandwidth up to 6 kHz with an output data rate of 26.7 kHz.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/accel14_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/accel-14-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jul 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Accel14 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Accel14 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void accel14_cfg_setup ( accel14_cfg_t *cfg ); 
 
- Initialization function.
> ACCEL14_RETVAL accel14_init ( accel14_t *ctx, accel14_cfg_t *cfg );

- Click Default Configuration function.
> void accel14_default_cfg ( accel14_t *ctx );


#### Example key functions :

- Check accel data ready function.
> uint8_t accel14_check_accel_data_ready ( accel14_t *ctx );
 
- Get temperature function.
> float accel14_get_temperature ( accel14_t *ctx );

- Read Accel data function
> void accel14_read_accel ( accel14_t *ctx, accel14_accel_fs_xl_t *accel_fs );

## Examples Description

> This application measures accelermeter data.

**The demo application is composed of two sections :**

### Application Init 

> SPI, check device ID, sets default configuration, also write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    accel14_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    accel14_cfg_setup( &cfg );
    ACCEL14_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    accel14_init( &accel14, &cfg );

    Delay_ms( 100 );
    
    log_printf( &logger, "   Driver init done   \r\n" );
    log_printf( &logger, "--------------------- \r\n" );
    log_printf( &logger, " Communication check  \r\n" );
    
    if ( accel14_check_communication( &accel14 ) == ACCEL14_CHECK_ID_SUCCESS )
    {
        log_printf( &logger, "       SUCCESS        \r\n" );
        log_printf( &logger, "--------------------- \r\n" );
    }
    else
    {
        log_printf( &logger, "        ERROR         \r\n" );
        log_printf( &logger, "   Reset the device   \r\n" );
        log_printf( &logger, "--------------------- \r\n" );
        for ( ; ; );
    }
    
    log_printf( &logger, " Set default config.  \r\n" );
    log_printf( &logger, "--------------------- \r\n" );
    accel14_default_cfg( &accel14 );
    Delay_ms( 100 );
    
    log_printf( &logger, "  Acceleration data:  \r\n" );
    log_printf( &logger, "--------------------- \r\n" );
}
  
```

### Application Task

> This is an example which demonstrates the use of Accel 14 Click board.
> Measured and display Acceleration data for X-axis, Y-axis and Z-axis.
> Results are being sent to the Usart Terminal where you can track their changes.
> All data logs write on USB uart changes for every 1 sec.

```c

void application_task ( void )
{
    data_ready_flag = accel14_check_accel_data_ready( &accel14 );
    Delay_ms( 10 );
    
    if ( data_ready_flag == ACCEL14_NEW_DATA_AVAILABLE )
    {
        accel14_get_data ( &accel14, &accel_data );

        log_printf( &logger, "  Accel X : %d \r\n", accel_data.x );
        log_printf( &logger, "  Accel Y : %d \r\n", accel_data.y );
        log_printf( &logger, "  Accel Z : %d \r\n", accel_data.z );
        log_printf( &logger, "--------------------- \r\n" );
        Delay_ms( 1000 );
    }
} 

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Accel14

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
