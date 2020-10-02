
---
# LoRa 3 click

LoRa 3 click is a LoRa® technology-based SRD transceiver, which operates at a sub-gigahertz frequency of 868MHz. Thanks to the spread spectrum modulation feature, as well as the low power consumption, it is capable of achieving a long-range communication, immune to interferences. This click board™ features a complete LoRa® stack onboard: it implements physical, network and MAC layers, allowing for easy operation via the UART interface. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lora3_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/lora-3-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the LoRa3 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LoRa3 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lora3_cfg_setup ( lora3_cfg_t *cfg ); 
 
- Initialization function.
> LORA3_RETVAL lora3_init ( lora3_t *ctx, lora3_cfg_t *cfg );


#### Example key functions :

- Function performs the recovery of EEPROM default values.
> LORA3_RETVAL lora3_factory_reset ( lora3_t *ctx );
 
- Function writes data to EEPROM.
> LORA3_RETVAL lora3_write_eeprom ( lora3_t *ctx, uint8_t address, uint8_t n_bytes, uint8_t *data_in );

- Function performs the transmission of radio frames.
> LORA3_RETVAL lora3_tx_message ( lora3_t *ctx, lora3_tx_msg_t *tx_msg );

## Examples Description

> This example reads and processes data from LoRa 3 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes UART bus driver, sets device (module) as MASTER and enables pairing
> in first case. In second case sets device as END NODE and sends pairing request and 
> message witch causes that MASTER will get indication.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lora3_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lora3_cfg_setup( &cfg );
    LORA3_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lora3_init( &lora3, &cfg );

    Delay_ms( 100 );
    lora3_set_ind_handler( &lora3, indication_handler );
    lora3_hard_reset( &lora3 );
    lora3_factory_reset( &lora3 );
    Delay_ms( 1000 );

    lora3.flag = 0;
    tmp_cnt = 0;
    crc = 0;

#ifdef MASTER
    // Set device as MASTER and enable pairing 
    tmp_msg.pay_load[ 0 ] = 0;

    lora3_write_eeprom( &lora3, 0x00, 1, &tmp_msg.pay_load[ 0 ] );
    if( !lora3.result )
    {
        log_printf( &logger, "EEPROM writting Error\r\n" );
    }
    else
    {
        log_printf( &logger, "EEPROM writting is OK\r\n" );
    }
    Delay_ms( 1000 );
    
    lora3_enable_pairing( &lora3, 1 );
    log_printf( &logger, "Pairing enable\r\n" );
    Delay_ms( 1000 );
#endif

#ifdef END_NODE
    // Set device as END NODE and send pairing request and message
    tmp_msg.pay_load[ 1 ] = 2;
    tmp_msg.pay_load[ 2 ] = 3;
    tmp_msg.pay_load[ 3 ] = 4;
    tmp_msg.pay_load[ 4 ] = 5;

    lora3_get_pairing_request( &lora3 );
    log_printf( &logger, "Pairing request\r\n" );
    Delay_ms( 2000 );
    
    lora3_tx_msg.data_in = &tmp_msg.pay_load[ 1 ];
    lora3_tx_msg.n_bytes = 3;
    lora3_tx_msg.destination_id = 0xFFFFFFFF;
    lora3_tx_msg.option = LORA3_UNCONFIRMED_DATA_TX;

    lora3_tx_message( &lora3, &lora3_tx_msg );
#endif
}
  
```

### Application Task

> Reads the received data and parses it.

```c

void application_task ( void )
{
    lora3_process( );  
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LoRa3

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
