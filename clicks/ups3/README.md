\mainpage Main Page

---
# UPS 3 Click

UPS 3 Click is a compact add-on board that represents a bidirectional active charge/balancing solution. This board features the LTC3110, a bidirectional buck-boost DC/DC regulator/charger combination with selectable operation modes for charging and system backup from Analog Devices. It can autonomously transition from Charge to Backup mode or switch modes based on an external command. A proprietary low noise switching algorithm optimizes efficiency with capacitor/battery voltages above, below, or equal to the system output voltage. Additional features include voltage supervisors for direction control and end of a charge and a general-purpose comparator with open-collector output for interfacing with MCU. This Click board™ is suitable for a backup power source for a wide range of battery-operated embedded applications.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/ups3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/ups-3)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2020.
- **Type**          : GPIO type


# Software Support

We provide a library for the Ups3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for Ups3 Click driver.
```

#### Standard key functions :

- Config Object Initialization function.
```
void ups3_cfg_setup ( ups3_cfg_t *cfg );
```

- Initialization function.
```
UPS3_RETVAL ups3_init ( ups3_t *ctx, ups3_cfg_t *cfg );
```

- Click Default Configuration function.
```
void ups3_default_cfg ( ups3_t *ctx );
```

#### Example key functions :

- UPS 3 enable device function.
```
err_t ups3_set_enable ( ups3_t *ctx, uint8_t enable );ON>
```

- UPS 3 get error function.
```
uint8_t ups3_get_error ( ups3_t *ctx );
```

 UPS 3 get charge/backup mode function.
```
uint8_t ups3_get_chrg ( ups3_t *ctx );
```

## Examples Description

> This application demonstrates the use of UPS 3 Click board. 

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enable's - GPIO, also write log.

```
void application_init ( void ) {
    log_cfg_t log_cfg;    /**< Logger config object. */
    ups3_cfg_t ups3_cfg;  /**< Click config object. */

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
    log_printf( &logger, "\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    ups3_cfg_setup( &ups3_cfg );
    UPS3_MAP_MIKROBUS( ups3_cfg, MIKROBUS_1 );
    if ( ups3_init( &ups3, &ups3_cfg ) == DIGITAL_OUT_UNSUPPORTED_PIN ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    ups3_default_cfg ( &ups3 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 100 );
}
```

### Application Task

> With this example we show the operation of UPS 3 clicks.
> This example shows an autonomously transition from charge to backup mode.
> Results are being sent to the Usart Terminal where you can track their changes. 

```
void application_task ( void ) {      
    if ( ups3_get_error( &ups3 ) == UPS3_GET_ERROR_CMPIN_OK ) {
        if ( ups3_get_cap_ok( &ups3 ) != cok_status ) {
            new_status = UPS3_STATUS_NEW; 
            cok_status = ups3_get_cap_ok( &ups3 );
        } else {
            new_status = UPS3_STATUS_OLD;    
        }
    
        if ( new_status == UPS3_STATUS_NEW ) {
            ups3_hw_reset( &ups3 );
            new_status = UPS3_STATUS_OLD;
        }
        
        if ( ( ups3_get_chrg( &ups3 ) == UPS3_GET_CHRG_BACKUP_MODE ) && 
             ( ups3_get_cap_ok( &ups3 ) == UPS3_GET_CAP_OK_FBV_LOW ) ) {
            log_printf( &logger, "      Backup Mode ON      \r\n" );
        }
        
        if ( ups3_get_cap_ok( &ups3 ) == UPS3_GET_CAP_OK_FBV_HIGH ) {
            log_printf( &logger, "       Vcap charged       \r\n" );
        }
    } else {
        log_printf( &logger, "      Backup Mode OFF     \r\n" );
        log_printf( &logger, " Turn ON the Power Supply \r\n" );
            
        while ( ups3_get_error( &ups3 ) == UPS3_GET_ERROR_CMPIN_EMPTY ) {
            Delay_ms ( 100 );   
        }
            
        ups3_hw_reset( &ups3 );
        Delay_ms ( 100 );
    }
    
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Ups3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
