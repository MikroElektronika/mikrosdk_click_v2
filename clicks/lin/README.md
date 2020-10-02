\mainpage Main Page
 
---
# LIN click

The LIN Click is a Click board™ that features the TLE7259-3GE, a LIN transceiver from Infineon Technologies, with integrated wake-up and protection features.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lin_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/lin-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Lin Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Lin Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lin_cfg_setup ( lin_cfg_t *cfg ); 
 
- Initialization function.
> LIN_RETVAL lin_init ( lin_t *ctx, lin_cfg_t *cfg );

#### Example key functions :

- Generic write function.
> void lin_generic_write ( lin_t *ctx, char *data_buf, uint16_t len );
 
- Generic read function.
> uint16_t lin_generic_read ( lin_t *ctx, char *data_buf, uint16_t max_len );

- Function for send command.
> void lin_send_command ( lin_t *ctx, char *command );

## Examples Description

> This example reads and processes data from LIN clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lin_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 9600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lin_cfg_setup( &cfg );
    LIN_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lin_init( &lin, &cfg );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
#ifdef DEMO_APP_RECEIVER
    lin_process( );
#endif    
    
#ifdef DEMO_APP_TRANSMITER
    lin_process( );
    
    if ( send_data_cnt == 5 )
    {
        lin_send_command( &lin, TEXT_TO_SEND );
        lin_process( );
        send_data_cnt = 0;
    }
    else
    {
        send_data_cnt++;
    }
#endif    
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Lin

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
