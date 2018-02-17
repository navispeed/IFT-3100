
set(OF_INCLUDE_DIR ${OF_MAIN_DIR}/libs/openFrameworks)
include_directories(${OF_INCLUDE_DIR})
include_directories(${OF_INCLUDE_DIR}/gl)
include_directories(${OF_INCLUDE_DIR}/3d)
include_directories(${OF_INCLUDE_DIR}/app)
include_directories(${OF_INCLUDE_DIR}/communication)
include_directories(${OF_INCLUDE_DIR}/events)
include_directories(${OF_INCLUDE_DIR}/graphics)
include_directories(${OF_INCLUDE_DIR}/math)
include_directories(${OF_INCLUDE_DIR}/sound)
include_directories(${OF_INCLUDE_DIR}/types)
include_directories(${OF_INCLUDE_DIR}/utils)
include_directories(${OF_INCLUDE_DIR}/video)


set(BOOST_DIR ${OF_MAIN_DIR}/libs/boost)
set(FMODEX_DIR ${OF_MAIN_DIR}/libs/fmodex)
set(FREEIMAGE_DIR ${OF_MAIN_DIR}/libs/FreeImage)
set(FREETYPE_DIR ${OF_MAIN_DIR}/libs/Freetype)
set(GLFW_DIR ${OF_MAIN_DIR}/libs/glfw)
set(POCO_DIR ${OF_MAIN_DIR}/libs/poco)
set(QUICKTIME_DIR ${OF_MAIN_DIR}/libs/quicktime)
set(RTAUDIO_DIR ${OF_MAIN_DIR}/libs/rtAudio)
set(TESS2_DIR ${OF_MAIN_DIR}/libs/tess2)
set(UTF8CPP_DIR ${OF_MAIN_DIR}/libs/utf8cpp)
set(VIDEOINPUT_DIR ${OF_MAIN_DIR}/libs/videoInput)
set(GLU_DIR ${OF_MAIN_DIR}/libs/glu)


include_directories(${BOOST_DIR}/include)
include_directories(${FMODEX_DIR}/include)
include_directories(${FREEIMAGE_DIR}/include)
include_directories(${FREETYPE_DIR}/include)
include_directories(${GLFW_DIR}/include)
include_directories(${GLU_DIR}/include)
include_directories(${POCO_DIR}/include)
include_directories(${QUICKTIME_DIR}/include)
include_directories(${RTAUDIO_DIR}/include)
include_directories(${TESS2_DIR}/include)
include_directories(${UTF8CPP_DIR}/include)
include_directories(${VIDEOINPUT_DIR}/include)


link_directories(${FMODEX_DIR}/lib/osx)
link_directories(${GLFW_DIR}/lib/osx)
link_directories(${RTAUDIO_DIR}/lib/osx)
link_directories(${TESS2_DIR}/lib/osx)
#link_directories(${VIDEOINPUT_DIR}/lib/osx)

file(READ addons.make addons)

