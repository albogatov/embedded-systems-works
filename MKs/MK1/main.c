#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
int main(int argc, char** argv) {
    IMAGE_DOS_HEADER dos_header;
    IMAGE_FILE_HEADER file_header;
    IMAGE_OPTIONAL_HEADER optional_header;
    FILE* filePointer;
    FILE* textFilePointer;
    FILE* binFilePointer;
    if (fopen_s(&binFilePointer, "code.bin", "wb") != 0)
        return 1;
    if (fopen_s(&filePointer, argv[1], "rb") != 0)
        return 1;
    if (fread(&dos_header, sizeof(IMAGE_DOS_HEADER), 1, filePointer) != 1)
        return 1;
    if (fseek(filePointer, dos_header.e_lfanew, SEEK_SET) != 0)
        return 1;
    if (fseek(filePointer, 4, SEEK_CUR) != 0)
        return 1;
    if (fread(&file_header, sizeof(IMAGE_FILE_HEADER), 1, filePointer) != 1)
        return 1;
    if (fread(&optional_header, sizeof(IMAGE_OPTIONAL_HEADER), 1, filePointer) != 1)
        return 1;
    if (fopen_s(&textFilePointer, "section_info.txt", "w") != 0)
        return 1;
    fprintf(textFilePointer, "Section info: \n");
    fprintf(textFilePointer, "Number of sections: %d \n", file_header.NumberOfSections);
    fprintf(textFilePointer, "Sum of all sections: 0x%X \n", optional_header.SizeOfCode);
    fprintf(textFilePointer, "Uninitialized data size: 0x%X \n", optional_header.SizeOfUninitializedData);
    fprintf(textFilePointer, "Initialized data size: 0x%X \n", optional_header.SizeOfInitializedData);
    fprintf(textFilePointer, "Base of code: 0x%X \n", optional_header.BaseOfCode);
    fprintf(textFilePointer, "Base of data: 0x%X \n", optional_header.BaseOfData);
    fprintf(textFilePointer, "Address of Entry Point is 0x%X \n", optional_header.AddressOfEntryPoint);
    if (fseek(filePointer, abs(224 - file_header.SizeOfOptionalHeader), SEEK_CUR) != 0)
        return 1;
    fprintf(textFilePointer, "\n\nList of sections: \n");
    IMAGE_SECTION_HEADER* section_header = (IMAGE_SECTION_HEADER*) malloc(sizeof(IMAGE_SECTION_HEADER)* file_header.NumberOfSections);
    if (fread(section_header, sizeof(IMAGE_SECTION_HEADER), file_header.NumberOfSections, filePointer) != file_header.NumberOfSections)
        return 1;
    for (size_t i = 0; i < file_header.NumberOfSections; i++) {
        fprintf(textFilePointer, "\nSection %d\n", i + 1);
        fprintf(textFilePointer, "Section name: %s\n", section_header[i].Name);
        fprintf(textFilePointer, "Virtual size: %X\n", section_header[i].Misc.VirtualSize);
        fprintf(textFilePointer, "Virtual address: %X\n", section_header[i].VirtualAddress);
        fprintf(textFilePointer, "Raw data size: %X\n", section_header[i].SizeOfRawData);
        fprintf(textFilePointer, "Pointer to raw data: %X\n", section_header[i].PointerToRawData);
        fprintf(textFilePointer, "Pointer to relocations: %X\n", section_header[i].PointerToRelocations);
        fprintf(textFilePointer, "Pointer to line numbers: %X\n", section_header[i].PointerToLinenumbers);
        fprintf(textFilePointer, "Number of relocations: %X\n", section_header[i].NumberOfRelocations);
        fprintf(textFilePointer, "Number of linenumbers: %X\n", section_header[i].NumberOfLinenumbers);
        fprintf(textFilePointer, "Characteristics: %X\n", section_header[i].Characteristics);
        if (section_header[i].Characteristics & IMAGE_SCN_MEM_EXECUTE) {
            void* data = malloc(section_header[i].SizeOfRawData);
            if (data) {
                if (fseek(filePointer, section_header[i].PointerToRawData, SEEK_SET) != 0) {
                    free(data);
                    free(section_header);
                    return 1;
                }
                if (fread(data, section_header[i].SizeOfRawData, 1, filePointer) != 1) {
                    free(data);
                    free(section_header);
                    return 1;
                }
                if (fwrite(data, section_header[i].SizeOfRawData, 1, binFilePointer) != 1) {
                    free(data);
                    free(section_header);
                    return 1;
                }
            }
            free(data);
        }
       
    }
    free(section_header);
    fclose(textFilePointer);
    fclose(binFilePointer);
    fclose(filePointer);
    return 0;
}
