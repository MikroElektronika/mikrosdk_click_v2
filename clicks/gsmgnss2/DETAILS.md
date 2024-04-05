
---
# GSM/GNSS 2 click

GSM/GNSS 2 click combines GPS/GLONASS location tracking with GSM module capability for mobile communication. The click carries SIM868 quad-band GSM/GPRS module.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/gsmgnss2_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/gsmgnss-2-click)

---


#### Click library

- **Author**        : Mikroe Team
- **Date**          : Mar 2022.
- **Type**          : UART type


# Software Support

We provide a library for the GSM/GNSS 2 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for GSM/GNSS 2 Click driver.

#### Standard key functions :

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

#### Example key functions :

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

## Example Description

> This example reads and processes data from GSM/GNSS 2 clicks.

**The demo application is composed of two sections :**

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

## Note

> A passive GPS antenna is required for the GNSS to receive the position fix. It may take several minutes for the module to receive the fix.
> In order for the example to work, user needs to set the phone number to which he wants 
> to send an SMS, and also will need to set an APN and SMSC (required for PDU mode only) of entered SIM card.
> Enter valid data for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
> > Example: 
> > - SIM_APN "vipmobile"
> > - SIM_SMSC "+381610401"
> > - PHONE_NUMBER_TO_MESSAGE "+381659999999"

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.GSMGNSS2

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
