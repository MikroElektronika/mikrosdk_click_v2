/*!
 * @file main.c
 * @brief microSD Click example
 *
 * # Description
 * This example demonstrates a basic file system functionality and operations with files
 * and directories using a microSD click board.
 * 
 * The demo application is composed of two sections :
 *
 * ## Application Init
 * Initializes the driver and logger and performs a several operations with file system
 * that demonstrates the basic usage of microSD click board.
 *
 * ## Application Task
 * Reads and displays on the USB UART the contents of all directories created
 * during application init.
 *
 * @author Stefan Filipovic
 *
 */

#include "board.h"
#include "log.h"
#include "microsd.h"

static microsd_t microsd;
static log_t logger;

// WARNING: If you change the value of below macro to 1 the inserted
// microSD card will be formatted at the beginning.
#define FORMAT_CARD 0

// Files and directories path and names definition
#define PATH_ROOT   "3:/"
#define PATH_DIR1   PATH_ROOT "_DIR1_/"
#define PATH_DIR2   PATH_DIR1 "_DIR2_/"
#define PATH_DIR3   PATH_DIR1 "_DIR3_/"
#define PATH_DIR4   PATH_ROOT "_DIR4_/"
#define PATH_DIR5   PATH_DIR1 "_DIR5_/"
#define PATH_FILE1  PATH_ROOT "_FILE1_.TXT"
#define PATH_FILE2  PATH_DIR3 "_FILE2_.CSV"

// Data buffer size used for read/write operations
#define BUFFER_SIZE 256

/**
 * @brief microSD check card detection function.
 * @details This function checks and waits for a microSD card to be inserted
 * to the click board.
 * @param[in] ctx : Click context object.
 * See #microsd_t object definition for detailed explanation.
 * @return None.
 * @note None.
 */
void microsd_check_card_detection ( microsd_t *ctx );

/**
 * @brief microSD display directory function.
 * @details This function reads and displays the content of the directory 
 * at the selected path.
 * @param[in] dir_path : The absolute path to the directory to be displayed.
 * @return None.
 * @note None.
 */
void microsd_display_directory ( uint8_t *dir_path );

/**
 * @brief microSD create directory function.
 * @details This function creates a new directory at the selected absolute path.
 * The path should contain a name of the directory to be created.
 * @param[in] dir_path : The absolute path to the directory to be created.
 * @return None.
 * @note None.
 */
void microsd_create_directory ( uint8_t *dir_path );

/**
 * @brief microSD remove path function.
 * @details This function removes a file or a directory from the selected absolute path.
 * @param[in] path : The absolute path to the file or directory to be removed.
 * @return None.
 * @note None.
 */
void microsd_remove_path ( uint8_t *path );

/**
 * @brief microSD rename path function.
 * @details This function renames a file or a directory from the selected absolute path
 * specified by the @c old_path parameter, to the absolute path specified by the 
 * @c new_path parameter.
 * @param[in] old_path : The old path to the file or directory to be renamed.
 * @param[in] new_path : The new path to the file or directory.
 * @return None.
 * @note None.
 */
void microsd_rename_path ( uint8_t *old_path, uint8_t *new_path );

/**
 * @brief microSD create file function.
 * @details This function creates a new file at the selected absolute path.
 * The path should contain a name of the file to be created.
 * @param[in] file_path : The absolute path to the file to be created.
 * @return None.
 * @note None.
 */
void microsd_create_file ( uint8_t *file_path );

/**
 * @brief microSD write to file function.
 * @details This function writes a desired number of data bytes to the end of file
 * at the selected absolute path.
 * @param[in] file_path : The absolute path to the file.
 * @param[in] data_in : The data buffer to be written.
 * @param[in] data_len : Number of data bytes to be written.
 * @return None.
 * @note None.
 */
void microsd_write_to_file ( uint8_t *file_path, uint8_t *data_in, uint32_t data_len );

/**
 * @brief microSD copy file function.
 * @details This function copies the content of a file from the selected absolute path
 * specified by the @c src_file_path parameter, to the absolute path specified by the 
 * @c dst_file_path parameter.
 * @param[in] src_file_path : The source file absolute path.
 * @param[in] dst_file_path : The destination file absolute path.
 * @return None.
 * @note None.
 */
