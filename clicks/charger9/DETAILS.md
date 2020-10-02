
---
# Charger 9 click

Charger 9 click is a Li-Ion (Li+, Li-Po) battery charger, capable of charging one, two or three battery cells. It is based on the MAX1757, an integrated Li+ battery charger with many features that allow safe and reliable charging.

<p align="center">
  <img src="http://download.mikroe.com/images/click_for_ide/charger9_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/charger-9-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the Charger9 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Charger9 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void charger9_cfg_setup ( charger9_cfg_t *cfg ); 
 
- Initialization function.
> CHARGER9_RETVAL charger9_init ( charger9_t *ctx, charger9_cfg_t *cfg );


#### Example key functions :

- Enable function
> CHARGER9_RETVAL charger9_enable ( charger9_t *ctx, CHARGER9_STATE pwr_state );
 
- Fast-Charge Indicate function
> CHARGER9_RETVAL charger9_fast_charge_ind ( charger9_t *ctx );

- Full-Charge Indicate function
> CHARGER9_RETVAL charger9_full_charge_ind ( charger9_t *ctx );

## Examples Description

> This application is battery charger, capable of charging one, two or three battery cells. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO driver and turns OFF the charger as initial state.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    charger9_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    charger9_cfg_setup( &cfg );
    CHARGER9_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    charger9_init( &charger9, &cfg );
    
    charger9_enable( &charger9, CHARGER9_DISABLE );
    en_flag = CHARGER9_DISABLE;
    Delay_ms( 100 );
    
    log_printf( &logger, "** Charger 9 initialization done ** \r\n" );
}
  
```

### Application Task

> Checks which command was sent by user and performs the selected command.
> Also checks the fault condition, and when fault condition is detected sends a report message to the uart terminal 
> and turns OFF the charger. 

```c

void application_task ( )
{   
    CHARGER9_RETVAL charge_state;
    
    if ( en_flag == CHARGER9_DISABLE )
    {
        charger9_enable( &charger9, CHARGER9_ENABLE );
        en_flag = CHARGER9_ENABLE;
        
        log_printf( &logger, "** Charger 9 is enabled ** \r\n" );
    }
    else
    {
        log_printf( &logger, "** Charger 9 is already enabled ** \r\n" );
    }

    if ( en_flag == CHARGER9_ENABLE )
    {
        charger9_enable( &charger9, CHARGER9_DISABLE );
        en_flag = CHARGER9_DISABLE;

        log_printf( &logger, "** Charger 9 is disabled ** \r\n" );
    }
    else
    {
        log_printf( &logger, "** Charger 9 is already disabled ** \r\n" );
    }

    charge_state = charger9_full_charge_ind( &charger9 );
                
    if ( charge_state == CHARGER9_IND_ACTIVE )
    {
        log_printf( &logger, "** Full-Charge state ** \r\n" );
    }
    
    charge_state = charger9_fast_charge_ind( &charger9 );
    if ( charge_state == CHARGER9_IND_ACTIVE )
    {
        log_printf( &logger, "** Fast-Charge state ** \r\n" );
    }

    charge_state = charger9_fault_ind ( &charger9 );
    
    if ( charge_state == CHARGER9_IND_ACTIVE )
    {
        charger9_enable( &charger9, CHARGER9_DISABLE );
        en_flag = CHARGER9_DISABLE;
        
        log_printf( &logger, "** Fault condition! ** \r\n" );
        log_printf( &logger, "** Charger 9 is disabled ** \r\n" );
    }
}

```

## Note

> When user sends a desired command to the charger, a report message will be sent to the uart terminal as 
> indication to the user.
> The possible commands, for Charger 9 control, will be written to the uart terminal.
> The alarm sound will be generated on the determined commands: enable, disable and fault condition detecting.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Charger9

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
