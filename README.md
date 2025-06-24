# TaskCLI

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
g++ main.cpp -o taskcli
````

### Run (Interactive Mode)

```bash
./taskcli
```

### Run (Command-Line Mode)

```bash
# View all tasks
./taskcli view

# View only done tasks
./taskcli view done

# Add a new task
./taskcli add

# Delete a task with ID 3
./taskcli delete 3
```

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
