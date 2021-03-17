\mainpage Main Page
 
 

---
# Ambient 4 click

Ambient 4 click is a light intensity-sensing and measuring Click board™, which features an accurate, light-intensity sensor labeled as BH1721FVC, made by ROHM Corporation.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ambient4_click.png" height=300px>
</p>


[click Product page](<https://www.mikroe.com/ambient-4-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the Ambient4 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ambient4 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ambient4_cfg_setup ( ambient4_cfg_t *cfg ); 
 
- Initialization function.
> AMBIENT4_RETVAL ambient4_init ( ambient4_t *ctx, ambient4_cfg_t *cfg );

- Click Default Configuration function.
> void ambient4_default_cfg ( ambient4_t *ctx );


#### Example key functions :

- Function for send command.
> void ambient4_send_command ( ambient4_t *ctx, uint8_t cmd );
 
- Function for read 16bit data.
> uint16_t ambient4_read_data ( ambient4_t *ctx );

- Function for device reset.
> void ambient4_device_reset ( ambient4_t *ctx );

## Examples Description

> This application is a light intensity-sensing and measuring.

**The demo application is composed of two sections :**

### Application Init 

> Initialization device and power ON chip and set resolution mode. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ambient4_cfg_t cfg;

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    
    log_info(&logger, "|-----Application init -----|");

    ambient4_cfg_setup( &cfg );
    AMBIENT4_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ambient4_init( &ambient4, &cfg );
    ambient4_default_cfg ( &ambient4 );
}
  
```

### Application Task

> Read ambient light in [lx] and logs data to USBUART every 1 sec. 

```c

void application_task ( void )
{
    uint16_t read_value;

    //  Task implementation.
    
    read_value = ambient4_read_data( &ambient4 );
    
    log_printf( &logger, " Ambient light: %d \r\n", read_value );

    Delay_ms( 1000);
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ambient4

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
