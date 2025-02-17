#include <iostream>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <math.h>
using namespace std;

#define MAX_PROCESSES 100

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completed_time;
    int turnaround_time;
    int waiting_time;
};

void SRTF(int &, process [], int &, int[], bool &);
void import_processes(int &, process[], int &, int[], bool &);
void export_processes(int, process[]);
void print_table(int, process[]);
void print_chart(int, int[]);
int Menu(int, int, process[], int[], bool);
void loading();

int main() {

    int n;
    process *processes;
    int *gantt_chart;
    int current_time;
    bool flag = false;
    while (1) {
        switch (Menu(n, current_time, processes, gantt_chart, flag)) {
            case 1:
                loading();
                if (flag) {
                    delete processes;
                    delete gantt_chart;
                }
                processes = new process [MAX_PROCESSES];
                gantt_chart = new int [1000];
                current_time = 0;
                SRTF(n, processes, current_time, gantt_chart, flag);
                loading();
                break;

            case 2:
                loading();
                if (flag) {
                    delete processes;
                    delete gantt_chart;
                }
                processes = new process [MAX_PROCESSES];
                gantt_chart = new int [1000];
                current_time = 0;
                import_processes(n, processes, current_time, gantt_chart, flag);
                loading();
                break;

            case 3:
                loading();
                if (flag)
                    export_processes(n, processes);
                else {
                    system("cls");
                    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
                    cout << "\n\n\n\n\t\t\t\tNo processes have been created yet!";
                    Sleep(3000);
                }
                loading();
                break;

            case 4:
                SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
                system("cls");
                cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t*** Good Bye ***";
                Sleep(3000);
                exit(1);

            default:
                system("cls");
                cout << "\n\n\n\n\t\t\t\tPlease enter correct option!";
                Sleep(3000);
        }
    }
    return 0;
}

