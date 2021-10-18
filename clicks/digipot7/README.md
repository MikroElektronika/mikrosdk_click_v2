\mainpage Main Page

---
# DIGI POT 7 click

DIGI POT 7 Click is a compact add-on board used as a digitally controlled potentiometer. This board features the AD5175, a single-channel 1024-position digital rheostat with less than ±1% end-to-end resistor tolerance error and 50-time programmable wiper memory from Analog Devices. This I2C configurable IC is designed to operate as a variable resistor for analog signals, within the voltage range of single-supply operation at 2.7 V to 5.5 V.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/digipot7_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/digi-pot-7-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the DIGIPOT7 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for DIGIPOT7 Click driver.

#### Standard key functions :

- `digipot7_cfg_setup` Config Object Initialization function.
```c
void digipot7_cfg_setup ( digipot7_cfg_t *cfg );
```

- `digipot7_init` Initialization function.
```c
err_t digipot7_init ( digipot7_t *ctx, digipot7_cfg_t *cfg );
```

#### Example key functions :

- `digipot7_hw_reset` Hardware reset function
```c
void digipot7_hw_reset ( digipot7_t *ctx );
```

- `digipot7_read_rdac` The function read a 10-bit RDAC data
```c
uint16_t digipot7_read_rdac ( digipot7_t *ctx );
```

- `digipot7_write_rdac` The function writes a 10-bit RDAC data
```c
void digipot7_write_rdac ( digipot7_t *ctx, uint16_t rdac_data );
```

## Example Description

> This is an example that demonstrate the use of the DIGI POT 7 click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization enables I2C, perform a hardware reset, enable write and set to normal operating mode, also write log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    digipot7_cfg_t digipot7_cfg;  /**< Click config object. */

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
    digipot7_cfg_setup( &digipot7_cfg );
    DIGIPOT7_MAP_MIKROBUS( digipot7_cfg, MIKROBUS_1 );
    err_t init_flag = digipot7_init( &digipot7, &digipot7_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, " Hardware Reset \r\n" );
    digipot7_hw_reset( &digipot7 );
    Delay_ms( 100 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, " Enable Write \r\n" );
    digipot7_enable_write( &digipot7 );
    Delay_ms( 100 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_printf( &logger, " Set normal operating mode \r\n" );
    digipot7_operating_mode( &digipot7, DIGIPOT7_NORMAL_MODE );
    Delay_ms( 100 );
    
    log_printf( &logger, "----------------------------\r\n" );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "----------------------------\r\n" );
}

```

### Application Task

> In this example we set different resistance values: 1.024 kOhm, 2.048 kOhm, 4.096 kOhm and 8.192 kOhm. Results are being sent to the Usart Terminal where you can track their changes. All data logs write on USB uart changes approximately for every 5 sec.

```c

void application_task ( void ) {
    log_printf( &logger, " Set Resistance: 1.024 kOhm \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    digipot7_set_resistance( &digipot7, 1024 );
    Delay_ms( 5000 );
    
    log_printf( &logger, " Set Resistance: 2.048 kOhm \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    digipot7_set_resistance( &digipot7, 2048 );
    Delay_ms( 5000 );
    
    log_printf( &logger, " Set Resistance: 4.096 kOhm \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    digipot7_set_resistance( &digipot7, 4096 );
    Delay_ms( 5000 );
    
    log_printf( &logger, " Set Resistance: 8.192 kOhm \r\n" );
    log_printf( &logger, "----------------------------\r\n" );
    digipot7_set_resistance( &digipot7, 8192 );
    Delay_ms( 5000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.DIGIPOT7

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