void microsd_copy_file ( uint8_t *src_file_path, uint8_t *dst_file_path );

/**
 * @brief microSD format drive function.
 * @details This function formats the logical drive previously mounted to file system
 * with identifying drive number.
 * @param[in] path : The ROOT path of drive to be formatted.
 * @return None.
 * @note None.
 */
void microsd_format_drive ( uint8_t *path );

/**
 * @brief microSD mount drive function.
 * @details This function mounts the initialized logical drive to the initialized
 * physical drive and overall file system.
 * @param[in] ctx : Click context object.
 * See #microsd_t object definition for detailed explanation.
 * @param[in] path : The ROOT path of drive to be mounted.
 * @return None.
 * @note None.
 */
void microsd_mount_drive ( microsd_t *ctx, uint8_t *path );

/**
 * @brief microSD unmount drive function.
 * @details This function unmounts the mounted logical drive from the file system.
 * @param[in] path : The ROOT path of drive to be unmounted.
 * @return None.
 * @note None.
 */
void microsd_unmount_drive ( uint8_t *path );

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

int main ( void ) 
{
    /* Do not remove this line or clock might not be set correctly. */
    #ifdef PREINIT_SUPPORTED
    preinit();
    #endif
    
    application_init( );
    
    for ( ; ; ) 
    {
        application_task( );
    }

    return 0;
}

void microsd_check_card_detection ( microsd_t *ctx )
{
    if ( microsd_get_card_detect ( ctx ) )
    {
        log_printf ( &logger, " microSD card is not detected.\r\n" );
        log_printf ( &logger, " Make sure to insert a card correctly.\r\n" );
        log_printf ( &logger, "--------------------------------------\r\n\n" );
        while ( microsd_get_card_detect ( ctx ) );
        
        log_printf ( &logger, " microSD card is detected.\r\n" );
        log_printf ( &logger, "--------------------------------------\r\n\n" );
    }
}

void microsd_display_directory ( uint8_t *dir_path )
{
    dir_t dir1;
    DIR fatfs_dir_1;
    FILINFO info;
    
    log_printf ( &logger, " #### Display directory: %s\r\n", dir_path );
    // Open directory and make it ready for reading operation
    if ( FSS_OK == dir_open ( &dir1, &fatfs_dir_1, dir_path ) ) 
    {
        log_printf ( &logger, " Open directory\r\n" );
        log_printf ( &logger, " Content:\r\n" );
        // Read directory entries and print their type and name
        for ( ; ; ) 
        {
            if ( FSS_OK == dir_read( &dir1, &info ) ) 
            {
                if ( info.fattrib & AM_DIR ) 
                {
                    log_printf ( &logger, "\t<DIR>\tname: %s\r\n", info.fname );
                }
                else 
                {
                    log_printf ( &logger, "\t<FILE>\tname: %s size: %lu\r\n", info.fname, info.fsize );
                }
            }
            else
            {
                break;
            }
        }
        
        // Close directory
        if ( FSS_OK == dir_close ( &dir1 ) ) 
        {
            log_printf( &logger, " Close directory\r\n" );
        }
    }
    log_printf ( &logger, "--------------------------------------\r\n\n" );
}

void microsd_create_directory ( uint8_t *dir_path )
{
    if ( FSS_OK == file_system_mkdir ( dir_path ) ) 
    {
        log_printf ( &logger, " Create directory: %s\r\n", dir_path );
        log_printf ( &logger, "--------------------------------------\r\n\n" );
    }
}

void microsd_remove_path ( uint8_t *path )
{
    if ( FSS_OK == file_system_remove ( path ) ) 
    {
        log_printf ( &logger, " Remove path: %s\r\n", path );
        log_printf ( &logger, "--------------------------------------\r\n\n" );
    }
}

void microsd_rename_path ( uint8_t *old_path, uint8_t *new_path )
{
    if ( FSS_OK == file_system_rename ( old_path, new_path ) ) 
    {
        log_printf ( &logger, " Rename %s to %s\r\n", old_path, new_path );
        log_printf ( &logger, "--------------------------------------\r\n\n" );
    }
}

