
# LTE IoT 5 click

> LTE IoT 5 Click is add-on board with compact and cost-effective secure cloud multi-band module solution designed for IoT applications. This board features the SARA-R510M8S, a cellular module that supports LTE-M/NB-IoT* bands with integrated high performance standard precision M8 GNSS receiver for global position acquisition from u-Blox.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lteiot5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lte-iot-5-click)

---


#### Click library

- **Author**        : Luka Filipovic
- **Date**          : Dec 2020.
- **Type**          : UART type


# Software Support

We provide a library for the LTEIoT5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for LTEIoT5 Click driver.
```

#### Standard key functions :

- Config Object Initialization function.
```
void lteiot5_cfg_setup ( lteiot5_cfg_t *cfg );
```

- Initialization function.
```
LTEIOT5_RETVAL lteiot5_init ( lteiot5_t *ctx, lteiot5_cfg_t *cfg );
```

- Click Default Configuration function.
```
void lteiot5_default_cfg ( lteiot5_t *ctx );
```

#### Example key functions :

> LTE IoT 5 data reading function.
```
err_t lteiot5_generic_read ( lteiot5_t *ctx, char *data_buf, uint16_t max_len );
```

> Send command function.
```
void lteiot5_send_cmd ( lteiot5_t *ctx, char *cmd );
```

> LTE IoT 5 power on.
```
void lteiot5_power_on ( lteiot5_t *ctx );
```

## Examples Description

> This example reads and processes data from LTE IoT 5 clicks.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and wake-up module and sets default configuration for connecting device to network.

```
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    lteiot5_cfg_t lteiot5_cfg;  /**< Click config object. */

    // Logger initialization.
    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );
    Delay_ms( 1000 );
    
    // Click initialization.
    lteiot5_cfg_setup( &lteiot5_cfg );
    LTEIOT5_MAP_MIKROBUS( lteiot5_cfg, MIKROBUS_1 );
    err_t init_flag  = lteiot5_init( &lteiot5, &lteiot5_cfg );
    if ( init_flag == UART_ERROR )
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    log_info( &logger, " Power on device... " );
    lteiot5_reset( &lteiot5 );
    lteiot5_power_on( &lteiot5 );
    
    lteiot5_send_cmd( &lteiot5, LTEIOT5_CMD_AT );
    Delay_ms( 500 );
    lteiot5_process(  );
    lteiot5_clear_app_buf(  );
    
    //AT
    lteiot5_send_cmd( &lteiot5, LTEIOT5_CMD_AT );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //ATI
    lteiot5_send_cmd( &lteiot5, LTEIOT5_CMD_ATI );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //ATI
    lteiot5_send_cmd( &lteiot5, LTEIOT5_CMD_CGMR );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //CFUN
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_CFUN, "0" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //COPS
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_COPS, "2" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //CGDCONT
    lteiot5_set_sim_apn( &lteiot5, SIM_APN );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //URAT
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_URAT, "7" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //UBANDMASK,
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_UBANDMASK, "0,185473183" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //CFUN
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_CFUN, "1" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms( 1000 );
    
    //CFUN
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_CFUN, "16" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms( 5000 );
    
    lteiot5_send_cmd_check( &lteiot5, LTEIOT5_CMD_CFUN );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //COPS
    lteiot5_send_cmd_check( &lteiot5, LTEIOT5_CMD_COPS );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //UANTR
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_UANTR, "0" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //CEREG
    lteiot5_send_cmd_with_parameter( &lteiot5, LTEIOT5_CMD_CEREG, "2" );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms( 500 );
    
    //CIMI
    lteiot5_send_cmd( &lteiot5, LTEIOT5_CMD_CIMI );
    app_error_flag = lteiot5_rsp_check();
    lteiot5_error_check( app_error_flag );
    Delay_ms( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task " );
    Delay_ms( 5000 );
}
```

### Application Task

Waits for device to connect to network and then sends SMS to selected phone number.

```
void application_task ( void )
{  
    if ( app_connection_status == WAIT_FOR_CONNECTION )
    {
        lteiot5_send_cmd_check( &lteiot5, LTEIOT5_CMD_CGATT );
        app_error_flag = lteiot5_rsp_check();
        lteiot5_error_check( app_error_flag );
        Delay_ms( 500 );
        
        lteiot5_send_cmd_check( &lteiot5, LTEIOT5_CMD_CEREG );
        app_error_flag = lteiot5_rsp_check();
        lteiot5_error_check( app_error_flag );
        Delay_ms( 500 );
        
        lteiot5_send_cmd( &lteiot5, LTEIOT5_CMD_CSQ );
        app_error_flag = lteiot5_rsp_check();
        lteiot5_error_check( app_error_flag );
        Delay_ms( 5000 );
    }
    else
    {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        lteiot5_send_cmd_with_parameter( &lteiot5, "AT+CMGF", "1" );
        app_error_flag = lteiot5_rsp_check();
        lteiot5_error_check( app_error_flag );
        Delay_ms( 3000 );
        
        for( ; ; )
        {   
            log_printf( &logger, "> Sending message to phone number...\r\n" );
            lteiot5_send_text_message( &lteiot5, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
            app_error_flag = lteiot5_rsp_check();
            lteiot5_error_check( app_error_flag );
            Delay_ms( 10000 );
        }
    }
}
```

## Note

> In order for the example to work, 
   user needs to set the phone number and sim apn to which he wants to send an SMS
>> Enter valid data for the following macros: SIM_APN and PHONE_NUMBER_TO_MESSAGE.
>>> E.g.\
    SIM_APN "vip.mobile"\
    PHONE_NUMBER_TO_MESSAGE "999999999"

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LTEIoT5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
