\mainpage Main Page
 
---
# LTE Cat.1 click

LTE Cat.1-EU click is a Click board™ based on Thales Cinterion® ELS61 wireless module that delivers highly efficient Cat 1 LTE connectivity.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ltecat1eu_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/lte-cat1-eu-click-for-europe>)

[click Product page](<https://www.mikroe.com/lte-cat1-us-click-for-united-states>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the LteCat1 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LteCat1 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ltecat1_cfg_setup ( ltecat1_cfg_t *cfg ); 
 
- Initialization function.
> LTECAT1_RETVAL ltecat1_init ( ltecat1_t *ctx, ltecat1_cfg_t *cfg );

#### Example key functions :

- Generic read function.
> uint16_t ltecat1_generic_read ( ltecat1_t *ctx, char *data_buf, uint16_t max_len );
 
- Function for send command.
> void ltecat1_send_command ( ltecat1_t *ctx, char *command );

- Generic parser function.
> char *ltecat1_gps_parser ( char *data_in, char *cmd, uint8_t data_pos );

## Examples Description

> This example reads and processes data from LTE Cat.1 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and power module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ltecat1_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ltecat1_cfg_setup( &cfg );
    LTECAT1_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ltecat1_init( &ltecat1, &cfg );

    Delay_ms( 100 );

    log_printf( &logger, "-------------------- \r\n" );
    log_printf( &logger, "  LTE Cat. 1 Click   \r\n" );
    log_printf( &logger, "-------------------- \r\n" );
    
    Delay_ms( 100 );

    ltecat1_module_power( &ltecat1, 1 );

    ltecat1_send_command( &ltecat1, LTECAT1_AT );
    ltecat1_process( );
    Delay_ms( 2000 );
    ltecat1_send_command( &ltecat1, LTECAT1_AT );
    ltecat1_process( );
    Delay_ms( 2000 );
    ltecat1_send_command( &ltecat1, LTECAT1_AT );
    ltecat1_process( );
    Delay_ms( 2000 );
    ltecat1_send_command( &ltecat1, LTECAT1_ATE );
    ltecat1_process( );
    Delay_ms( 2000 );
    ltecat1_send_command( &ltecat1, LTECAT1_AT_CREG );
    ltecat1_process( );
    Delay_ms( 2000 );

    ltecat1_send_command( &ltecat1, LTECAT1_ATI );
    ltecat1_process( );
    Delay_ms( 1000 );
    ltecat1_send_command( &ltecat1, LTECAT1_AT_CREG );
    ltecat1_process( );
    Delay_ms( 1000 );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{   
    ltecat1_process( );
    if ( send_data_cnt == 5 )
    {
       ltecat1_send_command( &ltecat1, LTECAT1_ATH );
       ltecat1_process( );
       send_data_cnt = 0;
    }
    send_data_cnt++;
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LteCat1

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
