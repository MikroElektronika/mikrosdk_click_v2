
---
# LightRanger 5 click

LightRanger 5 Click is a compact add-on board that contains a ranging sensor with multi-target detection. This board features the TMF8801, a dToF (direct time of flight) optical distance sensor achieving up to 2500mm target detection distance from company AMS-TAOS. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/lightranger_5_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/lightranger-5-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Mar 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the LightRanger5 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for LightRanger5 Click driver.

#### Standard key functions :

- `lightranger5_cfg_setup` Config Object Initialization function.
```c
void lightranger5_cfg_setup ( lightranger5_cfg_t *cfg );
```

- `lightranger5_init` Initialization function.
```c
LIGHTRANGER5_RETVAL lightranger5_init ( lightranger5_t *ctx, lightranger5_cfg_t *cfg );
```

- `lightranger5_default_cfg` Click Default Configuration function.
```c
void lightranger5_default_cfg ( lightranger5_t *ctx );
```

#### Example key functions :

- `lightranger5_get_status` LightRanger 5 get status function.
```c
err_t lightranger5_get_status ( lightranger5_t *ctx, uint8_t *status );
```

- `lightranger5_set_factory_calib_data` LightRanger 5 set factory calib data function.
```c
err_t lightranger5_set_factory_calib_data ( lightranger5_t *ctx, uint8_t *factory_calib_data );
```

- `lightranger5_measure_distance` LightRanger 5 measure distance function.
```c
uint16_t lightranger5_measure_distance ( lightranger5_t *ctx );
```

## Example Description

> This is an example that demonstrates the use of the LightRanger 5 click board.
> This demo application shows an example of distance measurement.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module, log UART and additional pins.
> After driver initialization and default settings,
> the app performs and check factory calibrationa and 
> check and wait for OK status. This process takes a few seconds, so please wait.
> After current status is OK, app performs the configuration of the TMF8801 sensor:
> read and write calibration data, set algorithm state and command data. 

```c

void application_init ( void ) {
    log_cfg_t log_cfg;                    /**< Logger config object. */
    lightranger5_cfg_t lightranger5_cfg;  /**< Click config object. */

    // Logger initialization.

    LOG_MAP_USB_UART( log_cfg );
    log_cfg.level = LOG_LEVEL_DEBUG;
    log_cfg.baud = 115200;
    log_init( &logger, &log_cfg );
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    lightranger5_cfg_setup( &lightranger5_cfg );
    LIGHTRANGER5_MAP_MIKROBUS( lightranger5_cfg, MIKROBUS_1 );
    err_t init_flag = lightranger5_init( &lightranger5, &lightranger5_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    lightranger5_default_cfg( &lightranger5 );
    log_info( &logger, " Application Task " );
    Delay_ms( 100 );
    
    if ( !lightranger5_check_factory_calibration( &lightranger5 ) ) {
        log_info( &logger, " Factory calibration success." );
    } else {
        log_info( &logger, " Factory calibration FAILED." );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    
    do {
        lightranger5_get_status( &lightranger5, &status );
        
        if ( status_old != status ) {
            if ( status < LIGHTRANGER5_STATUS_OK ) {
                display_status_no_error( );    
            } else {
                display_status_error( );   
            }  
            status_old = status;
        }
        Delay_ms( 100 );
    } while ( status );
    
    lightranger5_get_factory_calib_data( &lightranger5, factory_calib_data );
    
    log_printf( &logger, "------------------------------\r\n" );
    log_printf( &logger, " factory_calib_data[ 14 ] =\r\n { " );
    
    for ( uint8_t n_cnt = 0 ; n_cnt < 14 ; n_cnt++ ) {
        log_printf( &logger, "0x%.2X, ", factory_calib_data[ n_cnt ] );
    }
    
    log_printf( &logger, "};\r\n" );
    log_printf( &logger, "------------------------------\r\n" );
    
    lightranger5_set_command( &lightranger5, LIGHTRANGER5_CMD_DL_CALIB_AND_STATE );

    lightranger5_set_factory_calib_data( &lightranger5, factory_calib_data );

    lightranger5_set_algorithm_state_data( &lightranger5, tmf8801_algo_state );
    
    lightranger5_set_command_data( &lightranger5, command_data );
    
    lightranger5_get_status( &lightranger5, &status );
        
    if ( status_old != status ) {
        if ( status < LIGHTRANGER5_STATUS_OK ) {
            display_status_no_error( );    
        } else {
            display_status_error( );   
        }  
        status_old = status;
    }
    
    lightranger5_get_currently_run_app( &lightranger5, &appid_data );
    
    if ( appid_data == LIGHTRANGER5_APPID_MEASUREMENT ) {
        log_printf( &logger, " Measurement app running.\r\n" );
    }
    else if ( appid_data == LIGHTRANGER5_APPID_BOOTLOADER ) {
        log_printf( &logger, " Bootloader running.\r\n" );
    } else {
        log_printf( &logger, " Result: 0x%X\r\n", appid_data );    
    }
    
    log_printf( &logger, "------------------------------\r\n" );
}

```

### Application Task

> This is an example that shows the use of a LightRanger 5 click board.
> A new data ready is checked as soon as possible which signals 
> the time required for the ranging sensor to perform the distance measurement.
> Results are being sent to the Usart Terminal where you can track their changes.

```c

void application_task ( void ) {
    
    if ( lightranger5_check_data_ready( &lightranger5 ) == LIGHTRANGER5_DATA_IS_READY ) {
        uint16_t distance_mm = lightranger5_measure_distance( &lightranger5 );
        
        if ( distance_mm ) {
            log_printf( &logger, "       Distance : %ld mm\r\n", distance_mm );    
        } else {
            log_printf( &logger, "         Out of range    \r\n", distance_mm );    
        }
        
        log_printf( &logger, "------------------------------\r\n" );
    }
    
    Delay_ms( 1000 );
}

```

## Note

> <NOTE_IF_REQUIRED>

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.LightRanger5

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
