\mainpage Main Page
 
---
# LTE IoT 2 click

LTE IoT 2 click is a Click board™ that allows connection to the LTE networks

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lteiot2_click.png" height=300px>
</p>

[click Product page](<https://www.mikroe.com/lte-iot-2-click>)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type


# Software Support

We provide a library for the LteIot2 Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LteIot2 Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void lteiot2_cfg_setup ( lteiot2_cfg_t *cfg ); 
 
- Initialization function.
> LTEIOT2_RETVAL lteiot2_init ( lteiot2_t *ctx, lteiot2_cfg_t *cfg );

#### Example key functions :

- Power module.
> void lteiot2_module_power( lteiot2_t *ctx, uint8_t power_state );

- Send command
> void lteiot2_send_command ( lteiot2_t *ctx, char *command );

## Examples Description

> This example reads and processes data from LTE IoT 2 clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and power module. 

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    lteiot2_cfg_t cfg;

    //  Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, "---- Application Init ----" );

    //  Click initialization.

    lteiot2_cfg_setup( &cfg );
    LTEIOT2_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    lteiot2_init( &lteiot2, &cfg );

    lteiot2_module_power( &lteiot2, true );

    lteiot2_send_command( &lteiot2, ATI );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+IPR=115200;&W, set baudrate
    lteiot2_send_command( &lteiot2, AT_IPR );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QCFG="nbsibscramble",0, Enable scrambling
    lteiot2_send_command( &lteiot2, AT_QCFG_1 );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QCFG="band",0,0,80,1, set baud
    lteiot2_send_command( &lteiot2, AT_QCFG_2 );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QCFG="nwscanmode",3,1, Set LTE mode
    lteiot2_send_command( &lteiot2, AT_QCFG_3 );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QCFG="nwscanseq",030201,1, set priority  NB1 > M1 > 2G
    lteiot2_send_command( &lteiot2, AT_QCFG_4 );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QCFG="iotopmode",1,1, select CAT-NB1
    lteiot2_send_command( &lteiot2, AT_QCFG_5 );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QCFG="servicedomain",1,1, Set PS domain
    lteiot2_send_command( &lteiot2, AT_QCFG_6 );
    Delay_1sec( );
    //Command: AT+CGDCONT=1,"IP","internet", set APN provided
    lteiot2_send_command( &lteiot2, AT_CGDCONT );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+CFUN=1, Full functionality
    lteiot2_send_command( &lteiot2, AT_CFUN );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+COPS=1,2,"22001",0, set MCC and MNC provided
    lteiot2_send_command( &lteiot2, AT_COPS );
    lteiot2_process( );
    Delay_1sec( );
    lteiot2_send_command( &lteiot2, AT_CGATT );
    lteiot2_process( );
    Delay_1sec( );
    lteiot2_send_command( &lteiot2, AT_CEREG );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QIACT=1, activate PDP context
    lteiot2_send_command( &lteiot2, AT_QIACT );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QIOPEN=1,0,"UDP","79.114.83.116",16666, create an UDP socket
    lteiot2_send_command( &lteiot2, AT_QIOPEN );
    lteiot2_process( );
    Delay_1sec( );
    //Command: AT+QISENDEX=0,"48656C6C6F", Send message - Hello
    lteiot2_send_command( &lteiot2, AT_QISENDEX );
    lteiot2_process( );
    Delay_1sec( );
}
  
```

### Application Task

> Reads the received data.

```c

void application_task ( void )
{
    lteiot2_process( );
    // Send message - Hello
    if ( send_data_cnt == 5 )
    {
        lteiot2_send_command( &lteiot2, AT_QISENDEX );
        lteiot2_process( );
        send_data_cnt = 0;
    }
    else
    {
        send_data_cnt++;
    }
} 

```

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LteIot2

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
