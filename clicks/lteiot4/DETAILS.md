
---
# LTE IoT 4 click

LTE IoT 4 Click is a compact add-on board that contains an IoT module with worldwide coverage. This board features the nRF9160, highly integrated, low-power SiP with LTE-M/NB-IoT and GPS from Nordic Semiconductor.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lte_iot_4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lte-iot-4-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Dec 2020.
- **Type**          : UART type


# Software Support

We provide a library for the LTEIoT4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for LTEIoT4 Click driver.
```

#### Standard key functions :

- Config Object Initialization function.
```
void lteiot4_cfg_setup ( lteiot4_cfg_t *cfg );
```

- Initialization function.
```
LTEIOT4_RETVAL lteiot4_init ( lteiot4_t *ctx, lteiot4_cfg_t *cfg );
```

- Click Default Configuration function.
```
void lteiot4_default_cfg ( lteiot4_t *ctx );
```

#### Example key functions :

> Sets state of the rst pin setting.
```
void lteiot4_set_rst ( lteiot4_t *ctx, uint8_t state );
```

> Send command function.
```
void lteiot4_send_cmd ( lteiot4_t *ctx, char *cmd );
```

> Set sim card APN.
```
void lteiot4_set_sim_apn ( lteiot4_t *ctx, char *sim_apn );
```

## Examples Description

This example reads and processes data from LTE IoT 4 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and wake-up module.

```
void application_init ( void )
{
    log_cfg_t log_cfg;          /**< Logger config object. */
    lteiot4_cfg_t lteiot4_cfg;    /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );
    Delay_ms( 1000 );
    
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
    Delay_ms( 5000 );
    
    lteiot4_process(  );
    lteiot4_process(  );
    lteiot4_process(  );
    lteiot4_clear_app_buf(  );
    
    //AT
    log_info( &logger, " Communication test " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_AT );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //CGMM
    log_info( &logger, " Module version " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_MODULE_VERSION );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //CGMR
    log_info( &logger, " FW version " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_FW_VERSION );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //CFUN
    log_info( &logger, " Flight mode " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_FLIGHT_MODE );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //XSYSTEMMODE
    log_info( &logger, " Enable NB network " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_NBIOT_MODE );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //CIND
    log_info( &logger, " Enable service and messages " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_ENABLE_NET_SMS );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //CFUN
    log_info( &logger, " Full functionalty mode " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_FULL_FUNCTION );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //CGDCONT
    log_info( &logger, " Set APN " );
    lteiot4_set_sim_apn( &lteiot4, SIM_APN );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //COPS
    log_info( &logger, " Set automatic network search " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_AUTO_NET_SRC );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //CEREG
    log_info( &logger, " Activate search for network  " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_SEARCH_NET );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //CIMI
    log_info( &logger, " SIM test " );
    lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_SIM_TEST );
    app_error_flag = lteiot4_rsp_check();
    lteiot4_error_check( app_error_flag );
    Delay_ms( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task\r\n" );
    log_printf( &logger, "-------------------------------\r\n" );
    Delay_ms( 3000 );
}
```

### Application Task

> Reads the received data and parses it.

```
void application_task ( void )
{
    if ( app_connection_status == WAIT_FOR_CONNECTION )
    {
        //CEREG
        log_info( &logger, " Check connection  " );
        lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_CHECK_CONNECTION );
        app_error_flag = lteiot4_rsp_check();
        lteiot4_error_check( app_error_flag );
        Delay_ms( 500 );
        
        //CEREG
        log_info( &logger, " Check network status  " );
        lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_CHECK_REGISTARTION );
        app_error_flag = lteiot4_rsp_check();
        lteiot4_error_check( app_error_flag );
        Delay_ms( 500 );
        
        //CEREG
        log_info( &logger, " Check signal quality  " );
        lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_SIGNAL_QUALITY );
        app_error_flag = lteiot4_rsp_check();
        lteiot4_error_check( app_error_flag );
        log_printf( &logger, "-------------------------------\r\n" );
        Delay_ms( 5000 );
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
        Delay_ms( 3000 );
        
        for(;;)
        {
            //XTEMP
            log_info( &logger, " Check Temperature " );
            lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_CHECK_TEMPERATURE );
            app_error_flag = lteiot4_rsp_check();
            lteiot4_error_check( app_error_flag );
            Delay_ms( 500 );
            //CCLK
            log_info( &logger, " Check Time " );
            lteiot4_send_cmd( &lteiot4, LTEIOT4_CMD_CHECK_CLOCK );
            app_error_flag = lteiot4_rsp_check();
            lteiot4_error_check( app_error_flag );
            log_printf( &logger, "-------------------------------\r\n" );
            Delay_ms( 5000 );
        }
    }
}
```

## Note

> In order for the example to work, enter valid data for the following macros: SIM_APN.
>> E.g. SIM_APN "vip.mobile"

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LTEIoT4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
