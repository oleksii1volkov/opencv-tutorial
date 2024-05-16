$projectDirectory = Get-Location | Select-Object -ExpandProperty Path
$outputDirectory = "$projectDirectory\build"

$env:PATH = "$outputDirectory\vcpkg_installed\x64-windows\bin;$outputDirectory\vcpkg_installed\x64_windows\tools\gstreamer;" + $env:PATH

$env:GST_DEBUG = "*:INFO"
$env:GST_PLUGIN_PATH = "$outputDirectory\vcpkg_installed\x64-windows\plugins\gstreamer"

$env:QT_QPA_PLATFORM_PLUGIN_PATH = "$outputDirectory\vcpkg_installed\x64-windows\Qt6\plugins\platforms"
$env:QT_PLUGIN_PATH = "$outputDirectory\vcpkg_installed\x64-windows\Qt6\plugins"
$env:QML2_IMPORT_PATH = "$outputDirectory\vcpkg_installed\x64-windows\Qt6\qml"

$targetName = "object_detection"
# $targetName = "gstreamer"
$executablePath = "$outputDirectory\targets\$targetName\Release\$targetName.exe"

& $executablePath
