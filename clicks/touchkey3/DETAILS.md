
---
# TouchKey 3 click

There are many kinds of touch sensors on the market, but every one of them has some unique features that make it stand out from the crowd. TouchKey 3 click is equipped with seven advanced capacitive sensors, based on the proprietary QTouch® technology. Besides quite a large number of QTouch® capacitive sensor channels, TouchKey 3 click also offers some additional features, such as the Adjacent Key Suppression (AKS®), a technology that ensures correct button press, even when the touch sensing pads are placed close to each other.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/touchkey3_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/touchkey-3-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Dec 2019.
- **Type**          : SPI type


# Software Support

We provide a library for the TouchKey3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for TouchKey3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void touchkey3_cfg_setup ( touchkey3_cfg_t *cfg ); 
 
- Initialization function.
> TOUCHKEY3_RETVAL touchkey3_init ( touchkey3_t *ctx, touchkey3_cfg_t *cfg );

- Click Default Configuration function.
> void touchkey3_default_cfg ( touchkey3_t *ctx );


#### Example key functions :

- Function executes one of the possible commands.
> uint8_t touchkey3_send_command ( touchkey3_t *ctx, uint8_t command );
 
- Function sends a request command, and returns the response.
> uint8_t touchkey3_send_request ( touchkey3_t *ctx, uint8_t request, uint8_t * p_response );

- Function reads from a selected configuration register.
> uint8_t touchkey3_get_data ( uint8_t data_address, uint8_t * read_data );

## Examples Description

> This click uses 7 capacitive sensing channels, with the #CHANGE pin routed to the INT pin of the mikroBUS™, so that an interrupt can be triggered if any of the sensors detect a touch event. This can be used to trigger an SPI read cycle only when the key is actually pressed, avoiding the need for constant polling of the sensor registers.

**The demo application is composed of two sections :**

### Application Init 

> Initializes click driver and performs a soft reset of the click.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    touchkey3_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    touchkey3_cfg_setup( &cfg );
    TOUCHKEY3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    touchkey3_init( &touchkey3, &cfg );

    touchkey3_send_command( &touchkey3, TOUCHKEY3_CMD_RESET );
}
  
```

### Application Task

> Reads the status of the keys, and outputs a message if a key is touched.

```c

void application_task ( void )
{ 
    touchkey3_send_request( &touchkey3, TOUCHKEY3_REQ_ALL_KEYS, &return_data );

    for ( counter = 0; counter < 7; counter++ )
    {
        if ( ( return_data[ 1 ] >> counter ) & 0x01 )
        {
            log_info( &logger, "Touch detected on key " );
            //Converts the key index into ascii character ( 0 - 7 -> '1' - '7')
            temp = counter + 49;
            log_info( &logger, "%d\r\n", temp );
            Delay_ms( 1000 );
        }
    }
    Delay_ms( 200 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.TouchKey3

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
