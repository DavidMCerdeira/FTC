import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2

Window {
    id: w
    visible: true
    visibility: Window.FullScreen

    color: 'white'

    SwipeDetect{
        // function to switch view on swipe
        function onLeftSwipe() {
            pageloader.source = 'Home.qml'
            console.log('1');
        }

        function onRightSwipe() {
            pageloader.source = 'Search.qml'
            console.log('2');
        }
    }

    Loader{
        id:pageloader
        anchors.fill: parent
        source: 'Home.qml'
    }

    Frame{}

    //Home{}
    //Search{}
}
