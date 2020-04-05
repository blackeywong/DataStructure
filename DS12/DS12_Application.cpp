#include <iostream>
#include <fstream>

#include "Heap.h"
#include "DS12_Application.h"
#include "HuffmanCoding.h"

void makeSchedule(JobNode a[], int n, int m) {
    if (n <= m) {
        std::cout << "Schedule each job on a different machine." << endl;
        return;
    }

    heapSort(a, n);

    Heap<MachineNode> machineHeap(m, false);
    for (int i = 1; i <= m; ++i) {
        machineHeap.push(MachineNode(i, 0));
    }

    for (int i = n - 1; i >= 0; --i) {
        MachineNode x = machineHeap.top();
        machineHeap.pop();
        //std::cout << "Schedule job " << a[i].id << " on machine " << x.id << " from " << x.avail << " to " << (x.avail + a[i].time) << std::endl;
        x.avail += a[i].time;
        machineHeap.push(x);
    }
}
//Exercise 33
void makeSchedule2(JobNode a[], int n, int m) {
    if (n <= m) {
        std::cout << "Schedule each job on a different machine." << endl;
        return;
    }

    heapSort(a, n);

    Heap<MachineNode> machineHeap(m, false);
    for (int i = 1; i <= m; ++i) {
        machineHeap.push(MachineNode(i, 0));
    }

    for (int i = n - 1; i >= 0; --i) {
        MachineNode x = machineHeap.top();
        //std::cout << "Schedule job " << a[i].id << " on machine " << x.id << " from " << x.avail << " to " << (x.avail + a[i].time) << std::endl;
        x.avail += a[i].time;
        machineHeap.changeTop(x);
    }
}

bool packItems(ItemNode a[], int n, int m, int c) {//Exercise 36
    if (n <= m) {
        //std::cout << "Pack each item in a different container." << endl;
        return false;
    }

    heapSort(a, n);

    Heap<ContainerNode> containerHeap(m);
    for (int i = 1; i <= m; ++i) {
        containerHeap.push(ContainerNode(i, c));
    }

    for (int i = n - 1; i >= 0; --i) {
        ContainerNode x = containerHeap.top();
        containerHeap.pop();
        //std::cout << "Item " << a[i].id << " is put in container " << x.id << " and available space reduced from " << x.avail << " to " << (x.avail - a[i].space) << std::endl;
        x.avail -= a[i].space;
        if (x.avail < 0) {
            //std::cout << "Item " << a[i].id << " needs space " << a[i].space << " cannot be put in container " << x.id << " which has largest available space " << x.avail << std::endl;
            return false;
        }
        containerHeap.push(x);
    }

    return true;
}

//Exercise 43
void HuffmanCompress::init() {
    weight = new unsigned int[charNum];
    elements = new unsigned int[charNum];
    for (int i = 0; i < charNum; ++i) {
        weight[i] = 0;
        elements[i] = 0;
    }
}

bool HuffmanCompress::compress(const std::string& inFile, const std::string& outFile) {
    std::ifstream in(inFile, std::ifstream::in | std::ifstream::binary);
    std::ofstream out(outFile, std::ofstream::out | std::ofstream::binary);

    //int chars[] = { 'a','b' };
    for (int i = 0; i < charNum; ++i) {
        weight[i] = 0;
    }
    //count the frequency of each char, put in weight array
    unsigned int c = in.get();
    while (!in.eof()) {
        //++weight[c - 97];
        ++weight[c];
        c = in.get();
    }
    in.close();
 
    HuffmanCoding hc(weight, charNum);// , chars);
    //hc.output(std::cout);
    in.open(inFile, std::ifstream::in | std::ifstream::binary);
    hc.store(in, out);

    in.close();
    out.close();
    return true;
}

bool HuffmanCompress::uncompress(const std::string& inFile, const std::string& outFile) {
    std::ifstream in(inFile, std::ifstream::in | std::ifstream::binary);
    std::ofstream out(outFile, std::ofstream::out | std::ofstream::binary);

    for (int i = 0; i < charNum; ++i) {
        weight[i] = 0;
        elements[i] = 0;
    }

    //read weights
    unsigned int codeCount = 0;
 
    codeCount = getInt(in);
    for (unsigned int i = 0; i < codeCount; ++i) {
        weight[i] = getInt(in);
        elements[i] = getInt(in);
    }

    HuffmanCoding hc(weight, charNum, elements);
    //hc.output(std::cout);
    hc.read(in, out);

    in.close();
    out.close();
    return true;
}

bool huffmanCompress(const std::string& inFile, const std::string& outFile) {
    HuffmanCompress hc(256);
    return hc.compress(inFile, outFile);
}

bool huffmanUncompress(const std::string& inFile, const std::string& outFile) {
    HuffmanCompress hc(256);
    return hc.uncompress(inFile, outFile);
}

//Exercise 44
bool huffmanCompress512(const std::string& inFile, const std::string& outFile) {
    HuffmanCompress hc(512);
    return hc.compress(inFile, outFile);
}

bool huffmanUncompress512(const std::string& inFile, const std::string& outFile) {
    HuffmanCompress hc(512);
    return hc.uncompress(inFile, outFile);
}