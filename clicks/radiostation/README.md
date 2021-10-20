\mainpage Main Page
 
---
# RadioStation click

RadioStation click is a unique click board™ that can be used to broadcast the music via the FM radio band. It features the Si4713-B30 from Silicon Labs, the best in class integrated FM broadcast stereo transmitter, which operates in the frequency range of 76MHz to 108MHz. It can also broadcast RDS/RDBS data. The click board™ can be equipped with a small FM antenna, which is used to extend the broadcasting range.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/radiostation_click.png" height=300px>
</p>


[click Product page](https://www.mikroe.com/radiostation-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the RadioStation Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for RadioStation Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void radiostation_cfg_setup ( radiostation_cfg_t *cfg ); 
 
- Initialization function.
> RADIOSTATION_RETVAL radiostation_init ( radiostation_t *ctx, radiostation_cfg_t *cfg );

- Click Default Configuration function.
> void radiostation_default_cfg ( radiostation_t *ctx );


#### Example key functions :

- Returns status information about the Audio Signal Quality and current FM transmit frequency. 
 1 byte for return status (same as return value) and 4 bytes for ASQ status.
> uint8_t radiostation_get_asq_status ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint8_t *ret_vals ) ;
 
- Powers up the chip with default settings. This function should be executed before sending any commands to the chip.
> uint8_t radiostation_power_up ( radiostation_t *ctx, radiostation_cmd_t *cmd );

- Returns status information which is set by radiostation_get_tune_measure, radiostation_set_tune_frequency or radiostation_set_tune_power. 1 byte for return status (same as return value) and 7 bytes for tune status.
> uint8_t radiostation_get_tune_status ( radiostation_t *ctx, radiostation_cmd_t *cmd, uint8_t clear_stc_status_bit, uint8_t *ret_vals );

## Examples Description

> RadioStation click can be used to broadcast the music via the FM radio band 
> ( which operates in the frequency range of 76MHz to 108MHz ).

**The demo application is composed of two sections :**

### Application Init 

> Initialization driver enable's - I2C and sets transmit_frequency.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    radiostation_cfg_t cfg;

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

    radiostation_cfg_setup( &cfg, true );
    RADIOSTATION_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    radiostation_init( &radiostation, &cfg );

    radiostation.transmit_frequency = 10000; 
    radiostation.status = 0xFF;

    radiostation_default_cfg( &radiostation, &radiostation_cmd );
}
  
```

### Application Task

> In this example Radio Station Click is receiving signal from audio connector and broadcasting 
> it on 100.00 MHz frequency. 

```c

void application_task ( void )
{
    radiostation_get_asq_status( &radiostation, &radiostation_cmd, &buff[ 0 ] );
    Delay_ms( 50 );
}  

```


The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.RadioStation

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
