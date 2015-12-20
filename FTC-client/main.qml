import QtQuick 2.3
import QtQuick.Window 2.2
import QtQuick.Layouts 1.2



Window {
    id: w
    visible: true
    width: 800; height: 480
    maximumWidth: 800; maximumHeight: 480
    minimumWidth: 800; minimumHeight: 480

    color: 'white'

//        MouseArea {
//            anchors.fill: parent
//            onClicked: {
//                pageloader.source = 'Search.qml'
//            }
//        }

//        Loader{
//            id:pageloader
//            anchors.fill: parent
//            source: 'Home.qml';
//        }

    Frame{}

    Home{}
    /*Search{}
    //*/
    /*Rectangle{
        color: '#90D3D3D3'
        x: parent.width * 2 / 5
        y: 0
        width: parent.width * 3 / 5
        height: parent.height
    }*/
}

