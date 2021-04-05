@set OPTIONS=/utf-8 /nologo /W4 /WX /MP /FS /Od /Oi /D _UNICODE /D UNICODE /Gm- /Gd /GS- /GR- /EHsc /MDd /fp:fast /permissive- /Zc:wchar_t /Zc:forScope /Zc:inline /Zc:rvalueCast /Zc:externConstexpr /Zc:throwingNew /Zc:strictStrings /std:c++latest /Zc:__cplusplus
@rem configuraton header-only
@set COMMON=%OPTIONS% /D FMT_USE_IMPLEMENTATION_UNIT
@rem module
CL.exe /c %COMMON% /interface /ifcOutput fmt-iu.ifc /Fo"fmt-m-iu.obj" fmt.cpp
CL.exe /c %COMMON% /reference "fmt=fmt-iu.ifc" /Fo"fmt-m-impl.obj" fmt-impl.cpp
Lib.exe /OUT:fmt-m-iu.lib /NOLOGO /MACHINE:X64 /Ignore:4221 fmt-m-iu.obj fmt-m-impl.obj
CL.exe %COMMON% /reference "fmt=fmt-iu.ifc" /Fe"check-m-iu.exe" check.cpp fmt-m-iu.lib
@rem traditional
CL.exe /c %COMMON% /Fo"fmt-t-impl.obj" format.cc
Lib.exe /OUT:fmt-t.lib /NOLOGO /MACHINE:X64 /Ignore:4221 fmt-t-impl.obj
CL.exe %COMMON% /D NO_MODULE /Fe"check-t-iu.exe" check.cpp fmt-t.lib
check-t-iu.exe