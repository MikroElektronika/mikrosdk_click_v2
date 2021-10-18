
---
# Water Detect click

Water Detect click is used for detecting water and other electroconductive liquids.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/waterdetect_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/water-detect-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : GPIO type


# Software Support

We provide a library for the WaterDetect Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for WaterDetect Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void waterdetect_cfg_setup ( waterdetect_cfg_t *cfg ); 
 
- Initialization function.
> WATERDETECT_RETVAL waterdetect_init ( waterdetect_t *ctx, waterdetect_cfg_t *cfg );

- Click Default Configuration function.
> void waterdetect_default_cfg ( waterdetect_t *ctx );


#### Example key function :

- Get the status of the water detection function.
> uint8_t waterdetect_get_status ( waterdetect_t *ctx );

## Examples Description

> Water Detect click is used for detecting water and other electroconductive liquids. If the detection area is wet the output of Microchip's MCP606 CMOS op-amp will go positive, signaling the presence of liquid.

**The demo application is composed of two sections :**

### Application Init 

> Initializes GPIO and LOG structures, set INT pins as input and starts to write log.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    waterdetect_cfg_t cfg;

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
    log_info(&logger, "---- Application Init ----");

    //  Click initialization.

    waterdetect_cfg_setup( &cfg );
    WATERDETECT_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    waterdetect_init( &waterdetect, &cfg );
    Delay_100ms();
    
    log_printf( &logger, "  Initialization Driver   \r\n" );
    log_printf( &logger, "------------------------- \r\n" );
    log_printf( &logger, "  Wait to detect water...  \r\n" );
    log_printf( &logger, "------------------------- \r\n" );
}
  
```

### Application Task

> Reads device status and determines if there are water presence or not.

```c

void application_task ( void )
{
    wd_state = waterdetect_get_status( &waterdetect );

    if ( wd_state > wd_state_old )
    {
        log_printf( &logger, " >  Water is detected  < \r\n" );
        log_printf( &logger, "------------------------- \r\n" );
        wd_state_old = 1;
    }

    if ( wd_state < wd_state_old )
    {
        log_printf( &logger, " There is no water \r\n" );
        log_printf( &logger, "------------------- \r\n" );
        wd_state_old = 0;
    }
}

```

## Note

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.WaterDetect

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
