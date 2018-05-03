
#指定生成版本
CONFIG += C++11 debug

#定义生成目录
CONFIG(debug, debug | release){
    PUBLISH = debug
}
else{
    win32{
        #release可调试
        QMAKE_CXXFLAGS_RELEASE += $$QMAKE_CFLAGS_RELEASE_WITH_DEBUGINFO
        QMAKE_LFLAGS_RELEASE += $$QMAKE_LFLAGS_RELEASE_WITH_DEBUGINFO
    }
    PUBLISH = release
}

#指定目标文件生成路径
DESTDIR = $$(ISCS_HOME)/bin/$$PUBLISH

#编译窄字符串时，将其编码转换为UTF-8编码
QMAKE_CXXFLAGS += /execution-charset:utf-8

#指定中间文件生成目录
TEMP_DIR = $$(ISCS_HOME)/tmp/$$TARGET
MOC_DIR = $$TEMP_DIR/moc
OBJECTS_DIR = $$TEMP_DIR/obj
RCC_DIR = $$TEMP_DIR/rcc
UI_DIR = $$TEMP_DIR/form

#指定头文件查找路径
INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/PropertyBrowser
INCLUDEPATH += $$PWD/GraphicalShape

#指定库文件查找路径
LIBS += -L$$(ISCS_HOME)/bin/$$PUBLISH
