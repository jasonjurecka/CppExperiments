function os.winSdkVersion()
    local reg_arch = iif( os.is64bit(), "\\Wow6432Node\\", "\\" )
    local sdk_version = os.getWindowsRegistry( "HKLM:SOFTWARE" .. reg_arch .."Microsoft\\Microsoft SDKs\\Windows\\v10.0\\ProductVersion" )
    if sdk_version ~= nil then return sdk_version end
end

configurations { "Debug", "Release" }
platforms { "x32", "x64" }
characterset ("MBCS") -- will need to change for cross platform
location "Build"

warnings "Extra"
staticruntime "On"
flags { "FatalCompileWarnings" }
symbols "On"
cppdialect "C++17"

filter "configurations:Release"
    optimize "Full"
    flags { "LinkTimeOptimization" }

filter {"system:windows", "action:vs*"}
    systemversion(os.winSdkVersion() .. ".0")