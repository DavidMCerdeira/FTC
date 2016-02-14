import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2
import DistanceSensor 1.0

Window {
    id: w
    visible: true
    //    visibility: Window.FullScreen
    width: 800; height: 480

    color: 'white'

    SwipeDetect{
        id: swipping
        property bool allowed: false
        // function to switch view on swipe
        function onLeftSwipe() {
            allowed = false
            console.log("Swipped to home screen");
            pageloader.source = 'Home.qml'
            ds.userLeft();
            sq.opacity = 1
            sq.width = 500
            sq.height = 200
        }

        function onRightSwipe() {
            if(allowed){
                console.log("Swipped to search screen");
                pageloader.source = 'Search.qml'
            }
        }
    }

    Loader{
        id:pageloader
        anchors.fill: parent
        /*
        source: 'Search.qml'
        /*/
        source: 'Home.qml'
        //*/
    }

    Connections{
        target: pageloader.item
        onLogout: {
            console.log("No swipping!")
            swipping.allowed = false;
            sq.opacity = 1
            sq.width = 500
            sq.height = 200
        }
    }
    Connections{
        target: pageloader.item
        onPriviledgedLogIn: {
            console.log("Login is priviledged, you may swipe")
            swipping.allowed = true;
        }
    }

    Frame{}

    Rectangle{
        id: sq
        width: 500
        height: 200
        anchors.centerIn: parent
        color: 'white' //'#B33A3A'
        border.width: 5
        radius: 10
        Text{
            anchors.centerIn: parent
            text: "CLICK TO ENTER"
            font.pointSize: 35
            font.bold: true
        }
        MouseArea{
            id: ma
            anchors.fill: parent
            onPressed: {
                ds.userDetected();
                sq.opacity = 0
                sq.width = 0
                sq.height = 0
            }
        }
    }

    DistanceSensor{
        id: ds
    }

}

