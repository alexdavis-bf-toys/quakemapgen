TEMPLATE        = app
TARGET          = quakemapgen

CONFIG          += qt warn_on release
#CONFIG         += qt warn_on debug
DEPENDPATH      = /Devloper/Qt/include
#REQUIRES        = large-config

SOURCES   = main.cpp world.cpp block.cpp object.cpp stairs.cpp teleport.cpp room.cpp entity.cpp imagetemplateroom.cpp
