
---
# Smart Buck 4 click

> Smart Buck 4 Click is a compact add-on board that contains a high-frequency synchronous step-down DC-DC converter. This board features the LTS3562, a quad synchronous step-down DC-DC regulator from Analog Devices. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/smartbuck4_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/smart-buck-4-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : May 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the Smart Buck 4 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for Smart Buck 4 Click driver.

#### Standard key functions :

- `smartbuck4_cfg_setup` Config Object Initialization function.
```c
void smartbuck4_cfg_setup ( smartbuck4_cfg_t *cfg );
```

- `smartbuck4_init` Initialization function.
```c
err_t smartbuck4_init ( smartbuck4_t *ctx, smartbuck4_cfg_t *cfg );
```

- `smartbuck4_default_cfg` Click Default Configuration function.
```c
err_t smartbuck4_default_cfg ( smartbuck4_t *ctx );
```

#### Example key functions :

- `smartbuck4_en_r40_reg` Smart Buck 4 enable 400A regulator function.
```c
void smartbuck4_en_r40_reg ( smartbuck4_t *ctx );
```

- `smartbuck4_send_command` Smart Buck 4 send command function.
```c
err_t smartbuck4_send_command ( smartbuck4_t *ctx, uint8_t addr, uint8_t data_in );
```

- `smartbuck4_disable_regulators` Smart Buck 4 disable regulators function.
```c
err_t smartbuck4_disable_regulators ( smartbuck4_t *ctx );
```

## Example Description

> This example demonstrates the use of the Smart Buck 4 Click board.
  This driver provides functions for device configurations 
  and for the setting of the output voltage.

**The demo application is composed of two sections :**

### Application Init

> Initialization of I2C module and log UART.
  After initializing the driver, the default configuration is executed 
  and the outputs are turned off.

```c

void application_init ( void ) 
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    smartbuck4_cfg_t smartbuck4_cfg;  /**< Click config object. */

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
    smartbuck4_cfg_setup( &smartbuck4_cfg );
    SMARTBUCK4_MAP_MIKROBUS( smartbuck4_cfg, MIKROBUS_1 );
    if ( I2C_MASTER_ERROR == smartbuck4_init( &smartbuck4, &smartbuck4_cfg ) ) 
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    if ( SMARTBUCK4_ERROR == smartbuck4_default_cfg ( &smartbuck4 ) )
    {
        log_error( &logger, " Default configuration." );
        for ( ; ; );
    }
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> Changes the output voltage every 5 seconds, starting from 0.6 V to 3.3V/3.7V 
 depending on the input voltage.

```c

void application_task ( void ) 
{
    for ( uint8_t n_cnt = SMARTBUCK4_REGULATOR_B_600_MV; 
          n_cnt <= SMARTBUCK4_REGULATOR_B_3700_MV; 
          n_cnt += SMARTBUCK4_REGULATOR_B_700_MV )
    {
        err_t error_flag = smartbuck4_send_command( &smartbuck4, SMARTBUCK4_REG_R600B_PROGRAM | 
                                                                 SMARTBUCK4_REG_R400B_PROGRAM | 
                                                                 SMARTBUCK4_REG_LDO_MODE, 
                                                                 SMARTBUCK4_ENABLE_REGULATOR | n_cnt );
        if ( SMARTBUCK4_OK == error_flag )
        {
            log_printf( &logger, " Set output to %d mV. \r\n", 
                        ( SMARTBUCK4_MIN_VOLTAGE + n_cnt * SMARTBUCK4_STEP ) );
        }
        else
        {
            log_error( &logger, " Transmission error occurred." );
            smartbuck4_disable_regulators( &smartbuck4 );
            for ( ; ; );
        }
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
        Delay_ms ( 1000 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.SmartBuck4

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
