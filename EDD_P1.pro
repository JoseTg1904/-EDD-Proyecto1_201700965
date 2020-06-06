TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Estructuras/avl.cpp \
        Estructuras/listadoblecircular.cpp \
        Estructuras/matriz.cpp \
        Estructuras/nodo.cpp \
        Objetos/activo.cpp \
        Objetos/transaccion.cpp \
        Objetos/usuario.cpp \
        main.cpp \
        menus.cpp

HEADERS += \
    Estructuras/avl.h \
    Estructuras/listadoblecircular.h \
    Estructuras/matriz.h \
    Estructuras/nodo.h \
    Objetos/activo.h \
    Objetos/transaccion.h \
    Objetos/usuario.h \
    menus.h
