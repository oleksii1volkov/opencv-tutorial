$projectDirectory = Get-Location | Select-Object -ExpandProperty Path
$outputDirectory = "$projectDirectory\build"

$env:PATH = "$outputDirectory\vcpkg_installed\x64-windows\debug\bin;$outputDirectory\vcpkg_installed\x64_windows\tools\gstreamer;" + $env:PATH

$env:GST_DEBUG = "*:INFO"
$env:GST_PLUGIN_PATH = "$outputDirectory\vcpkg_installed\x64-windows\debug\plugins\gstreamer"

$env:QT_QPA_PLATFORM_PLUGIN_PATH = "$outputDirectory\vcpkg_installed\x64-windows\debug\Qt6\plugins\platforms"
$env:QT_PLUGIN_PATH = "$outputDirectory\vcpkg_installed\x64-windows\debug\Qt6\plugins"
$env:QML2_IMPORT_PATH = "$outputDirectory\vcpkg_installed\x64-windows\debug\Qt6\qml"

# $targetName = "gstreamer"
# $targetName = "object_detection"
$targetName = "object_tracking"
$executablePath = "$outputDirectory\targets\$targetName\Debug\$targetName.exe"

& $executablePath
