#include "BitStream.h"
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

void BitStream::walloc() {
	if ((this->bytes.size() < this->writePointerByte) || (this->bytes.size() == 0) || 
		(this->writePointerBit == 8)) {
		this->bytes.push_back(0x0);
		this->writePointerBit = 0;
		this->writePointerByte = this->bytes.size() - 1;
	}
}

void BitStream::ralloc() {
	if (this->readPointerBit == 8) {
		this->readPointerBit = 0;
		this->readPointerByte++;
	}
	if (this->bytes.size() < this->readPointerByte) {
		/*end of bitstream, move to forvard byte*/
		this->readPointerByte--;
	}
}

void BitStream::writeBoolean(bool boolean) {
	walloc();
	byte b = this->bytes[this->writePointerByte];         
	b |= boolean << (7 - this->writePointerBit);
	this->bytes[this->writePointerByte] = b;
	this->writePointerBit++;
}

bool BitStream::readBoolean() {
	ralloc();
	bool bit = ((this->bytes[this->readPointerByte] >> (7 - this->readPointerBit)) & 1);
	this->readPointerBit++;
	return bit;
}

void BitStream::writeByte(byte b) {
	for (int i = 0; i < 8; i++) {
		bool bit = ((b >> (7 - i)) & 1);
		this->writeBoolean(bit);
	}
}

byte BitStream::readByte() {
	byte b = 0x0;
	for (int i = 0; i < 8; i++) {
		bool bit = this->readBoolean();
		b |= bit << (7 - i);
	}
	return b;
}

void BitStream::printByteArray() {
	cout << "WP Byte: " << this->writePointerByte << '\n';
	cout << "WP Bit: " << this->writePointerBit << '\n';

	cout << "RP Bit: " << this->readPointerBit << '\n';
	cout << "RP Bit: " << this->readPointerBit << '\n';

	for (size_t i = 0; i < this->bytes.size(); i++) {
		cout << "0x" << hex << this->bytes[i] << " ";
	}
}

void BitStream::writeInt32(int32_t integer) {
	for (size_t i = 0; i < 32; i++) {
		bool bit = (integer >> i) & 1;
		this->writeBoolean(bit);
	}
}

int32_t BitStream::readInt32() {
	int32_t r = 0;
	for (int i = 0; i < 32; i++) {
		bool bit = this->readBoolean();
		r |= bit << (i);
	}
	return r;
}

int16_t BitStream::readInt16() {
	int16_t r = 0;
	for (int i = 0; i < 16; i++) {
		bool bit = this->readBoolean();
		r |= bit << (i);
	}
	return r;
}

void BitStream::writeInt16(int16_t integer) {
	for (size_t i = 0; i < 16; i++) {
		bool bit = (integer >> i) & 1;
		this->writeBoolean(bit);
	}
}

void BitStream::writeString(string str) {
	for (size_t i = 0; i < str.size(); i++) {
		byte b = (char)str[i];
		this->writeByte(b);
	}
}

string BitStream::readString(size_t size) {
	vector<byte> bytes;
	for (size_t i = 0; i < size; i++) {
		bytes.push_back(this->readByte());
	}

	return string(bytes.begin(), bytes.end());
}

void BitStream::readFromFile(string path) {
	if (this->bytes.size() > 0) {
		cout << "cannot read stream from file, because bs is not empty" << endl;
		return;
	}
	ifstream file;
	file.open(path);

	if (!file.is_open()) {
		cout << "failed to open file " + path << endl;
		return;
	}

	char b;
	while (file.get(b)) {
		this->bytes.push_back((int)b);
	}

	file.close();
}

void BitStream::saveToFile(string path) {
	ofstream file;
	file.open(path);

	if (!file.is_open()) {
		cout << "failed to open file " + path << endl;
		return;
	}

	for (size_t i = 0; i < this->bytes.size(); i++) {
		file << (char)this->bytes[i];
	}

	file.close();
}