QT += widgets

HEADERS       = wallpaper.h
SOURCES       = wallpaper.cpp \
                main.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/imageviewer
INSTALLS += target
