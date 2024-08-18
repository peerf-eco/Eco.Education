call ndk-build clean
call ndk-build TARGET_LINK=0 NDK_DEBUG=0 CONFIGURATION=StaticRelease
call ndk-build TARGET_LINK=0 NDK_DEBUG=1 CONFIGURATION=StaticDebug
rmdir /s /q libs
rmdir /s /q obj
call ndk-build clean
call ndk-build TARGET_LINK=1 NDK_DEBUG=0 CONFIGURATION=DynamicRelease
call ndk-build TARGET_LINK=1 NDK_DEBUG=1 CONFIGURATION=DynamicDebug
rmdir /s /q libs
rmdir /s /q obj
rem xcopy /y ..\..\..\..\BuildFiles\Android\arm64-v8a\StaticRelease\lib53884AFC93C448ECAA929C8D3A562281.a %ECO_FRAMEWORK%\Eco.List1\BuildFiles\Android\arm64-v8a\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi\StaticRelease\lib53884AFC93C448ECAA929C8D3A562281.a %ECO_FRAMEWORK%\Eco.List1\BuildFiles\Android\armeabi\
rem xcopy /y ..\..\..\..\BuildFiles\Android\armeabi-v7a\StaticRelease\lib53884AFC93C448ECAA929C8D3A562281.a %ECO_FRAMEWORK%\Eco.List1\BuildFiles\Android\armeabi-v7a\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips\StaticRelease\lib53884AFC93C448ECAA929C8D3A562281.a %ECO_FRAMEWORK%\Eco.List1\BuildFiles\Android\mips\
rem xcopy /y ..\..\..\..\BuildFiles\Android\mips64\StaticRelease\lib53884AFC93C448ECAA929C8D3A562281.a %ECO_FRAMEWORK%\Eco.List1\BuildFiles\Android\mips64\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86\StaticRelease\lib53884AFC93C448ECAA929C8D3A562281.a %ECO_FRAMEWORK%\Eco.List1\BuildFiles\Android\x86\
rem xcopy /y ..\..\..\..\BuildFiles\Android\x86_64\StaticRelease\lib53884AFC93C448ECAA929C8D3A562281.a %ECO_FRAMEWORK%\Eco.List1\BuildFiles\Android\x86_64\
pause
