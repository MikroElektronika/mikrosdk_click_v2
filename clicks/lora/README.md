\mainpage Main Page
 
---
# LoRa click

LoRa and LoRa 2 clicks are a LoRa® RF technology based SRD transceiver, which operates at a sub-gigahertz frequency. This click board™ features an embedded LoRaWAN® Class A compliant stack, providing a long-range spread spectrum communication, with high interference immunity.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/grupe/lora-click-group.png" height=300px>
</p>

[click Product page 1](https://www.mikroe.com/lora-rf-click)

[click Product page 2](https://www.mikroe.com/lora-2-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jul 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the LoRa Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LoRa Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lora_cfg_setup ( lora_cfg_t *cfg ); 
 
- Initialization function.
> LORA_RETVAL lora_init ( lora_t *ctx, lora_cfg_t *cfg );

- Click Default Configuration function.
> void lora_default_cfg ( lora_t *ctx, bool cb_default, void ( *response_p )( char *response ) );


#### Example key functions :

- Used by parser to send data inside the software buffer. User can send valid
- commands with this function but command string and data should be well formated.
> void lora_cmd ( lora_t *ctx, char *cmd,  char *response );
 
- This function is used for receive message.
> uint8_t lora_rx ( lora_t *ctx, char *window_size, char *response );

- This function is used for sending message.
> uint8_t lora_tx ( lora_t *ctx, char *buffer );

## Examples Description

> This example reads and processes data from LoRa clicks. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver init and LoRa init.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lora_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lora_cfg_setup( &cfg );
    LORA_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lora_init( &lora, &cfg );

    lora_default_cfg( &lora, 0, &lora_cbk );

    lora_cmd( &lora, LORA_CMD_SYS_GET_VER, &tmp_txt[ 0 ] );

    lora_cmd( &lora, LORA_CMD_MAC_PAUSE,  &tmp_txt[ 0 ] );
    log_printf( &logger, "mac pause\r\n" );
    for ( cnt = 0; cnt < 10; cnt++ )
    {
        log_printf( &logger, "%c", tmp_txt[ cnt ] );
    }

    log_printf( &logger, "\r\n" );

    lora_cmd( &lora, LORA_CMD_RADIO_SET_WDT, &tmp_txt[ 0 ] );

    log_printf( &logger, "radio set wdt 0\r\n" );
    log_printf( &logger, "%s\r\n", &tmp_txt[ 0 ] );
}
  
```

### Application Task

> The transceiver sends one by one byte in UART which is for the work of the lora,
> the Receiver mode, receives one byte and logs it on usbuart. Receiver mode is default mode.

```c

void application_task ( void )
{
    char *ptr;
    lora_process( );
    
    #ifdef DEMO_APP_RECEIVER
        rx_state = lora_rx( &lora, LORA_ARG_0, &tmp_txt[ 0 ] );
        if ( rx_state == 0 )
        {
            tmp_txt[ 12 ] = 0;
            ptr = ( char* )&int_data;
            hex_to_int( &tmp_txt[ 10 ], ptr );

            log_printf( &logger, "%c", int_data  );
            log_printf( &logger, "\r\n");
        }
    #endif
    
    #ifdef DEMO_APP_TRANSCEIVER
        for ( cnt = 0; cnt < 7; cnt++ )
        {
            send_data = send_message[ cnt ] ;
            int8_to_hex( send_data, send_hex );
            tx_state = lora_tx( &lora, &send_hex[ 0 ] );
            if ( tx_state == 0 )
            {
                log_printf( &logger, "  Response : %s\r\n", &tmp_txt[ 0 ] );
            }
            Delay_1sec();
        }
    #endif
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LoRa

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
