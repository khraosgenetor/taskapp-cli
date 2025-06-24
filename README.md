# [TaskCLI](https://github.com/khraosgenetor/taskapp-cli-json)

A simple command-line task manager written in C++ using [nlohmann/json](https://github.com/nlohmann/json) for persistent storage in `taskCLI.json`.

## 📦 Features

- View all tasks or filter by status:
  - `Done`
  - `In Progress`
  - `Not Done`
- Add new tasks with a status.
- Delete tasks by ID (auto re-indexes IDs).
- JSON-based persistent storage.
- Supports both interactive mode and command-line arguments.

## 🛠️ Usage

### Build

```bash
g++ main.cpp -o main.exe
````

### Run (Interactive Mode)

```bash
./main.exe
```

### Run (Command-Line Mode)

```bash
# View all tasks
./main.exe view

# View only done tasks
./main.exe view done

# Add a new task
./main.exe add

# Delete a task with ID 3
./main.exe delete 3
```

## Showcase:

https://github.com/user-attachments/assets/a8401d42-a26e-460e-a87a-d408852a9ad9

## 📂 Task Format

Each task is stored as an object in `taskCLI.json`:

```json
{
  "id": 1,
  "title": "Finish homework",
  "status": 2
}
```

Where:

* `1` = Done
* `2` = In Progress
* `3` = Not Done

## 📚 Dependencies

* [nlohmann/json](https://github.com/nlohmann/json)

Make sure to include the `json.hpp` file in your `headers/` directory.

## 👤 Author

**Khraos Genetor**
Email: [khraos@khraos.in](mailto:khraos@khraos.in)

---

Feel free to clone, extend, and modify the project.
