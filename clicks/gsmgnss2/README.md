
---
# GSM/GNSS 2 Click

> [GSM GNSS 2 Click](https://www.mikroe.com/?pid_product=MIKROE-2440) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2440&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Mikroe Team
- **Date**          : Mar 2022.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from GSM/GNSS 2 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GSMGNSS2

### Example Key Functions

- `gsmgnss2_cfg_setup` Config Object Initialization function.
```c
void gsmgnss2_cfg_setup ( gsmgnss2_cfg_t *cfg );
```

- `gsmgnss2_init` Initialization function.
```c
err_t gsmgnss2_init ( gsmgnss2_t *ctx, gsmgnss2_cfg_t *cfg );
```

- `gsmgnss2_module_power` Power ON/OFF the module.
```c
void gsmgnss2_module_power ( gsmgnss2_t *ctx, uint8_t state );
```

- `gsmgnss2_send_cmd` Send command function.
```c
void gsmgnss2_send_cmd ( gsmgnss2_t *ctx, char *cmd );
 ```

- `gsmgnss2_set_sim_apn` Set sim card APN.
```c
void gsmgnss2_set_sim_apn ( gsmgnss2_t *ctx, char *sim_apn );
```

- `gsmgnss2_send_sms_pdu` GSM GNSS send SMS in PDU mode.
```c
err_t gsmgnss2_send_sms_pdu ( gsmgnss2_t *ctx, char *service_center_number, char *phone_number, char *sms_text );
```

### Application Init

> Initializes the driver and powers up the module, then sets default configuration for connecting the device to network.

```c
void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    gsmgnss2_cfg_t gsmgnss2_cfg;  /**< Click config object. */

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

    // Click initialization.
    gsmgnss2_cfg_setup( &gsmgnss2_cfg );
    GSMGNSS2_MAP_MIKROBUS( gsmgnss2_cfg, MIKROBUS_1 );
    gsmgnss2_init( &gsmgnss2, &gsmgnss2_cfg );

    gsmgnss2_module_power( &gsmgnss2, GSMGNSS2_MODULE_POWER_ON );
    
    // dummy read
    gsmgnss2_process( );
    gsmgnss2_clear_app_buf( );
    
    // AT
    gsmgnss2_send_cmd( &gsmgnss2, GSMGNSS2_CMD_AT );
    app_error_flag = gsmgnss2_rsp_check( );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // ATI - product information
    gsmgnss2_send_cmd( &gsmgnss2, GSMGNSS2_CMD_ATI );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGMR - firmware version
    gsmgnss2_send_cmd( &gsmgnss2, GSMGNSS2_CMD_CGMR );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CMEE - Report Mobile Equipment Error
    gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_CMEE, "2" );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - deregister from network
    gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_COPS, "2" );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGDCONT - set sim apn
    gsmgnss2_set_sim_apn( &gsmgnss2, SIM_APN );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CFUN - full funtionality
    gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_CFUN, "1" );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - automatic mode
    gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_COPS, "0" );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // CREG - network registration status
    gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_CREG, "1" );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // SMS message format - PDU mode
    gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_CMGF, "0" );      
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // QGNSSC - power ON GNSS
    gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_CGNSPWR, "1" );
    app_error_flag = gsmgnss2_rsp_check(  );
    gsmgnss2_error_check( app_error_flag );
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

> Waits for the device to connect to network, then waits for the GNSS position fix. Once it get a fix,
it sends an SMS with GNSS info to the selected phone number approximately every 40 seconds.

```c
void application_task ( void )
{
    if ( app_connection_status == WAIT_FOR_CONNECTION )
    {
        // CREG - network registration status
        gsmgnss2_send_cmd_check( &gsmgnss2, GSMGNSS2_CMD_CREG );
        app_error_flag = gsmgnss2_rsp_check(  );
        gsmgnss2_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CSQ - signal quality
        gsmgnss2_send_cmd( &gsmgnss2, GSMGNSS2_CMD_CSQ );
        app_error_flag = gsmgnss2_rsp_check(  );
        gsmgnss2_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        for ( ; ; )
        {
            // Get GNSS info
            gnss_parser_flag = 1;
            gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_CGNSTST, "1" );
            
            for ( ; ; )
            {
                if ( GSMGNSS2_OK == gsmgnss2_process( ) )
                {                    
                    gnss_parser_application( app_buf );
                            
                    if ( gnss_parser_flag == 2 ) 
                    {
                        gsmgnss2_send_cmd_with_parameter( &gsmgnss2, GSMGNSS2_CMD_CGNSTST, "0" ); 
                        app_error_flag = gsmgnss2_rsp_check(  );
                        gsmgnss2_error_check( app_error_flag );                      
                        log_printf( &logger, "> Sending message to phone number...\r\n" );
                        gsmgnss2_send_sms_pdu ( &gsmgnss2, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, gnss_info_message );      
                        app_error_flag = gsmgnss2_rsp_check(  );
                        gsmgnss2_error_check( app_error_flag );
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
                    if ( gnss_parser_flag != 1 ) 
                    {
                        break;
                    }
                }
            }            
        }
    }
}
```

### Note

> A passive GPS antenna is required for the GNSS to receive the position fix. It may take several minutes for the module to receive the fix.
> In order for the example to work, user needs to set the phone number to which he wants 
> to send an SMS, and also will need to set an APN and SMSC (required for PDU mode only) of entered SIM card.
> Enter valid data for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
> > Example: 
> > - SIM_APN "vipmobile"
> > - SIM_SMSC "+381610401"
> > - PHONE_NUMBER_TO_MESSAGE "+381659999999"

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