string(REPLACE "
" ";" addonsList ${addons})

#list(LENGTH SEXY_LIST len)
#message(STATUS "len = ${len}")
#

include_directories(${OF_MAIN_DIR}/addons/ofxGui/src)
include_directories("/Users/greg/Downloads/of_v0.9.8_osx_release/apps/myApps/IFT-3100/bin/include"
        "${OF_MAIN_DIR}/libs/openFrameworks/**"
 "${OF_MAIN_DIR}/libs/poco/include"
  "${OF_MAIN_DIR}/libs/freetype/include"
   "${OF_MAIN_DIR}/libs/freetype/include/freetype2"
    "${OF_MAIN_DIR}/libs/fmodex/include"
     "${OF_MAIN_DIR}/libs/glew/include"
      "${OF_MAIN_DIR}/libs/FreeImage/include"
       "${OF_MAIN_DIR}/libs/tess2/include"
        "${OF_MAIN_DIR}/libs/cairo/include/cairo"
         "${OF_MAIN_DIR}/libs/rtAudio/include"
          "${OF_MAIN_DIR}/libs/glfw/include"
           "${OF_MAIN_DIR}/libs/boost/include"
            "${OF_MAIN_DIR}/libs/utf8cpp/include"
             "${OF_MAIN_DIR}/libs/openssl/include"
              src src/controllers src/model/canvas src/model/of2d src/services/cursors src/services/history
             "${OF_MAIN_DIR}/addons/ofxGui/src"
        "${OF_MAIN_DIR}/libs/openFrameworks/**"
        "${OF_MAIN_DIR}/libs/poco/include"
        "${OF_MAIN_DIR}/libs/freetype/include"
        "${OF_MAIN_DIR}/libs/freetype/include/freetype2"
        "${OF_MAIN_DIR}/libs/fmodex/include"
        "${OF_MAIN_DIR}/libs/glew/include"
        "${OF_MAIN_DIR}/libs/FreeImage/include"
        "${OF_MAIN_DIR}/libs/tess2/include"
        "${OF_MAIN_DIR}/libs/cairo/include/cairo"
        "${OF_MAIN_DIR}/libs/rtAudio/include"
        "${OF_MAIN_DIR}/libs/glfw/include"
        "${OF_MAIN_DIR}/libs/boost/include"
        "${OF_MAIN_DIR}/libs/utf8cpp/include"
        "${OF_MAIN_DIR}/libs/openssl/include")

target_link_libraries(app "${OF_MAIN_DIR}/libs/poco/lib/osx/PocoCrypto.a"
        "${OF_MAIN_DIR}/libs/poco/lib/osx/PocoData.a"
        "${OF_MAIN_DIR}/libs/poco/lib/osx/PocoDataSQLite.a"
        "${OF_MAIN_DIR}/libs/poco/lib/osx/PocoJSON.a"
        "${OF_MAIN_DIR}/libs/poco/lib/osx/PocoUtil.a"
        "${OF_MAIN_DIR}/libs/poco/lib/osx/PocoXML.a"
        "${OF_MAIN_DIR}/libs/poco/lib/osx/PocoNet.a"
        "${OF_MAIN_DIR}/libs/poco/lib/osx/PocoNetSSL.a"
        "${OF_MAIN_DIR}/libs/poco/lib/osx/PocoZip.a"
        "${OF_MAIN_DIR}/libs/poco/lib/osx/PocoFoundation.a"
        "${OF_MAIN_DIR}/libs/tess2/lib/osx/tess2.a"
        "${OF_MAIN_DIR}/libs/glew/lib/osx/glew.a"
        "${OF_MAIN_DIR}/libs/cairo/lib/osx/cairo-script-interpreter.a"
        "${OF_MAIN_DIR}/libs/cairo/lib/osx/cairo.a"
        "${OF_MAIN_DIR}/libs/cairo/lib/osx/pixman-1.a"
        "${OF_MAIN_DIR}/libs/fmodex/lib/osx/libfmodex.dylib"
        "${OF_MAIN_DIR}/libs/rtAudio/lib/osx/rtAudio.a"
        "${OF_MAIN_DIR}/libs/openssl/lib/osx/crypto.a"
        "${OF_MAIN_DIR}/libs/openssl/lib/osx/ssl.a"
        "${OF_MAIN_DIR}/libs/glfw/lib/osx/glfw3.a"
        "${OF_MAIN_DIR}/libs/FreeImage/lib/osx/freeimage.a"
        "${OF_MAIN_DIR}/libs/freetype/lib/osx/freetype.a"
        "${OF_MAIN_DIR}/libs/boost/lib/osx/boost_filesystem.a"
        "${OF_MAIN_DIR}/libs/boost/lib/osx/boost_system.a"
        "${OF_MAIN_DIR}/libs/openFrameworksCompiled/lib/osx/libopenFrameworks.a")

#link_directories(${OF_MAIN_DIR}/libs/openFrameworksCompiled/lib/osx)
#
#link_libraries(openFrameworks pthread fmodex   tess2 videoinput cairo z ssl crypto glew32
#        PocoNetSSL PocoNet PocoCrypto PocoUtil PocoXML PocoFoundation PocoZip PocoJSON PocoData
#        PocoDataSQLite ksuser opengl32 gdi32 msimg32 glu32 dsound winmm strmiids uuid ole32
#        oleaut32 setupapi wsock32 ws2_32 Iphlpapi Comdlg32 freeimage boost_filesystem-mt
#        boost_system-mt freetype cairo
#        )