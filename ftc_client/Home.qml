import QtQuick 2.0
import QtQuick.Layouts 1.2

RowLayout{
    id: mainLayout
    anchors.fill: parent
    Layout.margins: 30

    signal logout()
    signal priviledgedLogIn()

    Login{
        id: login
        width: parent.width * 2 / 5
    }

    Connections{
        target:login
        onUsrLogout: {
            logout()
        }
    }

    Connections{
        target: login
        onPriviledgedUser: priviledgedLogIn()
    }

    PersonalInfo{
        id: info
        Layout.fillWidth: true
    }

    /*Rectangle{
        color: '#90D3D3D3'
        x: parent.width * 2 / 5
        y: 0
        width: parent.width * 3 / 5
        height: parent.height
    }*/
}

