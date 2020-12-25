\mainpage Main Page
 
---
# OOK TX click

OOK TX click is a simple wireless transmitter that operates at the frequency of 433MHz (sub-GHz). This device allows realization of a simple, low-speed wireless ad-hoc communication network between a transmitter and compatible receiver, such as the OOK RX click.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ooktx_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/ook-tx-click>)

---

#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jan 2020.
- **Type**          : GPIO type

# Software Support

We provide a library for the OOKTX Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for OOKTX Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void ooktx_cfg_setup ( ooktx_cfg_t *cfg ); 
 
- Initialization function.
> OOKTX_RETVAL ooktx_init ( ooktx_t *ctx, ooktx_cfg_t *cfg );

- Click Default Configuration function.
> void ooktx_default_cfg ( ooktx_t *ctx );


#### Example key functions :

- This function initiates the OOK communication.
> void ooktx_communication_init ( ooktx_t *ctx, uint8_t calibration, 
                                  uint8_t configuration, uint16_t cfg_settings );
 
- This function stops the OOK communication.
> void ooktx_communication_stop ( ooktx_t *ctx );

- This function transmits data in the OOK communication.
> void ooktx_communication_transmit ( ooktx_t *ctx, uint8_t transmit_data );

## Examples Description

> This example showcases how to initialize and use the OOK TX click. The click encodes information
  using the On-Off Keying modulation, embeds it in a 433 MHz radio signal and acts as a transmitter
  for this signal. The OOK RX click should play the role of the receiver in this communication.

**The demo application is composed of two sections :**

### Application Init 

> This function initializes and configures the logger and click modules. 

```c

void application_init ( )
{
    log_cfg_t log_cfg;
    ooktx_cfg_t cfg;

    //  Logger initialization.

    log_cfg.level = LOG_LEVEL_DEBUG;
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info(&logger, "Application Init");

    //  Click initialization.

    ooktx_cfg_setup( &cfg );
    OOKTX_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    ooktx_init( &ooktx, &cfg );
    Delay_100ms( ); 
    
    tx_index = 0;
#ifdef BYTE_TRANSMIT
    log_info(&logger, "Application Task\r\n BYTE TRANSMIT DEMO");
#endif
    
#ifdef DATA_TRANSMIT
    log_info(&logger, "Application Task\r\n DATA TRANSMIT DEMO");
#endif
}
  
```

### Application Task

> This application consists 2 types:
>  - BYTE_TRANSMIT: Transmiting one by one byte of data
>  - DATA_TRANSMIT: Transmiting package of data ( 6 bytes in this example )

```c

void application_task ( )
{
    uint8_t cnt;
    
    ooktx_communication_init ( &ooktx, OOKTX_CALIBRATION_ENABLE, OOKTX_CONFIGURATION_ENABLE,
                                       OOKTX_CFG_DEFAULT );
    for ( cnt = 0; cnt < 8; cnt++ )
    {
        ooktx_communication_transmit ( &ooktx, OOKTX_PREAMBULE );
    }
#ifdef BYTE_TRANSMIT
    ooktx_transmit_byte( &ooktx, 0xCE35, tx_data[ tx_index ] );
    tx_index++;
    if ( tx_data[ tx_index ] == '\0' )
        tx_index = 0;
#endif
    
#ifdef DATA_TRANSMIT
    ooktx_transmit_data( &ooktx, 0xCE35, tx_data, 6 );
#endif

    ooktx_communication_stop( &ooktx );
    
#ifdef BYTE_TRANSMIT
    Delay_ms ( 100 );
#endif
    
#ifdef DATA_TRANSMIT
    Delay_ms ( 2000 );
#endif
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.OOKTX

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
