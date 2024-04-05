\mainpage Main Page
 
---
# Spectral 3 click

Spectral 3 click is a multispectral sensing device, which uses the state-of-the-art sensor IC for a very accurate near-IR (NIR) sensing.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/spectral3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/spectral-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the Spectral3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Spectral3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void spectral3_cfg_setup ( spectral3_cfg_t *cfg ); 
 
- Initialization function.
> SPECTRAL3_RETVAL spectral3_init ( spectral3_t *ctx, spectral3_cfg_t *cfg );

#### Example key functions :

- Reset module.
> void spectral3_module_reset ( spectral3_t *ctx );
 
- Send command.
> void spectral3_send_command ( spectral3_t *ctx, char *command );

- Read raw X, Y, Z and NIR data as well as two special internal registers D, & C.
> void spectral3_get_data ( char *rsp, uint16_t *c_data );

## Examples Description

> This example reads and processes data from Spectral 3 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and configures the sensor.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    spectral3_cfg_t cfg;

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

    spectral3_cfg_setup( &cfg );
    SPECTRAL3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    spectral3_init( &spectral3, &cfg );

    spectral3_module_reset( &spectral3 );
    Delay_ms ( 500 );
    
    log_printf( &logger, "Configuring the sensor...\r\n" );
    spectral3_send_command( &spectral3, SPECTRAL3_CMD_AT );
    spectral3_process( );
    spectral3_send_command( &spectral3, SPECTRAL3_CMD_GAIN );
    spectral3_process( );
    spectral3_send_command( &spectral3, SPECTRAL3_CMD_MODE );
    spectral3_process( );
    log_printf( &logger, "The sensor has been configured!\r\n" );
    Delay_ms ( 1000 );
}
  
```

### Application Task

> Reads the values of all 6 channels and parses it to the USB UART each second.

```c

void application_task ( void )
{
    parser_application( );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Spectral3

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
