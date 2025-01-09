
---
# LTE IoT 2 Click

> [LTE IoT 2 Click](https://www.mikroe.com/?pid_product=MIKROE-3144) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3144&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GPS/GNSS type

# Software Support

## Example Description

> This example reads and processes data from LTE IoT 2 Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LteIot2

### Example Key Functions

- `lteiot2_cfg_setup` Config Object Initialization function. 
```c
void lteiot2_cfg_setup ( lteiot2_cfg_t *cfg );
``` 
 
- `lteiot2_init` Initialization function. 
```c
err_t lteiot2_init ( lteiot2_t *ctx, lteiot2_cfg_t *cfg );
```

- `lteiot2_module_power` Power ON/OFF the module. 
```c
void lteiot2_module_power ( lteiot2_t *ctx, uint8_t state );
```

- `lteiot2_send_cmd_with_parameter` Send command function with parameter. 
```c
void lteiot2_send_cmd_with_parameter ( lteiot2_t *ctx, char *at_cmd_buf, char *param_buf );
```
 
- `lteiot2_send_sms_pdu` LTE IoT 2 send SMS in PDU mode. 
```c
err_t lteiot2_send_sms_pdu ( lteiot2_t *ctx, char *service_center_number, char *phone_number, char *sms_text );
```

- `lteiot2_generic_parser` Generic parser function. 
```c
lteiot2_error_t lteiot2_generic_parser ( char *rsp,  uint8_t command, uint8_t element, char *parser_buf );
```

### Application Init

> Initializes the driver and powers up the module, then sets default configuration for connecting the device to network.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;
    lteiot2_cfg_t cfg;

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
    Delay_ms ( 500 );
    
    // ATI - product information
    lteiot2_send_cmd( &lteiot2, LTEIOT2_CMD_ATI );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGMR - firmware version
    lteiot2_send_cmd( &lteiot2, LTEIOT2_CMD_CGMR );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - deregister from network
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_COPS, "2" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGDCONT - set sim apn
    lteiot2_set_sim_apn( &lteiot2, SIM_APN );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms ( 500 );
     
    // CFUN - full funtionality
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_CFUN, "1" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - automatic mode
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_COPS, "0" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // CREG - network registration status
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_CREG, "2" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CIMI - request IMSI
    lteiot2_send_cmd( &lteiot2, LTEIOT2_CMD_CIMI );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // QGPSCFG - Set <nmeasrc> to 1 to enable acquisition of NMEA sentences via AT+QGPSGNMEA
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_QGPSCFG, "\"nmeasrc\",1" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // QGPS - Set to 1 to turn ON GNSS
    lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_QGPS, "1" );
    app_error_flag = lteiot2_rsp_check(  );
    lteiot2_error_check( app_error_flag );
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
        lteiot2_send_cmd_check( &lteiot2, LTEIOT2_CMD_CGATT );
        app_error_flag = lteiot2_rsp_check(  );
        lteiot2_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CREG - network registration status
        lteiot2_send_cmd_check( &lteiot2, LTEIOT2_CMD_CREG );
        app_error_flag = lteiot2_rsp_check(  );
        lteiot2_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CSQ - signal quality
        lteiot2_send_cmd( &lteiot2, LTEIOT2_CMD_CSQ );
        app_error_flag = lteiot2_rsp_check(  );
        lteiot2_error_check( app_error_flag );
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
        lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_CMGF, "0" );
        app_error_flag = lteiot2_rsp_check(  );
        lteiot2_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        
        for( ; ; )
        {   
            // Get GPS info
            gps_parser_flag = 1;
            lteiot2_send_cmd_with_parameter( &lteiot2, LTEIOT2_CMD_QGPSGNMEA, "\"GGA\"" );
            app_error_flag = lteiot2_rsp_check(  );
            lteiot2_error_check( app_error_flag );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            
            if ( gps_parser_flag == 0 )
            {
                log_printf( &logger, "> Sending message to phone number...\r\n" );
                lteiot2_send_sms_pdu ( &lteiot2, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, gps_info_message );
                app_error_flag = lteiot2_rsp_check(  );
                lteiot2_error_check( app_error_flag );
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
