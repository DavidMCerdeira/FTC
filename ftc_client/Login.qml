import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Login 1.0
//import CameraCapture 1.0

ColumnLayout{
    Layout.margins: 30
    height: parent.Height
    spacing: 5

    signal priviledgedUser()
    signal usrLogout()

    Text {
        text: 'Press the image after you\'re done!'
        anchors.horizontalCenter: parent.horizontalCenter
    }

    Rectangle {
        id: cam
        anchors.horizontalCenter: parent.horizontalCenter
        color: 'white'
        border.color: 'red'
        border.width: 4

        Layout.minimumWidth: 250
        Layout.minimumHeight: 250

//        Image {
//            id: image
//            cache: false;
//            anchors.centerIn: parent
//            width: parent.width - 2*parent.border.width
//            height: parent.height - 2*parent.border.width
//            Timer{
//                interval: 10; running: true; repeat: true
//                onTriggered: {
//                    /* force image reload */
//                    image.source = "image://WebCam/" + Math.random();
//                }
//            }
//        }

        MouseArea{
            anchors.fill: parent
            onClicked: {
                log.logout()
            }
        }
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        id: recognitionStatus
        text: 'Facial recognition Status:'
    }

    ListView{
        id: wat
        width: 250
        Layout.fillHeight: true
        anchors.horizontalCenter: parent.horizontalCenter
        clip: true
        interactive: false

        model: Login{
            id: log
            onDataChanged: {
                if(log.logged){
                    if(log.priviledged){
                        priviledgedUser()
                        cam.border.color = "gold"
                    }
                    else{
                        cam.border.color = "green"
                    }
                }
                else{
                    cam.border.color = "red"
                    usrLogout()
                }
                if(log.clocked === -1){
                   clockB.text = 'Clock In/Out'
                }
                else if(log.clocked === 0){
                    clockB.text = 'Clock In'
                }
                else if(log.clocked === 1){
                    clockB.text = 'Clock Out'
                }

                update();
            }
        }

        delegate: Text{
            anchors.fill: parent
            id: logText;
            horizontalAlignment: Text.AlignHCenter
            wrapMode: Text.WordWrap
            text: display
            font.pointSize: 15
        }
    }


    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        id: recognitionSuggestion
        verticalAlignment: Text.AlignVCenter
    }

    MyButton{
        id: clockB
        Layout.minimumHeight: 50
        Layout.minimumWidth: 200
        name_pointSize: 18
        name: 'Clock In/Out'
        anchors.horizontalCenter: parent.horizontalCenter

        onClicked: {
            if(log.logged){
                log.clockUser();
            }
            else{
                console.log("You're not logged in!")
            }
        }
    }
}
