@set OPTIONS=/utf-8 /nologo /W4 /WX /MP /FS /Od /Oi /D _UNICODE /D UNICODE /Gm- /Gd /GS- /GR- /EHsc /MDd /fp:fast /permissive- /Zc:wchar_t /Zc:forScope /Zc:inline /Zc:rvalueCast /Zc:externConstexpr /Zc:throwingNew /Zc:strictStrings /std:c++latest /Zc:__cplusplus
@rem configuraton header-only
@set COMMON=%OPTIONS%
@rem module
CL.exe /c %COMMON% /interface /ifcOutput fmt-pp.ifc /Fo"fmt-m-pp.obj" fmt.cpp
CL.exe %COMMON% /reference "fmt=fmt-pp.ifc" /Fe"check-m-pp.exe" check.cpp fmt-m-pp.obj
@rem traditional
CL.exe /c %COMMON% /Fo"fmt-t-un.obj" fmt-lib.cpp
CL.exe %COMMON% /D NO_MODULE /Fe"check-t-un.exe" check.cpp fmt-t-un.obj
check-t-un.exe
check-m-pp.exe
