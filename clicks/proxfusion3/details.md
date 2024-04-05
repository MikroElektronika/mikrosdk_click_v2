

---
# ProxFusion 3 click

ProxFusion 3 Click is a compact add-on board that represents a multifunctional touch sensing Click board™. This board features the IQS2692A, an 8-channel ProxFusion® capacitive touch and proximity controller with additional sensing such as Hall- and inductive sensing from Azoteq.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/proxfusion3_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/proxfusion-3-click)

---


#### Click library

- **Author**        : Nenad Filipovic
- **Date**          : Dec 2020.
- **Type**          : I2C type


# Software Support

We provide a library for the ProxFusion3 Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

```
This library contains API for ProxFusion3 Click driver.
```

#### Standard key functions :

- Config Object Initialization function.
```
void proxfusion3_cfg_setup ( proxfusion3_cfg_t *cfg );
```

- Initialization function.
```
PROXFUSION3_RETVAL proxfusion3_init ( proxfusion3_t *ctx, proxfusion3_cfg_t *cfg );
```

- Click Default Configuration function.
```
void proxfusion3_default_cfg ( proxfusion3_t *ctx );
```

#### Example key functions :

- ProxFusion 3 get touch function.
```
uint8_t proxfusion3_get_touch ( proxfusion3_t *ctx );
```

- ProxFusion 3 check touch event function.
```
uint8_t proxfusion3_check_touch_event ( proxfusion3_t *ctx );
```

- ProxFusion 3 get version info data function.
```
err_t proxfusion3_get_version_info ( proxfusion3_t *ctx, uint8_t *product_number, uint8_t *software_version );
```

## Examples Description

Display information about the last detected touch.

**The demo application is composed of two sections :**

### Application Init

Initializes I2C driver, read and display version info value
and start to write log.

```
void application_init ( void ) {
    log_cfg_t log_cfg;                  /**< Logger config object. */
    proxfusion3_cfg_t proxfusion3_cfg;  /**< Click config object.  */

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
    log_printf( &logger, "\r\n---------------------------\r\n" );
    log_info( &logger, " Application Init " );

    // Click initialization.

    proxfusion3_cfg_setup( &proxfusion3_cfg );
    PROXFUSION3_MAP_MIKROBUS( proxfusion3_cfg, MIKROBUS_1 );
    err_t init_flag = proxfusion3_init( &proxfusion3, &proxfusion3_cfg );
    if ( init_flag == I2C_MASTER_ERROR ) {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    proxfusion3_default_cfg ( &proxfusion3 );
    log_info( &logger, " Application Task " );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 500 );
    
    proxfusion3_get_version_info( &proxfusion3, &product_number, &software_version );
    log_printf( &logger, "  Product Number   : 0x%.2X \r\n", ( uint16_t )product_number );
    log_printf( &logger, "  Software Version : 0x%.2X \r\n", ( uint16_t )software_version );
    log_printf( &logger, "---------------------------\r\n" );
    Delay_ms ( 1000 );
    log_printf( &logger, "      Touch Detection      \r\n" );
    log_printf( &logger, "---------------------------\r\n" );
}
```

### Application Task

This is an example that demonstrates the use of the ProxFusion 3 click board.
In this example, we check the touch event and display the last detected touch. 
Results are being sent to the Usart Terminal where you can track their changes.

```
void application_task ( void ) {
    if ( proxfusion3_check_touch_event( &proxfusion3 ) == PROXFUSION3_EVENT_TOUCH ) {        
        uint8_t touch_data = proxfusion3_get_touch( &proxfusion3 );
        Delay_ms ( 100 );
        
        switch ( touch_data ) {
            case PROXFUSION3_TOUCH_POS_8: {
                log_printf( &logger, "       >>>   8   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_7: {
                log_printf( &logger, "       >>>   7   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_6: {
                log_printf( &logger, "       >>>   6   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_5: {
                log_printf( &logger, "       >>>   5   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_4: {
                log_printf( &logger, "       >>>   4   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_3: {
                log_printf( &logger, "       >>>   3   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_2: {
                log_printf( &logger, "       >>>   2   <<<       \r\n" );
                break;
            }
            case PROXFUSION3_TOUCH_POS_1: {
                log_printf( &logger, "       >>>   1   <<<       \r\n" );
                break;
            }
            default: {
                Delay_ms ( 10 );
                break;
            }
        }
        
        Delay_ms ( 10 );
    } else {
        Delay_ms ( 10 );
    }
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [mikroE github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other mikroE Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.ProxFusion3

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all Mikroelektronika
[compilers](https://shop.mikroe.com/compilers).

---
