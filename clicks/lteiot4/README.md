
---
# LTE IoT 4 Click

> [LTE IoT 4 Click](https://www.mikroe.com/?pid_product=MIKROE-4477) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-4477&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Luka Filipovic
- **Date**          : Dec 2020.
- **Type**          : UART type

# Software Support

## Example Description

> This example reads and processes data from LTE IoT 4 Clicks.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.LTEIoT4

### Example Key Functions

- `lteiot4_cfg_setup` Config Object Initialization function.
```c
void lteiot4_cfg_setup ( lteiot4_cfg_t *cfg );
```

- `lteiot4_init` Initialization function.
```c
err_t lteiot4_init ( lteiot4_t *ctx, lteiot4_cfg_t *cfg );
```

- `lteiot4_default_cfg` Click Default Configuration function.
```c
void lteiot4_default_cfg ( lteiot4_t *ctx );
```

- `lteiot4_set_rst` Sets state of the rst pin setting.
```c
void lteiot4_set_rst ( lteiot4_t *ctx, uint8_t state );
```

- `lteiot4_send_cmd` Send command function.
```c
void lteiot4_send_cmd ( lteiot4_t *ctx, char *cmd );
```

- `lteiot4_set_sim_apn` Set sim card APN.
```c
void lteiot4_set_sim_apn ( lteiot4_t *ctx, char *sim_apn );
```

### Application Init

> Initializes driver and wake-up module.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    lteiot4_cfg_t lteiot4_cfg;    /**< Click config object. */

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
    lteiot4_cfg_setup( &lteiot4_cfg );
    LTEIOT4_MAP_MIKROBUS( lteiot4_cfg, MIKROBUS_1 );
    err_t init_flag  = lteiot4_init( &lteiot4, &lteiot4_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Power up device... " );
    lteiot4_default_cfg ( &lteiot4 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    lteiot4_process(  );
    lteiot4_process(  );
    lteiot4_process(  );
    lteiot4_clear_app_buf(  );
    
    //AT
    log_info( &logger, " Communication test " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_AT );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CGMM
    log_info( &logger, " Module version " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_MODULE_VERSION );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CGMR
    log_info( &logger, " FW version " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_FW_VERSION );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CFUN
    log_info( &logger, " Flight mode " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_FLIGHT_MODE );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //XSYSTEMMODE
    log_info( &logger, " Enable NB network " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_NBIOT_MODE );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CIND
    log_info( &logger, " Enable service and messages " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_ENABLE_NET_SMS );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CFUN
    log_info( &logger, " Full functionalty mode " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_FULL_FUNCTION );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CGDCONT
    log_info( &logger, " Set APN " );
    lteiot4_set_sim_apn( &lteiot4, SIM_APN );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //COPS
    log_info( &logger, " Set automatic network search " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_AUTO_NET_SRC );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CEREG
    log_info( &logger, " Activate search for network  " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_SEARCH_NET );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    //CIMI
    log_info( &logger, " SIM test " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_SIM_TEST );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms ( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task\r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
}
```

### Application Task

> Reads the received data and parses it.

```c
void application_task ( void )
{
    if ( app_connection_status == WAIT_FOR_CONNECTION )
    {
        //CEREG
        log_info( &logger, " Check connection  " );
        lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_CHECK_CONNECTION );
        app_error_flag = lteiot4_rsp_check();
        lteiot4_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        //CEREG
        log_info( &logger, " Check network status  " );
        lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_CHECK_REGISTARTION );
        app_error_flag = lteiot4_rsp_check();
        lteiot4_error_check( app_error_flag );
        Delay_ms ( 500 );
        
        //CEREG
        log_info( &logger, " Check signal quality  " );
        lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_SIGNAL_QUALITY );
        app_error_flag = lteiot4_rsp_check();
        lteiot4_error_check( app_error_flag );
        log_printf( &logger, "-------------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK\r\n" );
        log_printf( &logger, "-------------------------------\r\n" );
        //CCLK
        log_info( &logger, " Set Time " );
        lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_SET_DUMMY_CLOCK );
        app_error_flag = lteiot4_rsp_check();
        lteiot4_error_check( app_error_flag );
        log_printf( &logger, "-------------------------------\r\n" );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        
        for(;;)
        {
            //XTEMP
            log_info( &logger, " Check Temperature " );
            lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_CHECK_TEMPERATURE );
            app_error_flag = lteiot4_rsp_check();
            lteiot4_error_check( app_error_flag );
            Delay_ms ( 500 );
            //CCLK
            log_info( &logger, " Check Time " );
            lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_CHECK_CLOCK );
            app_error_flag = lteiot4_rsp_check();
            lteiot4_error_check( app_error_flag );
            log_printf( &logger, "-------------------------------\r\n" );
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

> In order for the example to work, enter valid data for the following macros: SIM_APN.
>> E.g. SIM_APN "vip.mobile"

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
