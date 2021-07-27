\mainpage Main Page
 
---
# LTE IoT 2 click

LTE IoT 2 click is a Click board™ that allows connection to the LTE networks, featuring Quectel BG96 LTE module, which offers two LTE technologies aimed at Machine to Machine communication (M2M) and Internet of Things (IoT).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lteiot2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lte-iot-2-click)

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

- Power ON/OFF the module.
> void lteiot2_module_power ( lteiot2_t *ctx, uint8_t state );

#### Example key functions :

- Send command function with parameter.
> void lteiot2_send_cmd_with_parameter ( lteiot2_t *ctx, char *at_cmd_buf, char *param_buf );
 
- LTE IoT 2 send SMS in PDU mode.
> err_t lteiot2_send_sms_pdu ( lteiot2_t *ctx, char *service_center_number, char *phone_number, char *sms_text );

- Generic parser function.
> lteiot2_error_t lteiot2_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );

## Examples Description

> This example reads and processes data from LTE IoT 2 click.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and powers up the module, then sets default configuration for connecting the device to network.

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

    lteiot2_module_power( &lteiot2, LTEIOT2_MODULE_POWER_ON );
    
    // dummy read
    lteiot2_process( );
    lteiot2_clear_app_buf( );
    // AT
    lteiot2_send_cmd( &lteiot2, LTEIOT2_CMD_AT );
    app_error_flag = lteiot2_rsp_check( );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // ATI - product information
    lteiot2_send_cmd( &lteiot2, LTEIOT2_CMD_ATI );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGMR - firmware version
    lteiot2_send_cmd( &lteiot2, LTEIOT2_CMD_CGMR );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - deregister from network
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_COPS, "2" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGDCONT - set sim apn
    lteiot2_set_sim_apn( &lteiot2, SIM_APN );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
     
    // CFUN - full funtionality
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_CFUN, "1" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - automatic mode
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_COPS, "0" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 2000 );
    
    // CREG - network registration status
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_CREG, "2" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CIMI - request IMSI
    lteiot2_send_cmd( &lteiot2, LTEIOT2_CMD_CIMI );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // QGPSCFG - Set <nmeasrc> to 1 to enable acquisition of NMEA sentences via AT+QGPSGNMEA
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_QGPSCFG, "\"nmeasrc\",1" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task " );
    Delay_ms( 5000 );
}
  
```

### Application Task

> Waits for the device to connect to network, then waits for the GPS position fix. Once it get a fix, 
> it sends an SMS with GPS info to the selected phone number approximately every 40 seconds.

```c

void application_task ( void )
{
    if ( app_connection_status == WAIT_FOR_CONNECTION )
    {
        // CGATT - request IMSI
        lteiot2_send_cmd_check( &lteiot2, LTEIOT2_CMD_CGATT );
        app_error_flag = lteiot2_rsp_check(  );
        lteiot2_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CREG - network registration status
        lteiot2_send_cmd_check( &lteiot2, LTEIOT2_CMD_CREG );
        app_error_flag = lteiot2_rsp_check(  );
        lteiot2_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CSQ - signal quality
        lteiot2_send_cmd( &lteiot2, LTEIOT2_CMD_CSQ );
        app_error_flag = lteiot2_rsp_check(  );
        lteiot2_error_check( app_error_flag );
        Delay_ms( 5000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        // SMS message format - PDU mode
        lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_CMGF, "0" );
        app_error_flag = lteiot2_rsp_check(  );
        lteiot2_error_check( app_error_flag );
        Delay_ms( 3000 );
        
        for( ; ; )
        {   
            // Get GPS info
            gps_parser_flag = 1;
            lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_QGPSGNMEA, "\"GGA\"" );
            app_error_flag = lteiot2_rsp_check(  );
            lteiot2_error_check( app_error_flag );
            Delay_ms( 3000 );
            
            if ( gps_parser_flag == 0 )
            {
                log_printf( &logger, "> Sending message to phone number...\r\n" );
                lteiot2_send_sms_pdu ( &lteiot2, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, gps_info_message );
                app_error_flag = lteiot2_rsp_check(  );
                lteiot2_error_check( app_error_flag );
                Delay_ms( 10000 );
                Delay_ms( 10000 );
                Delay_ms( 10000 );
            }
        }
    }
} 

```

## Note

> In order for the example to work, user needs to set the phone number to which he wants 
> to send an SMS, and also will need to set an APN and SMSC (required for PDU mode only) of entered SIM card.
> Enter valid data for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
>> E.g. 
   >> * SIM_APN "vipmobile"
   >> * SIM_SMSC "+381610401"
   >> * PHONE_NUMBER_TO_MESSAGE "+381659999999"

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
