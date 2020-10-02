\mainpage Main Page
 
 

---
# LED Flash click

LED Flash click functions as a high power LED flash, and carries the CAT3224 flash LED driver. The click is designed to run on a 5V power supply.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ledflash_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/led-flash-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the LedFlash Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LedFlash Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ledflash_cfg_setup ( ledflash_cfg_t *cfg ); 
 
- Initialization function.
> LEDFLASH_RETVAL ledflash_init ( ledflash_t *ctx, ledflash_cfg_t *cfg );

#### Example key functions :

- Charge Supercapacitor Enable function
> void ledflash_char_supcap_enable ( ledflash_t *ctx );
 
- Flash Enable function
> void ledflash_flash_enable ( ledflash_t *ctx );

- Check Flash Ready Flag function
> uint8_t ledflash_flash_rdy_flag ( ledflash_t *ctx );

## Examples Description

> This application switching on and off led flash.

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enables GPIO, starts write log and issues a warning. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ledflash_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ledflash_cfg_setup( &cfg );
    LEDFLASH_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ledflash_init( &ledflash, &cfg );
    Delay_ms( 100 );
    
    log_printf( &logger, "----------------------------------\r\n" );
    log_printf( &logger, " LED Flash Click \r\n" );
    log_printf( &logger, "----------------------------------\r\n" );
    log_printf( &logger, "/////////////////\r\n" );
    log_printf( &logger, " WARNING!!! \r\n" );
    log_printf( &logger, " DO NOT LOOK \r\n" );
    log_printf( &logger, " INTO THE LEDS, \r\n" );
    log_printf( &logger, " WHILE THAY ARE ON!!! \r\n" );
    log_printf( &logger, "/////////////////\r\n" );
    Delay_ms( 1000 );
}
  
```

### Application Task

> This example demonstrates the use of LED Flash Click board by flashing
> with LEDs when ever supercapacitor is at a full voltage.

```c

void application_task (  )
{
    uint8_t state;
    
    log_printf( &logger, " Charge Supercapacitor Enable \r\n" );
    ledflash_char_supcap_enable( &ledflash );
    Delay_ms( 1000 );
    state = ledflash_flash_rdy_flag( &ledflash );

    if ( state == 0 )
    {
        log_printf( &logger, " Flash ON! \r\n" );
        ledflash_flash_enable( &ledflash );
    }
    else
    {
        log_printf( &logger, " Flash OFF! \r\n" );
        ledflash_flash_disable( &ledflash );
    }
    log_printf( &logger, "----------------------------------\r\n" );
}

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LedFlash

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
