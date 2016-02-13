import QtQuick 2.0

MouseArea {
    id: mouseArea
    anchors.fill: parent;

    property int oldX: 0
    property int oldY: 0

    onPressed: {
        oldX = mouseX;
        oldY = mouseY;
    }

    onReleased: {
        var xDiff = oldX - mouseX;
        var yDiff = oldY - mouseY;
        if( Math.abs(xDiff) > Math.abs(yDiff) ) {
            if( xDiff > 0 && xDiff > 100) {
                onLeftSwipe();
            } else if(xDiff < 0 && xDiff < -100) {
                onRightSwipe();
            }
        } else {
            if( oldY > mouseY) {/*up*/ }
            else {/*down*/ }
        }
    }
}
