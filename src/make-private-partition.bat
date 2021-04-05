@set OPTIONS=/utf-8 /nologo /W4 /WX /MP /FS /Od /Oi /D _UNICODE /D UNICODE /Gm- /Gd /GS- /GR- /EHsc /MDd /fp:fast /permissive- /Zc:wchar_t /Zc:forScope /Zc:inline /Zc:rvalueCast /Zc:externConstexpr /Zc:throwingNew /Zc:strictStrings /std:c++latest /Zc:__cplusplus
@rem configuraton header-only
@set COMMON=%OPTIONS%
@rem module
CL.exe /c %COMMON% /interface /ifcOutput fmt-pp.ifc /Fo"fmt-m-pp.obj" fmt.cpp
Lib.exe /OUT:fmt-m-pp.lib /NOLOGO /MACHINE:X64 /Ignore:4221 fmt-m-pp.obj
CL.exe %COMMON% /reference "fmt=fmt-pp.ifc" /Fe"check-m-pp.exe" check.cpp fmt-m-pp.lib
@rem traditional
CL.exe %COMMON% /D NO_MODULE /D UNITY_BUILD /Fe"check-t-un.exe" check.cpp
check-t-un.exe
check-m-pp.exe