void microsd_create_file ( uint8_t *file_path )
{
    file_t file;
    FIL fatfs_file;
    // Create the file and make it ready for read and write operations
    if ( FSS_OK == file_open ( &file, &fatfs_file, file_path, 
                               FS_FILE_CREATE_NEW | FS_FILE_WRITE | FS_FILE_READ ) ) 
    {
        log_printf( &logger, " Create and open file: %s\r\n", file_path );
        if ( FSS_OK == file_close ( &file ) ) 
        {
            log_printf( &logger, " Close file.\r\n" );
        }
        log_printf ( &logger, "--------------------------------------\r\n\n" );
    }
}

void microsd_write_to_file ( uint8_t *file_path, uint8_t *data_in, uint32_t data_len )
{
    file_t file;
    FIL fatfs_file;
    // Open the file and make it ready for read and write operations
    if ( FSS_OK == file_open ( &file, &fatfs_file, file_path, 
                               FS_FILE_WRITE | FS_FILE_READ | FS_FILE_OPEN_APPEND ) ) 
    {
        log_printf( &logger, " Open file: %s\r\n", file_path );
        
        if ( FSS_OK == file_write ( &file, data_in, data_len ) ) 
        {
            log_printf( &logger, " Write data buffer to file\r\n" );
        }
        if ( FSS_OK == file_sync ( &file ) ) 
        {
            log_printf( &logger, " Save file changes\r\n" );
        }
        if ( FSS_OK == file_close ( &file ) ) 
        {
            log_printf( &logger, " Close file.\r\n" );
        }
        log_printf ( &logger, "--------------------------------------\r\n\n" );
    }
}

void microsd_copy_file ( uint8_t *src_file_path, uint8_t *dst_file_path )
{
    uint8_t data_read = 0;
    file_t file1, file2;
    FIL fatfs_file1, fatfs_file2;
    // Create or open the file and make it ready for read and write operations
    if ( FSS_OK == file_open ( &file1, &fatfs_file1, src_file_path, FS_FILE_WRITE | FS_FILE_READ ) ) 
    {
        log_printf( &logger, " Open source file: %s\r\n", src_file_path );
        if ( FSS_OK == file_open ( &file2, &fatfs_file2, dst_file_path, FS_FILE_WRITE | FS_FILE_READ ) ) 
        {
            log_printf( &logger, " Open destination file: %s\r\n", dst_file_path );
            
            log_printf( &logger, " Copying data from source to destination file...\r\n" );
            for ( ; ; )
            {
                if ( FSS_OK == file_read ( &file1, &data_read, 1 ) ) 
                {
                    file_write ( &file2, &data_read, 1 ); 
                }
                else
                {
                    break;
                }
            }
            
            if ( FSS_OK == file_close ( &file1 ) ) 
            {
                log_printf( &logger, " Close source file.\r\n" );
            }
            if ( FSS_OK == file_close ( &file2 ) ) 
            {
                log_printf( &logger, " Close destination file.\r\n" );
            }
        }
        log_printf ( &logger, "--------------------------------------\r\n\n" );
    }
}

void microsd_format_drive ( uint8_t *path )
{
    if ( FSS_OK == file_system_format ( path ) ) 
    {
        log_printf( &logger, " Format drive: %s\r\n", path );
        log_printf ( &logger, "--------------------------------------\r\n\n" );
    }
}

void microsd_mount_drive ( microsd_t *ctx, uint8_t *path )
{
    if ( FSS_OK == file_system_mount ( &ctx->fat_ldrive.base, path, &ctx->sd_pdrive.base ) ) 
    {
        log_printf ( &logger, " Mount drive: %s\r\n", path );
        log_printf ( &logger, "--------------------------------------\r\n\n" );
    }
}

void microsd_unmount_drive ( uint8_t *path )
{
    if ( FSS_OK == file_system_unmount ( path ) ) 
    {
        log_printf ( &logger, " Unmount drive: %s\r\n", path );
        log_printf ( &logger, "--------------------------------------\r\n\n" );
    }
}

// ------------------------------------------------------------------------ END
