
---
# Nano LoRa click

Nano LoRa Click is a LoRa® technology-based transceiver Click board™, which operates at a sub-gigahertz frequency of 815MHz and 928 MHz Bands, optimized for very long-range, low consumption applications, suitable for LPWA networks. Thanks to the spread spectrum modulation feature, as well as the low power consumption, it is capable of achieving a long-range communication, immune to interferences. Operated over the UART interface, it represents a very simple, yet powerful solution for the LoRa-based IoT communication network solution.

<p align="center">
  <img src="@{CLICK_IMAGE_LINK}" height=300px>
</p>

[click Product page](https://www.mikroe.com/nano-lora-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the NanoLora Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](http://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](http://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for NanoLora Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void nanolora_cfg_setup ( nanolora_cfg_t *cfg ); 
 
- Initialization function.
> NANOLORA_RETVAL nanolora_init ( nanolora_t *ctx, nanolora_cfg_t *cfg );

- Click Default Configuration function.
> void nanolora_default_cfg ( nanolora_t *ctx );


#### Example key functions :

- The function the send data command depends on the network protocol chosen.
> void nanolora_send_data ( nanolora_t *ctx, uint8_t *tx_data, uint8_t length );
 
- The function read response bytes from the device and sets flag after each received byte.
> void nanolora_uart_isr ( nanolora_t *ctx, uint8_t reader_hdlr );

- The function check if the response is ready.
> uint8_t nanolora_rsp_rdy ( nanolora_t *ctx );

## Examples Description

> This example reads and processes data from Nano LoRa clicks. 

**The demo application is composed of two sections :**

### Application Init 

> Initializes UART serial interface, UART interrupt, and power ON the module.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    nanolora_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 57600;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    nanolora_cfg_setup( &cfg );
    NANOLORA_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    nanolora_init( &nanolora, &cfg );

    nanolora_default_cfg( &nanolora );

    log_printf( &logger,  "--  Nano LoRa Click --\r\n" );
    log_printf( &logger,  " Initialization  done \r\n" );
    log_printf( &logger,  "----------------------\r\n" );

    #ifdef TRANSMITTER
    
        log_printf( &logger,  "----  TRANSMITER  ----\r\n" );

    #endif

    #ifdef RECEIVER
    
        log_printf( &logger,  "-----  RECEIVER  -----\r\n" );

    #endif

    log_printf( &logger, "----------------------\r\n" ); 
    Delay_ms( 2000 );
}
  
```

### Application Task

> This function has two segments.
> The first segment allows user to enter a commands, module configurations,
> data which will be transmitted, and also to check all module and connection
> status by using the serial terminal.
> Special commands:
> Press 'Enter' when you want to send the entered command (data).
> Press 'Backspace' to delete the wrong entered character before you send the
> command.
> Press 'Up-Down' or 'Left-Right' to see and enter a 3 last sent commands.
> Press 'Esc' and then 'r' character to perform a hardware reset via RST pin.
> The second segment allows user to read and check response from the SIM868
> module when the response is ready. 

```c

void application_task ( void )
{    
    #ifdef RECEIVER

    nanolora_process( );
    application_handler( );
        
    #endif

    #ifdef TRANSMITTER

    nanolora_send_data( &nanolora, &demo_text[ 0 ], 6 );
    Delay_ms( 2000 );

    #endif
}

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.NanoLora

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART click](http://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](http://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](http://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](http://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
