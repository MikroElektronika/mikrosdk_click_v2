\mainpage Main Page
 
---
# LoRa 5 click

LoRa 5 click is a LoRa® technology-based SRD transceiver Click board™, which operates at a sub-gigahertz frequency of 902-928 MHz SRD Band optimized for very long range, low consumption applications, suitable for LPWA networks. Thanks to the spread spectrum modulation feature, as well as the low power consumption, it is capable of achieving a long-range communication, immune to interferences. Operated over the UART interface, it represents a very simple, yet powerful solution for the LoRa-based IoT communication network.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lora5_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/lora-5-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the LoRa5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LoRa5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lora5_cfg_setup ( lora5_cfg_t *cfg ); 
 
- Initialization function.
> LORA5_RETVAL lora5_init ( lora5_t *ctx, lora5_cfg_t *cfg );


#### Example key functions :

- This command allows user to get the 32bit firmware version.
> void lora5_get_fw_version_cmd ( lora5_t *ctx );
 
- This command allows user to get the 32bit Mipot serial number.
> void lora5_get_serial_no_cmd ( lora5_t *ctx );

- This command allows user to get the module current status.
> void lora5_get_session_status_cmd ( lora5_t *ctx );

## Examples Description

> This example reads and processes data from LoRa 5 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes UART interface and UART interrupt, and performs a module reset commands.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lora5_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lora5_cfg_setup( &cfg );
    LORA5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lora5_init( &lora5, &cfg );

    lora5_response_handler_set( &lora5, &make_response );
    Delay_ms( 1000 );

    lora5_reset_cmd( &lora5 );
    wait_response( );
    Delay_ms( 1000 );
    lora5_factory_reset_cmd( &lora5 );
    wait_response( );
    
    log_printf( &logger, "** LoRa 5 (MIPOT 32001409) reset is done **\r\n" );
    log_printf( &logger, "\r\n" );
    Delay_ms( 1000 );
}
  
```

### Application Task

> Performs a group of commands to get FW version, the serial number provided by Mipot,
> DevEUI, the session status, the activation status and the parameters for the selected channel.
> Also sets the next transmission data rate to the desired value.
> The responses from the Mipot module to the host will be sent to the uart terminal.

```c

void application_task ( void )
{
    lora5_process(  );

    log_printf( &logger, "** FW version reading...\r\n" );
    lora5_get_fw_version_cmd( &lora5 );
    wait_response( );
    
    log_printf( &logger, "** Serial number reading...\r\n" );
    lora5_get_serial_no_cmd( &lora5 );
    wait_response( );
    
    log_printf( &logger, "** DevEUI reading...\r\n" );
    lora5_get_dev_eui_cmd( &lora5 );
    wait_response( );
    
    log_printf( &logger, "** Session status reading...\r\n" );
    lora5_get_session_status_cmd( &lora5 );
    wait_response( );
    switch ( response.cmd_data[ 0 ] )
    {
        case 0x00 :
        {
            log_printf( &logger, "Idle.\r\n" );
        break;
        }
        case 0x01 :
        {
            log_printf( &logger, "Busy (LoRa session running).\r\n" );
        break;
        }
        case 0x02 :
        {
            log_printf( &logger, "Device not activated.\r\n" );
        break;
        }
        case 0x03 :
        {
            log_printf( &logger, "Delayed.\r\n" );
        break;
        }
        default :
        {
        break;
        }
    }
    log_printf( &logger, "***********************************************\r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, "** Activation status reading...\r\n" );
    lora5_get_activation_status_cmd( &lora5 );
    wait_response( );
    switch ( response.cmd_data[ 0 ] )
    {
        case 0x00 :
        {
            log_printf( &logger, "Not activated.\r\n" );
        break;
        }
        case 0x01 :
        {
            log_printf( &logger, "Joining...\r\n" );
        break;
        }
        case 0x02 :
        {
            log_printf( &logger, "Joined.\r\n" );
        break;
        }
        case 0x03 :
        {
            log_printf( &logger, "MAC ERROR.\r\n" );
        break;
        }
        default :
        {
        break;
        }
    }
    log_printf( &logger, "***********************************************\r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, "** Next TX Data Rate setting...\r\n" );
    lora5_set_next_dr_cmd( &lora5, LORA5_SF10_125KHZ );
    wait_response( );
    if ( response.cmd_data[ 0 ] == 0x00 )
    {
        log_printf( &logger, "Success!\r\n" );
    }
    else
    {
        log_printf( &logger, "Error!\r\n" );
    }
    log_printf( &logger, "***********************************************\r\n" );
    Delay_ms( 1000 );
    
    log_printf( &logger, "** Channel parameters reading...\r\n" );
    lora5_get_ch_param_cmd( &lora5, LORA5_CH_IDX_15 );
    wait_response( );
    Delay_ms( 10000 );
} 

```

## Note
> <pre>
> ## Additional Function
> - lora5_process ( ) - The general process of collecting presponce 
>                                   that sends a module.
> - make_response - Stores data from the module to the response structure.
> - log_response -  Sends the recevied response from the module to the uart terminal.
> - wait_response - Waits until response from the module was ready and then calls the 
>                 response logging function, or writes the error message on the uart terminal.
> </pre>

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LoRa5

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
