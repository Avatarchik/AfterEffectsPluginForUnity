Add-Type -AssemblyName System.IO.Compression.FileSystem
function Unzip
{
    param([string]$zipfile, [string]$outpath)
    [System.IO.Compression.ZipFile]::ExtractToDirectory($zipfile, $outpath)
}

wget http://download.macromedia.com/pub/developer/aftereffects/sdk/Adobe_After_Effects_CC_2015_Win_SDK.zip -OutFile Plugin/External/Adobe_After_Effects_CC_2015_Win_SDK.zip
Unzip "Plugin/External/Adobe_After_Effects_CC_2015_Win_SDK.zip" "Plugin/External"
