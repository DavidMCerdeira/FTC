import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2

Window {
    id: w
    visible: true
//    visibility: Window.FullScreen
    width: 800; height: 480

    color: 'white'

    Frame{}

    SwipeDetect{
        // function to switch view on swipe
        function onLeftSwipe() {
            pageloader.source = 'Home.qml'
            console.log("On home screen");
        }

        function onRightSwipe() {
            pageloader.source = 'Search.qml'
            console.log("On search screen");
        }
    }

    Loader{
        id:pageloader
        anchors.fill: parent
        /*
        source: 'Search.qml'
        //*/
        //*
        source: 'Home.qml'
        //*/
    }
}

