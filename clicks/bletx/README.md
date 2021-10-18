\mainpage Main Page

---
# BLE TX click

BLE TX Click is a compact add-on board that contains a low-energy Bluetooth transmitter. This board features the AK1595, a Bluetooth 5.2 transmitter with incorporated proprietary algorithm software from AKM Semiconductor. The AK1595 transmitter simplifies wireless connectivity to a system with no need to develop complicated, proprietary microcontroller code. Bluetooth Low Energy compliant advertising transmission can be achieved by simply configuring the transmission power, data, and transmission start-trigger via the UART or I2C interface.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ble_tx_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/ble-tx-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the BleTx Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for BleTx Click driver.

#### Standard key functions :

- `bletx_cfg_setup` Config Object Initialization function.
```c
void bletx_cfg_setup ( bletx_cfg_t *cfg );
```

- `bletx_init` Initialization function.
```c
BLETX_RETVAL bletx_init ( bletx_t *ctx, bletx_cfg_t *cfg );
```

- `bletx_default_cfg` Click Default Configuration function.
```c
void bletx_default_cfg ( bletx_t *ctx );
```

#### Example key functions :

- `bletx_start_advertising` BLE TX start advertising function.
```c
err_t bletx_start_advertising ( bletx_t *ctx );
```

- `bletx_set_configuration` BLE TX configuration setting function
```c
err_t bletx_set_configuration ( bletx_t *ctx, bletx_adv_cfg_t adv_cfg );
```

- `bletx_create_eddystone_uri` BLE TX create Eddystone™ URI data packet function.
```c
err_t bletx_create_eddystone_uri ( bletx_t *ctx, bletx_eddystone_data_t adv_data );
```

## Example Description

