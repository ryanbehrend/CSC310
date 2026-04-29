#include "geneBank.h"

// =================================== PUBLIC FUNCTIONS =======================================================

GENE_BANK::GENE_BANK()
{
    this->fileSize = 0;
    this->entryByte = sizeof(Sample);
}

GENE_BANK::~GENE_BANK()
{
    cout << "Destructing ..." << endl;
}

void GENE_BANK::sort(Sample array[], int fileSize)
{
    const int NUM_SPECIES = 5;
    int count[NUM_SPECIES] = {0};

    for (int i = 0; i < fileSize; i++)
    {
        count[array[i].speciesCode]++;
    }

    int startIndex[NUM_SPECIES];
    startIndex[0] = 0;
    for (int i = 1; i < NUM_SPECIES; i++)
    {
        startIndex[i] = startIndex[i - 1] + count[i - 1];
    }

    Sample *temp = new Sample[fileSize];
    int index[NUM_SPECIES];
    for (int i = 0; i < NUM_SPECIES; i++)
    {
        index[i] = startIndex[i];
    }

    for (int i = 0; i < fileSize; i++)
    {
        int species = array[i].speciesCode;
        temp[index[species]++] = array[i];
    }

    for (int i = 0; i < fileSize; i++)
    {
        array[i] = temp[i];
    }

    delete[] temp;
}

void GENE_BANK::indexSamples(Sample array[], int indexArray[])
{
    this->p_index(array, indexArray);
}

void GENE_BANK::displayResearcher(int speciesCode, int offset, char *filename)
{
    bool checkSample;

    checkSample = searchSample(speciesCode, offset, filename);

    if (checkSample)
    {
        p_displayResearcher(speciesCode, offset, filename);
    }
    else
    {
        cout << "Sample record doesn't exist! Can't display researcher name." << endl;
    }
}

bool GENE_BANK::searchSample(int speciesCode, int offset, char *filename)
{
    ifstream inFile(filename, ios::binary | ios::in);

    if (!inFile)
    {
        cout << "Error: Could not open file " << filename << endl;
        return false;
    }

    int speciesStart = indexArray[speciesCode];
    long filePosition = (speciesStart + offset) * sizeof(Sample);

    inFile.seekg(filePosition, ios::beg);

    Sample tempSample;
    inFile.read(reinterpret_cast<char *>(&tempSample), sizeof(Sample));

    inFile.close();

    if (tempSample.speciesCode == speciesCode)
    {
        return true;
    }

    return false;
}

void GENE_BANK::updateResearcher(int speciesCode, int offset, char *newName, char *filename)
{
    bool checkSample;

    checkSample = this->searchSample(speciesCode, offset, filename);

    if (checkSample)
    {
        p_updateResearcher(speciesCode, offset, newName, filename);
    }
    else
    {
        cout << "Sample record to be updated doesn't exist!" << endl;
    }
}

void GENE_BANK::deleteSample(int speciesCode, int offset, char *filename)
{
    bool checkSample;

    checkSample = this->searchSample(speciesCode, offset, filename);

    if (checkSample)
    {
        p_deleteSample(speciesCode, offset, filename);
    }
    else
    {
        cout << "Sample record to be deletesd doesn't exist!" << endl;
    }
}

void GENE_BANK::printSampleRange(int speciesCode, int startIndex, int endIndex, char *filename)
{
    if (startIndex >= endIndex)
    {
        throw MyException("ERROR: start index is larger than end index!");
    }
    else
    {
        this->p_printRange(speciesCode, startIndex, endIndex, filename);
    }
}

// =================================== PRIVATE FUNCTIONS =======================================================

// your sorting algorithm here

void GENE_BANK::p_index(Sample array[], int indexArray[])
{
    for (int i = 0; i < 5; i++)
    {
        indexArray[i] = -1;
    }

    int currentSpecies = -1;

    for (int i = 0; i < fileSize; i++)
    {
        if (array[i].speciesCode != currentSpecies)
        {
            indexArray[array[i].speciesCode] = i;
            currentSpecies = array[i].speciesCode;
        }
    }
}

void GENE_BANK::p_displayResearcher(int speciesCode, int offset, char *filename)
{
    fstream binaryFile(filename, ios::in | ios::binary);

    if (!binaryFile)
    {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    int speciesStart = indexArray[speciesCode];

    long filePosition = (speciesStart + offset) * sizeof(Sample);
    binaryFile.seekg(filePosition, ios::beg);

    Sample tempSample;
    binaryFile.read(reinterpret_cast<char *>(&tempSample), sizeof(Sample));

    binaryFile.close();

    cout << "Species Code: " << tempSample.speciesCode << endl;
    cout << "Sample ID: " << tempSample.sampleID << endl;
    cout << "Researcher: " << tempSample.researcher << endl;
    cout << "Purity Score: " << tempSample.purityScore << endl;
    cout << endl;
}

void GENE_BANK::p_updateResearcher(int speciesCode, int offset, char *newName, char *filename)
{
    fstream binaryFile(filename, ios::in | ios::out | ios::binary);

    if (!binaryFile)
    {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    int speciesStart = indexArray[speciesCode];

    long filePosition = (speciesStart + offset) * sizeof(Sample);
    binaryFile.seekg(filePosition, ios::beg);

    Sample tempSample;
    binaryFile.read(reinterpret_cast<char *>(&tempSample), sizeof(Sample));

    strcpy(tempSample.researcher, newName);

    binaryFile.seekp(filePosition, ios::beg);
    binaryFile.write(reinterpret_cast<char *>(&tempSample), sizeof(Sample));

    binaryFile.close();

    cout << "Researcher name updated successfully." << endl;
}

void GENE_BANK::p_deleteSample(int speciesCode, int offset, char *filename)
{
    fstream binaryFile(filename, ios::in | ios::out | ios::binary);

    if (!binaryFile)
    {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    int speciesStart = indexArray[speciesCode];

    long deletePosition = (speciesStart + offset) * sizeof(Sample);

    binaryFile.seekg(0, ios::end);

    binaryFile.seekg(deletePosition, ios::beg);
    Sample deletedSample;
    binaryFile.read(reinterpret_cast<char *>(&deletedSample), sizeof(Sample));

    deletedSample.speciesCode = -1;
    deletedSample.sampleID = -1;

    binaryFile.seekp(deletePosition, ios::beg);
    binaryFile.write(reinterpret_cast<char *>(&deletedSample), sizeof(Sample));

    binaryFile.close();

    cout << "Sample record deleted successfully." << endl;
}

void GENE_BANK::p_printRange(int speciesCode, int startIndex, int endIndex, char *filename)
{
    fstream binaryFile(filename, ios::in | ios::binary);

    if (!binaryFile)
    {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    int speciesStart = indexArray[speciesCode];

    for (int i = startIndex; i <= endIndex; i++)
    {
        long filePosition = (speciesStart + i) * sizeof(Sample);
        binaryFile.seekg(filePosition, ios::beg);

        Sample tempSample;
        binaryFile.read(reinterpret_cast<char *>(&tempSample), sizeof(Sample));

        if (tempSample.speciesCode == -1)
        {
            continue;
        }

        cout << "--- Sample " << i << " ---" << endl;
        cout << "Species Code: " << tempSample.speciesCode << endl;
        cout << "Sample ID: " << tempSample.sampleID << endl;
        cout << "Researcher: " << tempSample.researcher << endl;
        cout << "Purity Score: " << tempSample.purityScore << endl;
        cout << endl;
    }

    binaryFile.close();
}
