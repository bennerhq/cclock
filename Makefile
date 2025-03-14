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
	main.cpp \
	cpp/ClockWidget.cpp \
	cpp/ClockWindow.cpp \
	cpp/ConfigYAML.cpp

HEADERS = \
	h/ClockWidget.h \
	h/ClockWindow.h \
	h/ConfigYAML.h

OBJECTS_DIR = ./obj/

CXXFLAGS = \
    -pipe -O2 -std=gnu++1z -Wall -Wextra -D_REENTRANT -fPIC \
    -DQT_NO_DEBUG -DQT_WIDGETS_LIB -DQT_GUI_LIB -DQT_CORE_LIB

# Get the home directory
HOME_DIR := $(shell echo ~)

# Detect the operating system
UNAME_S := $(shell uname -s)

# Set paths and libraries based on the operating system
ifeq ($(UNAME_S), Linux)
	INCPATH = \
		-I. \
		-I/usr/include/yaml-cpp \
		-I/usr/include/x86_64-linux-gnu/qt5 \
		-I/usr/include/x86_64-linux-gnu/qt5/QtWidgets \
		-I/usr/include/x86_64-linux-gnu/qt5/QtGui \
		-I/usr/include/x86_64-linux-gnu/qt5/QtCore

	LIBS = \
		-lyaml-cpp \
		/usr/lib/x86_64-linux-gnu/libQt5Widgets.so \
		/usr/lib/x86_64-linux-gnu/libQt5Gui.so \
		/usr/lib/x86_64-linux-gnu/libQt5Core.so \
		-lGL \
		-lpthread
else ifeq ($(UNAME_S), Darwin)
	QT_DIR = $(HOME_DIR)/Qt/6.10.0/macos
    YAML_CPP_PATH = /opt/homebrew/Cellar/yaml-cpp/0.8.0

	INCPATH = \
		-I. \
        -I$(YAML_CPP_PATH)/include \
		-I$(QT_DIR)/include \
		-F$(QT_DIR)/lib \
		-I$(QT_DIR)/lib/QtCore.framework/Headers \
		-I$(QT_DIR)/lib/QtGui.framework/Headers \
		-I$(QT_DIR)/lib/QtWidgets.framework/Headers

	LIBS = \
		-L$(YAML_CPP_PATH)/lib -lyaml-cpp \
		$(QT_DIR)/lib/QtWidgets.framework/QtWidgets \
		$(QT_DIR)/lib/QtGui.framework/QtGui \
		$(QT_DIR)/lib/QtCore.framework/QtCore \
		-framework OpenGL \
		-lpthread \
		-Wl,-rpath,$(QT_DIR)/lib
endif

OBJECTS = $(addprefix $(OBJECTS_DIR), $(notdir $(SOURCES:.cpp=.o)))
MOC_SOURCES = $(addprefix $(OBJECTS_DIR), $(notdir $(HEADERS:.h=.moc.cpp)))
MOC_OBJECTS = $(MOC_SOURCES:.cpp=.o)

all: $(TARGET)

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
	rm -f $(OBJECTS_DIR)*.o $(OBJECTS_DIR)*.moc.cpp $(TARGET)

mocables: $(MOC_SOURCES)
