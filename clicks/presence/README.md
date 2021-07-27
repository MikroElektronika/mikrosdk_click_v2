\mainpage Main Page
 
 

---
# Presence click

Presence click is an infrared sensing Click board™ which can be used for presence sensing, motion detection, and a remote overtemperature protection. 

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}">
</p>

[click Product page](https://www.mikroe.com/presence-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the Presence Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Presence Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void presence_cfg_setup ( presence_cfg_t *cfg ); 
 
- Initialization function.
> PRESENCE_RETVAL presence_init ( presence_t *ctx, presence_cfg_t *cfg );

- Click Default Configuration function.
> void presence_default_cfg ( presence_t *ctx );


#### Example key functions :

- This function writes general call address and sets slave address.
> void presence_general_call_addr ( presence_t *ctx );
 
- This Function enables , reads and disables the eeprom and then checks whether or not 
- it has successfully read any data from it.
> uint8_t presence_eeprom_process ( presence_t *ctx );

- This function returns object temperature.
> float presence_object_temperature( presence_t *ctx );

## Examples Description

> This application enables usage of sensor for motion and presence sensing 
> and measuring of object's and ambient temperature.


**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init, start eeprom process and configuration chip for measurement.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    presence_cfg_t cfg;

    uint8_t tmp;
    uint8_t w_temp;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    presence_cfg_setup( &cfg );
    PRESENCE_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    presence_init( &presence, &cfg );

    // General call address

    presence_general_call_addr( &presence );
    Delay_1sec( );

    // EEPROM
    
    tmp = presence_eeprom_process( &presence );
    if ( tmp == 0 )
    {
        log_printf( &logger, "----- EEPROM READ OK! ------\r\n" );
    }
    else
    {
        log_printf( &logger, "---- EEPROM READ ERROR! ----\r\n" );
        log_printf( &logger, "----------------------------\r\n" );

        while ( 1 );
    }
    Delay_ms( 2000 );
    w_temp = PRESENCE_INT_MASK1_TP_OT | PRESENCE_INT_MASK1_MOTION | PRESENCE_INT_MASK1_PRESENCE;
    presence_generic_write( &presence, PRESENCE_REG_INTERRUPT_MASK_1, &w_temp, 1 );
    w_temp = PRESENCE_INT_MASK2_TPOT_DIR | PRESENCE_INT_MASK2_SRC_LP1_LP2 | PRESENCE_INT_MASK2_CYCLE_TIME_30ms;
    presence_generic_write( &presence, PRESENCE_REG_INTERRUPT_MASK_2, &w_temp, 1 );
    
    w_temp = PRESENCE_LOW_PASS_TIME_1s;
    presence_generic_write( &presence, PRESENCE_REG_LOW_PASS_TIME_1, &w_temp, 1 );
    
    w_temp = 0x22;
    presence_generic_write( &presence, PRESENCE_REG_TP_PRESENCE_THR, &w_temp, 1 );
    w_temp = 0x0A;
    presence_generic_write( &presence, PRESENCE_REG_TP_MOTION_THR, &w_temp, 1 );
    presence_generic_write( &presence, PRESENCE_REG_TP_OT_THR_1, &w_temp, 1 );
    w_temp = 0x00;
    presence_generic_write( &presence, PRESENCE_REG_TP_OT_THR_2, &w_temp, 1 );
    
    log_printf( &logger, "-------- INIT DONE ---------\r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    Delay_ms( 3000 );
}
  
```

### Application Task

> Check whether a new event (Motion, Presence or Temp threshold exceeded) is detected.

```c

void application_task ( void )
{
    //  Task implementation.

    uint8_t int_status;
    float tamb;
    float tobj;

    presence_generic_read( &presence, PRESENCE_REG_INTERRUPT_STATUS, &int_status, 1 );
    
    tamb = presence_ambient_temperature( &presence );
    log_printf( &logger, "---- Ambient Temperature: %.2f\r\n", tamb );
    Delay_ms( 100 );

    tobj = presence_object_temperature( &presence );
    log_printf( &logger, "---- Object Temperature: %.2f\r\n", tobj );
    Delay_ms( 800 );
        
    if ( ( int_status & 0x08 ) != 0 )
    {
        log_printf( &logger, "--- Presence detected! ---\r\n" );
    }
    else if ( ( int_status & 0x04 ) != 0 )
    {
        log_printf( &logger, "--- Motion detected! ---\r\n" );
    }
    else if ( ( int_status & 0x10 ) != 0 )
    {
        log_printf( &logger, "--- Temp threshold exceeded! ---\r\n" );
    }

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Presence

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
