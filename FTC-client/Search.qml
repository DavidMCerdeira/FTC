import QtQuick 2.0
import QtQuick.Layouts 1.2

Item {
    //anchors.fill: parent

    RowLayout{
        id: mainLayout
        anchors.fill: parent

        ColumnLayout{
            Layout.margins: 30

            Layout.fillHeight: true
            Layout.maximumWidth: parent.width * 1 / 3

            SearchEmployee{
                id: employee;
                anchors.fill: parent
                Layout.fillWidth: true;
            }

            MyButton{
                id: searchButton;
                anchors.horizontalCenter: parent.horizontalCenter
                name: 'Search'
                name_pointSize: 18
                Layout.minimumWidth: 150
                Layout.minimumHeight: 50

                onClicked: {
                    employee.search();
                    working.search();
                }
            }
        }

        SearchWorking{
            id: working
            //anchors.left: employee.right
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}

