\mainpage Main Page

---
# Proximity 12 Click

Proximity 12 Click is a compact add-on board that contains a high-performance light and proximity sensing solution. This board features the TMD3719, an optical sensor that integrates ambient light sensing, proximity detection, and flicker detection sensing from AMS-AG.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proximity12_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/proximity-12-click)

---


#### Click library

- **Author**        : Stefan Filipovic
- **Date**          : Jun 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the Proximity12 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Proximity12 Click driver.

#### Standard key functions :

- `proximity12_cfg_setup` Config Object Initialization function.
```c
void proximity12_cfg_setup ( proximity12_cfg_t *cfg );
```

- `proximity12_init` Initialization function.
```c
err_t proximity12_init ( proximity12_t *ctx, proximity12_cfg_t *cfg );
```

- `proximity12_default_cfg` Click Default Configuration function.
```c
err_t proximity12_default_cfg ( proximity12_t *ctx );
```

#### Example key functions :

- `proximity12_read_proximity` This function reads the raw proximity value measured by the Click board.
```c
err_t proximity12_read_proximity ( proximity12_t *ctx, uint16_t *prox_data );
```

- `proximity12_read_als` This function reads all als data measured by the Click board.
```c
err_t proximity12_read_als ( proximity12_t *ctx, proximity12_als_data_t *als );
```

- `proximity12_set_led_isink` This function sets the LEDs sink scaler and current values.
```c
err_t proximity12_set_led_isink ( proximity12_t *ctx, uint8_t scaler, uint8_t current );
```

## Example Description

> This function demonstrates the use of Proximity 12 Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes the driver and performs the Click default configuration.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;                  /**< Logger config object. */
    proximity12_cfg_t proximity12_cfg;  /**< Click config object. */

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
    Delay_ms ( 100 );
    log_info( &logger, " Application Init " );

    // Click initialization.
    proximity12_cfg_setup( &proximity12_cfg );
    PROXIMITY12_MAP_MIKROBUS( proximity12_cfg, MIKROBUS_1 );
    err_t init_flag = proximity12_init( &proximity12, &proximity12_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    Delay_ms ( 100 );
    
    init_flag = proximity12_default_cfg ( &proximity12 );
    if ( PROXIMITY12_ERROR == init_flag ) 
    {
        log_error( &logger, " Default Cfg Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Reads the proximity and ALS values and displays the results on the USB UART approximately every 100ms.

```c

void application_task ( void )
{
    uint16_t prox_data = 0;
    proximity12_als_data_t als;
    err_t error_flag = proximity12_read_proximity ( &proximity12, &prox_data );
    error_flag |= proximity12_read_als ( &proximity12, &als );

    if ( PROXIMITY12_OK == error_flag )
    {
        log_printf( &logger, " - Proximity data -\r\n" );
        log_printf( &logger, " Proximity: %u\r\n", prox_data );
        log_printf( &logger, " - ALS data -\r\n" );
        log_printf( &logger, " Clear: %lu - Red: %lu - Green: %lu - Blue: %lu\r\n", als.clear,
                                                                                    als.red,
                                                                                    als.green, 
                                                                                    als.blue );
        
        log_printf( &logger, " Leakage: %lu - Wideband: %lu - IR1: %lu - IR2: %lu\r\n\r\n", als.leakage,
                                                                                            als.wideband,
                                                                                            als.ir1, 
                                                                                            als.ir2 );
    }
    Delay_ms ( 100 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.Proximity12

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
