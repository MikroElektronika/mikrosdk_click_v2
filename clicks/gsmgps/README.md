
---
# GSM-GPS Click

> [GSM-GPS Click](https://www.mikroe.com/?pid_product=MIKROE-2382) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2382&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : May 2020.
- **Type**          : UART GSM/IOT type

# Software Support

## Example Description

> This example reads and processes data from GSM-GPS Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.Gsmgps

### Example Key Functions

- `gsmgps_cfg_setup` Config Object Initialization function. 
```c
void gsmgps_cfg_setup ( gsmgps_cfg_t *cfg );
``` 
 
- `gsmgps_init` Initialization function. 
```c
err_t gsmgps_init ( gsmgps_t *ctx, gsmgps_cfg_t *cfg );
```

- `gsmgps_module_power` Power ON/OFF the module. 
```c
void gsmgps_module_power ( gsmgps_t *ctx, uint8_t state );
```

- `gsmgps_send_cmd_with_parameter` Send command function with parameter. 
```c
void gsmgps_send_cmd_with_parameter ( gsmgps_t *ctx, char *at_cmd_buf, char *param_buf );
```
 
- `gsmgps_send_sms_pdu` GSM-GPS send SMS in PDU mode. 
```c
err_t gsmgps_send_sms_pdu ( gsmgps_t *ctx, char *service_center_number, char *phone_number, char *sms_text );
```

- `gsmgps_generic_parser` Generic parser function. 
```c
gsmgps_error_t gsmgps_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );
```

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

### Note

> In order for the example to work, user needs to set the phone number to which he wants 
> to send an SMS, and also will need to set an APN and SMSC (required for PDU mode only) of entered SIM card.
> Enter valid data for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
>> E.g. 
   >> * SIM_APN "vipmobile"
   >> * SIM_SMSC "+381610401"
   >> * PHONE_NUMBER_TO_MESSAGE "+381659999999"

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
