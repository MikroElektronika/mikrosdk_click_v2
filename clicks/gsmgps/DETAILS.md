
---
# GSM-GPS Click

GSM-GPS Click is a mikroBUS add-on board with a SIM808 module that combines GSM/GPRS and GPS into a single device. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gsmgps_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/gsm-gps-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the Gsmgps Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for Gsmgps Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gsmgps_cfg_setup ( gsmgps_cfg_t *cfg ); 
 
- Initialization function.
> GSMGPS_RETVAL gsmgps_init ( gsmgps_t *ctx, gsmgps_cfg_t *cfg );

- Power ON/OFF the module.
> void gsmgps_module_power ( gsmgps_t *ctx, uint8_t state );


#### Example key functions :

- Send command function with parameter.
> void gsmgps_send_cmd_with_parameter ( gsmgps_t *ctx, char *at_cmd_buf, char *param_buf );
 
- GSM-GPS send SMS in PDU mode.
> err_t gsmgps_send_sms_pdu ( gsmgps_t *ctx, char *service_center_number, char *phone_number, char *sms_text );

- Generic parser function.
> gsmgps_error_t gsmgps_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );

## Examples Description

> This example reads and processes data from GSM-GPS Click.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and powers up the module, then sets default configuration for connecting the device to network.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gsmgps_cfg_t cfg;

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

    gsmgps_cfg_setup( &cfg );
    GSMGPS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gsmgps_init( &gsmgps, &cfg );

    gsmgps_module_power( &gsmgps, GSMGPS_MODULE_POWER_ON );
    
    // dummy read
    gsmgps_process( );
    gsmgps_clear_app_buf( );
    // AT
    gsmgps_send_cmd( &gsmgps, GSMGPS_CMD_AT );
    app_error_flag = gsmgps_rsp_check( );
    gsmgps_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // ATI - product information
    gsmgps_send_cmd( &gsmgps, GSMGPS_CMD_ATI );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGMR - firmware version
    gsmgps_send_cmd( &gsmgps, GSMGPS_CMD_CGMR );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - deregister from network
    gsmgps_send_cmd_with_parameter( &gsmgps, GSMGPS_CMD_COPS, "2" );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGDCONT - set sim apn
    gsmgps_set_sim_apn( &gsmgps, SIM_APN );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms ( 500 );
     
    // CFUN - full funtionality
    gsmgps_send_cmd_with_parameter( &gsmgps, GSMGPS_CMD_CFUN, "1" );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - automatic mode
    gsmgps_send_cmd_with_parameter( &gsmgps, GSMGPS_CMD_COPS, "0" );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // CREG - network registration status
    gsmgps_send_cmd_with_parameter( &gsmgps, GSMGPS_CMD_CREG, "2" );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CIMI - request IMSI
    gsmgps_send_cmd( &gsmgps, GSMGPS_CMD_CIMI );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGNSPWR - power ON GPS
    gsmgps_send_cmd_with_parameter( &gsmgps, GSMGPS_CMD_CGNSPWR, "1" );
    app_error_flag = gsmgps_rsp_check(  );
    gsmgps_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task " );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
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
        gsmgps_send_cmd_check( &gsmgps, GSMGPS_CMD_CGATT );
        app_error_flag = gsmgps_rsp_check(  );
        gsmgps_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CREG - network registration status
        gsmgps_send_cmd_check( &gsmgps, GSMGPS_CMD_CREG );
        app_error_flag = gsmgps_rsp_check(  );
        gsmgps_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CSQ - signal quality
        gsmgps_send_cmd( &gsmgps, GSMGPS_CMD_CSQ );
        app_error_flag = gsmgps_rsp_check(  );
        gsmgps_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        // SMS message format - PDU mode
        gsmgps_send_cmd_with_parameter( &gsmgps, GSMGPS_CMD_CMGF, "0" );
        app_error_flag = gsmgps_rsp_check(  );
        gsmgps_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        
        for( ; ; )
        {   
            // Get GPS info
            gps_parser_flag = 1;
            gsmgps_send_cmd_with_parameter( &gsmgps, GSMGPS_CMD_CGPSINF, "2" );
            app_error_flag = gsmgps_rsp_check(  );
            gsmgps_error_check( app_error_flag );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            
            if ( gps_parser_flag == 0 )
            {
                log_printf( &logger, "> Sending message to phone number...\r\n" );
                gsmgps_send_sms_pdu ( &gsmgps, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, gps_info_message );
                app_error_flag = gsmgps_rsp_check(  );
                gsmgps_error_check( app_error_flag );
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
- Click.Gsmgps

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
