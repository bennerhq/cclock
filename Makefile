# ----------------------------------------------------------------------------
# "THE BEER-WARE LICENSE" (Revision 43):
#
# Github Co-pilot & <jens@bennerhq.com> wrote this file.  As long as you 
# retain this notice you can do whatever you want with this stuff. If we meet 
# some day, and you think this stuff is worth it, you can buy me a beer in 
# return.   
#
# /benner
# ----------------------------------------------------------------------------

TARGET = cclock

SOURCES = \
    $(wildcard cpp/*.cpp)

HEADERS = \
    $(wildcard h/*.h)

OBJECTS_DIR = \
	./obj/

CXXFLAGS = \
    -pipe -O2 -std=gnu++1z -Wall -Wextra -D_REENTRANT -fPIC \
    -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SVG_LIB

# Get the home directory
HOME_DIR := $(shell echo ~)

# Detect the operating system
UNAME_S := $(shell uname -s)

# Set paths and libraries based on the operating system
ifeq ($(UNAME_S), Linux)
    QT_INC_PATH = /usr/include/x86_64-linux-gnu
    QT_LIB_PATH = /usr/lib/x86_64-linux-gnu

    INCPATH = \
        -I$(QT_INC_PATH)/qt5 \
        -I$(QT_INC_PATH)/qt5/QtWidgets \
        -I$(QT_INC_PATH)/qt5/QtGui \
        -I$(QT_INC_PATH)/qt5/QtCore \
        -I$(QT_INC_PATH)/qt5/QtSvg \
        -I. \
        -I/usr/include/yaml-cpp

    LIBS = \
        $(QT_LIB_PATH)/libQt5Widgets.so \
        $(QT_LIB_PATH)/libQt5Gui.so \
        $(QT_LIB_PATH)/libQt5Core.so \
        $(QT_LIB_PATH)/libQt5Svg.so \
        -lyaml-cpp \
        -lGL \
        -lpthread
else ifeq ($(UNAME_S), Darwin)
    QT_PATH = $(HOME_DIR)/Qt/6.10.0/macos
    YAML_CPP_PATH = /opt/homebrew/Cellar/yaml-cpp/0.8.0

    INCPATH = \
        -I. \
        -I$(YAML_CPP_PATH)/include \
        -I$(QT_PATH)/include \
        -F$(QT_PATH)/lib \
        -I$(QT_PATH)/lib/QtCore.framework/Headers \
        -I$(QT_PATH)/lib/QtGui.framework/Headers \
        -I$(QT_PATH)/lib/QtWidgets.framework/Headers \
        -I$(QT_PATH)/lib/QtSvg.framework/Headers

    LIBS = \
        -L$(YAML_CPP_PATH)/lib -lyaml-cpp \
        $(QT_PATH)/lib/QtWidgets.framework/QtWidgets \
        $(QT_PATH)/lib/QtGui.framework/QtGui \
        $(QT_PATH)/lib/QtCore.framework/QtCore \
        $(QT_PATH)/lib/QtSvg.framework/QtSvg \
        -framework OpenGL \
        -lpthread \
        -Wl,-rpath,$(QT_PATH)/lib
else
    $(error Unsupported operating system)
endif

OBJECTS = $(addprefix $(OBJECTS_DIR), $(notdir $(SOURCES:.cpp=.o)))
MOC_SOURCES = $(addprefix $(OBJECTS_DIR), $(notdir $(HEADERS:.h=.moc.cpp)))
MOC_OBJECTS = $(MOC_SOURCES:.cpp=.o)

all: $(TARGET)

$(shell ./yaml2config cclock.yaml h/ConfigYAML.h)

$(TARGET): $(OBJECTS) $(MOC_OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS) $(MOC_OBJECTS) $(LIBS)

$(OBJECTS_DIR)%.o: %.cpp $(HEADERS)
	@mkdir -p $(OBJECTS_DIR)
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

$(OBJECTS_DIR)%.o: cpp/%.cpp $(HEADERS)
	@mkdir -p $(OBJECTS_DIR)
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

$(OBJECTS_DIR)%.moc.o: $(OBJECTS_DIR)%.moc.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

$(OBJECTS_DIR)%.moc.cpp: h/%.h
	@mkdir -p $(OBJECTS_DIR)
	moc $< -o $@

clean:
	rm -f $(OBJECTS_DIR)*.o $(OBJECTS_DIR)*.moc.cpp $(TARGET) h/ConfigYAML.h

mocables: \
	$(MOC_SOURCES)
