
---
# 5G NB IoT Click

> [5G NB IoT Click](https://www.mikroe.com/?pid_product=MIKROE-4034) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4034&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : jun 2020.
- **Type**          : UART GSM/IOT type

# Software Support

## Example Description

> This example reads and processes data from 5G NB IoT Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.5gNbIot

### Example Key Functions

- `c5gnbiot_cfg_setup` Config Object Initialization function. 
```c
void c5gnbiot_cfg_setup ( c5gnbiot_cfg_t *cfg );
``` 
 
- `c5gnbiot_init` Initialization function. 
```c
err_t c5gnbiot_init ( c5gnbiot_t *ctx, c5gnbiot_cfg_t *cfg );
```

- `c5gnbiot_power_on` Module power on function. 
```c
void c5gnbiot_power_on ( c5gnbiot_t *ctx );
```

- `c5gnbiot_send_cmd` Send command function. 
```c
void c5gnbiot_send_cmd ( c5gnbiot_t *ctx, char *cmd );
```
 
- `c5gnbiot_set_sim_apn` Set sim card APN function. 
```c
void c5gnbiot_set_sim_apn ( c5gnbiot_t *ctx, char *sim_apn );
```

- `c5gnbiot_send_text_message` Send SMS in PDU mode function. 
```c
err_t c5gnbiot_send_text_message ( c5gnbiot_t *ctx, char *service_center_number, char *phone_number, char *sms_text );
```

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
    Delay_ms ( 1000 );
    
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
    Delay_ms ( 1000 );
    c5gnbiot_power_on( &c5gnbiot );
    
    // dummy read
    c5gnbiot_process( );
    c5gnbiot_clear_app_buf( );
    // AT
    c5gnbiot_send_cmd( &c5gnbiot, C5GNBIOT_CMD_AT );
    app_error_flag = c5gnbiot_rsp_check( );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // ATI - product information
    c5gnbiot_send_cmd( &c5gnbiot, C5GNBIOT_CMD_ATI );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGMR - firmware version
    c5gnbiot_send_cmd( &c5gnbiot, C5GNBIOT_CMD_CGMR );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - deregister from network
    c5gnbiot_send_cmd_with_parameter( &c5gnbiot, C5GNBIOT_CMD_COPS, "2" );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGDCONT - set sim apn
    c5gnbiot_set_sim_apn( &c5gnbiot, SIM_APN );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
     
    // CFUN - full funtionality
    c5gnbiot_send_cmd_with_parameter( &c5gnbiot, C5GNBIOT_CMD_CFUN, "1" );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - automatic mode
    c5gnbiot_send_cmd_with_parameter( &c5gnbiot, C5GNBIOT_CMD_COPS, "0" );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // CEREG - network registration status
    c5gnbiot_send_cmd_with_parameter( &c5gnbiot, C5GNBIOT_CMD_CEREG, "2" );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CIMI - request IMSI
    c5gnbiot_send_cmd( &c5gnbiot, C5GNBIOT_CMD_CIMI );
    app_error_flag = c5gnbiot_rsp_check(  );
    c5gnbiot_error_check( app_error_flag );
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
        Delay_ms ( 500 );
        
        // CEREG - network registration status
        c5gnbiot_send_cmd_check( &c5gnbiot, C5GNBIOT_CMD_CEREG );
        app_error_flag = c5gnbiot_rsp_check(  );
        c5gnbiot_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CSQ - signal quality
        c5gnbiot_send_cmd( &c5gnbiot, C5GNBIOT_CMD_CESQ );
        app_error_flag = c5gnbiot_rsp_check(  );
        c5gnbiot_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
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
```

### Note

> In order for the example to work, user needs to set the phone number to which he wants 
> to send an SMS, and also will need to set an APN and SMSC of entered SIM card.
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
