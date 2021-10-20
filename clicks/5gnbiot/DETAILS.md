
---
# 5G NB IoT click

5G NB IoT Click is a Click board™ based on Gemalto's Cinterion® ENS22 NB-IoT Wireless Module platform that boosts highly efficient future 5G connectivity for the IoT.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/5gnbiot_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/5g-nb-iot-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the 5gNbIot Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for 5gNbIot Click driver.

#### Standard key functions :

- Config Object Initialization function.
> void c5gnbiot_cfg_setup ( c5gnbiot_cfg_t *cfg ); 
 
- Initialization function.
> err_t c5gnbiot_init ( c5gnbiot_t *ctx, c5gnbiot_cfg_t *cfg );

- Module power on function.
> void c5gnbiot_power_on ( c5gnbiot_t *ctx );


#### Example key functions :

- Send command function.
> void c5gnbiot_send_cmd ( c5gnbiot_t *ctx, char *cmd );
 
- Set sim card APN function.
> void c5gnbiot_set_sim_apn ( c5gnbiot_t *ctx, char *sim_apn );

- Send SMS in PDU mode function.
> err_t c5gnbiot_send_text_message ( c5gnbiot_t *ctx, char *service_center_number, char *phone_number, char *sms_text );

## Examples Description

> This example reads and processes data from 5G NB IoT clicks.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module and sets default configuration for connecting device to network.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    c5gnbiot_cfg_t c5gnbiot_cfg;  /**< Click config object. */

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
    log_info( &logger, " Application Init " );
    Delay_ms( 1000 );
    
    // Click initialization.
    c5gnbiot_cfg_setup( &c5gnbiot_cfg );
    C5GNBIOT_MAP_MIKROBUS( c5gnbiot_cfg, MIKROBUS_1 );
    err_t init_flag  = c5gnbiot_init( &c5gnbiot, &c5gnbiot_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Power on device... " );
    Delay_ms( 1000 );
    c5gnbiot_power_on( &c5gnbiot );
    
    // dummy read
    c5gnbiot_process( );
    c5gnbiot_clear_app_buf( );
    // AT
    c5gnbiot_send_cmd( &c5gnbiot, C5GNBIOT_CMD_AT );
    app_error_flag = c5gnbiot_rsp_check( );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // ATI - product information
    c5gnbiot_send_cmd( &c5gnbiot, C5GNBIOT_CMD_ATI );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGMR - firmware version
    c5gnbiot_send_cmd( &c5gnbiot, C5GNBIOT_CMD_CGMR );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - deregister from network
    c5gnbiot_send_cmd_with_parameter( &c5gnbiot, C5GNBIOT_CMD_COPS, "2" );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGDCONT - set sim apn
    c5gnbiot_set_sim_apn( &c5gnbiot, SIM_APN );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms( 500 );
     
    // CFUN - full funtionality
    c5gnbiot_send_cmd_with_parameter( &c5gnbiot, C5GNBIOT_CMD_CFUN, "1" );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - automatic mode
    c5gnbiot_send_cmd_with_parameter( &c5gnbiot, C5GNBIOT_CMD_COPS, "0" );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms( 2000 );
    
    // CEREG - network registration status
    c5gnbiot_send_cmd_with_parameter( &c5gnbiot, C5GNBIOT_CMD_CEREG, "2" );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CIMI - request IMSI
    c5gnbiot_send_cmd( &c5gnbiot, C5GNBIOT_CMD_CIMI );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task " );
    Delay_ms( 5000 );
}
  
```

### Application Task

> Waits for device to connect to network and then sends an SMS to the selected phone number.

```c

void application_task ( void )
{
    if ( app_connection_status == WAIT_FOR_CONNECTION )
    {
        // CGATT - request IMSI
        c5gnbiot_send_cmd_check( &c5gnbiot, C5GNBIOT_CMD_CGATT );
        app_error_flag = c5gnbiot_rsp_check(  );
        c5gnbiot_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CEREG - network registration status
        c5gnbiot_send_cmd_check( &c5gnbiot, C5GNBIOT_CMD_CEREG );
        app_error_flag = c5gnbiot_rsp_check(  );
        c5gnbiot_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CSQ - signal quality
        c5gnbiot_send_cmd( &c5gnbiot, C5GNBIOT_CMD_CESQ );
        app_error_flag = c5gnbiot_rsp_check(  );
        c5gnbiot_error_check( app_error_flag );
        Delay_ms( 5000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        for( ; ; )
        {   
            log_printf( &logger, "> Sending message to phone number...\r\n" );
            c5gnbiot_send_text_message( &c5gnbiot, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
            app_error_flag = c5gnbiot_rsp_check(  );
            c5gnbiot_error_check( app_error_flag );
            Delay_ms( 10000 );
            Delay_ms( 10000 );
            Delay_ms( 10000 );
        }
    }
}

```

## Note

> In order for the example to work, user needs to set the phone number to which he wants 
> to send an SMS, and also will need to set an APN and SMSC of entered SIM card.
> Enter valid data for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
>> E.g. 
   >> * SIM_APN "vipmobile"
   >> * SIM_SMSC "+381610401"
   >> * PHONE_NUMBER_TO_MESSAGE "+381659999999"

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.5gNbIot

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
