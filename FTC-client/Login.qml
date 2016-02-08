import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import Login 1.0

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
        anchors.horizontalCenter: parent.horizontalCenter
        color: 'white'
        border.color: 'black'
        border.width: 2

        Layout.minimumWidth: 250
        Layout.minimumHeight: 250

        MouseArea{
            anchors.fill: parent
            onClicked: {
                //usrLogout()
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
                    }
                }
                else{
                    usrLogout()
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
