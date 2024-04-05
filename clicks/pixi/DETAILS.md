
---
# Pixi click

PIXI™ click is equipped with MAX11300 IC from Maxim Integrated, which features Maxim Integrated's versatile, proprietary PIXI™ technology - it is the industry's first configurable 20-channel mixed-signal data converter. Besides the 12bit multichannel SAR ADC and buffered DAC, it also features one internal and two external temperature sensors for tracking the junction and the environmental temperatures.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/pixi_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/pixi-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Pixi Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Pixi Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void pixi_cfg_setup ( pixi_cfg_t *cfg ); 
 
- Initialization function.
> PIXI_RETVAL pixi_init ( pixi_t *ctx, pixi_cfg_t *cfg );

- Click Default Configuration function.
> void pixi_default_cfg ( pixi_t *ctx );


#### Example key functions :

- This function writes data to the click module.
> uint8_t pixi_write_reg ( pixi_t *ctx, const uint8_t reg_addr, uint32_t reg_data );
 
- This function reads data from the click module.
> uint8_t pixi_read_reg ( pixi_t *ctx, const uint8_t reg_addr, uint32_t *reg_data );

## Examples Description

> This example showcases how to initialize, configure and use the Pixi click moduel. The click
  features Maxim Integrated's versatile, proprietary PIXI™ technology - the industry's first
  configurable 20-channel mixed-signal data converter. 

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the click and logger modules. After the initial setup
  a device id check is performed which will stop the module if the check fails. Additional con-
  figurating is done in the default_cfg(...) function. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    pixi_cfg_t cfg;
    uint32_t res;

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
    Delay_100ms( );

    //  Click initialization.

    pixi_cfg_setup( &cfg );
    PIXI_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    pixi_init( &pixi, &cfg );

    //  Device ID check.

    pixi_read_reg( &pixi, PIXI_REG_DEVICE_ID, &res );
    if ( res != 1060 )
    {
        log_printf( &logger, "ERROR : WRONG DEVICE ID!\r\n" );
        for( ; ; );
    }
    else
    {
        log_printf( &logger, "Driver Init - DONE!\r\n" );
    }

    //  Default configuration.

    pixi_default_cfg( &pixi );
}
  
```

### Application Task

> This function sets the output signal on port 0 to different values every second. 

```c

void application_task ( void )
{
    pixi_write_reg( &pixi, PIXI_REG_GPO_DATA, 1 );
    Delay_ms ( 1000 );
    pixi_write_reg( &pixi, PIXI_REG_GPO_DATA, 0 );
    Delay_ms ( 1000 );
}
  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Pixi

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
