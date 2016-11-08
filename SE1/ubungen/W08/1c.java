if(changed) {
    if (fullFileName.isEmpty()) {
        savePresentationAs_(aGraphic);
    } else{
        // hier drin werden string undXMLException als fehler geworfen
        theDocument.save();
    }
}
