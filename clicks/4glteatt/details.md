
---
# 4G LTE-ATT  click

4G LTE-AT&T click is an LTE Cat 1 / UMTS multimodecellular network solution, featuring the compact LARA-R2 series modem from u-blox. This module supports up to four LTE bands and up to two UMTS bands. It also features a full range of options for the high speed cellular networking and communication, such as the network indication, full embedded TCP/UDP stack, HTTP and HTTPS transfer protocols, IPv4/IPv6 dual-stack support, secondary antenna for the RX diversity, antenna detection, jamming signal detection, embedded TLS 1.2 protocol for the improved security and more. 4G LARA click can achieve data rates up to 10.3 Mbps/5.2 Mbps (downlink/uplink).

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/4g-lte-att-click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/4g-lte-att-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jun 2021.
- **Type**          : UART type


# Software Support

We provide a library for the C4GLTEATT Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for C4GLTEATT Click driver.

#### Standard key functions :

- `c4glteatt_cfg_setup` Config Object Initialization function.
```c
void c4glteatt_cfg_setup ( c4glteatt_cfg_t *cfg );
```

- `c4glteatt_init` Initialization function.
```c
err_t c4glteatt_init ( c4glteatt_t *ctx, c4glteatt_cfg_t *cfg );
```

#### Example key functions :

- `c4glteatt_module_power_on` This function powers ON the module.
```c
void c4glteatt_module_power_on ( c4glteatt_t *ctx );
```

- `c4glteatt_send_cmd_with_parameter` This function sends a command with specified parameter to the click module.
```c
void c4glteatt_send_cmd_with_parameter ( c4glteatt_t *ctx, char *at_cmd_buf, char *param_buf );
```

- `c4glteatt_send_cmd_parameter_check` This function checks the command that is sent.
```c
void c4glteatt_send_cmd_parameter_check ( c4glteatt_t *ctx, char *at_cmd_buf );
```

## Example Description

> This example reads and processes data from 4G LTE ATT click.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and powers up the module, then sets default configuration for connecting the device to network.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    c4glteatt_cfg_t c4glteatt_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_info( &logger, " Application Init " );

    // Click initialization.

    c4glteatt_cfg_setup( &c4glteatt_cfg );
    C4GLTEATT_MAP_MIKROBUS( c4glteatt_cfg, MIKROBUS_1 );
    c4glteatt_init( &c4glteatt, &c4glteatt_cfg );
    
    c4glteatt_module_power_on( &c4glteatt );
    
    // dummy read
    c4glteatt_process( );
    c4glteatt_clear_app_buf( );
    
    // AT
    c4glteatt_send_cmd( &c4glteatt, C4GLTEATT_CMD_AT );
    app_error_flag = c4glteatt_rsp_check( );
    c4glteatt_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // ATI - product information
    c4glteatt_send_cmd( &c4glteatt, C4GLTEATT_CMD_ATI );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGMR - firmware version
    c4glteatt_send_cmd( &c4glteatt, C4GLTEATT_CMD_CGMR );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CMEE - Report Mobile Equipment Error
    c4glteatt_send_cmd_with_parameter( &c4glteatt, C4GLTEATT_CMD_CMEE, "2" );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - deregister from network
    c4glteatt_send_cmd_with_parameter( &c4glteatt, C4GLTEATT_CMD_COPS, "2" );
    Delay_ms( 4000 );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CGDCONT - set sim apn
    c4glteatt_set_sim_apn( &c4glteatt, SIM_APN );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CFUN - full funtionality
    c4glteatt_send_cmd_with_parameter( &c4glteatt, C4GLTEATT_CMD_CFUN, "1" );
    Delay_ms( 2000 );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // COPS - automatic mode
    c4glteatt_send_cmd_with_parameter( &c4glteatt, C4GLTEATT_CMD_COPS, "0" );
    Delay_ms( 4000 );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
    Delay_ms( 500 );
    
    // CREG - network registration status
    c4glteatt_send_cmd_with_parameter( &c4glteatt, C4GLTEATT_CMD_CREG, "1" );
    app_error_flag = c4glteatt_rsp_check(  );
    c4glteatt_error_check( app_error_flag );
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
        c4glteatt_send_cmd_check( &c4glteatt, C4GLTEATT_CMD_CREG );
        app_error_flag = c4glteatt_rsp_check(  );
        c4glteatt_error_check( app_error_flag );
        Delay_ms( 500 );
        
        // CSQ - signal quality
        c4glteatt_send_cmd( &c4glteatt, C4GLTEATT_CMD_CSQ );
        app_error_flag = c4glteatt_rsp_check(  );
        c4glteatt_error_check( app_error_flag );
        Delay_ms( 3000 );
    } else {
        log_info( &logger, "CONNECTED TO NETWORK" );
        
        // SMS message format - PDU mode
        c4glteatt_send_cmd_with_parameter( &c4glteatt, C4GLTEATT_CMD_CMGF, "0" );
        app_error_flag = c4glteatt_rsp_check(  );
        c4glteatt_error_check( app_error_flag );
        Delay_ms( 3000 );
        
        for( ; ; ) {   
            log_printf( &logger, "> Sending message to phone number...\r\n" );
            c4glteatt_send_sms_pdu ( &c4glteatt, SIM_SMSC, PHONE_NUMBER_TO_MESSAGE, MESSAGE_CONTENT );
            app_error_flag = c4glteatt_rsp_check(  );
            c4glteatt_error_check( app_error_flag );
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
- Click.C4GLTEATT

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
