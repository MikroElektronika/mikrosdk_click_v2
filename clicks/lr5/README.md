\mainpage Main Page
 
---
# LR 5 Click

LR 5 Click is a compact add-on board that contains a long-range transceiver. This board features the 32001409, RF technology-based SRD transceiver, which operates at a frequency of 915MHz from Mipot.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lr5_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/lr-5-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the LR5 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LR5 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lr5_cfg_setup ( lr5_cfg_t *cfg ); 
 
- Initialization function.
> LR5_RETVAL lr5_init ( lr5_t *ctx, lr5_cfg_t *cfg );


#### Example key functions :

- This command allows user to get the 32bit firmware version.
> void lr5_get_fw_version_cmd ( lr5_t *ctx );
 
- This command allows user to get the 32bit Mipot serial number.
> void lr5_get_serial_no_cmd ( lr5_t *ctx );

- This command allows user to get the module current status.
> void lr5_get_session_status_cmd ( lr5_t *ctx );

## Examples Description

> This example reads and processes data from LR 5 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes UART interface and UART interrupt, and performs a module reset commands.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lr5_cfg_t cfg;

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

    lr5_cfg_setup( &cfg );
    LR5_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lr5_init( &lr5, &cfg );

    lr5_response_handler_set( &lr5, &make_response );
    Delay_ms ( 1000 );

    lr5_reset_cmd( &lr5 );
    wait_response( );
    Delay_ms ( 1000 );
    lr5_factory_reset_cmd( &lr5 );
    wait_response( );
    
    log_printf( &logger, "** LR 5 (MIPOT 32001409) reset is done **\r\n" );
    log_printf( &logger, "\r\n" );
    Delay_ms ( 1000 );
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
    lr5_process(  );

    log_printf( &logger, "** FW version reading...\r\n" );
    lr5_get_fw_version_cmd( &lr5 );
    wait_response( );
    
    log_printf( &logger, "** Serial number reading...\r\n" );
    lr5_get_serial_no_cmd( &lr5 );
    wait_response( );
    
    log_printf( &logger, "** DevEUI reading...\r\n" );
    lr5_get_dev_eui_cmd( &lr5 );
    wait_response( );
    
    log_printf( &logger, "** Session status reading...\r\n" );
    lr5_get_session_status_cmd( &lr5 );
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
            log_printf( &logger, "Busy (LR session running).\r\n" );
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
    Delay_ms ( 1000 );
    
    log_printf( &logger, "** Activation status reading...\r\n" );
    lr5_get_activation_status_cmd( &lr5 );
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
    Delay_ms ( 1000 );
    
    log_printf( &logger, "** Next TX Data Rate setting...\r\n" );
    lr5_set_next_dr_cmd( &lr5, LR5_SF10_125KHZ );
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
    Delay_ms ( 1000 );
    
    log_printf( &logger, "** Channel parameters reading...\r\n" );
    lr5_get_ch_param_cmd( &lr5, LR5_CH_IDX_15 );
    wait_response( );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LR5

**Additional notes and informations**

Depending on the development board you are using, you may need 
[USB UART Click](https://shop.mikroe.com/usb-uart-click), 
[USB UART 2 Click](https://shop.mikroe.com/usb-uart-2-click) or 
[RS232 Click](https://shop.mikroe.com/rs232-click) to connect to your PC, for 
development systems with no UART to USB interface available on the board. The 
terminal available in all Mikroelektronika 
[compilers](https://shop.mikroe.com/compilers), or any other terminal application 
of your choice, can be used to read the message.



---
