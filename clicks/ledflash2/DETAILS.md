

---
# Led Flash 2 click

LED Flash 2 click is a powerful flash/torch click, featuring the MIC2870 from Microchip, a high-efficiency flash LED driver, optimized for driving one or two high-brightness camera flash LEDs.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ledflash2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/led-flash-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : I2C type


# Software Support

We provide a library for the LedFlash2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LedFlash2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ledflash2_cfg_setup ( ledflash2_cfg_t *cfg ); 
 
- Initialization function.
> LEDFLASH2_RETVAL ledflash2_init ( ledflash2_t *ctx, ledflash2_cfg_t *cfg );

- Click Default Configuration function.
> void ledflash2_default_cfg ( ledflash2_t *ctx );


#### Example key functions :

- This function reads raw data from any register.
> uint8_t ledflash2_read_register ( ledflash2_t *ctx, uint8_t reg_address );
 
- This function writes data into any register.
> void ledflash2_write_register ( ledflash2_t *ctx, uint8_t reg_address, uint8_t reg_data );

- This function will set the flash inhibit pin to either 1 or 0. It should be
- used when click is in flash mode, to reduce the flash intensity.
> void ledflash2_toggle_flash_inhibit ( ledflash2_t *ctx, uint8_t pin_state );

## Examples Description

> This app demonstrate flash and torch mode on LED light.

**The demo application is composed of two sections :**

### Application Init 

> Initializes device and sets the click into "OFF" mode.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ledflash2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ledflash2_cfg_setup( &cfg );
    LEDFLASH2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ledflash2_init( &ledflash2, &cfg );

    ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_OFF, 0, 0 );
    log_printf( &logger, "Initialized...\r\n" );
}
  
```

### Application Task

> This function will demonstrate how to use the flash mode,
> and the torch mode, with different power settings. 
> It will then turn the click off.

```c

void application_task ( void )
{
    Delay_ms( 1000 );
    log_printf( &logger, "Do not look directly into the led lights.\r\n" );
    log_printf( &logger, "Triggering flash in 5...\r\n" );
    Delay_ms( 1000 );
    log_printf( &logger, "4...\r\n" );
    Delay_ms( 1000 );
    log_printf( &logger, "3...\r\n" );
    Delay_ms( 1000 );
    log_printf( &logger, "2...\r\n" );
    Delay_ms( 1000 );
    log_printf( &logger, "1...\r\n" );
    Delay_ms( 1000 );
    log_printf( &logger, "Cheese!\r\n" );

    ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_FLASH, LEDFLASH2_CUR_50, LEDFLASH2_FTMR_312 );
    Delay_ms( 350 );
    ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_OFF, 0, 0 );
    Delay_ms( 2000 );
    
    log_printf( &logger, "Switching to the torch mode in a moment...\r\n" );
    Delay_ms( 2000 );
    ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_TORCH, LEDFLASH2_CUR_100, 0 );
    Delay_ms( 3000 );
    log_printf( &logger, "Dimming the torch light...\r\n" );
    
    for ( uint8_t cnt = LEDFLASH2_CUR_100; cnt <= LEDFLASH2_CUR_18; cnt++ )
    {
        ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_TORCH, cnt, 0 );
        Delay_ms( 500 );
    }
    Delay_ms( 1000 );
    log_printf( &logger, "Switching off...\r\n" );
    ledflash2_set_mode( &ledflash2, LEDFLASH2_MODE_OFF, 0, 0 );
    log_printf( &logger, "------------------------------------------------\r\n" );
}
 

```

## Note

> LED lights can be very bright, even on lowest power settings.
> Avoid looking directly into the light when click is in operation.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LedFlash2

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
