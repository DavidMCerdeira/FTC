import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2

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
            console.log("Swipped to home screen");
            pageloader.source = 'Home.qml'
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
}

