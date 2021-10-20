\mainpage Main Page
 
---
# GSM/GNSS click

GSM/GNSS click combines GPS/GLONASS location tracking with GSM module capability for mobile communication. The click features Quectel’s MC60 quad-band module.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gsmgnss_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gsm-gnss-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : apr 2020.
- **Type**          : UART type


# Software Support

We provide a library for the GsmGnss Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for GsmGnss Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void gsmgnss_cfg_setup ( gsmgnss_cfg_t *cfg ); 
 
- Initialization function.
> GSMGNSS_RETVAL gsmgnss_init ( gsmgnss_t *ctx, gsmgnss_cfg_t *cfg );

- Power ON/OFF the module.
> void gsmgnss_module_power ( gsmgnss_t *ctx, uint8_t state );


#### Example key functions :

- Send command function.
> void gsmgnss_send_cmd ( gsmgnss_t *ctx, char *cmd );
 
- Set sim card APN.
> void gsmgnss_set_sim_apn ( gsmgnss_t *ctx, char *sim_apn );

- GSM GNSS send SMS in PDU mode.
> err_t gsmgnss_send_sms_pdu ( gsmgnss_t *ctx, char *service_center_number, char *phone_number, char *sms_text );

## Examples Description

> This example reads and processes data from GSM/GNSS clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes the driver and powers up the module, then sets default configuration 
> for connecting the device to network.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;
    gsmgnss_cfg_t cfg;

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

    gsmgnss_cfg_setup( &cfg );
    GSMGNSS_MAP_MIKROBUS( cfg, MIKROBUS_1 );
    gsmgnss_init( &gsmgnss, &cfg );

    gsmgnss_module_power( &gsmgnss, GSMGNSS_MODULE_POWER_ON );
    
    // dummy read
    gsmgnss_process( );
    gsmgnss_clear_app_buf( );
    
    // AT
    gsmgnss_send_cmd( &gsmgnss, GSMGNSS_CMD_AT );
    app_error_flag = gsmgnss_rsp_check( );
    gsmgnss_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // ATI - product information
    gsmgnss_send_cmd( &gsmgnss, GSMGNSS_CMD_ATI );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGMR - firmware version
    gsmgnss_send_cmd( &gsmgnss, GSMGNSS_CMD_CGMR );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CMEE - Report Mobile Equipment Error
    gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_CMEE, "2" );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - deregister from network
    gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_COPS, "2" );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGDCONT - set sim apn
    gsmgnss_set_sim_apn( &gsmgnss, SIM_APN );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CFUN - full funtionality
    gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_CFUN, "1" );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - automatic mode
    gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_COPS, "0" );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms( 2000 );
    
    // CREG - network registration status
    gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_CREG, "1" );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // QGNSSC - power ON GNSS
    gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_QGNSSC, "1" );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task " );
    Delay_ms( 5000 );
}
  
```

### Application Task

> Waits for the device to connect to network, then waits for the GNSS position fix. Once it get a fix, 
> it sends an SMS with GNSS info to the selected phone number approximately every 40 seconds.

```c

void application_task ( void )
{
    if ( app_connection_status == WAIT_FOR_CONNECTION )
    {
        // CREG - network registration status
        gsmgnss_send_cmd_check( &gsmgnss, GSMGNSS_CMD_CREG );
        app_error_flag = gsmgnss_rsp_check(  );
        gsmgnss_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CSQ - signal quality
        gsmgnss_send_cmd( &gsmgnss, GSMGNSS_CMD_CSQ );
        app_error_flag = gsmgnss_rsp_check(  );
        gsmgnss_error_check( app_error_flag );
        Delay_ms( 5000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        // SMS message format - PDU mode
        gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_CMGF, "0" );
        app_error_flag = gsmgnss_rsp_check(  );
        gsmgnss_error_check( app_error_flag );
        Delay_ms( 3000 );
        
        for( ; ; )
        {   
            // Get GNSS info
            gnss_parser_flag = 1;
            gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_QGNSSRD, "\"NMEA/GGA\"" );
            app_error_flag = gsmgnss_rsp_check(  );
            gsmgnss_error_check( app_error_flag );
            Delay_ms( 3000 );
            
            if ( gnss_parser_flag == 0 )
            {
                log_printf( &logger, "> Sending message to phone number...\r\n" );
                gsmgnss_send_sms_pdu ( &gsmgnss, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, gnss_info_message );
                app_error_flag = gsmgnss_rsp_check(  );
                gsmgnss_error_check( app_error_flag );
                Delay_ms( 10000 );
                Delay_ms( 10000 );
                Delay_ms( 10000 );
            }
        }
    }
} 

```

## Note

> A passive GPS antenna is required for the GNSS to receive the position fix. It may take several minutes for the module to receive the fix.
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
- Click.GsmGnss

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
