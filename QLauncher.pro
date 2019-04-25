QT += widgets

HEADERS       = desktopwindow.h \
		xdgdesktopfile.h \
		xdgdesktopfile_p.h \
		xdgdirs.h \
		xdgicon.h \
		xdgmacros.h

SOURCES       = desktopwindow.cpp \
		main.cpp \
		xdgdesktopfile.cpp \
		xdgdirs.cpp \
		xdgicon.cpp

RESOURCES     += QLauncher.qrc

TARGET = QLauncher
