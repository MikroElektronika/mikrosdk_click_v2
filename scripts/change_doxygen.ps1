$dir_list = Get-ChildItem -Path "../clicks"

foreach ( $dir in $dir_list ) {

    $CLICK_NAME = $dir.Name

    $FILE_DOXY = '../clicks/' + $CLICK_NAME + '/doc/doxy/Doxyfile.doxy'
    $PATH_NAME_TEMP = '../clicks/' + $CLICK_NAME + '/temp/Help/doc'
    $PATH_NAME_LIB= '../clicks/' + $CLICK_NAME + '/lib/include'
    $PATH_NAME_README = '../clicks/' + $CLICK_NAME + '/README.md'
    $PATH_NAME_EXAMPLE = '../clicks/' +  $CLICK_NAME + '/example'

    ( ( Get-Content -path $FILE_DOXY -Raw ) -replace './temp/Help/doc/output', $PATH_NAME_TEMP ) | Set-Content -Path $FILE_DOXY
    ( ( Get-Content -path $FILE_DOXY -Raw ) -replace './lib/include', $PATH_NAME_LIB ) | Set-Content -Path $FILE_DOXY
    ( ( Get-Content -path $FILE_DOXY -Raw ) -replace './README.md', $PATH_NAME_README ) | Set-Content -Path $FILE_DOXY
    ( ( Get-Content -path $FILE_DOXY -Raw ) -replace './example', $PATH_NAME_EXAMPLE ) | Set-Content -Path $FILE_DOXY
    Write-Host $CLICK_NAME -ForegroundColor Green
}
