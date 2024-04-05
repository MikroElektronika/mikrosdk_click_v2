
---
# Balancer 2 click

Balancer 2 Click is an overvoltage protection device for a 2-series cell lithium-ion battery. Click contains two separate overvoltage battery detection circuits and automatic cell imbalance correction.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/balancer2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/balancer-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Feb 2020.
- **Type**          : SPI type


# Software Support

We provide a library for the Balancer2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Balancer2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void balancer2_cfg_setup ( balancer2_cfg_t *cfg ); 
 
- Initialization function.
> BALANCER2_RETVAL balancer2_init ( balancer2_t *ctx, balancer2_cfg_t *cfg );

- Click Default Configuration function.
> void balancer2_default_cfg ( balancer2_t *ctx );


#### Example key functions :

- Function for getting real battery lvl.
> float balancer2_get_batttery_lvl ( balancer2_t *ctx, uint8_t bat_num );
 
- Function for converting adc value to mV.
> float balancer2_adc_to_mv ( balancer2_t *ctx, uint16_t adc_val );

- Function for reading adc value.
> uint16_t balancer2_read_adc ( balancer2_t *ctx, uint8_t cmd_byte );


## Examples Description

> This application enable the batery charge. 

**The demo application is composed of two sections :**

### Application Init 

> Sets reference volatage of device, sets pins for supply and cells to high.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    balancer2_cfg_t cfg;

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

    balancer2_cfg_setup( &cfg );
    BALANCER2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    balancer2_init( &balancer2, &cfg );

    Delay_ms ( 100 );
    log_printf( &logger, "--------------------\r\n" );
    log_printf( &logger, "  Balancer 2 Click  \r\n" );
    log_printf( &logger, "--------------------\r\n" );
    Delay_ms ( 100 );
    balancer2_default_cfg ( &balancer2 );
    Delay_ms ( 100 );
}
  
```

### Application Task

> Every 2 seconds logs readings of battery mV lvl

```c

void application_task ( void )
{
    float battery;

    battery = balancer2_get_batttery_lvl( &balancer2, BALANCER2_BATT1 );
    log_printf( &logger, "Battery 1 : %f mV\r\n", battery );

    battery = balancer2_get_batttery_lvl( &balancer2, BALANCER2_BATT2 );
    log_printf( &logger, "Battery 2 : %f mV\r\n", battery );

    battery = balancer2_get_batttery_lvl( &balancer2, BALANCER2_BATT_BOTH );
    log_printf( &logger, "Batteries : %f mV\r\n", battery );

    log_printf( &logger, "__________________________________________\r\n" );

    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}  

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.Balancer2

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
