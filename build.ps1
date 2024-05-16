param(
    [string]$BuildType = "Debug"
)

$outputDirectory = "build"
cmake --build $outputDirectory --config $BuildType
