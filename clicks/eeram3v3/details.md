
---
# EERAM 3v3 Click

EERAM 3.3V Click is a static RAM (SRAM) memory Click board™ with the unique feature - it has a backup non-volatile memory array, used to store the data from the SRAM array. Since the SRAM is not able to maintain its content after the power loss, the non-volatile EEPROM backup can be a very handy addition that can be used to preserve the data, even after the power loss event. This is a very useful feature when working with critical or sensitive applications. The memory backup procedure can be executed both automatically and manually. When it is set to work in the manual mode, the onboard capacitor will act as a power source with enough power to complete the backup cycle. The power-on backup restore mode is also available, taking only about 25ms to complete.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/eeram33v_click.png" height=300px>
</p>

[Click Product page](https://www.mikroe.com/eeram-33v-click)

---


#### Click library

- **Author**        : Jelena Milosavljevic
- **Date**          : Jun 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the EERAM3v3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for EERAM3v3 Click driver.

#### Standard key functions :

- `eeram3v3_cfg_setup` Config Object Initialization function.
```c
void eeram3v3_cfg_setup ( eeram3v3_cfg_t *cfg );
```

- `eeram3v3_init` Initialization function.
```c
err_t eeram3v3_init ( eeram3v3_t *ctx, eeram3v3_cfg_t *cfg );
```

#### Example key functions :

- `eeram3v3_generic_write` This function writes a desired number of data bytes starting from the selected register by using I2C serial interface.
```c
void eeram3v3_generic_write ( eeram3v3_t *ctx, uint8_t reg, uint8_t *tx_buf, uint8_t tx_len );
```

- `eeram3v3_generic_read` This function reads a desired number of data bytes starting from the selected register by using I2C serial interface.
```c
void eeram3v3_generic_read ( eeram3v3_t *ctx, uint8_t reg, uint8_t *rx_buf, uint8_t rx_len );
```

- `eeram3v3_status_write` Status register contains settings for write protection and auto-store function. Use this function to configure them.
```c
void eeram3v3_status_write ( eeram3v3_t *ctx, uint8_t command );
```

## Example Description

> This example show using EERAM Click to store the data to the SRAM ( static RAM ) memory. The data is read and written by the I2C serial communication bus, and the memory cells are organized into 2048 bytes, each 8bit wide.

**The demo application is composed of two sections :**

### Application Init

> EERAM driver nitialization.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;             /**< Logger config object. */
    eeram3v3_cfg_t eeram3v3_cfg;   /**< Click config object. */

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
    
    eeram3v3_cfg_setup( &eeram3v3_cfg );
    EERAM3V3_MAP_MIKROBUS( eeram3v3_cfg, MIKROBUS_1 );
    err_t init_flag = eeram3v3_init( &eeram3v3, &eeram3v3_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_info( &logger, " Application Task " );
}

```

### Application Task

> Writing data to Click memory and displaying the read data via UART. 

```c

void application_task ( void ){
    log_info( &logger, "Writing MikroE to  SRAM memory, from address 0x0150:" );
    eeram3v3_write( &eeram3v3, 0x0150, &wr_data, 9 );
    log_info( &logger, "Reading 9 bytes of SRAM memory, from address 0x0150:" );
    eeram3v3_read( &eeram3v3, 0x0150, &rd_data, 9 );
    log_info( &logger, "Data read: %s", rd_data );
    Delay_ms ( 1000 );
}

```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.EERAM3v3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART Click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
