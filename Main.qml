import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs 6.3

ApplicationWindow {
    width: 1500
    height: 750
    visible: true
    title: "Image Pixel Reader"

    // Force Material dark theme
    Material.theme: Material.Dark
    Material.accent: Material.Purple    // optional accent color

    Row {
        anchors.fill: parent
        spacing: 10
        anchors.margins: 10

        // Left column: controls + image preview
        Column {
            width: parent.width * 0.35
            spacing: 10

            TextField {
                id: pathField
                placeholderText: "Enter image path..."
                width: parent.width
            }

            Button {
                text: "Browse..."
                onClicked: {
                    var selected = FileDialogHelper.openFile("Select an image", "Images (*.png *.jpg *.bmp)")
                    if (selected !== "")
                        pathField.text = selected
                }
            }

            Button {
                text: "Generate code"
                onClicked: {
                    outputArea.text = imageReader.loadAndRead(pathField.text)
                }
            }

            // Image preview
            Image {
                id: previewImage
                width: parent.width
                height: width   // square preview
                fillMode: Image.PreserveAspectFit
                layer.smooth: false    // show pixels sharply
                smooth: false

                // Convert local path to proper file URL
                source: pathField.text !== "" ? "file://" + pathField.text : ""
                visible: source !== ""
            }

            FileDialog {
                id: fileDialog
                title: "Select an image"
                nameFilters: ["Image files (*.png *.jpg *.bmp)"]

                onAccepted: {
                    console.log("Accepted!")
                    console.log("fileUrl:", fileDialog.selectedFile)

                    // Convert file:// URL to local path
                    var localPath = fileDialog.selectedFile.toString()
                    if (localPath.startsWith("file://")) {
                        localPath = localPath.replace("file://", "")
                    }
                    console.log("fileUrl2:", localPath)

                    pathField.text = localPath
                }

                onRejected: {
                    console.log("Dialog rejected")
                }
            }
        }

        // Right column: output + copy button
        Column {
            width: parent.width * 0.65
            height: parent.height
            spacing: 10

            ScrollView {
                id: outputScroll
                width: parent.width
                height: parent.height - 60   // leave space for button

                ScrollBar.horizontal.policy: ScrollBar.AlwaysOn
                ScrollBar.vertical.policy: ScrollBar.AlwaysOn

                Flickable {
                    contentWidth: Math.max(outputArea.implicitWidth, parent.width)
                    contentHeight: Math.max(outputArea.implicitHeight, parent.height)
                    clip: true

                    TextArea {
                        id: outputArea
                        readOnly: true
                        wrapMode: Text.NoWrap
                        textFormat: Text.PlainText
                        font.family: "Monospace"
                        anchors.top: parent.top
                        anchors.left: parent.left
                        width: Math.max(implicitWidth, parent.width)
                        height: Math.max(implicitHeight, parent.height)
                    }
                }
            }

            Button {
                text: "Copy Output"
                onClicked: {
                    imageReader.copyText(outputArea.text)
                }
            }
        }
    }
}