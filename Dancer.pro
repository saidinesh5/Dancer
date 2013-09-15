# Add more folders to ship with the application, here
folder_01.source = qml/
folder_01.target = .
folder_02.source = images/
folder_02.target = .

DEPLOYMENTFOLDERS += folder_01
DEPLOYMENTFOLDERS += folder_02

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# The .cpp file which was generated for your project. Feel free to hack it.

INCLUDEPATH += libs/

measure_bpm {
    SOURCES += libs/MiniBpm/MiniBpm.cpp
    HEADERS += libs/MiniBpm/MiniBpm.h
    DEFINES += MEASURE_BPM
}

SOURCES += libs/RtAudio/RtAudio.cpp \
           libs/fftreal/fftreal.cpp \
    audiolistener.cpp \
    main.cpp \
    audiolistenerbpm.cpp

HEADERS += libs/RtAudio/RtAudio.h \
           libs/RtAudio/RtError.h \
           libs/fftreal/fftreal.h \
    audiolistener.h \
    audiolistenerbpm.h

linux {
    DEFINES += __LINUX_PULSE__
    LIBS += -lpulse-simple -lpulse
}

win32 {
    DEFINES += __WINDOWS_DS__
    LIBS += winmm dsound
}

macx {
    DEFINES += __MACOSX_CORE__
    LIBS += -lpthread -framework CoreAudio
}

# Optional compile time defines
linux_alsa {
    DEFINES += __LINUX_ALSA__
    LIBS += -lasound -lpthread
}

linux_oss {
    DEFINES += __LINUX_OSS__
    LIBS += -lpthread
}

unix_jack {
    DEFINES += __UNIX_JACK__
    LIBS += -ljack -lpthread
}



# Installation path
# target.path =

# Please do not modify the following two lines. Required for deployment.
include(qtquick2applicationviewer/qtquick2applicationviewer.pri)
qtcAddDeployment()

OTHER_FILES += images/Head.png \
               images/Necklace.png \
               images/RightHand.png \
               images/LeftHand.png \
               images/Body.png \
               images/RightShoe.png \
               images/LeftShoe.png \
               qml/Head.qml \
               qml/Necklace.qml \
               qml/RightHand.qml \
               qml/LeftHand.qml \
               qml/Body.qml \
    qml/LeftShoe.qml
