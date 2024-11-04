
---
# I2C Isolator 3 Click

> I2C Isolator 3 Click is a compact add-on board that offers completely isolated bidirectional communication. This board features the CPC5902, a dual optically isolated bidirectional logic-bus repeater from IXYS Integrated Circuits Division. 

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/i2cisolator3_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/i2c-isolator-3-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jul 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the I2CIsolator3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for I2CIsolator3 Click driver.

#### Standard key functions :

- `i2cisolator3_cfg_setup` Config Object Initialization function.
```c
void i2cisolator3_cfg_setup ( i2cisolator3_cfg_t *cfg );
```

- `i2cisolator3_init` Initialization function.
```c
err_t i2cisolator3_init ( i2cisolator3_t *ctx, i2cisolator3_cfg_t *cfg );
```

#### Example key functions :

- `i2cisolator3_send_cmd` The function sends the desired command to a remote device wired with CPC5902, Optically Isolated I2C Bus Repeater on I2C Isolator 3 Click board.
```c
void i2cisolator3_send_cmd ( i2cisolator3_t *ctx, uint8_t command );
```

- `i2cisolator3_write_byte` The function writes the byte of data to the targeted 8-bit register address of the remote device wired with CPC5902, Optically Isolated I2C Bus Repeater on I2C Isolator 3 Click board.
```c
void i2cisolator3_write_byte ( i2cisolator3_t *ctx, uint8_t reg, uint8_t tx_data );
```

- `i2cisolator3_read_byte` The function read a the byte of data from the targeted 8-bit register address of the remote device wired with CPC5902, Optically Isolated I2C Bus Repeater on I2C Isolator 3 Click board.
```c
uint8_t i2cisolator3_read_byte ( i2cisolator3_t *ctx, uint8_t reg );
```

## Example Description

>  This is an example that demonstrates the use of the I2C Isolator 3 Click board. In this example, we measure temperature
from the Thermo 20 Click connected to the I2C Isolator 3 Click board. 

**The demo application is composed of two sections :**

### Application Init

>  Initializes I2C and start to write log. Initialization driver enables - I2C, set I2C slave address of the Thermo 20 Click, performs software reset, also write log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;                         /**< Logger config object. */
    i2cisolator3_cfg_t i2cisolator3_cfg;       /**< Click config object. */

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
    i2cisolator3_cfg_setup( &i2cisolator3_cfg );
    I2CISOLATOR3_MAP_MIKROBUS( i2cisolator3_cfg, MIKROBUS_1 );
    err_t init_flag = i2cisolator3_init( &i2cisolator3, &i2cisolator3_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }
    log_printf( &logger, "  Driver Init. Done  \r\n" );
    log_printf( &logger, "  Set I2C Slave Address   \r\n" );
    log_printf( &logger, "  of the Thermo 20 Click   \r\n" );
    Delay_ms ( 100 );
    
    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "      Software Reset      \r\n" );
    i2cisolator3_send_cmd(  &i2cisolator3, I2CISOLATOR3_THERMO20_CMD_RESET );
    Delay_ms ( 100 );

    log_printf( &logger, "--------------------------\r\n" );
    log_printf( &logger, "     Start Measuring      \r\n" );
    log_printf( &logger, "--------------------------\r\n" );
    Delay_ms ( 100 );

    log_info( &logger, " Application Task \r\n" );
}

```

### Application Task

> In this example via Thermo 20 Click we get the data processed by the function. When the function processes the data, we get
the temperature information. All data logs write on USB UART changes every 3 sec.

```c

void application_task ( void ) {
    i2cisolator3_send_cmd( &i2cisolator3, I2CISOLATOR3_THERMO20_CMD_CONVERSION );
    Delay_ms ( 100 );

    calculate_temperature( );

    log_printf( &logger, "Temperature : %.2f \r\n", temperature );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );    
}

```
The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.I2CIsolator3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
