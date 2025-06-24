#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>

#include "headers/json.hpp"

using json = nlohmann::json;

int g_argc;
const char** g_argv;

void ensure_json_exists() {
    std::ifstream file_check("taskCLI.json");
    if (!file_check) {
        std::ofstream create_file("taskCLI.json");
        create_file << "[]";
        create_file.close();
        std::cout << "Created new taskCLI.json\n";
    }
}

void view_done() {
    std::ifstream in("taskCLI.json");
    json tasks;
    in >> tasks;
    in.close();

    std::cout << "----- DONE TASKS -----\n";

    for (const auto& task : tasks) {
        if (task["status"] == 1) {
            std::cout << "Title: " << task["title"] << "\n";
            std::cout << "Status: Done\n";
            std::cout << "ID: " << task["id"] << "\n";
            std::cout << "---------------------------\n";
        }
    }
}

void view_inprog() {
    std::ifstream in("taskCLI.json");
    json tasks;
    in >> tasks;
    in.close();

    std::cout << "----- IN PROGRESS TASKS -----\n";

    for (const auto& task : tasks) {
        if (task["status"] == 2) {
            std::cout << "Title: " << task["title"] << "\n";
            std::cout << "Status: In Progress\n";
            std::cout << "ID: " << task["id"] << "\n";
            std::cout << "---------------------------\n";
        }
    }
}

void view_noprog() {
    std::ifstream in("taskCLI.json");
    json tasks;
    in >> tasks;
    in.close();

    std::cout << "----- NOT DONE TASKS -----\n";

    for (const auto& task : tasks) {
        if (task["status"] == 3) {
            std::cout << "Title: " << task["title"] << "\n";
            std::cout << "Status: Not Done\n";
            std::cout << "ID: " << task["id"] << "\n";
            std::cout << "---------------------------\n";
        }
    }
}

void view() {
    if (g_argc > 2) {
        if (strcmp(g_argv[2], "done") == 0) {
            view_done();
        } else if (strcmp(g_argv[2], "inprog") == 0) {
            view_inprog();
        } else if (strcmp(g_argv[2], "noprog") == 0) {
            view_noprog();
        } else {
            std::cout << "Invalid view filter. Use: done, inprog, or noprog.\n";
        }
    } else {
        std::ifstream in("taskCLI.json");
        json tasks;
        in >> tasks;
        in.close();

        if (!tasks.is_array()) {
            std::cout << "Invalid JSON format\n";
            return;
        }

        if (tasks.empty()) {
            std::cout << "No tasks found.\n";
            return;
        }

        std::cout << "----- TASK LIST -----\n";

        for (const auto& task : tasks) {
            std::string status_text = "Unknown";
            if (task["status"] == 1) status_text = "Done";
            else if (task["status"] == 2) status_text = "In Progress";
            else if (task["status"] == 3) status_text = "Not Done";

            std::cout << "Title: " << task["title"] << "\n";
            std::cout << "Status: " << status_text << "\n";
            std::cout << "ID: " << task["id"] << "\n";
            std::cout << "---------------------------\n";
        }
    }
}

void add() {
    std::ifstream in("taskCLI.json");
    json tasks;
    in >> tasks;
    in.close();

    std::string title;
    int status;

    std::cout << "Enter name of task: ";
    std::getline(std::cin >> std::ws, title); // Handles whitespace correctly

    int max_id = 0;
    for (const auto& task : tasks) {
        if (task.contains("id") && task["id"].is_number_integer()) {
            max_id = std::max(max_id, (int)task["id"]);
        }
    }

    int new_id = max_id + 1;

    std::cout << "Done, In Progress, or Not Started?(1, 2, 3): ";
    std::cin >> status;

    json new_task = {
        {"id", new_id},
        {"title", title},
        {"status", status}
    };

    tasks.push_back(new_task);

    std::ofstream out("taskCLI.json");
    out << tasks.dump(4);
    out.close();

    std::cout << "Task added with ID " << new_id << "\n";
}

void deleteFunc(int del_id) {
    std::ifstream in("taskCLI.json");
    json tasks;
    in >> tasks;
    in.close();

    if (!tasks.is_array()) {
        std::cout << "Invalid JSON format\n";
        return;
    }

    bool deleted = false;
    json new_tasks = json::array();

    for (const auto& task : tasks) {
        if (task["id"] == del_id) {
            deleted = true;
            continue;
        }

        json new_task = task;

        if (task["id"] > del_id) {
            new_task["id"] = task["id"].get<int>() - 1;
        }

        new_tasks.push_back(new_task);
    }

    if (!deleted) {
        std::cout << "Task with ID " << del_id << " not found.\n";
        return;
    }

    std::ofstream out("taskCLI.json");
    out << new_tasks.dump(4);
    out.close();

    std::cout << "Task ID " << del_id << " deleted and remaining IDs updated.\n";
}

void deleteM() {
    if(g_argc > 2) {
        int id = std::atoi(g_argv[2]);
        deleteFunc(id);
        return;
    }

    view();

    std::cout << "Enter the ID of the task you want to delete: ";
    int del_id;
    std::cin >> del_id;
    
    deleteFunc(del_id);
}

void main_noargs() {
    std::cout << "Welcome to the CLI Task Manager!\n";
    std::cout << "Enter one of the following commands: \n\n";
    std::cout << "1) View Tasks (All, Done, In Progress, Not Done).\n";
    std::cout << "2) Add a task.\n";
    std::cout << "3) Delete a task\n";
    std::cout << "Enter your command: ";

    int c;
    std::cin >> c;

    if (c == 1) {
        view();
    } else if (c == 2) {
        add();
    } else if (c == 3) {
        deleteM();
    } else {
        std::cout << "Invalid Menu Number: " << c << "\n";
    }
}

int main(int argc, char const* argv[]) {
    ensure_json_exists();
    g_argc = argc;
    g_argv = argv;

    if (argc > 1) {
        if (strcmp(argv[1], "view") == 0 || strcmp(argv[1], "list") == 0) {
            view();
        } else if (strcmp(argv[1], "add") == 0) {
            add();
        } else if (strcmp(argv[1], "delete") == 0) {
            deleteM();
        } else {
            std::cout << "Invalid Argument.\n";
        }
        return 0;
    }

    while (true) {
        main_noargs();

        std::cout << "Do you wish to repeat the program? (Y/N): ";
        char o = 'N';
        std::cin >> o;
        if (!(o == 'y' || o == 'Y')) {
            break;
        }
    }

    return 0;
}
