@set OPTIONS=/utf-8 /nologo /W4 /WX /MP /FS /Od /Oi /D _UNICODE /D UNICODE /Gm- /Gd /GS- /GR- /EHsc /MDd /fp:fast /permissive- /Zc:wchar_t /Zc:forScope /Zc:inline /Zc:rvalueCast /Zc:externConstexpr /Zc:throwingNew /Zc:strictStrings /std:c++latest /Zc:__cplusplus
@rem configuraton header-only
@set COMMON=%OPTIONS% /D FMT_HEADER_ONLY
@rem module
CL.exe /c %COMMON% /interface /ifcOutput fmt-ho.ifc /Fo"fmt-m-ho.obj" fmt.cpp
Lib.exe /OUT:fmt-m-ho.lib /NOLOGO /MACHINE:X64 /Ignore:4221 fmt-m-ho.obj
CL.exe %COMMON% /reference "fmt=fmt-ho.ifc" /Fe"check-m-ho.exe" check.cpp fmt-m-ho.lib
@rem traditional
CL.exe %COMMON% /D NO_MODULE /Fe"check-t-ho.exe" check.cpp
check-t-ho.exe
check-m-ho.exe
