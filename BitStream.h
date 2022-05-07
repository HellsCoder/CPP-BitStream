#pragma once
#include <vector>
#include <string>

typedef int byte;

class BitStream
{

private:
	std::vector<byte> bytes;
	size_t writePointerByte;
	size_t writePointerBit;
	
	size_t readPointerByte;
	size_t readPointerBit;

	/*alloc mem to write*/
	void walloc();
	/*alloc mem to read*/
	void ralloc();

public:
	/*bytes - to initial state of bitstream*/
	BitStream(std::vector<byte> bytes = {}) {
		this->bytes = bytes;
		this->writePointerByte = 0;
		this->writePointerBit = 0;

		this->readPointerBit = 0;
		this->readPointerByte = 0;
	}

	/*write bool/bit*/
	void writeBoolean(bool);
	/*read bool/bit*/
	bool readBoolean();

	/*write byte/8 bit int*/
	void writeByte(byte);
	/*read byte/8 bit int*/
	byte readByte();

	/*write string, only 8 bit characters*/
	void writeString(std::string);
	/*read string*/
	std::string readString(size_t);

	/*write 32 bit int*/
	void writeInt32(int32_t);
	/*read 32 bit int*/
	int32_t readInt32();

	/*write 16 bit int*/
	void writeInt16(int16_t);
	/*read 16 bit int*/
	int16_t readInt16();

	/*print byte array and state*/
	void printByteArray();
	/*save bs to file*/
	void saveToFile(std::string);
	/*read bs from file. its work on empty bs*/
	void readFromFile(std::string);
};

