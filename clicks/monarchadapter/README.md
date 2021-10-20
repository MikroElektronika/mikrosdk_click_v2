\mainpage Main Page
 
---
# Monarch Adapter click

The Monarch Adapter Click is used to connect a compatible Monarch Go LTE-M modems from Sequanse to your development board or prototype device.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/monarchadapter_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/monarch-adapter-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART type


# Software Support

We provide a library for the MonarchAdapter Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for MonarchAdapter Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void monarchadapter_cfg_setup ( monarchadapter_cfg_t *cfg ); 
 
- Initialization function.
> MONARCHADAPTER_RETVAL monarchadapter_init ( monarchadapter_t *ctx, monarchadapter_cfg_t *cfg );

#### Example key functions :

- Get INT pin state.
> uint8_t monarchadapter_get_int_pin ( monarchadapter_t *ctx );
 
- Get RNG ( an ) pin state.
> uint8_t monarchadapter_get_rng_pin ( monarchadapter_t *ctx );

- Function for send command.
> void monarchadapter_send_command ( monarchadapter_t *ctx, char *command );

## Examples Description

> This example reads and processes data from Monarch Adapter clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and checks the module firmware revision.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    monarchadapter_cfg_t cfg;

    /** 
     * Logger initialization.
     * Default baud rate: 115200
     * Default log level: LOG_LEVEL_DEBUG
     * @note If USB_UART_RX and USB_UART_TX 
     * are defined as HAL_PIN_NC, you will 
     * need to define them manually for log to work. 
     * See @b LOG_MAP_USB_UART macro definition for detailed explanation.
     */
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    monarchadapter_cfg_setup( &cfg );
    MONARCHADAPTER_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    monarchadapter_init( &monarchadapter, &cfg );

    monarchadapter_power_on( &monarchadapter );
    
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_AT );
    monarchadapter_process( );
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_ATE1 );
    monarchadapter_process( );
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_ATI );
    monarchadapter_process( );
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_ATI1 );
    monarchadapter_process( );
}
  
```

### Application Task

> Checks EPS Network Registration Status (+CEREG) every 3 seconds.

```c

void application_task ( void )
{
    monarchadapter_send_command( &monarchadapter, MONARCH_CMD_CEREG );
    monarchadapter_process( );
    Delay_ms( 3000 );
}

```

## Note

> Monarch GO and Monarch GO-GPS are certified for use on the Verizon network (LTE band 13) 
> with roadmap for global band support. Monarch module is not delivered as part of 
> the Click board package. For more information about module features please read 
> Monarch GO module specification.

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.MonarchAdapter

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
