
---
# FT click

FT Click is a compact smart transceiver add-on board that helps you add a Free Topology (FT) interface to any host board with the mikroBUS™ socket. Leveraging FT, the most reliable and easiest-to-scale wired communications media, FT Click lets you network sensors and devices to create IoT solutions for automation and control networks that are easier to develop, integrate and install. This Click board™ supports full communication stacks for LON® and BACnet FT, as well as FTMQ (MQTT like messaging format) on board to simplify integration of BACnet, LON or custom IoT networks over twisted pair wire. FT Click is ideal for markets including smart buildings, cities, machines, agriculture, manufacturing, transportation and many more where wireless communications do not provide the required reliability and scale.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ft_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ft-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Ft Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Ft Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ft_cfg_setup ( ft_cfg_t *cfg ); 
 
- Initialization function.
> FT_RETVAL ft_init ( ft_t *ctx, ft_cfg_t *cfg );



#### Example key functions :

- Use this function for gets current status of data
> uint8_t ft_get_data_status ( ft_t *ctx );
 
- Use this function for read received data
> uint16_t ft_get_data ( ft_t *ctx, uint8_t *data_buf );

- Use this function for send data to other module
> void ft_send_package ( ft_t *ctx, uint8_t *data_buf, uint16_t len, uint8_t queue );

## Examples Description

> This example reads and processes data from FT clicks. 

**The demo application is composed of two sections :**

### Application Init 

> Initialize driver init.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    ft_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    ft_cfg_setup( &cfg );
    FT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ft_init( &ft, &cfg );

  #ifdef DEMO_APP_RECEIVER
        log_printf( &logger, "---------------------------\r\n" );
        log_printf( &logger, "--> CURRENT MODE [ RX ] <--\r\n" );
        log_printf( &logger, "---------------------------\r\n" );
  #endif

  #ifdef DEMO_APP_TRANSMITER
        log_printf( &logger, "---------------------------\r\n" );
        log_printf( &logger, "--> CURRENT MODE [ TX ] <--\r\n" );
        log_printf( &logger, "---------------------------\r\n" );
  #endif
}
  
```

### Application Task

> RX mode : Reads and logs new receive data.
> TX mode : sends (MikroE) data every 1 seconds. 

```c

void application_task ( void )
{
    #ifdef DEMO_APP_RECEIVER
        ft_process(  );
        if ( ft_get_data_status( &ft ) == FT_NEW_DATA_AVAILABLE )
        {
            ft_process(  );
            rsp_data_num = ft_get_data( &ft, &rsp_data_buf[ 0 ] );
            if( rsp_data_num != 0 )
            {
                log_printf( &logger, "---------------------------\r\n" );
                log_printf( &logger, "--> READ: %s\r\n", rsp_data_buf );
                log_printf( &logger, "---------------------------\r\n" );
            }
        }
    #endif

    #ifdef DEMO_APP_TRANSMITER
        log_printf( &logger, "--------------------------\r\n" );
        log_printf( &logger, "-->  SEND MIKROE DATA  <--\r\n" );
        log_printf( &logger, "--------------------------\r\n" );
        ft_send_package( &ft, &MIKROE_DATA_BUF[ 0 ], MIKROE_DATA_BUF_LEN, MIKROE_DATA_QUEUE );
        Delay_ms( 1000 );
    #endif
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Ft

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
