\mainpage Main Page

---
# 3G-EA click

3G-EA click is a versatile cellular network communication solution, featuring the compact 3G UMTS/HSPA Quectel UG95 module. This module features a full set of options for the cellular networking and communication, such as the network indication, embedded TCP/UDP stack, HTTP/HTTPS stack, full GSM/GPRS/EDGE implementation, UMTS/HSDPA/HSUPA protocol implementation and more. 3G-EA click features data-rates of 7.2 Mb/s (downlink) and 5.76 Mb/s (uplink) in HSPA mode. Onboard 16bit audio CODEC IC adds high-quality voice communication capability.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/3g_ea_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/3g-ea-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : UART type


# Software Support

We provide a library for the C3GEA Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for C3GEA Click driver.

#### Standard key functions :

- `c3gea_cfg_setup` Config Object Initialization function.
```c
void c3gea_cfg_setup ( c3gea_cfg_t *cfg );
```

- `c3gea_init` Initialization function.
```c
err_t c3gea_init ( c3gea_t *ctx, c3gea_cfg_t *cfg );
```

#### Example key functions :

- `c3gea_module_power` This function powers ON/OFF the module.
```c
void c3gea_module_power ( c3gea_t *ctx, uint8_t state );
```

- `c3gea_send_cmd_with_parameter` This function sends a command with specified parameter to the click module.
```c
void c3gea_send_cmd_with_parameter ( c3gea_t *ctx, char *at_cmd_buf, char *param_buf );
```

- `c3gea_send_sms_text` This function sends text message to a phone number.
```c
void c3gea_send_sms_text ( c3gea_t *ctx, char *phone_number, char *sms_text );
```

## Example Description

> This example reads and processes data from 3G EA click.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and powers up the module, then sets default configuration for connecting the device to network.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    c3gea_cfg_t c3gea_cfg;  /**< Click config object. */

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

    c3gea_cfg_setup( &c3gea_cfg );
    C3GEA_MAP_MIKROBUS( c3gea_cfg, MIKROBUS_1 );
    c3gea_init( &c3gea, &c3gea_cfg );

    c3gea_module_power( &c3gea, C3GEA_MODULE_POWER_ON );
    
    // dummy read
    c3gea_process( );
    c3gea_clear_app_buf( );
    
    // AT
    c3gea_send_cmd( &c3gea, C3GEA_CMD_AT );
    app_error_flag = c3gea_rsp_check( );
    c3gea_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // ATI - product information
    c3gea_send_cmd( &c3gea, C3GEA_CMD_ATI );
    app_error_flag = c3gea_rsp_check(  );
    c3gea_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGMR - firmware version
    c3gea_send_cmd( &c3gea, C3GEA_CMD_CGMR );
    app_error_flag = c3gea_rsp_check(  );
    c3gea_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CMEE - Report Mobile Equipment Error
    c3gea_send_cmd_with_parameter( &c3gea, C3GEA_CMD_CMEE, "2" );
    app_error_flag = c3gea_rsp_check(  );
    c3gea_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - deregister from network
    c3gea_send_cmd_with_parameter( &c3gea, C3GEA_CMD_COPS, "2" );
    Delay_ms( 4000 );
    app_error_flag = c3gea_rsp_check(  );
    c3gea_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGDCONT - set sim apn
    c3gea_set_sim_apn( &c3gea, SIM_APN );
    app_error_flag = c3gea_rsp_check(  );
    c3gea_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CFUN - full funtionality
    c3gea_send_cmd_with_parameter( &c3gea, C3GEA_CMD_CFUN, "1" );
    app_error_flag = c3gea_rsp_check(  );
    c3gea_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - automatic mode
    c3gea_send_cmd_with_parameter( &c3gea, C3GEA_CMD_COPS, "0" );
    Delay_ms( 4000 );
    app_error_flag = c3gea_rsp_check(  );
    c3gea_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CREG - network registration status
    c3gea_send_cmd_with_parameter( &c3gea, C3GEA_CMD_CREG, "1" );
    app_error_flag = c3gea_rsp_check(  );
    c3gea_error_check( app_error_flag );
    Delay_ms( 500 );
    
    app_buf_len = 0;
    app_buf_cnt = 0;
    app_connection_status = WAIT_FOR_CONNECTION;
    log_info( &logger, " Application Task " );
    Delay_ms( 5000 );
}

```

### Application Task

> Waits for device to connect to network and then sends a desired SMS to the selected phone number approximately every 30 seconds.

```c

void application_task ( void ) {
     if ( app_connection_status == WAIT_FOR_CONNECTION ) {
        // CREG - network registration status
        c3gea_send_cmd_check( &c3gea, C3GEA_CMD_CREG );
        app_error_flag = c3gea_rsp_check(  );
        c3gea_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CSQ - signal quality
        c3gea_send_cmd( &c3gea, C3GEA_CMD_CSQ );
        app_error_flag = c3gea_rsp_check(  );
        c3gea_error_check( app_error_flag );
        Delay_ms( 3000 );
    } else {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        // SMS message format - PDU mode
        c3gea_send_cmd_with_parameter( &c3gea, C3GEA_CMD_CMGF, "0" );
        app_error_flag = c3gea_rsp_check(  );
        c3gea_error_check( app_error_flag );
        Delay_ms( 3000 );
        
        for( ; ; ) {   
            log_printf( &logger, "> Sending message to phone number...\r\n" );
            c3gea_send_sms_pdu ( &c3gea, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
            app_error_flag = c3gea_rsp_check(  );
            c3gea_error_check( app_error_flag );
            Delay_ms( 10000 );
            Delay_ms( 10000 );
            Delay_ms( 10000 );
        }
    }
}

```

## Note

> In order for the example to work, user needs to set the phone number to which he wants 
> to send an SMS, and also will need to set an APN and SMSC (required for PDU mode only) of entered SIM card.
> Enter valid data for the following macros: SIM_APN, SIM_SMSC and PHONE_NUMBER_TO_MESSAGE.
>> E.g. 
   >> * SIM_APN "vipmobile"
   >> * SIM_SMSC "+381610401"
   >> * PHONE_NUMBER_TO_MESSAGE "+381659999999"

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.C3GEA

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
