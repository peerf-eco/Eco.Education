rmdir /s /q build

call ndk-build clean
call ndk-build NDK_LOG=1 V=1 TARGET_LINK=0 NDK_DEBUG=0 CONFIGURATION=StaticRelease
call ndk-build TARGET_LINK=0 NDK_DEBUG=1 CONFIGURATION=StaticDebug
rmdir /s /q libs
rmdir /s /q obj
rem call ndk-build clean
rem call ndk-build TARGET_LINK=1 NDK_DEBUG=0 CONFIGURATION=DynamicRelease
rem call ndk-build TARGET_LINK=1 NDK_DEBUG=1 CONFIGURATION=DynamicDebug
rem rmdir /s /q libs
rem rmdir /s /q obj

mkdir build\gen build\obj build\apk

set PROJECT=%~dp0
set TARGET=Eco.DemoCalculator1
set SOURCE=ru\peerf\eco\democalculator1
set SDK=%ECO_TOOLCHAIN%\android-sdk
set BUILD_TOOLS=%SDK%\build-tools\33.0.0
set PLATFORM=%SDK%\platforms\android-19

xcopy /y build\libs\arm64-v8a\StaticDebug\lib%TARGET%.so build\apk\lib\arm64-v8a\
xcopy /y build\libs\armeabi\StaticDebug\lib%TARGET%.so build\apk\lib\armeabi\
xcopy /y build\libs\armeabi-v7a\StaticDebug\lib%TARGET%.so build\apk\lib\armeabi-v7a\
xcopy /y build\libs\mips\StaticDebug\lib%TARGET%.so build\apk\lib\mips\
xcopy /y build\libs\mips64\StaticDebug\lib%TARGET%.so build\apk\lib\mips64\
xcopy /y build\libs\x86\StaticDebug\lib%TARGET%.so build\apk\lib\x86\
xcopy /y build\libs\x86_64\StaticDebug\lib%TARGET%.so build\apk\lib\x86_64\

call %BUILD_TOOLS%\aapt package -f -m -J build\gen\ -S res -A assets -M AndroidManifest.xml -I %PLATFORM%\android.jar
rem javac -classpath %PLATFORM%\android.jar -d build\obj  %PROJECT%build\gen\%SOURCE%\R.java 
call %BUILD_TOOLS%\d8 --release --lib %PLATFORM%\android.jar --output=build\apk 
%BUILD_TOOLS%\aapt package -f -M AndroidManifest.xml -S res\ -A assets\ -I %PLATFORM%\android.jar -F build\%TARGET%.unsigned.apk build\apk\ 
%BUILD_TOOLS%\zipalign -f 4 build\%TARGET%.unsigned.apk build\%TARGET%.aligned.apk
rem keytool -genkeypair -keystore keystore.jks -alias androidkey -validity 10000 -keyalg RSA -keysize 2048 -storepass android -keypass android
%BUILD_TOOLS%\apksigner sign --ks keystore.jks --ks-key-alias androidkey --ks-pass pass:android --key-pass pass:android --out build\%TARGET%.apk build\%TARGET%.aligned.apk
rem adb install -r build\Eco.List1UnitTest.apk

rmdir /s /q build\libs
rmdir /s /q build\obj
rmdir /s /q build\gen
pause
