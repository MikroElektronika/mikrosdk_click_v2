\mainpage Main Page

---
# NFC click

> NFC click is a mikroBUS™ add-on board with a versatile near field communications controller from NXP — the PN7120 IC. NFC devices are used in contactless payment systems, electronic ticketing, smartcards, but also in retail and advertising — inexpensive NFC tags can be embedded into packaging labels, flyers or posters.

<p align="center">
  <img src="https://download.mikroe.com/images/click_for_ide/nfc_click.png" height=300px>
</p>

[click Product page](https://www.mikroe.com/nfc-click)

---


#### Click library

- **Author**        : Stefan Ilic
- **Date**          : Mar 2023.
- **Type**          : I2C type


# Software Support

We provide a library for the NFC Click
as well as a demo application (example), developed using MikroElektronika
[compilers](https://www.mikroe.com/necto-studio).
The demo can run on all the main MikroElektronika [development boards](https://www.mikroe.com/development-boards).

Package can be downloaded/installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

## Library Description

> This library contains API for NFC Click driver.

#### Standard key functions :

- `nfc_cfg_setup` Config Object Initialization function.
```c
void nfc_cfg_setup ( nfc_cfg_t *cfg );
```

- `nfc_init` Initialization function.
```c
err_t nfc_init ( nfc_t *ctx, nfc_cfg_t *cfg );
```

- `nfc_default_cfg` Click Default Configuration function.
```c
void nfc_default_cfg ( nfc_t *ctx );
```

#### Example key functions :

- `nfc_hw_reset` HW reset function.
```c
void nfc_hw_reset( nfc_t *ctx );
```

- `nfc_get_data` Get data function.
```c
uint8_t nfc_get_data ( nfc_t *ctx, uint8_t *p_rx_data );
```

- `nfc_cmd_disable_standby_mode` Disable standby mode command function.
```c
void nfc_cmd_disable_standby_mode ( nfc_t *ctx );
```

## Example Description

> This is an example which demonstrates the usage of NFC Click board.

**The demo application is composed of two sections :**

### Application Init

> Initializes driver and logger, then performs hardware reset, puts the device in operating mode by 
 disabling standby mode, performs test procedure, and configures the device to start discovery.

```c

void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    nfc_cfg_t nfc_cfg;  /**< Click config object. */

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
    nfc_cfg_setup( &nfc_cfg );
    NFC_MAP_MIKROBUS( nfc_cfg, MIKROBUS_1 );
    err_t init_flag = nfc_init( &nfc, &nfc_cfg );
    if ( I2C_MASTER_ERROR == init_flag ) 
    {
        log_error( &logger, " Application Init Error. " );
        log_info( &logger, " Please, run program again... " );

        for ( ; ; );
    }

    log_printf( &logger, "        HW Reset       \r\n" );
    nfc_hw_reset( &nfc );
    Delay_ms ( 100 );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, " Reset and Init. Core  \r\n" );
    nfc_cmd_core_reset( &nfc );
    Delay_ms ( 100 );

    nfc_read_ctrl_packet_data( &nfc, &ctrl_pck_data );
    Delay_ms ( 100 );

    nfc_cmd_core_init( &nfc );
    Delay_ms ( 100 );

    nfc_read_ctrl_packet_data( &nfc, &ctrl_pck_data );
    Delay_ms ( 100 );
    display_packet( &ctrl_pck_data );

    while ( nfc_check_irq( &nfc ) == NFC_IRQ_STATE_HIGH );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, " Disabling Standby Mode \r\n" );
    nfc_cmd_disable_standby_mode( &nfc );
    Delay_ms ( 100 );

    nfc_read_ctrl_packet_data( &nfc, &ctrl_pck_data );
    Delay_ms ( 100 );
    display_packet( &ctrl_pck_data );

    nfc_test_antenna( &nfc, &ctrl_pck_data );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "Starting Test Procedure\r\n" );
    nfc_cmd_test_procedure( &nfc );
    Delay_ms ( 100 );

    nfc_read_ctrl_packet_data( &nfc, &ctrl_pck_data );
    Delay_ms ( 100 );
    display_packet( &ctrl_pck_data );

    nfc_hw_reset( &nfc );
    Delay_ms ( 100 );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "       NFC Config.     \r\n" );
    nfc_default_cfg ( &nfc, &ctrl_pck_data );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "     Discovery Start   \r\n" );
    nfc_cmd_start_discovery( &nfc );
    Delay_ms ( 100 );

    nfc_read_ctrl_packet_data( &nfc, &ctrl_pck_data );
    Delay_ms ( 100 );
    display_packet( &ctrl_pck_data );

    log_printf( &logger, "-----------------------\r\n" );
    log_printf( &logger, "-------- START --------\r\n" );
    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 500 );

    log_info( &logger, " Application Task " );
}

```

### Application Task

> NFC Click board can be used for detection of RFiD tag
  and displays it's value via USART terminal.
  All data logs write on USB uart changes for every 1 sec.

```c
void application_task ( void )
{
    while ( nfc_check_irq( &nfc ) == NFC_IRQ_STATE_HIGH ) 
    {
        nfc_read_nfc_data ( &nfc, &ctrl_pck_data );
    }

    while ( nfc_check_irq( &nfc ) == NFC_IRQ_STATE_LOW );

    log_printf( &logger, "-----------------------\r\n" );
    Delay_ms ( 1000 );
}
```

The full application code, and ready to use projects can be installed directly from *NECTO Studio Package Manager*(recommended way), downloaded from our [LibStock&trade;](https://libstock.mikroe.com) or found on [Mikroe github account](https://github.com/MikroElektronika/mikrosdk_click_v2/tree/master/clicks).

**Other Mikroe Libraries used in the example:**

- MikroSDK.Board
- MikroSDK.Log
- Click.NFC

**Additional notes and informations**

Depending on the development board you are using, you may need
[USB UART click](https://www.mikroe.com/usb-uart-click),
[USB UART 2 Click](https://www.mikroe.com/usb-uart-2-click) or
[RS232 Click](https://www.mikroe.com/rs232-click) to connect to your PC, for
development systems with no UART to USB interface available on the board. UART
terminal is available in all MikroElektronika
[compilers](https://shop.mikroe.com/compilers).

---
