void read_Raw(String path) {
	if (SD.exists(path.c_str()))
		f = SD.open(path.c_str());
	else
		return;
	short int signalLenght = 0;
	//conta virgole e terminatore e metti in signalLenght, poi torna a posizione 0
	unsigned int signal[signalLenght];
	short int signalIndex = 0;
	String bufferText = "";
	char tmpChar;
	while (f.available()) {
		tmpChar = f.read();
		if (tmpChar == ",") {
			signal[signalIndex] = bufferText.toInt(); //trasforma in intero
			if (bufferText.length() > 0)
				bufferText.remove(0);
			signalIndex++;
		}
		else if (tmpChar == "§") {
			signal[signalIndex] = bufferText.toInt(); //trasforma in intero
			if (bufferText.length() > 0)
				bufferText.remove(0);
			break;
		}
		else {
			bufferText += tmpChar;
		}
	}
	//sendraw signal[]
	f.close();
	return;
}