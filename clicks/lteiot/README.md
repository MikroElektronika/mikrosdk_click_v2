
---
# LTE IoT Click

> [LTE IoT Click](https://www.mikroe.com/?pid_product=MIKROE-3072) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-3072&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : MikroE Team
- **Date**          : Apr 2020.
- **Type**          : UART GSM/IOT type

# Software Support

## Example Description

> This example reads and processes data from LTE IoT Click.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LteIot

### Example Key Functions

- `lteiot_cfg_setup` LTE IoT configuration object setup function. 
```c
void lteiot_cfg_setup ( lteiot_cfg_t *cfg );
```
 
- `lteiot_init` LTE IoT initialization function. 
```c
err_t lteiot_init ( lteiot_t *ctx, lteiot_cfg_t *cfg );
```

- `lteiot_power_on` LTE IoT module power on. 
```c
void lteiot_power_on ( lteiot_t *ctx );
```

- `lteiot_send_cmd` Send command function. 
```c
void lteiot_send_cmd ( lteiot_t *ctx, char *cmd );
```

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
    Delay_ms ( 1000 );
    
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
    Delay_ms ( 500 );
    
    // ATI - product information
    lteiot_send_cmd( &lteiot, LTEIOT_CMD_ATI );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGMR - firmware version
    lteiot_send_cmd( &lteiot, LTEIOT_CMD_CGMR );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - deregister from network
    lteiot_send_cmd_with_parameter( &lteiot, LTEIOT_CMD_COPS, "2" );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CGDCONT - set sim apn
    lteiot_set_sim_apn( &lteiot, SIM_APN );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
    Delay_ms ( 500 );
     
    // CFUN - full funtionality
    lteiot_send_cmd_with_parameter( &lteiot, LTEIOT_CMD_CFUN, "1" );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // COPS - automatic mode
    lteiot_send_cmd_with_parameter( &lteiot, LTEIOT_CMD_COPS, "0" );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // CEREG - network registration status
    lteiot_send_cmd_with_parameter( &lteiot, LTEIOT_CMD_CEREG, "2" );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    // CIMI - request IMSI
    lteiot_send_cmd( &lteiot, LTEIOT_CMD_CIMI );
    app_error_flag = lteiot_rsp_check(  );
    lteiot_error_check( app_error_flag );
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
        Delay_ms ( 500 );
        
        // CEREG - network registration status
        lteiot_send_cmd_check( &lteiot, LTEIOT_CMD_CEREG );
        app_error_flag = lteiot_rsp_check(  );
        lteiot_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        // CSQ - signal quality
        lteiot_send_cmd( &lteiot, LTEIOT_CMD_CSQ );
        app_error_flag = lteiot_rsp_check(  );
        lteiot_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        // SMS message format - text mode
        lteiot_send_cmd_with_parameter( &lteiot, "AT+CMGF", "1" );
        app_error_flag = lteiot_rsp_check(  );
        lteiot_error_check( app_error_flag );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        
        for( ; ; )
        {   
            log_printf( &logger, "> Sending message to phone number...\r\n" );
            lteiot_send_text_message( &lteiot, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
            app_error_flag = lteiot_rsp_check(  );
            lteiot_error_check( app_error_flag );
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

> In order for the example to work, 
> user needs to set the phone number and sim apn to which he wants to send an SMS
> Enter valid data for the following macros: SIM_APN and PHONE_NUMBER_TO_MESSAGE.
>> E.g. 
   >> * SIM_APN "vipmobile"
   >> * PHONE_NUMBER_TO_MESSAGE "999999999"

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
