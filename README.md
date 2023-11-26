# PRPR Asignment 2 - Linked List of Structures - Dataloger

## Introduction

This program works with records in a dynamic linked list. The records are stored in a file called `dataloger_V2.txt`, which contains data from a measuring module. Before each record in the file, there will be a line containing the characters `$$$` to visibly separate the records. Each item in the record will be placed on a separate line in the file.

The meaning of the record items is as follows:

- **ID_cislo_mer_osoby:** (space) ten-digit integer divisible by 11
- **Meno_osoby:** (space) string (max. 30 characters)
- **Mer_modul:** (space) capital letter from the interval <A, Z> followed by a number from the interval <00, 99> (always 2 digits!)
- **Typ_mer_veliciny:** (space) 2 characters from the set {R1, U1, A1, R2, U2, A2, R4, U4, A4}
- **Hodnota:** real number
- **Cas_merania:** (space) 4 characters (1st-2nd character represents hours 0-23h, 3rd-4th character represents minutes 00-59)
- **Datum:** (space) eight-digit integer in the form rrrrmmdd (20201030 for October 30, 2020)
- (empty line)

The program executes commands read from the standard input. Each command consists of a lowercase letter followed by a newline.

## Commands

- `n`: This command reads records from the measuring module stored in the file `dataloger_V2.txt` into a linked list of structures. If the list existed before, it needs to free up memory. If the file cannot be opened, the program outputs "Zaznamy neboli nacitane!" terminated with a newline. If the records were successfully loaded into the linked list, the program outputs "Nacitalo sa <n> zaznamov" terminated with a newline, where <n> is the number of loaded records.

- `v`: This command prints the entire linked list of records. The output format is as follows: Before each record, there is a serial number of the record (starting from 1, followed by a colon). Then follows the printout of ID_cislo_mer_osoby, where the item name (without diacritics) is followed by a colon, a space, the value of the item, and a newline. Similarly, all other items are printed. If the list does not contain any records, this option generates no output.

- `s`: This command reads the ID_cislo_mer_osoby and then the record/s for the given ID_cislo_mer_osoby are deleted from the dynamic arrays. After deletion, the program outputs a message stating how many records were deleted (e.g., "Vymazalo sa: 5 zaznamov!"). If the arrays are not created, the program outputs "Polia nie su vytvorene." terminated with a newline.

- `k`: After activation, the program correctly deallocates dynamic arrays if they were previously created. If the input file is open, it will be closed, and the program will terminate. This command generates no output.

- `p`: This command adds a record to the linked list of records. The command is followed by a positive integer c1 > 0, indicating the position (counted from 1) where the record should be added (the record at position c1 moves to position c1+1). Then follow the next 6 lines, each ending with a newline, containing the items of the record in the order they appear in the file `dataloger_V2.txt`. If position c1 does not exist in the list, the record is added to the end of the list. This option generates no output.

- `h`: Allows the user to search and print all record items based on the Mer_modul name. The line with the `h` command is followed by a line with a letter and two digits. After entering this command, the program prints all records for the given measurement module. The output format is the same as the `v` command, with record numbers ranging from 1 to n, where n is the number of printed records. Records are printed in the order they appear in the linked list. If no such record exists, the program prints the message "Pre meraci modul niesu zaznamy." (For the measurement module, there are no records.) where is the code of the presentation room. The message is ended with a newline character.

- `r`: This command swaps two records in the linked list. The command is followed by two positive integers c1 > 0, c2 > 0 indicating the positions (counted from 1). The record at position c1 moves to position c2, and the record at position c2 moves to position c1. If position c1 or c2 does not exist in the list, the record swapping does not occur. This option generates no output.

- `k`: This command terminates the program. If the linked list existed, it correctly frees the allocated memory. This option generates no output. The program terminates.
