
---
# GSM/GNSS Click

> [GSM GNSS Click](https://www.mikroe.com/?pid_product=MIKROE-2439) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-2439&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : apr 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from GSM/GNSS Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.GsmGnss

### Example Key Functions

- `gsmgnss_cfg_setup` Config Object Initialization function. 
```c
void gsmgnss_cfg_setup ( gsmgnss_cfg_t *cfg );
``` 
 
- `gsmgnss_init` Initialization function. 
```c
err_t gsmgnss_init ( gsmgnss_t *ctx, gsmgnss_cfg_t *cfg );
```

- `gsmgnss_module_power` Power ON/OFF the module. 
```c
void gsmgnss_module_power ( gsmgnss_t *ctx, uint8_t state );
```

- `gsmgnss_send_cmd` Send command function. 
```c
void gsmgnss_send_cmd ( gsmgnss_t *ctx, char *cmd );
```
 
- `gsmgnss_set_sim_apn` Set sim card APN. 
```c
void gsmgnss_set_sim_apn ( gsmgnss_t *ctx, char *sim_apn );
```

- `gsmgnss_send_sms_pdu` GSM GNSS send SMS in PDU mode. 
```c
err_t gsmgnss_send_sms_pdu ( gsmgnss_t *ctx, char *service_center_number, char *phone_number, char *sms_text );
```

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
    Delay_ms ( 500 );
    
    // ATI - product information
    gsmgnss_send_cmd( &gsmgnss, GSMGNSS_CMD_ATI );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGMR - firmware version
    gsmgnss_send_cmd( &gsmgnss, GSMGNSS_CMD_CGMR );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CMEE - Report Mobile Equipment Error
    gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_CMEE, "2" );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - deregister from network
    gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_COPS, "2" );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGDCONT - set sim apn
    gsmgnss_set_sim_apn( &gsmgnss, SIM_APN );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CFUN - full funtionality
    gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_CFUN, "1" );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - automatic mode
    gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_COPS, "0" );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // CREG - network registration status
    gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_CREG, "1" );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // QGNSSC - power ON GNSS
    gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_QGNSSC, "1" );
    app_error_flag = gsmgnss_rsp_check(  );
    gsmgnss_error_check( app_error_flag );
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
        Delay_ms ( 500 );
        
        // CSQ - signal quality
        gsmgnss_send_cmd( &gsmgnss, GSMGNSS_CMD_CSQ );
        app_error_flag = gsmgnss_rsp_check(  );
        gsmgnss_error_check( app_error_flag );
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
        gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_CMGF, "0" );
        app_error_flag = gsmgnss_rsp_check(  );
        gsmgnss_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        
        for( ; ; )
        {   
            // Get GNSS info
            gnss_parser_flag = 1;
            gsmgnss_send_cmd_with_parameter( &gsmgnss, GSMGNSS_CMD_QGNSSRD, "\"NMEA/GGA\"" );
            app_error_flag = gsmgnss_rsp_check(  );
            gsmgnss_error_check( app_error_flag );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            Delay_ms ( 1000 );
            
            if ( gnss_parser_flag == 0 )
            {
                log_printf( &logger, "> Sending message to phone number...\r\n" );
                gsmgnss_send_sms_pdu ( &gsmgnss, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, gnss_info_message );
                app_error_flag = gsmgnss_rsp_check(  );
                gsmgnss_error_check( app_error_flag );
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

> A passive GPS antenna is required for the GNSS to receive the position fix. It may take several minutes for the module to receive the fix.
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
