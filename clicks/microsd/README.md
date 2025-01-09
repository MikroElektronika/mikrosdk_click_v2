
---
# microSD Click

> [microSD Click](https://www.mikroe.com/?pid_product=MIKROE-924) demo application is developed using
the [NECTO Studio](https://www.mikroe.com/necto), ensuring compatibility with [mikroSDK](https://www.mikroe.com/mikrosdk)'s
open-source libraries and tools. Designed for plug-and-play implementation and testing, the demo is fully compatible with
all development, starter, and mikromedia boards featuring a [mikroBUS&trade;](https://www.mikroe.com/mikrobus) socket.

<p align="center">
  <img src="https://www.mikroe.com/?pid_product=MIKROE-924&image=1" height=300px>
</p>

---

#### Click Library

- **Author**        : Stefan Filipovic
- **Date**          : Aug 2023.
- **Type**          : SPI type

# Software Support

## Example Description

> This example demonstrates a basic file system functionality and operations with files and directories using a microSD Click board.

### Example Libraries

- MikroSDK.Board
- MikroSDK.Log
- Click.microSD

### Example Key Functions

- `microsd_cfg_setup` Config Object Initialization function.
```c
void microsd_cfg_setup ( microsd_cfg_t *cfg );
```

- `microsd_init` Initialization function.
```c
err_t microsd_init ( microsd_t *ctx, microsd_cfg_t *cfg );
```

- `microsd_check_card_detection` This function checks and waits for a microSD card to be inserted to the Click board.
```c
void microsd_check_card_detection ( microsd_t *ctx );
```

- `microsd_create_directory` This function creates a new directory at the selected absolute path. The path should contain a name of the directory to be created.
```c
void microsd_create_directory ( uint8_t *dir_path );
```

- `microsd_display_directory` This function reads and displays the content of the directory  at the selected path.
```c
void microsd_display_directory ( uint8_t *dir_path );
```

### Application Init

> Initializes the driver and logger and performs a several operations with file system that demonstrates the basic usage of microSD Click board.

```c
void application_init ( void )
{
    log_cfg_t log_cfg;  /**< Logger config object. */
    microsd_cfg_t microsd_cfg;  /**< Click config object. */

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
    microsd_cfg_setup( &microsd_cfg );
    MICROSD_MAP_MIKROBUS( microsd_cfg, MIKROBUS_1 );
    if ( MICROSD_ERROR == microsd_init( &microsd, &microsd_cfg ) )
    {
        log_error( &logger, " Communication init." );
        for ( ; ; );
    }
    
    microsd_check_card_detection ( &microsd );
    Delay_ms ( 1000 );
    
    // Mount the initialized logical drive to the initialized physical drive and overall file system
    microsd_mount_drive ( &microsd, PATH_ROOT );

#if FORMAT_CARD
    // Format the logical drive previously mounted to file system with identifying ROOT drive number
    microsd_format_drive ( PATH_ROOT );
#endif
    microsd_display_directory ( PATH_ROOT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // Create DIR1 directory
    microsd_create_directory ( PATH_DIR1 );
    Delay_ms ( 500 );
    
    // Create DIR2 directory
    microsd_create_directory ( PATH_DIR2 );
    Delay_ms ( 500 );
    
    // Create DIR4 directory
    microsd_create_directory ( PATH_DIR4 );
    Delay_ms ( 500 );
    
    microsd_display_directory ( PATH_ROOT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // Remove DIR4 directory
    microsd_remove_path ( PATH_DIR4 );
    Delay_ms ( 500 );
    
    microsd_display_directory ( PATH_ROOT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    microsd_display_directory ( PATH_DIR1 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    // Rename DIR2 to DIR3
    microsd_rename_path ( PATH_DIR2, PATH_DIR3 );
    Delay_ms ( 500 );
    
    microsd_display_directory ( PATH_DIR1 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    microsd_display_directory ( PATH_ROOT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    // Create the FILE1
    microsd_create_file ( PATH_FILE1 );
    Delay_ms ( 500 );
    microsd_display_directory ( PATH_ROOT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    uint8_t rw_buffer[ BUFFER_SIZE ] = { 0 };
    // Populate write buffer with bytes ranging from 0 to 255
    for ( uint16_t cnt = 0; cnt < BUFFER_SIZE; cnt++ ) 
    {
        rw_buffer[ cnt ] = cnt & 0xFF;
    }
    microsd_write_to_file ( PATH_FILE1, rw_buffer, BUFFER_SIZE );
    Delay_ms ( 500 );
    microsd_display_directory ( PATH_ROOT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    microsd_display_directory ( PATH_DIR3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    // Create the FILE2
    microsd_create_file ( PATH_FILE2 );
    Delay_ms ( 500 );
    microsd_display_directory ( PATH_DIR3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );

    // Copy data from FILE1 to FILE2
    microsd_copy_file ( PATH_FILE1, PATH_FILE2 );
    Delay_ms ( 500 );
    microsd_display_directory ( PATH_DIR3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    // Create DIR5 directory
    microsd_create_directory ( PATH_DIR5 );
    Delay_ms ( 500 );
    microsd_display_directory ( PATH_DIR1 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    
    log_info( &logger, " Application Task " );
}
```

### Application Task

> Reads and displays on the USB UART the contents of all directories created during application init.

```c
void application_task ( void )
{
    microsd_display_directory ( PATH_ROOT );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    microsd_display_directory ( PATH_DIR1 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    microsd_display_directory ( PATH_DIR3 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    microsd_display_directory ( PATH_DIR5 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    Delay_ms ( 1000 );
    log_printf ( &logger, "\r\n\n" );
}
```

## Application Output

This Click board can be interfaced and monitored in two ways:
- **Application Output** - Use the "Application Output" window in Debug mode for real-time data monitoring.
Set it up properly by following [this tutorial](https://www.youtube.com/watch?v=ta5yyk1Woy4).
- **UART Terminal** - Monitor data via the UART Terminal using
a [USB to UART converter](https://www.mikroe.com/click/interface/usb?interface*=uart,uart). For detailed instructions,
check out [this tutorial](https://help.mikroe.com/necto/v2/Getting%20Started/Tools/UARTTerminalTool).

## Additional Notes and Information

The complete application code and a ready-to-use project are available through the NECTO Studio Package Manager for 
direct installation in the [NECTO Studio](https://www.mikroe.com/necto). The application code can also be found on
the MIKROE [GitHub](https://github.com/MikroElektronika/mikrosdk_click_v2) account.

---
