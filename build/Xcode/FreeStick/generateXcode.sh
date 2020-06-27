#!/bin/sh
#run from inside the folder
#SNFqtverion=5.15.0
echo "***** QT Version Used *****"
echo $SNFqtverion
#qmake=/Users/alan/Qt/$SNFqtverion/ios/bin/qmake
echo "******* Looking for qmake in $qmake ***********"
$qmake  -spec macx-xcode ../../QT/FreeStick/FreeStick.pro 
$qmake  -spec macx-xcode ../../QT/JoyStickConfig/JoyStickConfig.pro 
echo "Please add FreeStick as a link lib to JoyStickConfig to establish a dependency build order"