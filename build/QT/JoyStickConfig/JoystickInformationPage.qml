import QtQuick 2.12

JoystickInformationPageForm {
    property int currentInfoPageControllerID: 0
    onCurrentInfoPageControllerIDChanged: {
       frendlyname.text = deviceManager.getFriendlyName(currentInfoPageControllerID)
       vendorID.text = deviceManager.getVendorID(currentInfoPageControllerID).toString()
       vendorName.text = deviceManager.getVendorName(currentInfoPageControllerID).toString()
       productID.text =  deviceManager.getProductID(currentInfoPageControllerID).toString()
       productName.text = deviceManager.getProductName(currentInfoPageControllerID)
    }
}
