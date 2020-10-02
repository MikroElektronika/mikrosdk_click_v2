\mainpage Main Page
 
---
# ATA663254 click

ATA663254 click is a fully integrated LIN transceiver device with an integrated 5V LDO voltage regulator.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/ata663254.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/ata663254-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : feb 2020.
- **Type**          : UART type


# Software Support

We provide a library for the Ata663254 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ata663254 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ata663254_cfg_setup ( ata663254_cfg_t *cfg ); 
 
- Initialization function.
> ATA663254_RETVAL ata663254_init ( ata663254_t *ctx, ata663254_cfg_t *cfg );

#### Example key functions :

- Chip enable function.
> void ata663254_enable ( ata663254_t *ctx, uint8_t state );
 
- Undervoltage detect function.
> uint8_t ata663254_get_rst_state ( ata663254_t *ctx );

## Examples Description

> This application is the combination of voltage regulator and bus transceiver.

**The demo application is composed of two sections :**

### Application Init 

> Initializes click driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ata663254_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ata663254_cfg_setup( &cfg );
    ATA663254_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ata663254_init( &ata663254, &cfg );
}
  
```

### Application Task

> Checks if new data byte have received in rx buffer (ready for reading), 
  and if ready than reads one byte from rx buffer.

```c

void application_task ( void )
{    
    ata663254_data_t tmp;
    
    //  Task implementation.
    
#ifdef DEMO_APP_RECEIVER

       // RECEIVER - UART polling

       tmp =  ata663254_generic_single_read( &ata663254 );
       log_write( &logger, &tmp, LOG_FORMAT_BYTE );
#endif
#ifdef DEMO_APP_TRANSMITER

       // TRANSMITER - TX each 2 sec
       
       ata663254_generic_multi_write( &ata663254, demo_message, 9 );
       Delay_ms( 2000 );
#endif

}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ata663254

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
