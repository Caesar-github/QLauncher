QT += widgets gui

HEADERS       = wallpaper.h \
    xdgdesktopfile.h \
    xdgdesktopfile_p.h \
    xdgdirs.h \
    xdgicon.h \
    xdgmacros.h
SOURCES       = wallpaper.cpp \
                main.cpp \
    xdgdesktopfile.cpp \
    xdgdirs.cpp \
    xdgicon.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/widgets/imageviewer
INSTALLS += target
