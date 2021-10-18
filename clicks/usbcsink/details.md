
---
# USB-C Sink click

> USB-C Sink Click is a compact add-on board that contains a standalone autonomous USB power delivery controller. This board features the STUSB4500, a USB-C sink-only controller compatible with Power-Delivery (PD) from STMicroelectronics. It supports dead battery mode to allow a system to be powered from an external source directly, establishes a valid source-to-sink connection, and negotiates a USB power delivery (PD) contract with a PD capable source device.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/usbcsink_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/usb-c-sink-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Aug 2021.
- **Type**          : I2C type


# Software Support

We provide a library for the USBCSink Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for USBCSink Click driver.

#### Standard key functions :

- `usbcsink_cfg_setup` Config Object Initialization function.
```c
void usbcsink_cfg_setup ( usbcsink_cfg_t *cfg );
```

- `usbcsink_init` Initialization function.
```c
err_t usbcsink_init ( usbcsink_t *ctx, usbcsink_cfg_t *cfg );
```

#### Example key functions :

- `usbcsink_hw_reset` HW reset function.
```c
void usbcsink_hw_reset ( usbcsink_t *ctx );
```

- `usbcsink_get_pdo2` Get PO2 pin state function.
```c
uint8_t usbcsink_get_pdo2 ( usbcsink_t *ctx );
```

- `usbcsink_write_byte` Write byte function.
```c
void usbcsink_write_byte ( usbcsink_t *ctx, uint8_t reg, uint8_t tx_data );
```

## Example Description

> This is an example which demonstrates the use of USB-C Sink Click board.

**The demo application is composed of two sections :**

### Application Init

> Initialization driver enables - I2C, set hw reset, set PDO2 profile and current value for PDO2 1.5A,
> upload new data and reset device to write NVM settings to the STUSB450, also write log.

```c

void application_init ( void ) {
    log_cfg_t log_cfg;  /**< Logger config object. */
    usbcsink_cfg_t usbcsink_cfg;  /**< Click config object. */

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
    usbcsink_cfg_setup( &usbcsink_cfg );
    USBCSINK_MAP_MIKROBUS( usbcsink_cfg, MIKROBUS_1 );
    err_t init_flag = usbcsink_init( &usbcsink, &usbcsink_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    usbcsink_hw_reset( &usbcsink );
    Delay_ms( 1000 );
    
    usbcsink_set_pdo_num( USBCSINK_SET_PDO_2 );
    usbcsink_set_current( USBCSINK_SET_PDO_2, 1.5 );
    
    sel_profile = usbcsink_get_pdo_num( );
    log_printf( &logger , "- - - - - - - - - - - - \r\n" );
    log_printf( &logger , "   Setting PDO ~ PDO%d \r\n", ( uint16_t ) sel_profile );
    log_printf( &logger , "- - - - - - - - - - - - \r\n" );
    
    usbcsink_upload_new_data( &usbcsink, USBCSINK_UPLOAD_NEW_DATA_VAL );
    Delay_ms( 1000 );
    
    usbcsink_hw_reset( &usbcsink );
    Delay_ms( 1000 );
    
    log_info( &logger, " Application Task " );
}

```

### Application Task

> USB-C Sink Click board can be used to read the Power Data Objects (PDO) highest priority profile:
> PDO1 :  5V,
> PDO2 : 12V,
> PDO3 : 20V.
> All data logs write on USB uart changes for every 5 sec.

```c

void application_task ( void ) {
    usbcsink_load_data( &usbcsink );

    log_printf( &logger , "     New Parameters     \r\n" );
    log_printf( &logger , "------------------------\r\n" );
    
    sel_profile = usbcsink_get_pdo_num( );
    
    log_printf( &logger , "    PDO Number ~ PDO%d\r\n", ( uint16_t ) sel_profile );
    log_printf( &logger , "- - - - - - - - - - - - \r\n" );

    demo_data = usbcsink_get_voltage( sel_profile );
    log_printf( &logger , " Voltage : %.2f V\r\n", demo_data );

    demo_data = usbcsink_get_current( sel_profile );
    log_printf( &logger , " Current :  %.2f A\r\n", demo_data );

    log_printf( &logger , "------------------------\r\n" );
    Delay_ms( 5000 );
}

```


The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.USBCSink

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
