import QtQuick 2.0
import QtQuick.Layouts 1.2
import QtQuick.Controls 1.4
import QtQuick.Controls.Styles 1.4
import JobsModel 1.0
import DepartmentsModel 1.0
import SetNameForSearch 1.0

ColumnLayout {
    id: root
    spacing: 5

    Text{
        anchors.horizontalCenter: parent.horizontalCenter
        id: title
        font.pointSize: 24
        text: "Search Employee"
    }

    Text{
        anchors.left: parent.left
        id: filtersTitle
        font.pointSize: 20
        text: 'Filter:'
    }

    Rectangle{
          anchors.horizontalCenter: parent.horizontalCenter
          Layout.fillWidth: true
          Layout.minimumHeight: nameInput.height + 20
          border.width: 2

          MouseArea{
              id: nameInputArea
              anchors.fill: parent

              onClicked: {
                  keyboard.visible = !keyboard.visible
              }

              TextEdit{
                  id: nameInput
                  anchors.verticalCenter: parent.verticalCenter
                  anchors.horizontalCenter: parent.horizontalCenter
                  text: ''
                  font.pointSize: 16
              }
          }
      }

      Keyboard {
          id: keyboard
          visible: false

          Component.onCompleted: {
              keyboard.letterClicked.connect(letterPressed)
          }

          function letterPressed(letter){
              if(letter === '←'){
                  nameInput.text = nameInput.text.substr(0, nameInput.text.length-1)
                  nameInput.cursorPosition = nameInput.text.length
              }else if(letter === '┘'){
                  keyboard.visible = false;
                  setName.setName(nameInput.text)
              }else{
                  nameInput.insert(nameInput.length, letter);
              }
          }
      }

      SetNameForSearch{
          id: setName;
      }


    MyComboBox{
        id: departments
        anchors.horizontalCenter: parent.horizontalCenter
        height: 120
        Layout.fillWidth: true
        thisModel: DepartmentsModel{
            id: dprts
        }
    }

    MyComboBox{
        id: jobs
        anchors.horizontalCenter: parent.horizontalCenter
        height: 120
        Layout.fillWidth: true
        thisModel: JobsModel{
            id: jbs
        }
    }

    Connections{
        target: departments
        onCurItemChanged: {
            dprts.currentItemChanged(idx)
            jbs.departmentChanged(idx)
        }
    }

    Connections{
        target: jobs
        onCurItemChanged: {
            jbs.currentItemChanged(idx)
        }
    }
}