void SRTF(int &n, process processes[], int &current_time, int gantt_chart[], bool &printFlag) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);

    bool completed[MAX_PROCESSES] = {false};
    int shortest_index = 0;

    processes[0].remaining_time = processes[0].burst_time = INFINITY;

    cout << "\n\n\n\n\t\t\t\tEnter the number of processes: ";
    cin >> n;
    if (n < 1) {
        system("cls");
        cout << "\n\n\n\n\t\t\t\tEnter the correct number of processes!";
        Sleep(3000);
        printFlag = false;
        return;
    }
    printFlag = true;

    for (int i = 1; i <= n; i++) {
        cout << "\n\n\t\t\t\tEnter arrival time and burst time for process " << i << " : ";
        cin >> processes[i].arrival_time >> processes[i].burst_time;
        processes[i].pid = i;
        processes[i].remaining_time = processes[i].burst_time;
        processes[i].completed_time = processes[i].turnaround_time = processes[i].waiting_time = 0;
    }

    cout << endl;

    while (true) {
        bool completed_all = true;
        bool flag = true;
        for (int i = 1; i <= n; i++) {
            if (!completed[i]) {
                completed_all = false;
                if (processes[i].arrival_time <= current_time &&
                    processes[i].remaining_time < processes[shortest_index].remaining_time) {
                    shortest_index = i;
                }
            }
        }
        if (completed_all) {
            break;
        }
        for (int i = 1; i <= n; i++) {
            if (processes[i].arrival_time <= current_time && shortest_index != i && !completed[i]) {
                processes[i].waiting_time += 1;
            }
        }
        if (processes[shortest_index].arrival_time > current_time) {
            flag = false;
        }
        gantt_chart[current_time] = shortest_index;
        current_time++;
        if (flag) {
            processes[shortest_index].remaining_time--;
            if (processes[shortest_index].remaining_time == 0) {
                completed[shortest_index] = true;
                processes[shortest_index].completed_time = current_time;
                shortest_index = 0;
            }
        }
    }
}
void import_processes(int &n, process processes[], int &current_time, int gantt_chart[], bool &printFlag) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    system("cls");
    string line, word, fileName;
    cout << "\n\n\n\n\t\t\t\tEnter the file name of processes: ";
    cin >> fileName;
    fileName += ".csv";
    fstream file (fileName);

    if (file.is_open()) {
        int row = 0;
        while (getline(file, line)) {
            if (row == 0) {
                row++;
                continue;
            }
            stringstream str(line);
            int col = 0;
            while (getline(str, word, ',')) {
                if (col == 0)
                    processes[row].pid = stoi(word);
                else if (col == 1)
                    processes[row].arrival_time = stoi(word);
                else if (col == 2)
                    processes[row].remaining_time = processes[row].burst_time = stoi(word);
                col++;
            }
            processes[row].completed_time = processes[row].turnaround_time = processes[row].waiting_time = 0;
            row++;
        }
        n = row-1;
        printFlag = true;
        system("cls");
        cout << "\n\n\n\n\t\t\t\tProcesses imported successfully!";
        Sleep(3000);
        file.close();
    } else {
        system("cls");
        cout << "\n\n\n\n\t\t\t\tNo such file exists!";
        Sleep(3000);
        printFlag = false;
        return;
    }

    bool completed[MAX_PROCESSES] = {false};
    int shortest_index = 0;

    processes[0].remaining_time = processes[0].burst_time = INFINITY;

    while (true) {
        bool completed_all = true;
        bool flag = true;
        for (int i = 1; i <= n; i++) {
            if (!completed[i]) {
                completed_all = false;
                if (processes[i].arrival_time <= current_time &&
                    processes[i].remaining_time < processes[shortest_index].remaining_time) {
                    shortest_index = i;
                }
            }
        }
        if (completed_all) {
            break;
        }
        for (int i = 1; i <= n; i++) {
            if (processes[i].arrival_time <= current_time && shortest_index != i && !completed[i]) {
                processes[i].waiting_time += 1;
            }
        }
        if (processes[shortest_index].arrival_time > current_time) {
            flag = false;
        }
        gantt_chart[current_time] = shortest_index;
        current_time++;
        if (flag) {
            processes[shortest_index].remaining_time--;
            if (processes[shortest_index].remaining_time == 0) {
                completed[shortest_index] = true;
                processes[shortest_index].completed_time = current_time;
                shortest_index = 0;
            }
        }
    }
}
void export_processes(int n, process processes[]) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    system("cls");
    string line, word, fileName;
    cout << "\n\n\n\n\t\t\t\tEnter the file name of processes: ";
    cin >> fileName;
    fileName += ".csv";
    ofstream file (fileName);

    if (file.is_open()) {
        int total_waiting_time = 0;
        int total_turnaround_time = 0;
        for (int i = 0; i <= n; i++) {
            if (i == 0)
                file << "Process," << "Arrival Time," << "Burst Time," << "Waiting Time," << "TurnAround Time" << endl;
            else {
                file << processes[i].pid << "," << processes[i].arrival_time << "," << processes[i].burst_time << "," << processes[i].waiting_time << "," << processes[i].turnaround_time << endl;
                total_waiting_time += processes[i].waiting_time;
                total_turnaround_time += processes[i].turnaround_time;
            }
        }
        float avg_waiting_time = (float) total_waiting_time / n;
        float avg_turnaround_time = (float) total_turnaround_time / n;
        file << "The Average Waiting Time: " << avg_waiting_time << endl;
        file << "The Average Turnaround Time: " << avg_turnaround_time << endl;
        file.close();
        system("cls");
        cout << "\n\n\n\n\t\t\t\tProcesses exported successfully!";
        Sleep(3000);
    } else {
        system("cls");
        cout << "\n\n\n\n\t\t\t\tUnable to create file!";
        Sleep(3000);
        return;
    }
}
void print_table(int n, process processes[]) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
    cout << "\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    cout << "\t\t\t\t[#] SRTF Processes Table [#]\n\n";
    int rows = n+1;
    int cols = 5;
    int width = 20;
    string data[rows][cols];
    data[0][0] = "Process";
    data[0][1] = "Arrival Time";
    data[0][2] = "Burst Time";
    data[0][3] = "Waiting Time";
    data[0][4] = "TurnAround Time";
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    for (int i = 1; i < rows; i++) {
        processes[i].turnaround_time = processes[i].completed_time - processes[i].arrival_time;
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
        for (int j = 0; j < cols; j++) {
            if (j == 0)
                data[i][j] = to_string(processes[i].pid);
            else if (j == 1)
                data[i][j] = to_string(processes[i].arrival_time);
            else if (j == 2)
                data[i][j] = to_string(processes[i].burst_time);
            else if (j == 3)
                data[i][j] = to_string(processes[i].waiting_time);
            else if (j == 4)
                data[i][j] = to_string(processes[i].turnaround_time);
        }
    }

    cout << "\t\t\t\t " << setfill((char)205) << setw(width*cols+cols-1) << (char)205 << endl;
    for (int i = 0; i < rows; i++) {
        cout << "\t\t\t\t";
        cout << (char)186;
        for (int j = 0; j < cols; j++) {
            int padding = (width - data[i][j].length()) / 2;
            cout << right << setfill(' ') << setw(padding) << ' ';
            cout << left << setfill(' ') << setw(width - padding) << data[i][j];
            cout << (char)186;
        }
        cout << endl;
        if (i != rows - 1)
            cout << "\t\t\t\t " << setfill((char)205) << setw(width*cols+cols-1) << (char)205 << endl;
    }
    cout << "\t\t\t\t " << setfill((char)205) << setw(width*cols+cols-1) << (char)205 << endl;

    float avg_waiting_time = (float) total_waiting_time / n;
    float avg_turnaround_time = (float) total_turnaround_time / n;

    cout << "\n\t\t\t\tThe Average Waiting Time: " << avg_waiting_time << endl;
    cout << "\n\t\t\t\tThe Average Turnaround Time: " << avg_turnaround_time << endl;
    cout << "\n\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
}
void print_chart(int current_time, int gantt_chart[]) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
    cout << "\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    cout << "\t\t\t\t[*] SRTF Gantt Chart [*]\n";
    bool flag = true;
    int temp;
    int count = 0;
    for (int i = 0; i < current_time; i++) {
        if (gantt_chart[i] != temp) {
            flag = true;
        }
        if (flag) {
            temp = gantt_chart[i];
            count++;
            flag = false;
        }
    }

    cout << "\n\t\t\t\t" << setfill((char)205) << setw(count*9+1) << (char)205 << "\n\t\t\t\t";
    flag = true;
    temp = -1;
    for (int i = 0; i < current_time; i++) {
        if (gantt_chart[i] != temp) {
            flag = true;
            cout << (char)186;
        }
        if (flag) {
            if (gantt_chart[i] == 0)
                cout << "  idle  ";
            else if (gantt_chart[i] < 10)
                cout << "   P" << gantt_chart[i] << "   ";
            else
                cout << "  P" << gantt_chart[i] << "   ";
            temp = gantt_chart[i];
            flag = false;
        }
    }
    cout << (char)186;
    cout << "\n\t\t\t\t" << setfill((char)205) << setw(count*9+1) << (char)205 << "\n\t\t\t\t";

    flag = true;
    for (int i = 0; i < current_time; i++) {
        if (gantt_chart[i] != temp) {
            flag = true;
        }
        if (flag) {
            cout << setfill((char)32) << setw(9) << left << i;
            temp = gantt_chart[i];
            flag = false;
        }
    }
    cout << current_time << endl;
    cout << "\n\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
}
int Menu(int n, int current_time, process processes[], int gantt_chart[], bool flag) {
    system("cls");

    if (flag) {
        cout << "\n\n\n\n";
        print_table(n, processes);
        print_chart(current_time, gantt_chart);
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
        cout << "\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    }

    int option;
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
    if (!flag)
        cout << "\n\n\n\n";
    cout << "\t\t\t\t[+] Menu [+]" << endl << endl;
    cout << "\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    cout << "\t\t\t\t[1] Shortest Remaining Time First" << endl << endl;
    cout << "\t\t\t\t[2] Import processes from CSV file" << endl << endl;
    cout << "\t\t\t\t[3] Export processes to CSV file" << endl << endl;
    cout << "\t\t\t\t[4] Exit" << endl << endl;
    cout << "\t\t\t\t--------------------------------------------------------------------------------------------------------------------------------------------------------" << endl << endl;
    cout << "\t\t\t\tPlease enter option : ";
    cin >> option;
    return option;
}
void loading() {
    system("cls");
    system("COLOR 0e");
    printf("\e[?25l");

    SetConsoleCP(437);
    SetConsoleOutputCP(437);
    int bar1 = 177, bar2 = 219;

    cout << "\n\n\n\n\t\t\t\tLoading...";
    cout << "\n\n\t\t\t\t";

    for(int i = 0; i < 25; i++)
        cout << (char)bar1;

    cout <<"\r";
    cout <<"\t\t\t\t";
    for(int i = 0; i < 25; i++) {
        cout << (char)bar2;
        Sleep(15);
    }
    Sleep(40);
    system("cls");
}