> This library contains API for the Ble TX Click driver.
> This example processes data from Ble TX Click, Ble TX Click 
> Bluetooth® Low Energy compliant advertising transmission 
> can be achieved by simply configuring the transmission power, 
> data, and transmission - start trigger.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
> Initializes driver and set performs the default configuration.
> Configure Bluetooth Low Energy Beacons to transmit so-called advertising frames.
> Configuration of the Eddystone URI, UID, or TLM 
> Bluetooth Low Energy Beacons profile task depends on uncommented code.
> Eddystone ( URI ) : broadcasts a URL of at most 15 characters 
> that redirects to a website that is secured using SSL.
> Eddystone ( UID ) : broadcasts an identifying code 
> that allows apps to retrieve information from app servers. 
> Eddystone ( TLM ) : broadcasts information about the beacon,
> include battery level, sensor data, or other relevant information 
> to beacon administrators.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;      /**< Logger config object. */
    bletx_cfg_t bletx_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    bletx_cfg_setup( &bletx_cfg );
    BLETX_MAP_MIKROBUS( bletx_cfg, MIKROBUS_1 );
    err_t init_flag = bletx_init( &bletx, &bletx_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    bletx_default_cfg ( &bletx );
    log_info( &logger, " Application Task " );
    Delay_ms( 10 );

    adv_cfg.adv_ch_1_frequency = ADVCH1_37_Ch_2402_MHz;
    adv_cfg.adv_ch_2_frequency = ADVCH2_38_Ch_2426_MHz;
    adv_cfg.adv_ch_3_frequency = ADVCH3_39_Ch_2480_MHz;
    adv_cfg.tx_output_power = TX_POWER_0_dBm;
    adv_cfg.txdata_loop = 0;
    adv_cfg.txdata_cw = 0;
    adv_cfg.eventnum = 0;
    adv_cfg.advdelay_enb = 0x80;
    adv_cfg.avdintvl_interval_ms = 0;
    adv_cfg.crc_enb = 0x80;
    adv_cfg.white_enb = 0x40;
    adv_cfg.pdu_len = 39;
    
    adv_cfg.uuid[ 0 ] = 0x11;
    adv_cfg.uuid[ 1 ] = 0x22;
    adv_cfg.uuid[ 2 ] = 0x33;
    adv_cfg.uuid[ 3 ] = 0x44;
    adv_cfg.uuid[ 4 ] = 0x55;
    adv_cfg.uuid[ 5 ] = 0x66;
    
    bletx_set_configuration( &bletx, adv_cfg );
    Delay_ms( 100 );
    
    #ifdef URI
        adv_data.length_of_service_list = 3;
        adv_data.param_service_list = 3;
        adv_data.eddystone_id = BLETX_EDDYSTONE_SERVICE_UUID;
        adv_data.length_of_service_data = 13;
        adv_data.service_data = BLETX_EDDYSTONE_SERVICE_DATA_TYPE_VALUE;
        adv_data.frame_type_url = BLETX_EDDYSTONE_FRAME_TYPE_URL;
        adv_data.power = BLETX_TX_POWER_LVL_MODE_LOW;
        adv_data.spec_data = BLETX_EDDYSTONE_SPEC_DATA_HTTP_WWW;
        adv_data.advdata_url[ 0 ] = 'm';
        adv_data.advdata_url[ 1 ] = 'i';
        adv_data.advdata_url[ 2 ] = 'k';
        adv_data.advdata_url[ 3 ] = 'r';
        adv_data.advdata_url[ 4 ] = 'o';
        adv_data.advdata_url[ 5 ] = 'e';
        adv_data.domain = BLETX_CHARACTER_CODES_DOT_COM;
        
        bletx_create_eddystone_uri ( &bletx, adv_data );
    #endif
    
    #ifdef UID
        adv_data.length_of_service_list = 3;
        adv_data.param_service_list = 3;
        adv_data.eddystone_id = BLETX_EDDYSTONE_SERVICE_UUID;
        adv_data.length_of_service_data = 23;
        adv_data.service_data = BLETX_EDDYSTONE_SERVICE_DATA_TYPE_VALUE;
        adv_data.frame_type_url = BLETX_EDDYSTONE_FRAME_TYPE_UID;
        adv_data.power = BLETX_TX_POWER_LVL_MODE_LOW;          
        
        adv_data.name_space_id[ 0 ] = 0x01;
        adv_data.name_space_id[ 1 ] = 0x02;
        adv_data.name_space_id[ 2 ] = 0x03;
        adv_data.name_space_id[ 3 ] = 0x04;
        adv_data.name_space_id[ 4 ] = 0x05;
        adv_data.name_space_id[ 5 ] = 0x06;
        adv_data.name_space_id[ 6 ] = 0x07;
        adv_data.name_space_id[ 7 ] = 0x08;
        adv_data.name_space_id[ 8 ] = 0x09;
        adv_data.name_space_id[ 9 ] = 0x0A;
        
        adv_data.instance_id[ 0 ] = 0x01;
        adv_data.instance_id[ 1 ] = 0x23;
        adv_data.instance_id[ 2 ] = 0x45;
        adv_data.instance_id[ 3 ] = 0x67;
        adv_data.instance_id[ 4 ] = 0x89;
        adv_data.instance_id[ 5 ] = 0xAB;
        
        bletx_create_eddystone_uid ( &bletx, adv_data );
    #endif
    
    #ifdef TLM
        adv_data.length_of_service_list = 3;
        adv_data.param_service_list = 3;
        adv_data.eddystone_id = BLETX_EDDYSTONE_SERVICE_UUID;
        adv_data.length_of_service_data = 23;
        adv_data.service_data = BLETX_EDDYSTONE_SERVICE_DATA_TYPE_VALUE;
        adv_data.frame_type_url = BLETX_EDDYSTONE_FRAME_TYPE_TLM;
        adv_data.tlm_version = 0;          // TLM version
        adv_data.spec_data = BLETX_EDDYSTONE_SPEC_DATA_TLM;
        
        adv_data.battery_voltage = 3600;
        adv_data.beacon_temperature = 20.21;
        adv_data.pdu_count = 11223344;
        
        bletx_create_eddystone_tlm ( &bletx, adv_data );
    #endif
    
    Delay_ms( 100 );
}

```

### Application Task

> This is an example that shows the use of a Ble TX click board™.
> In this example, the application turns the selected advertising frames
> ON and OFF for a period of 10 seconds.

```c

void application_task ( void ) {  
    log_printf( &logger, ">>>\tStart Advertising \r\n" );
    bletx_start_advertising( &bletx );
    Delay_ms( 10000 );
    
    log_printf( &logger, ">>>\tStop Advertising \r\n" );
    bletx_stop_advertising( &bletx );
    Delay_ms( 10000 );
}

```

## Note

> For scanning BLE TX click board™ BLE Scanner is a recommended Android application 
> and you can find it at the link:
> https://play.google.com/store/apps/details?id=com.macdom.ble.blescanner

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.BleTx

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
