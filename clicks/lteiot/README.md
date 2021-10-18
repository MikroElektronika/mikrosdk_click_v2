\mainpage Main Page
 
---
# LTE IoT click

LTE IoT click is a Click board™ that allows connection to the LTE and 2G networks.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lteiot_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lte-iot-click)

---


#### Click library 

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GSM/IOT type


# Software Support

We provide a library for the LteIot Click 
as well as a demo application (example), developed using MikroElektronika 
[compilers](https://shop.mikroe.com/compilers). 
The demo can run on all the main MikroElektronika [development boards](https://shop.mikroe.com/development-boards).

Package can be downloaded/installed directly form compilers IDE(recommended way), or downloaded from our LibStock, or found on mikroE github account. 

## Library Description

> This library contains API for LteIot Click driver.

#### Standard key functions :

- LTE IoT configuration object setup function.
> void lteiot_cfg_setup ( lteiot_cfg_t *cfg );
 
- LTE IoT initialization function.
> err_t lteiot_init ( lteiot_t *ctx, lteiot_cfg_t *cfg );

#### Example key functions :

- LTE IoT module power on.
> void lteiot_power_on ( lteiot_t *ctx );

- Send command function.
> void lteiot_send_cmd ( lteiot_t *ctx, char *cmd );

## Examples Description

> This example reads and processes data from LTE IoT click.

**The demo application is composed of two sections :**

### Application Init 

> Initializes driver and wake-up module and sets default configuration for connecting device to network.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot_cfg_t lteiot_cfg;  /**< Click config object. */

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
    lteiot_cfg_setup( &lteiot_cfg );
    LTEIOT_MAP_MIKROBUS( lteiot_cfg, MIKROBUS_1 );
    err_t init_flag  = lteiot_init( &lteiot, &lteiot_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Power on device... " );
    lteiot_power_on( &lteiot );
    
    // dummy read
    lteiot_process( );
    lteiot_clear_app_buf( );
    
    // AT
    lteiot_send_cmd( &lteiot, LTEIOT_CMD_AT );
    app_error_flag = lteiot_rsp_check( );
    lteiot_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // ATI - product information
    lteiot_send_cmd( &lteiot, LTEIOT_CMD_ATI );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGMR - firmware version
    lteiot_send_cmd( &lteiot, LTEIOT_CMD_CGMR );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - deregister from network
    lteiot_send_cmd_with_parameter( &lteiot, LTEIOT_CMD_COPS, "2" );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGDCONT - set sim apn
    lteiot_set_sim_apn( &lteiot, SIM_APN );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
    Delay_ms( 500 );
     
    // CFUN - full funtionality
    lteiot_send_cmd_with_parameter( &lteiot, LTEIOT_CMD_CFUN, "1" );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - automatic mode
    lteiot_send_cmd_with_parameter( &lteiot, LTEIOT_CMD_COPS, "0" );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
    Delay_ms( 2000 );
    
    // CEREG - network registration status
    lteiot_send_cmd_with_parameter( &lteiot, LTEIOT_CMD_CEREG, "2" );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CIMI - request IMSI
    lteiot_send_cmd( &lteiot, LTEIOT_CMD_CIMI );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
    Delay_ms( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task " );
    Delay_ms( 5000 );
}
  
```

### Application Task

> Waits for device to connect to network and then sends SMS to selected phone number.

```c

void application_task ( void )
{
    if ( app_connection_status == WAIT_FOR_CONNECTION )
    {
        // CGATT - request IMSI
        lteiot_send_cmd_check( &lteiot, LTEIOT_CMD_CGATT );
        app_error_flag = lteiot_rsp_check(  );
        lteiot_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CEREG - network registration status
        lteiot_send_cmd_check( &lteiot, LTEIOT_CMD_CEREG );
        app_error_flag = lteiot_rsp_check(  );
        lteiot_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CSQ - signal quality
        lteiot_send_cmd( &lteiot, LTEIOT_CMD_CSQ );
        app_error_flag = lteiot_rsp_check(  );
        lteiot_error_check( app_error_flag );
        Delay_ms( 5000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        // SMS message format - text mode
        lteiot_send_cmd_with_parameter( &lteiot, "AT+CMGF", "1" );
        app_error_flag = lteiot_rsp_check(  );
        lteiot_error_check( app_error_flag );
        Delay_ms( 3000 );
        
        for( ; ; )
        {   
            log_printf( &logger, "> Sending message to phone number...\r\n" );
            lteiot_send_text_message( &lteiot, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
            app_error_flag = lteiot_rsp_check(  );
            lteiot_error_check( app_error_flag );
            Delay_ms( 10000 );
            Delay_ms( 10000 );
            Delay_ms( 10000 );
        }
    }
} 

```

## Note

> In order for the example to work, 
> user needs to set the phone number and sim apn to which he wants to send an SMS
> Enter valid data for the following macros: SIM_APN and PHONE_NUMBER_TO_MESSAGE.
>> E.g. 
   >> * SIM_APN "vipmobile"
   >> * PHONE_NUMBER_TO_MESSAGE "999999999"

The full application code, and ready to use projects can be  installed directly form compilers IDE(recommneded) or found on LibStock page or mikroE GitHub accaunt.

**Other mikroE Libraries used in the example:** 

- MikroSDK.Board
- MikroSDK.Log
- Click.LteIot

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
