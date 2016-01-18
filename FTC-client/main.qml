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



//    ListView {
//        id: views
//        anchors.fill: parent
//        focus: true
//        clip: true

//        model: ListModel{
//            ListElement{page: 'home'}
//            ListElement{page: 'search'}
//        }
////        delegate: Item{

////        }

//        delegate: Item{
//            id: pages_to_load
//            states: [
//                State {
//                    name: 'home'
//                    when: (views.currentIndex == 0)
//                    PropertyChanges { target: pageloader; source: 'Home.qml' }
//                },

//                State {
//                    name: 'search'
//                    when: (views.currentIndex == 1)
//                    PropertyChanges { target: pageloader; source: 'Search.qml' }
//                }
//            ]
//            onFocusChanged: pages_to_load.state = page
//        }
//    }

    Frame{}

    //Home{}
    //Search{}
}

